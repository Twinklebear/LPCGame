#include <vector>
#include <stdexcept>
#include <string>
#include "state.h"
#include "gamestate.h"
#include "menustate.h"
#include "statemanager.h"

std::vector<State*> StateManager::mStates;
int StateManager::mActiveID;

void StateManager::InitIntro(){
	mActiveID = -1;
	SetActiveState("intro");
}
void StateManager::Register(State *state){
	mStates.push_back(state);
}
int StateManager::IdFromName(std::string name){
	for (int i = 0; i < mStates.size(); ++i){
		if (mStates.at(i)->Name() == name)
			return i;
	}
	throw std::runtime_error("Failed to find state" + name);
}
void StateManager::SetActiveState(std::string name){
	int id;
	try {
		id = IdFromName(name);
	}
	catch (...){
		return;
	}
	if (mActiveID == id)
		return;
	//Free previous state if one was running
	if (mActiveID != -1){
		//mStates.at(mActiveID)->Save();
		mStates.at(mActiveID)->Free();
	}
	//Update the new id
	mActiveID = id;
	//Save and quit the active state, the load and start the new state
	mStates.at(mActiveID)->Init();
	mStates.at(mActiveID)->Run();
}
void StateManager::LoadState(std::string name){
	
}
void StateManager::SaveState(std::string name){

}
