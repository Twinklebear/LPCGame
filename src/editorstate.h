#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include <memory>
#include <string>
#include "../externals/json/json.h"
#include "state.h"
#include "timer.h"
#include "mapeditor.h"
#include "tilebar.h"
#include "tileset.h"
#include "uiobjectmanager.h"

///Runs the editor state
/**
*  Runs the editing state, which allows for map creation
*  and addition or removal of gameobjects
*/
class EditorState : public State{
public:
	EditorState();
	~EditorState();
	/**
	*  Run the state
	*  @return The next state to run, returning quit exits program
	*/
	std::string Run();
	/**
	*  Write the state data to a Json::Value and return it so it can
	*  be loaded later
	*  @see State::Save for saving of inherited members
	*  @return Json::Value containing the state's data
	*/
	Json::Value Save();
	/**
	*  Load the state data from a Json::Value
	*  @see State::Load for loading of inherited members
	*  @param val The Json::Value containing the data to load 
	*/
	void Load(Json::Value val);

protected:
	/**
	*  The state's rendering thread, takes care of drawing all objects
	*  and providing framerate limiting condition variable notifications
	*  to all other threads
	*  NOT USED AT THE MOMENT
	*/
	//void RenderThread();
	/**
	*  The state's physics thread, takes care of updating and moving
	*  all objects and managing physics between the objects
	*  NOT USED AT THE MOMENT
	*/
	//void PhysicsThread();
	///Initialize state memory
	void Init();
	///Free state memory
	void Free();

private:
	std::shared_ptr<MapEditor> mMapEditor;
	std::shared_ptr<UiObjectManager> mUiManager;
	std::shared_ptr<TileSet> mTileSet;
	//So we can get the tilebar into the gameobjecteditor
	//NEED A BETTER WAY
	TileBar* mTileBar;
};

#endif