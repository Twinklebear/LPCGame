#ifndef UIOBJECTMANAGER_H
#define UIOBJECTMANAGER_H

#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "entity.h"
#include "entitymanager.h"

///Handles the active ui objects
/**
*  Handles showing the ui elements in window space and reading input to them
*/
class UiObjectManager : public EntityManager {
public:
	///Constructor not really used, GameObjectManager constructor does what we need
	UiObjectManager();
	///Destructor not really used, GameObjectManager destructor does what we need
	~UiObjectManager();
	///Draw the game objects
	void Draw();
	///Update the objects
	void Update();
	/**
	*  Move the game objects
	*  @param deltaT The time elapsed
	*/
	void Move(float deltaT);
	/**
	*  Handle mouse clicks, run through the active game objects
	*  find what was clicked, and call it
	*  @param mouseEvent The mouse event that we're processing
	*/
	void HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent);
	/**
	*  Handle Mouse motion, check if the mouse entered/exited an object
	*  @param mouseEvent The mouse event that we're processing
	*/
	void HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent);
};

#endif