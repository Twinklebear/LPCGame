# Working on a C++ tile based 'engine' using SDL

### Todo:
- Implement moving camera to follow player
	- Need to enable objects to take the camera parameter to their draw functions to check if they're in camera and apply the appropriate offset
	- Need a way to get the scene's width and height for the camera, this would be the map dimensions in game states and the menu dimensions in menu states. Then with this i can center the camera in the screen if choosing a camera w/h smaller than the window.
- Simple map editor

### Done:
- State's Run() function now returns a string corresponding to the state that should be loaded next, 'quit' specifies that the program should exit completely. ObjectButtons can register a callback SetExit(std::string) for the class's function, which when called will exit Run() and return the desired string as the return code.
- GameObjects now have Save and Load functions, along with States. Save returns a Json::Value containing the information about the object, whereas Load will take a Json::Value and setup the appropriate configuration. I have yet to write load
- States are now loaded from file when needed, saved when they exit, deleted from the statemanager and a new state is loaded, only one state is tracked by the StateManager at a time instead of the vector like before, because they're loaded from file only when they're needed.
- State Manager is looking good, state system seems to be running well
- Image is able to generate uniform clips and can also Load/Save clips to file
- Tile's box, type and solid are now saved and loaded