#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include "state.h"
#include "gamestate.h"
#include "menustate.h"
#include "statemanager.h"

State* StateManager::mActiveState;
const std::string StateManager::mStatesDir = "../res/states/";

void StateManager::InitIntro(){
	SetActiveState("mIntro");
}
void StateManager::SetState(State* state){
	mActiveState = state;
}
void StateManager::SetActiveState(std::string name){
	if (!LoadState(name))
		std::cout << "Failed to load state: " << name << std::endl;

	std::string stateCode = mActiveState->Run();
	SaveState(mActiveState->Name());
	//Delete the state we quit
	delete mActiveState;
	
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
		menu->Load(root);
		SetState((State*)menu);

		fileIn.close();

		return true;
	}
	else if (name.at(0) == 'g'){
		std::ifstream fileIn((mStatesDir + name + ".json").c_str(), std::ifstream::binary);
		//Make sure the file opened ok		
		if (!fileIn || !reader.parse(fileIn, root, false))
			return false;
		//load game state
		GameState *game = new GameState();
		game->Load(root);
		SetState((State*)game);

		fileIn.close();

		return true;
	}
	return false;
}
void StateManager::SaveState(std::string name){
	Json::Value val = mActiveState->Save();
	std::ofstream fileOut((mStatesDir + name + ".json").c_str());

	Json::StyledWriter writer;
	std::string data = writer.write(val);
	fileOut << data << std::endl;

	fileOut.close();
}