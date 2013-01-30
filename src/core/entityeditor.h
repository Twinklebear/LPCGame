#ifndef ENTITYEDITOR_H
#define ENTITYEDITOR_H

#include <vector>
#include <memory>
#include "external/json/json.h"
#include "camera.h"
#include "entity.h"
#include "entitymanager.h"
#include "mapeditor.h"
#include "tilebar.h"

///Allows for editing of the Entities on a map
/**
*  Lets you add/remove Entites to a map along with
*  allowing for sending mouse input to the MapEditor
*  TODO: Editor system should be re-thought
*/
class EntityEditor : public EntityManager {
public:
	EntityEditor();
	~EntityEditor();
	///Update the objects
	void Update();
	/**
	*  Register the MapEditor with the EntityEditor
	*  so that it can recieve mouse input
	*  TODO: How will I get the selected tile from the UI?
	*  @param mapEditor The MapEditor to register
	*/
	void Register(std::shared_ptr<MapEditor> mapEditor);
	/**
	*  Register the TileBar with the EntityEditor so 
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
	//a shared tilebar pointer b/c it's managed as a GameObject shared ptr with
	//the ui object manager
	TileBar* mTileBar;
};

#endif