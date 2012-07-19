#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "state.h"
#include "button.h"
#include "objectbutton.h"

#include "debugger.h"

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
	*  Serialize the state data so that it can be loaded later
	*  @returns: The serialized data in string form
	*/
	std::string Serialize();

	//TESTING
	void CallTest(int a);

private:
	Debugger *dbg;
	bool mExit;
};

#endif