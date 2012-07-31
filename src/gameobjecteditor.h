#ifndef GAMEOBJECTEDITOR_H
#define GAMEOBJECTEDITOR_H

#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "camera.h"
#include "gameobjectmanager.h"
#include "mapeditor.h"

///Allows for editing of the GameObjects on a map
/**
*  Lets you add/remove GameObjects to a map along with
*  allowing for sending mouse input to the MapEditor
*/
class GameObjectEditor : public GameObjectManager{
public:
	GameObjectEditor();
	~GameObjectEditor();
	///Draw the game objects
	void Draw();
	/**
	*  Move the game objects
	*  @param deltaT The time elapsed
	*/
	void Move(float deltaT);
	///Update the objects
	void Update();
	/**
	*  Register the MapEditor with the GameObjectEditor
	*  so that it can recieve mouse input
	*  TODO: How will I get the selected tile from the UI?
	*  @param mapEditor The MapEditor to register
	*/
	void Register(std::shared_ptr<MapEditor> mapEditor);
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

private:
	std::weak_ptr<MapEditor> mMapEditor;
};

#endif