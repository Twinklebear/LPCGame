## Document only exists for reference, for the TODO plans visit the issue tracker

## How to use this document:
Entries will be written as follows, and should be updated as work progresses. In addition the description notes should also be updated if previously unmentioned things are found to be needed to meet the goal. When an item is completed or has had major work done, tag it [In Progress: user] or [Done: user - date]. Note: Done by no means implies the feature is finalized, just that the todo item is in place.

## Entry Title [DateAdded]
### Description of the work to be done
- Descriptions of steps that must be done
	- Additional information about each step

### Progress
- WorkerName and [Date]: notes on progress

## Physics [9.22.2012]
### Description
- Examine Box2D as a candidate for providing good physics functionality [In Progress: Twinklebear]
	- Physics class would then provide the object with capabilities for dealing with its Box2D physics component

- Physics::SetMove should instead take a vector move direction, instead of only Up/Down/Left/Right
	- Due to this not being in, the gamepad controlled entity (npctest) does not update his collision box and as such the collision box remains where he spawns and he won't collide with anything.

### Progress
- Twinklebear [9.22.2012]: I'm working on becoming familiar with the library and testing it out in a minal test bench program, to see how it would work with SDL and with providing the physics functionality needed.

## Gamepad Input [9.22.2012]
### Description
- Add SDL's gamepad and force feedback support into Input [In Progress: Twinklebear]
	- Should the SDL_HapticEffect be bundled into its own class and then exposed to Lua for creation of effects?


- Need to setup a Haptic class to take care of simplifying and exposing the SDL_HapticEffect type

### Progress
- Twinklebear [9.22.2012]: Can read Joystick button, hat and axis input through the Input class

- Twinklebear [9.23.2012]: Can check if the Joystick supports haptic via Input::JoySupportsHaptic()

- Twinklebear [9.25.2012]: Added function to check if a Joystick is available

## Entities/EntityManager [9.22.2012]
### Description
- Wouldn't it make more sense to add UIManager into EntityManager, and simply have UI elements ignore the camera offsets?
	- What if instead i used some kind of OnGui system like Unity to draw things without any camera offsets applied?

### Progress

## Map Objects [9.28.2012]
### Description
- Various objects that can be interacted with by the player in the map, like chests, doors, ladders and so on

- Should be scriptable to define their behaviours

- Could these just be entities?

### Progress

## Separation of Data [9.22.2012]
### Description
- Images/Animations should be described through their own json file that would be loaded as needed, instead of directly in the state's json file [Done: Twinklebear - 9.22.2012]

- Loading/Saving changes system [In Progress: Twinklebear]
	- Clean up old loading system
	- Put in place system for saving entities/images/etc. to json files via Blah::Save(file)

- Need to be able to save/modify the image data files in the editor

- Entities should be in their own json files and loaded through file links in the state's json file [In Progress: Twinklebear]
	- Entity json files [Done: Twinklebear - 9.27.2012]

	- Idea for state specific entity data: It could be overriden by specifying the state specific data in the state file, this data will then be used to override the entity data


- With all these extra file readings I think the need arises for a generic file reader/writer to write and read JSON from desired files, eliminating the need for Image, AnimatedImage and Entity to each have their own JSON file opening function [Done: Twinklebear - 9.28.2012]

- Maps should be described in their own json file [In Progress: Twinklebear]
	- Load maps from their own json file [Done: Twinklebear - 10.10.2012]
	- Editor must request filename to save as when saving a map of tiles. A scene is not a map, a scene has a map, entites and other junk
	- Map overrides??

- Tilesets should have an associated json file describing additional tile properties, which image to use and which tile goes with which clip

### Progress
- Twinklebear [9.22.2012]: Image's and AnimatedImage's now have their own associated json file, describing any clips or animation sequences
	- Note: Shouldn't animation be a seperate json file than the image file? So an image.json file would describe the image and its clips, while an animation would specify which image to load and the animation sequences.

- Twinklebear [9.27.2012]: Decided against seperating animation sequence information from clip information when loading an AnimatedImage. Thus you can still simply call "file.png" and the config file will be parsed from the image file name, instead of loading a json config file and then that would contain the image file name.

