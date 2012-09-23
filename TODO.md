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

## Joystick Input [9.22.2012]

### - Organize this list haha
- Adding Joystick and Force Feedback support to Input
	- Should keyboard, mouse and joystick each be their own class? A bit torn on this, kind of feel it will just add more junk, since Input can handle the three systems fine. Hmm
- Side Note: I changed System to not set as having the console prompt is invaluable for debugging/testing scripts
- Clean up warnings
- Is there a valid reason for not rolling the UIManager into the EntityManager?
- What if i put the image/animatedimage clips/settings/etc into it's own json file associated with the image file? Then you'd be able to load the entire image data seperately from the state file.
	- Working on putting this in now, this makes more sense anyways, why should an image's data be stored in a state's data file? It's just wierd
	- Move the Image's clips array to a vector
		- Tried this, for some reason it results in a runtime exception that was not very clear, will have to look into this further, something wierd is going on.
- Should be able to create a entity's configuration/properties seperately from importing it into a scene. Then when certain entity's are desired in a scene you can import them from the list.
- Implement Lua for scripting objects behavior
	- LuaScript class takes care of loading the script and its desired modules. Modules are stored in JSON as an array of ints corresponding to the MODULE enum in the LuaScript class. Then before calling dofile all the desired modules are registered.
	- Need to determine what is necessary to be exposed and what should be handled internally and how the API should work and such
	- How should the State class be handled?
		- If I create the ability to call state functions like SetExit from Lua, will ObjectButton no longer be needed? since Button's OnClick script would then simply call the function? I'll try this and then decide what to do with ObjectButton.
			- I think I've got a method for this setup, see the static StateManager function ChangeScene
		- Will need some way to grab the active state, perhaps from StateManager? It's a pure-static class so yes, I think that will work
		- Should states be run via script? Hmm. What to do with states..
		- Should tiles become entities that are managed by the Map class? This will allow tiles to have scripts attached. Or should tiles remain simple floor imagery and instead invisible entities should be created to enable area triggers. (kind of leaning to the latter, it'll be easier than reworking the Map & Tile class)
	- How to save data from script?
		- Have decided to leave this up to the user, so editor created data will be handled by JsonCPP and script data will be handled by whatever is desired for Lua, and will have no interoperation between the C++ saved data and custom script data.
- Simple map editor
	- Expand TileBar to allow for placing of GameObjects
		- I think to do this well, I should integrate scripting for behaviors first, thus all entities can simply be a gameobject with any special behaviors defined in the script.
- Animated Image class able to play desired animations at some speed from clips passed
	- Also framerate doesn't actually mean framerate. It's how many frames to increment the animation frame. Need to change this? Or maybe just clearer name
		- Changed name to framPerAnimFrame to better reflect what it actually means, until i figure out how to setup true framerate playing for animations
- Multithreading
	- Split into three threads: Physics, Rendering and Input (main)
	- Split GameState into 3 threads, seems ok at the moment it's pretty unsafe. Also, pushing the return button to quit sometimes plays the click recieved animation, but doesn't set exit. This is clearly a sign that while the current setup works, it needs to be made into a non-hacked together version
	- Commented out threading code, it will remain as a sample to work from in the future
- Better comments documenting code
- I believe there are some memory leaks to be addressed
	- Memory is not being freed when changing state
	- Got some memory stuff freeing correctly I think, but for some reason, if you go Menu -> Play/Editor -> Menu it allocates ~9MB of memory, I'm not sure why. It drops a bit in mem usage from Menu -> Play, but jumps up when returning to Menu. Need to investigate further

# "Done":
- State's Run() function now returns a string corresponding to the state that should be loaded next, 'quit' specifies that the program should exit completely. ObjectButtons can register a callback SetExit(std::string) for the class's function, which when called will exit Run() and return the desired string as the return code.
- GameObjects now have Save and Load functions, along with States. Save returns a Json::Value containing the information about the object, whereas Load will take a Json::Value and setup the appropriate configuration. I have yet to write load
- States are now loaded from file when needed, saved when they exit, deleted from the statemanager and a new state is loaded, only one state is tracked by the StateManager at a time instead of the vector like before, because they're loaded from file only when they're needed.
- State Manager is looking good, state system seems to be running well
- Image is able to generate uniform clips and can also Load/Save clips to file
- Tile's box, type and solid are now saved and loaded
- Moving camera now implemented
	- Also can set a width and height for the current scene being drawn, in gamestates it's the map w/h in menu statues it can be specified as desired. The scene will be centered on screen
	- New math functions available for converting vectors and rects to and from scene space
	- Would like to test camera on more cases but it seems good.
	- ISSUE: Resizing window doesn't seem to update the drawing of objects, ie. the scene doesn't recenter which is annoying
		- In addition: Resizing window while playing a gamestate and then trying to quit causes a crash
- UI Elements
	- UiObjectManager written, inherits from GameObjectManager and runs the same functions, but without camera checking and positions objects in window space.
	- Note: For menu states you should use the GameObjectManager to register your buttons, as the buttons in this case are the scene and as such should be positioned in scene space, Ui elements are intended to be in game things.
	- This method of ui management may not be the best, will probably revist it later. But this is ok for now
- Input mouse handling has been reworked to function similar to how keyboard is currently handled
	- No longer need to register managers with Input, mouse events are readable from anywhere that includes input.h
	- Can use MouseClick(int button) to check if a mouse button was clicked and GetClick to get the button event
	- Can use MouseMotion() to check if there was mouse motion and GetMotion to get the motion event.
	- Can use MouseDown(int button) to check if a mouse button is being pressed
	- Mouse events are unset each time PollEvent is called to prevent reading the same event multiple times, since we only want to read each click once, and mouse motion will continously register a fresh event each frame