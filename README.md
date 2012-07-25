# Working on a C++ tile based 'engine' using SDL

### Todo:
- Finish setting up the state machine, I hacked together a rudimentary system however I need to finish setting up the full a nice version with ability to transfer cleanly and many times between states
	- Write load function
- Implement moving camera to follow player
- Simple map editor

### Done:
- State's Run() function now returns a string corresponding to the state that should be loaded next, 'quit' specifies that the program should exit completely. ObjectButtons can register a callback SetExit(std::string) for the class's function, which when called will exit Run() and return the desired string as the return code.
- GameObjects now have Save and Load functions, along with States. Save returns a Json::Value containing the information about the object, whereas Load will take a Json::Value and setup the appropriate configuration. I have yet to write load