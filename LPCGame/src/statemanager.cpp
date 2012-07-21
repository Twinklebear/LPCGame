#include <vector>
#include <stdexcept>
#include "state.h"
#include "gamestate.h"
#include "menustate.h"
#include "statemanager.h"

std::vector<State*> StateManager::mStates;
int StateManager::mActiveID;

void StateManager::InitIntro(){
	mActiveID = -1;
	SetActiveState(IdFromName("intro"));
}
void StateManager::Register(State *state){
	mStates.push_back(state);
}
int StateManager::IdFromName(std::string name){
	for (int i = 0; i < mStates.size(); ++i){
		if (mStates.at(i)->Name() == name)
			return i;
	}
	return -1;
}
void StateManager::SetActiveState(int id){
	if (mActiveID == id)
		return;
	if (mActiveID != -1)
		mStates.at(mActiveID)->Free();
	//Save and quit the active state, the load and start the new state
	mStates.at(id)->Init();
	mStates.at(id)->Run();
}
void StateManager::LoadState(std::string name){
	
}
void StateManager::SaveState(std::string name){

}
