#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include "SDL.h"
#include "gameobjectmanager.h"
#include "uiobjectmanager.h"

///Input handler wrapper
/**
*  A simple wrapper around SDL's input handling system
*/
class Input{
public:
	Input();
	~Input();
	///Initialize the input manager
	static void Init();
	///Free the active managers
	static void FreeManagers();
	///Read event input
	static void PollEvent();
	/**
	*  Check if a key is being pressed down
	*  TODO: I need a way to handle special keys, perhaps a version of this
	*  that takes the SDL_SCANCODE?
	*  @param keyCode The char of the key to check, ex: 'a'
	*  @return T if key is down
	*/
	static bool KeyDown(char keyCode);
	/**
	*  Check if a key is being pressed down
	*  @param keyCode The SDL_SCANCODE of the key
	*  @return T if key is down
	*/
	static bool KeyDown(int keyCode);
	/**
	*  Check if the mouse button is clicked
	*  @param button The button to check
	*/
	static bool MouseClick(int button);
	///Check if the mouse moved
	static bool MouseMotionOccured();
	///Get the mouse motion
	static SDL_MouseMotionEvent MouseMotion();
	///Get the current mouse position
	static Vector2f MousePos();
	///Check if the program has been quit out of
	static bool Quit();
	///Clear input data, used when changing states to clear old input
	static void Clear();
	/**
	*  Register the gameobject manager with the input handler so 
	*  that we can pass it mouse events easily
	*  @param manager The gameobject manager to send events too
	*/
	static void RegisterManager(std::shared_ptr<GameObjectManager> manager);
	/**
	*  Register the ui object manager with the input handler
	*  @param manager The ui object manager
	*/
	static void RegisterManager(std::shared_ptr<UiObjectManager> manager);

private:
	static void ClearQuit();
	///Clear the keystates
	static void ClearKeys();
	///Clear the mouse
	static void ClearMouse();

public:
	///Enum for the 3 mouse buttons
	enum MOUSE { LEFT = 1, MIDDLE = 2, RIGHT = 3 };

private:
	static SDL_Event evt;
	static bool mQuit, mMouseMove, mMouseClick;
	static std::weak_ptr<GameObjectManager> mGameObjectManager;
	static std::weak_ptr<UiObjectManager> mUiObjectManager;
	static Uint8 *mKeyStates;
	static SDL_MouseButtonEvent mButtonEvt;
	static SDL_MouseMotionEvent mMotionEvt;
};

#endif