- Twinklebear [9.27.2012]: All Image & AnimatedImage config data (clips & sequences) is now loaded from  json files in the same directory as the image file, with the same name. So for tiles.png the corresponding clips data is in tiles.json. This file is automatically checked for and loaded when creating a new Image or AnimatedImage with Image("file.x") or AnimatedImage("file.x")

- Twinklebear [9.27.2012]: First test of loading an entity config through a json file successful. Will work on migrating everything over, and creating a simple file read class, as mentioned above in the description. Also must implement reading in override data for state specific entity configuration.

- Twinklebear [9.28.2012]: Created a JsonHandler class for simplifying reading/writing Json data from/to files.

- Twinklebear [10.1.2012]: Splitting player into another lua scripted entity, soon to delete classes: Player and NPC. Also messed around with setting overrides, need a way to save the overrides upon exit and an efficient way for parsing them in.

- Twinklebear [10.2.2012]: NPC and Player classes are deleted, updated GameState to only load entity types now

- Twinklebear [10.10.2012]: Maps will now load from their own json file that's specified in the state's json
	- As a side note, will all these extra file I/O present a significant slowdown for loading? Perhaps when "exporting" the game, state's should be merged into one file, pulling the json data from the files linked in them. If we do this the load from Json::Value functions should stick around to be used

- Twinklebear [10.10.2012]: Entities can now load from a filepath and if desired override values can be passed as well to be parsed
	- Should overrides be called something else? override is a keyword, and overrides is a bit awkward

- Twinklebear [10.10.2012]: Working on cleaning up loading, Image, AnimatedImge and LuaScript now just load from filenames and can be saved as filenames. Save() still exists but will be migrated to being used for saving entities to seperate JSON files from the editor so DO NOT USE IT for Image/AnimatedImage. Unless you're adding in saving editor created data, but that's a ways off.

## Make Image Clips Array into a Vector [9.22.2012]
### Description
- Image currently uses a dynamic array to store the clip rects, it should be changed to a vector

- Image clips should also be identified by a name instead of an array index

### Progress
- Twinklebear [9.22.2012]: Tried the naive method of simplying bumping everything over and got rather unclear runtime exceptions, something more is going on that must be looked into.

## Some Code Clean-up [10.6.2012]
### Description
- Image has 3 various "Load" functions, this needs to be cleaned up and made cleaarer, other classes may suffer from this as well due to the change in loading styles (seperate files vs. all in one file)

### Progress

## AnimatedImage Class Tweaks [9.22.2012]
### Description
- The framerate mentioned for the animations to play at doesn't actually mean framerate, it corresponds to how many program frames correspond to stepping the animation up a frame, this should be changed to be actual framerate [Done: Twinklebear - 10.2.2012]

- Should the sequences vector be a map? The key would be the sequence name, and it'd return a vector of sequences perhaps? May improve speed?
	- I don't think this would provide an improvement, a name lookup is only done once when the animations switch however multiple lookups are done each update loop to get information about how to play the animation, and in this case the map would be slower. I think a vector is probably ideal.

### Progress
- Twinklebear [10.1.2012]: Added a call to Update to AnimatedImage::Play, however now need to move over to playing images with an actually framerate to prevent skipping frames if Update called multiple times before Draw

- Twinklebear [10.2.2012]: Removed AnimatedImage::Move also changed the call to Update in AnimatedImage::Play to mFrame = 0 to start the animation, also put in code to make use of a Timer for playing the image at some framerate, however it's commented out for now as I have yet to test it. Will test when I get home. 

- Twinklebear [10.2.2012]: AnimatedImages now use a Timer to measure time and update the animation with the appropriate framerate. It's still necessary to call Update each frame to check the timer, however the AnimatedImage will take care of everything else related to playing the animation itself.

- Twinklebear [10.3.2012]: The AnimatedImage::Update function will now determine how many animation frames have elapsed since the last update, and increment mFrame by that number. Thus animations will play at their regular speed even if the game framerate is below the animation framerate, resulting in skipped animation frames. I think this behavior is preferable to capping the animation framerate to the game framerate as I'd rather drop frames than have laggy/miss-timed animations

