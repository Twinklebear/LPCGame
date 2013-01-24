#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <memory>
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
    //This should be a do-while setup instead.
	else (SetActiveState(stateCode));
}
std::shared_ptr<State> StateManager::GetActiveState(){
    return mActiveState;
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
    //Currently log invalid state names however I think everything but
    //Editor state should be rolled into a single generic State with no letter prefix to its name
    Debug::Log("StateManager: Invalid statename - " + name);
}
void StateManager::SaveState(std::string name){
    JsonHandler jsonHandler((mStatesDir + name + ".json"));
    jsonHandler.Write(mActiveState->Save());
}
void StateManager::ChangeScene(std::string scene){
    mActiveState->SetExit(scene);
}
