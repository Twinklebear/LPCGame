#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "json/json.h"
#include "state.h"
#include "button.h"
#include "objectbutton.h"

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
	*  @return Json::Value containing the state's save data
	*/
	Json::Value Save();
	/**
	*  Load the state data from a json value
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