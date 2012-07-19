#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "state.h"
#include "button.h"

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

private:
};

#endif