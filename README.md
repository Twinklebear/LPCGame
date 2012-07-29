# Working on a C++ tile based 'engine' using SDL

### Todo:
- Add Rect +/- vector operators
- Implement moving camera to follow player
	- I'm not happy with applying camera effects by only changing the draw location, the real box of the object should be moved, b/c buttons for example won't register clicks on the image b/c the collision box isn't actually there, but rather at its un-offset position
	- Also made the game center itself with a centering offset, also calculated by the camera.
	- Believe I have the camera offsets and centering ok, but now i need to test with proper scene boxes and more cases/maps
- Simple map editor

### Done:
- State's Run() function now returns a string corresponding to the state that should be loaded next, 'quit' specifies that the program should exit completely. ObjectButtons can register a callback SetExit(std::string) for the class's function, which when called will exit Run() and return the desired string as the return code.
- GameObjects now have Save and Load functions, along with States. Save returns a Json::Value containing the information about the object, whereas Load will take a Json::Value and setup the appropriate configuration. I have yet to write load
- States are now loaded from file when needed, saved when they exit, deleted from the statemanager and a new state is loaded, only one state is tracked by the StateManager at a time instead of the vector like before, because they're loaded from file only when they're needed.
- State Manager is looking good, state system seems to be running well
- Image is able to generate uniform clips and can also Load/Save clips to file
- Tile's box, type and solid are now saved and loaded