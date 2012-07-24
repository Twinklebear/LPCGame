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
	void Run();
	//Free the memory used by the state
	void Free();
	/*
	*  Save the state data so that it can be loaded later
	*/
	void Save();

private:
	bool mExit;
};

#endif