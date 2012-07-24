# Working on a C++ tile based 'engine' using SDL

### Todo:
- StateManager issues: The running state is not exiting when it makes the call to change the active state, thus resulting in a lot of issues, as the gamestate gets run inside menustate and then they both exit at the same time, and it's not good
	- Need the running state to break out before starting the next state, perhaps I can return something on exit describing the action to be taken
- Finish setting up the state machine, I hacked together a rudimentary system however I need to finish setting up the full a nice version with ability to transfer cleanly and many times between states
	- Related to clean transitions between states: states must be able to serialize and load themselves from a configuration file that will give them information about the state's configuration
- Simple map editor