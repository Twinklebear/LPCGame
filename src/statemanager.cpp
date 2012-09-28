#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <memory>
#include <luabind/luabind.hpp>
#include "state.h"
#include "gamestate.h"
#include "menustate.h"
#include "editorstate.h"
#include "jsonhandler.h"
#include "statemanager.h"

std::shared_ptr<State> StateManager::mActiveState;
const std::string StateManager::mStatesDir = "../res/states/";

void StateManager::InitIntro(){
	SetActiveState("mIntro");
}
void StateManager::SetState(State* state){
	mActiveState.reset(state);
}
void StateManager::SetActiveState(std::string name){
	if (!LoadState(name))
		throw std::runtime_error("Failed to load state: " + name);

	std::string stateCode = mActiveState->Run();
	SaveState(mActiveState->Name());

	if (stateCode == "quit")
		return;
	else (SetActiveState(stateCode));
}
bool StateManager::LoadState(std::string name){
    JsonHandler jsonHandler((mStatesDir + name + ".json"));

    //Differentiate between menu and game states
    //Todo: will this be necessary? in the future if states are more scripted
    //the only differences should be in the script/json? hmm
    if (name.at(0) == 'm'){
        MenuState *menu = new MenuState();
        try {
            menu->Load(jsonHandler.ReadFile());
        }
        catch (const std::runtime_error &e){
            std::cout << e.what() << std::endl;
            return false;
        }
        SetState((State*)menu);
        return true;
    }
    if (name.at(0) == 'g'){
        GameState *game = new GameState();
        try {
            game->Load(jsonHandler.ReadFile());
        }
        catch (const std::runtime_error &e){
            std::cout << e.what() << std::endl;
            return false;
        }
        SetState((State*)game);
        return true;
    }
    if (name.at(0) == 'e'){
        EditorState *editor = new EditorState();
        try {
            editor->Load(jsonHandler.ReadFile());
        }
        catch (const std::runtime_error &e){
            std::cout << e.what() << std::endl;
            return false;
        }
        SetState((State*)editor);
        return true;
    }
}
void StateManager::SaveState(std::string name){
    JsonHandler jsonHandler((mStatesDir + name + ".json"));
    jsonHandler.WriteFile(mActiveState->Save());
}
void StateManager::ChangeScene(std::string scene){
	mActiveState->SetExit(scene);
}
void StateManager::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<StateManager>("StateManager")
			.scope[
				def("InitIntro", &StateManager::InitIntro),
				def("SetActiveState", &StateManager::SetActiveState),
				def("ChangeScene", &StateManager::ChangeScene)
			]
	];
}
