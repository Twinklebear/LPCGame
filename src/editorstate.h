#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include <memory>
#include <string>
#include "../externals/json/json.h"
#include "state.h"
#include "timer.h"
#include "mapeditor.h"
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
	///Initialize state memory
	void Init();
	///Free state memory
	void Free();

private:
	std::shared_ptr<MapEditor> mMapEditor;
	std::shared_ptr<UiObjectManager> mUiManager;
};

#endif