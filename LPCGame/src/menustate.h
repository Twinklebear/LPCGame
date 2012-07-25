#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "json/json.h"
#include "state.h"
#include "button.h"
#include "objectbutton.h"

/*
*  For making a simple menu system
*/
class MenuState : public State{
public:
	MenuState();
	~MenuState();
	//Initialize state memory
	void Init();
	//Run the state
	std::string Run();
	//Free the memory used by the state
	void Free();
	/*
	*  Write the state data to a Json Value and return it so that
	*  it can be saved and loaded later
	*/
	Json::Value Save();
	/*
	*  Load the state data from a json value
	*  @param value: the Json::Value containing the data to load
	*/
	void Load(Json::Value value);

private:
};

#endif