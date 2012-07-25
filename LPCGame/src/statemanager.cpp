#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include "state.h"
#include "gamestate.h"
#include "menustate.h"
#include "statemanager.h"

std::vector<State*> StateManager::mStates;
int StateManager::mActiveID;
const std::string StateManager::mStatesDir = "states/";

void StateManager::InitIntro(){
	mActiveID = -1;
	SetActiveState("mIntro");
}
void StateManager::Register(State *state){
	mStates.push_back(state);
}
int StateManager::IdFromName(std::string name){
	for (int i = 0; i < mStates.size(); ++i){
		if (mStates.at(i)->Name() == name)
			return i;
	}
	//throw std::runtime_error("Failed to find state: " + name);
	return -1;
}
void StateManager::SetActiveState(std::string name){
	if (IdFromName(name) == -1){
		if (!LoadState(name))
			std::cout << "Failed to load state: " << name << std::endl;
	}
	int id = IdFromName(name);
	//try {
		//id = IdFromName(name);
	if (id == -1){
		std::cout << "failed to find state" << std::endl;
		return;
	}

	//}
	//catch (const std::runtime_error &e){
	//	std::cout << e.what() << std::endl;
		//Try loading the state, if false return if true
		//rerun SetActiveState
	//	return;
	//}
	//Update the new id
	mActiveID = id;
	//Save and quit the active state, the load and start the new state
	//mStates.at(mActiveID)->Init();
	std::string stateCode = mStates.at(mActiveID)->Run();
	//mStates.at(mActiveID)->Save(mStates.at(mActiveID)->Name());
	SaveState(mStates.at(mActiveID)->Name());
	//mStates.at(mActiveID)->Free();

	if (stateCode == "quit")
		return;
	else (SetActiveState(stateCode));
}
bool StateManager::LoadState(std::string name){
	//Need to differentiate menu and game states
	Json::Reader reader;
	Json::Value root;
	if (name.at(0) == 'm'){
		std::ifstream fileIn((mStatesDir + name + ".json").c_str(), std::ifstream::binary);
		//Make sure the file opened ok		
		if (!fileIn || !reader.parse(fileIn, root, false))
			return false;
		//load menu state
		MenuState *menu = new MenuState();
		//menu->Init();
		menu->Load(root);
		Register((State*)menu);

		return true;
	}
	else if (name.at(0) == 'g'){
		std::ifstream fileIn((mStatesDir + name + ".json").c_str(), std::ifstream::binary);
		//Make sure the file opened ok		
		if (!fileIn || !reader.parse(fileIn, root, false))
			return false;
		//load game state
		GameState *game = new GameState();
		//game->Init();
		game->Load(root);
		Register((State*)game);

		return true;
	}
	return false;
}
void StateManager::SaveState(std::string name){
	try {
		Json::Value val = mStates.at(IdFromName(name))->Save();
		std::ofstream fileOut((mStatesDir + name + ".json").c_str());

		Json::StyledWriter writer;
		std::string data = writer.write(val);
		fileOut << data << std::endl;

		fileOut.close();
	}
	catch (const std::runtime_error &e){
		std::cout << e.what() << std::endl;
	}
}