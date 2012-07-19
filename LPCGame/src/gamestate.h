#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"
#include "gameobjectmanager.h"
#include "player.h"
#include "npc.h"
#include "map.h"

/*
*  A simple state to run the game
*  Todo: how should i handle multiple levels? All in gamestate?
*/
class GameState : public State{
public:
	GameState();
	~GameState();

	/* data */
};

#endif