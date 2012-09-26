### TODO Document
## How to use this document:
Entries will be written as follows, and should be updated as work progresses. In addition the description notes should also be updated if previously unmentioned things are found to be needed to meet the goal

## Entry Title [DateAdded]
### Description of the work to be done
- Descriptions of steps that must be done
	- Additional information about each step

### Progress
- WorkerName and [Date]: notes on progress

## Physics [9.22.2012]
### Description
- Examine Box2D as a candidate for providing good physics functionality.
	- Physics class would then provide the object with capabilities for dealing with its Box2D physics component
- Physics::SetMove should instead take a vector move direction, instead of only Up/Down/Left/Right

### Progress
- Twinklebear [9.22.2012]: I'm working on becoming familiar with the library and testing it out in a minal test bench program, to see how it would work with SDL and with providing the physics functionality needed.

## Gamepad Input [9.22.2012]
### Description
- Add SDL's gamepad and force feedback support into Input
	- Should the SDL_HapticEffect be bundled into its own class and then exposed to Lua for creation of effects?

### Progress
- Twinklebear [9.22.2012]: Can read Joystick button, hat and axis input through the Input class
- Twinklebear [9.23.2012]: Can check if the Joystick supports haptic via Input::JoySupportsHaptic()
- Twinklebear [9.25.2012]: Added function to check if a Joystick is available

## Entities/EntityManager [9.22.2012]
### Description
- Wouldn't it make more sense to add UIManager into EntityManager, and simply have UI elements ignore the camera offsets?

### Progress

## Separation of Data [9.22.2012]
### Description
- Images/Animations should be described through their own json file that would be loaded as needed, instead of directly in the state's json file
	- Animations should be seperate from Image description files, see Twinklebear work note [9.22.2012]
- Entities should be in their own json files and loaded through file links in the state's json file
	- Idea for state specific entity data: It could be overriden by specifying the state specific data in the state file, this data will then be used to override the entity data

### Progress
- Twinklebear [9.22.2012]: Image's and AnimatedImage's now have their own associated json file, describing any clips or animation sequences
	- Note: Shouldn't animation be a seperate json file than the image file? So an image.json file would describe the image and its clips, while an animation would specify which image to load and the animation sequences.

## Make Image Clips Array into a Vector [9.22.2012]
### Description
- Image currently uses a dynamic array to store the clip rects, it should be changed to a vector

### Progress
- Twinklebear [9.22.2012]: Tried the naive method of simplying bumping everything over and got rather unclear runtime exceptions, something more is going on that must be looked into.

## AnimatedImage Class Tweaks [9.22.2012]
### Description
- The framerate mentioned for the animations to play at doesn't actually mean framerate, it corresponds to how many program frames correspond to stepping the animation up a frame, this should be changed to be actual framerate

### Progress

## Lua Embedding [9.22.2012]
### Description
- Need a better way for Lua scripts to load the modules they need through something like require or such.
	- Can also load other Lua scripts via calling dofile("filepath relative to exe")
		- How will these scripts have the right modules loaded?
- Implement Lua for scripting objects behavior
	- Need to determine what is necessary to be exposed and what should be handled internally and how the API should work and such
