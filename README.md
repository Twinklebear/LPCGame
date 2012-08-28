# Working on a C++ tile based "engine" using SDL 2.0

## Documentation:
- [Code](http://twinklebear.github.com/LPCGame/)
- [JsonCPP](http://jsoncpp.sourceforge.net/)
- [SDL 2.0](http://wiki.libsdl.org/moin.cgi/FrontPage)

## Todo:
- Implement Lua for scripting objects behavior
	- Each class will have a RegisterLua or something named function, and when that is called and passed a lua_State* it will expose the class to the Lua script.
	- Need to determine what is necessary to be exposed and what should be handled internally and how the API should work and such
	- How should the State class be handled?
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

## "Done":
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

## Some stress test results [30.7.2012]
Not very impressive, 12k tiles at about 60% CPU usage on my laptop with a Intel Core 2 Duo @ 2.4GHz and ATI Mobility Radeon HD 3870 X2
