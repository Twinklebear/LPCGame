#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../externals/json/json.h"
#include "state.h"
#include "button.h"
#include "objectbutton.h"

///A state for running a menu system
/**
*  For creating and using a simple menu state
*/
class MenuState : public State{
public:
	MenuState();
	~MenuState();
	/**
	*  Run the state
	*  @return The next state to run, returning quit exits program
	*/
	std::string Run();
	/**
	*  Write the state data to a Json Value and return it so that
	*  it can be saved and loaded later
	*  @see State::Save for saving inherited members
	*  @return Json::Value containing the state's save data
	*/
	Json::Value Save();
	/**
	*  Load the state data from a json value
	*  @see State::Load for loading inherited members, besides the 
	*  manager as it must be loaded differently for each state type
	*  @param val The Json::Value containing the data to load
	*/
	void Load(Json::Value val);

protected:
	///Initialize state memory
	void Init();
	///Free state memory
	void Free();

private:
};

#endif