- How should the State class be handled?
	- If I create the ability to call state functions like SetExit from Lua, will ObjectButton no longer be needed? since Button's OnClick script would then simply call the function? I'll try this and then decide what to do with ObjectButton.
		- I think I've got a method for this setup, see the static StateManager function ChangeScene
	- Will need some way to grab the active state, perhaps from StateManager? It's a pure-static class so yes, I think that will work
	- Should states be run via script? Hmm. What to do with states..
		- States will execute their basic C++ functionality, such as making the calls to the manager, and other background stuff, but will also call a function on a state script if one is attached
	- Should tiles become entities that are managed by the Map class? This will allow tiles to have scripts attached. Or should tiles remain simple floor imagery and instead invisible entities should be created to enable area triggers. (kind of leaning to the latter, it'll be easier than reworking the Map & Tile class)
- How to save data from script?
	- Have decided to leave this up to the user, so editor created data will be handled by JsonCPP and script data will be handled by whatever is desired for Lua, and will have no interoperation between the C++ saved data and custom script data.
- Should all modules be loaded for every script? It would prevent potential missing module errors/crashes, would it slow script loading time?

### Progress
- Twinklebear [9.23.2012]: Changed LuaScript::LoadModules to load all modules, we'll see how it effects load times, if it does at all
- Twinklebear [9.23.2012]: You can now load modules via LPCLoadModule, which is passed the name of the module you want to load (with proper capitalization) and should be called at the beginning of the script as you would call require usually
- Twinklebear [9.25.2012]: Removal of the old bad system for using the enum and JSON file for storing a list of required modules is now gone. Modules are loaded with LPCLoadModule. I'm considering migrating over to exposing each class's RegisterLua function however, and then you'd do LPCLoadInput() and it would eliminate the need for the string comparisons
- Twinklebear [9.25.2012]: Module's registration functions are now stored in a std::unordered_map to enable fast lookup. Map is created in LuaScript::CreateMap and given to a static const unordered_map as only one needs to exist, and it should never be able to change what it contains during the program run.
<<<<<<< HEAD
- Twinklebear [9.26.2012]: Changed the unordered_map to a map, since we never perform insertions we don't need to worry about that, just quick access across all elements. So a map is a better choice
=======
<<<<<<< HEAD
- Twinklebear [9.26.2012]: Correction, the name of the module loading function is changed to LPCRequireModule("modulename")
=======
- Twinklebear [9.26.2012]: Changed the unordered_map to a map, since we never perform insertions we don't need to worry about that, just quick access across all elements. So a map is a better choice
>>>>>>> changed the unordered_map toa  map
>>>>>>> a9bf7e469cf0d80cf50dce7c1cb4a4a8f1dffe8c

## Editor [9.22.2012]
### Description
- Tile map editor
- Need to be able to place Entities into the scene as well
	- Related: Need to be able to create new entities from within the editor
- Need to be able to import images to the editor and have them show up in the files list.
	- Need to be able to make folders, and so on, all editor folders will be subfolders of res/
	- How can i drag things into the editor without relying on platform specific API?
		- Should i just instead monitor folders? How does SDL's clipboard support work? If i can get the filepath i can copy the file.

### Progress
- Twinklebear [9.22.2012]: LuaScript class takes care of loading the script and its desired modules. Modules are stored in JSON as an array of ints corresponding to the MODULE enum in the LuaScript class. Then before calling dofile all the desired modules are registered.
	- Should I just load all modules for every script? It would prevent errors. Would it cause slower script loading? (Added to work notes)

## Multithreading [9.22.2012]
### Description
- Naive implementation: Split into three threads: Physics, Rendering and Input (main)

### Progress
- Twinklebear [9.22.2012]: Played around with it some, but some strange issues arise, this needs to be approached with caution. Perhaps when I have a better understanding of designing multithreaded programs.

## Memory Leaks [9.22.2012]
### Description
- Memory leaks when changing states
	- How will the Lua scripts effect memory usage/leaks?

### Progress
- Twinklebear [9.22.2012]: Got some memory stuff freeing correctly I think, but for some reason, if you go Menu -> Play/Editor -> Menu it allocates ~9MB of memory, I'm not sure why. It drops a bit in mem usage from Menu -> Play, but jumps up when returning to Menu. Need to investigate further

## Resizable Window [9.22.2012]
### Description
- Need to make the window resizable and have elements reposition to fit in the new window
	- Resizing window is currently disabled as resizing the window while playing and then exiting to menu would crash the program

### Progress

## General/Random/Unrelated [9.22.2012]
### Description
- Clean up warnings
- More comments/documentation

### Progress
- Twinklebear [9.22.2012]: Sidenote: Subsystem is currently as Not Set so that I can get console output for debugging scripts and such