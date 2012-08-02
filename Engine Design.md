# Engine Design Overview

## Goals
- Create an easy to use and easy to extend tile based game engine
- Allow for highly customizable objects that can be loaded from a configuration file
- Design an effecient, multithreaded game engine

## Code Overview
- Inheritence based engine
- Base class for entities (player, npcs, etc) is GameObject
	- Provides various functionalities necessary to a simple object along with virtual methods to further customize the object.
	- UI elements also inherite from GameObject
- Entities are managed by a GameObjectManager
	- Registers GameObject pointers and runs their functions, Update, Move, Draw, etc.
- UI elements are run by the UiManager at the moment, which does the same stuff GameObjectManager does, but just draws the Ui Elements last, and with no camera offsets
	- This may (probably will) change
- State system for changing between states, all states derive from a base State class
	- States are able to load and save all the relevant data to file, allowing for easy adjustment of the state's configuration
- States are run and swapped by the StateManager
	- Works similar to GameObjectManager except there's only one active state at a time, StateManager will run the active State and load the next desired state
- States will be multithreaded, and split into 3 threads.
	- Main thread: used for calling Input::PollEvent to get user input
	- Logic thread: used for running the game logic functions, mainly Update and Move
	- Render thread: used for drawing the scene to screen. Render thread is FPS limited and will provide a condition variable signal when it updates to trigger Main and Logic threads to update again, thus enabling FPS limiting of all threads
