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
#include "debug.h"
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
    LoadState(name);
    std::string stateCode = "quit";
    //Catching state errors for debugging, if error thrown program quits
    stateCode = mActiveState->Run();
	SaveState(mActiveState->Name());

	if (stateCode == "quit")
		return;
	else (SetActiveState(stateCode));
}
void StateManager::LoadState(std::string name){
    JsonHandler jsonHandler((mStatesDir + name + ".json"));

    //Differentiate between menu and game states
    //Todo: will this be necessary? in the future if states are more scripted
    //the only differences should be in the script/json? hmm
    if (name.at(0) == 'm'){
        MenuState *menu = new MenuState();
        menu->Load(jsonHandler.Read());
        SetState((State*)menu);
        return;
    }
    if (name.at(0) == 'g'){
        GameState *game = new GameState();
        game->Load(jsonHandler.Read());
        SetState((State*)game);
        return;
    }
    if (name.at(0) == 'e'){
        EditorState *editor = new EditorState();
        editor->Load(jsonHandler.Read());
        SetState((State*)editor);
        return;
    }
}
void StateManager::SaveState(std::string name){
    JsonHandler jsonHandler((mStatesDir + name + ".json"));
    jsonHandler.Write(mActiveState->Save());
}
void StateManager::ChangeScene(std::string scene){
	mActiveState->SetExit(scene);
}
int StateManager::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<StateManager>("StateManager")
			.scope[
				def("InitIntro", &StateManager::InitIntro),
				def("SetActiveState", &StateManager::SetActiveState),
				def("ChangeScene", &StateManager::ChangeScene)
			]
	];
    return 1;
}