## Lua Embedding [9.22.2012]
### Description
- Implement Lua for scripting objects behavior [In Progress: Twinklebear]
	- Need to determine what is necessary to be exposed and what should be handled internally and how the API should work and such

	- Should entities be drawn automatically? Or should it be required to make the call yourself in draw?
		- I think an image file should be described in the entity's json file and used. Rendering should be toggle-able to enable/disable drawing of the image

- Need a better way for Lua scripts to load the modules they need through something like require or such [Done: Twinklebear - 10.9.2012]
	- Need a system to prevent scripts from being able to try and register the same module twice as it causes a crash. This issue is easy to encounter if perhaps you call "dofile" from a script with a module loaded and then the script that's just been loaded via "dofile" also attempts to load the same module, it causes a crash. Need to track which modules are registered by the state and quietly ignore re-registration attempts.

- How should the State class be handled?
	- If I create the ability to call state functions like SetExit from Lua, will ObjectButton no longer be needed? since Button's OnClick script would then simply call the function? I'll try this and then decide what to do with ObjectButton.
		- I think I've got a method for this setup, see the static StateManager function ChangeScene
			- This isn't quite right. The button needs to set exit on the actively running scene so that it can exit cleanly

	- Will need some way to grab the active state, perhaps from StateManager? It's a pure-static class so yes, I think that will work

	- Should states be run via script? Hmm. What to do with states..
		- States will execute their basic C++ functionality, such as making the calls to the manager, and other background stuff, but will also call a function on a state script if one is attached

	- Should tiles become entities that are managed by the Map class? This will allow tiles to have scripts attached. Or should tiles remain simple floor imagery and instead invisible entities should be created to enable area triggers. (kind of leaning to the latter, it'll be easier than reworking the Map & Tile class)

- How to save data from script? [Done: Twinklebear - ?.?.?]
	- Have decided to leave this up to the user, so editor created data will be handled by JsonCPP and script data will be handled by whatever is desired for Lua, and will have no interoperation between the C++ saved data and custom script data.


- How much of the editor entities should be scripted?

### Progress
- Twinklebear [9.23.2012]: Changed LuaScript::LoadModules to load all modules, we'll see how it effects load times, if it does at all

- Twinklebear [9.23.2012]: You can now load modules via LPCLoadModule, which is passed the name of the module you want to load (with proper capitalization) and should be called at the beginning of the script as you would call require usually

- Twinklebear [9.25.2012]: Removal of the old bad system for using the enum and JSON file for storing a list of required modules is now gone. Modules are loaded with LPCLoadModule. I'm considering migrating over to exposing each class's RegisterLua function however, and then you'd do LPCLoadInput() and it would eliminate the need for the string comparisons

- Twinklebear [9.25.2012]: Module's registration functions are now stored in a std::unordered_map to enable fast lookup. Map is created in LuaScript::CreateMap and given to a static const unordered_map as only one needs to exist, and it should never be able to change what it contains during the program run.

- Twinklebear [9.26.2012]: Changed the unordered_map to a map, since we never perform insertions we don't need to worry about that, just quick access across all elements. So a map is a better choice

- Twinklebear [9.26.2012]: Correction, the name of the module loading function is changed to LPCRequireModule("modulename")

- Twinklebear [9.26.2012]: Changed the unordered_map to a map, since we never perform insertions we don't need to worry about that, just quick access across all elements. So a map is a better choice

- Twinklebear [10.6.2012]: Took a look at preventing multiple module inclusion errors.
	- Have written a simple class LuaModule which stores a Lua Module Registration function pointer and a bool value to track if it's been registered. When calling LuaModule::Register it first checks if the module is registered, if it isn't registered it registers the module if it is registered it returns.

	- Each instance of a LuaScript class now has its own map of strings to LuaModules to enable each script to take advantage of the new safe Register function defined in the LuaModule. 

	- In addition to this I've learned about the luabind::globals function to access/add values to the global table of a lua_State. 
		- This is now used to push the entity pointer on to the table instead of through Init(object) which now takes no parameters. Now the entity is accessed through the global "entity". I may re-name to "this" (is that a Lua keyword?)

		- This is also used in the module registration functions as they now require context to perform the registration because the RequireModule is no longer able to be static because it must perform the lookup in the TRegisterLuaMap corresponding to the lua_State, since it needs to check against the appropriate list of registered/unregistered modules. So now modules load with Script:RegisterModule("modulename") as Script is the name of the value pushed onto the globals.

	- I feel like this solution is a bit insane/convoluted as far as preventing module re-registration errors. Would adding a custom function to the package.loaders and then loading via require 'modulename' prevent this?

- Twinklebear [10.8.2012]: Turns out require does do module loaded checking and won't reload modules, so I've been working on getting require going, and it's now functional. Now I can strip out the old wacky system and simply use require to load modules.
	- In addition thinking about adding another package.loader to redirect loads to the res/scripts folder for easier script loading, instead of using dofile("path relative to exe")

	- To move over to require all module's RegisterLua functions had to be converted to lua_cfunctions and so they now return an int.

	- Will work on removing the old system and getting this one properly in place.

- Twinklebear [10.9.2012]: Migration to require for module loading complete, removed old system entirely
	- In addition added another package.loader function to redirect engine script load requests, so you can load a script located in scripts/* via require "scripts/scriptname.lua" and it will setup the relative file paths and call dofile for you.
	
	- The Json::Value save/loaded should just be a string at this point, there's no real reason in having it as a list.

## Change Button/ObjectButton to be managed by a Lua script
### Description
- The Button and ObjectButton should have their behaviours and OnClick function defined within a script, instead of in C++ code, allowing for more flexibility

### Progress

## States - Game vs. Menu
### Description
- With the slow migration of states to being scripted through Lua is there any point in having seperate C++ classes for these states? A menu state can easily be implemented as a game state with buttons in it. I think they should be rolled into the base State class and have behaviors managed through Lua.
	- To do this should probably work on merging UIManager and EntityManager first, Or can I do like Unity with an OnGUI function to request UI elements to draw?

### Progress

## Editor [9.22.2012]
### Description
- Tile map editor
	- Need to be able to place any sort of map down, not be limited to a pre-generated standard size map

- Need to be able to place Entities into the scene as well
	- Related: Need to be able to create new entities from within the editor

- Need to be able to import images to the editor and have them show up in the files list.
	- Need to be able to make folders, and so on, all editor folders will be subfolders of res/

	- How can i drag things into the editor without relying on platform specific API?
		- Should i just instead monitor folders? How does SDL's clipboard support work? If i can get the filepath i can copy the file.

### Progress
- Twinklebear [10.11.2012]: Working on getting some framework down for adding the ability to save Image, AnimatedImage and Entity configurations to their own json files through Save(file). The old system is still in place because buttons have yet to move over (next item i'll do) and then it'll be tweaked over to return the override information for saving to the state json file.
	- Note: None of these save functions are exported to Lua for anything more than testing. Undecided as to whether they should be available to Lua or only used internally.

## Multithreading [9.22.2012]
### Description
- Naive implementation: Split into three threads: Physics, Rendering and Input (main)

### Progress
- Twinklebear [9.22.2012]: Played around with it some, but some strange issues arise, this needs to be approached with caution. Perhaps when I have a better understanding of designing multithreaded programs.

## Resource Manager (?) [10.3.2012]
### Description
- Should some kind of manager class be used to govern the loading/unloading of resources? It would be able to give out Image, AnimatedImage and Text pointers and would monitor for resources no longer in use and clean them up. In addition resources could be marked to not be freed, but would this be a good idea?

- Other classes would then request the instance to be loaded from the manager and use it, and could return it when done.

### Progress

## Migration to OpenGL [9.26.2012]
### Description
- A long term goal, will eventually outgrow SDL when the time comes to being adding support for GLSL shaders, normal/diffuse/etc maps for lighting and so on.
	- Rendering will still remain 2D

- I need to learn OpenGL and become very acquinted with it. This TODO task does not and probably will not be worked on for a long time.

### Progress

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