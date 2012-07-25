#include <stdexcept>
#include <memory>
#include "map.h"
#include "window.h"
#include "gameobjectmanager.h"
#include "timer.h"
#include "player.h"
#include "npc.h"
#include "input.h"
#include "button.h"
#include "menustate.h"
#include "gamestate.h"
#include "statemanager.h"

#include "debugger.h"
#include <iostream>

int main(int argc, char** argv){
	//Initialize statics
	Window::Init();
	Input::Init();

	//Create and register the states
	/*
	MenuState *menuState = new MenuState();
	menuState->SetName("mIntro");
	menuState->Init();
	StateManager::Register((State*)menuState);
	*/
	//GameState *gameState = new GameState();
	//gameState->SetName("gGame");
	//StateManager::Register((State*)gameState);
	//gameState->Save();

	StateManager::InitIntro();

	Window::Quit();
	return 0;
}