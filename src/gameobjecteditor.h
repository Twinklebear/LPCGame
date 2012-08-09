#ifndef GAMEOBJECTEDITOR_H
#define GAMEOBJECTEDITOR_H

#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "camera.h"
#include "gameobjectmanager.h"
#include "mapeditor.h"
#include "tilebar.h"

///Allows for editing of the GameObjects on a map
/**
*  Lets you add/remove GameObjects to a map along with
*  allowing for sending mouse input to the MapEditor
*/
class GameObjectEditor : public GameObjectManager{
public:
	GameObjectEditor();
	~GameObjectEditor();
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
	*  Register the TileBar with the GameObjectEditor so 
	*  that we can get selected object from the bar for
	*  insertion into the map
	*/
	void Register(TileBar* tileBar);
	/**
	*  Handle mouse clicks, run through the active game objects
	*  find what was clicked, and call it
	*  @param mouseEvent The mouse event that we're processing
	*/
	void HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent);

private:
	std::weak_ptr<MapEditor> mMapEditor;
	//We use a non-managed pointer because we don't want to have to make
	//a shared tilebar pointer b/c it's managed as a GameObject shared ptr by 
	//the ui object manager
	TileBar* mTileBar;
};

#endif