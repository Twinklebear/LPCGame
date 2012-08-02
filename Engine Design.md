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
	- Entities are drawn with an offset into Scene Space
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
- Camera provides the view perspective for each state
	- Is able to be passed a GameObject to focus on, will move itself to keep the object centered in view
	- Map and GameObjects draw positions are converted into Scene Space to draw them relative to the Camera, in addition non-visible objects are blocked from being drawn, updated or moved.
	- Will also be able to pass movement commands to camera to animate it, perhaps two points and a speed to move to set a pan?
- Image is an easier to use version of the SDL_Texture
	- Can load images, be given clips to draw or read clips from a file to use.
- Text is a method for drawing text using SDL_TTF, but easier
	- Able to load fonts, set message, font size, and color
	- Message is drawn to an SDL_Texture for rendering
- Physics provides an object's physical actions
	- Movement, collision box, friction, etc.
- Map handles running the tile map
	- Is able to load/save tiles to a file along with providing CollisionMaps of solid tiles in some desired area
	- MapEditor inherites from Map, adds functionality for replacing tiles
- Tile is a simple map tile that is used by the map
- Timer is used for timing events, such as the time elapsed between each frame for calculating distance to move
- Input provides a singleton class that can allows for events to be read from anywhere in the program, without having to pass an SDL_Event to the function that wants to read the events
	- Currently mouse events are handled by registering GameObjectManagers with Input which then calls their mouse event functions when one occurs, however I'd like to changes this to operate the same way as reading keyboard input
- Window is a singleton class that wraps the SDL_Window and SDL_Renderer, and enables us to access the window functions from anywhere in the program
	- Provides methods for drawing and loading images

## Reasons for This Design
- GameObject/GameObjectManager
	- The GameObject inheritance coupled with the GameObjectManager makes it very easy for us to manage all of our entites in one place instead of having to deal with them each individually
- States
	- The easiest way to take advantage of multithreading in a game engine is to split the rendering, logic and input polling into seperate threads, which is what will be done here.
	- This also allows us to push up the speed of the logic thread which will allow for better physics checking, in addition the collision math should be upgraded as well heh.
	- Upon exiting a state's Run function it returns a string that is the name of which state should be loaded and run next
- StateManager
	- Only one state should be active at a time, but something needs to tie together loading, running, and saving each state
	- Is a singleton class as well, as we only need one, however I don't think there's anything in the current designe preventing it from being a regular class
- Input
	- Wanted a way to read events anywhere in the program without having to pass the SDL_Event structure all the way through, so instead a singleton input handler class was made
	- Is very handy because we can call Update for the player controlled object the same as all other objects as opposed to having to call it on its own and pass an SDL_Event
- Window
	- Wanted a way to draw and load images anywhere in the program without needing to pass the window to each load or draw call, so a singleton window class was designed

I think this covers the major classes, let me know if there are questions