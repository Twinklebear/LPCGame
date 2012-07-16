#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"

#include "debugger.h"

const int PLAYER_WIDTH	= 28;
const int PLAYER_HEIGHT = 28;
const int PLAYER_HSPEED = 300;
const int PLAYER_HACCEL = 700;

/*
*	The player class, for handling the player
*/
class Player : public GameObject{
public:
	Player();
	~Player();
	//Load images/setup initial values
	void Start(int x, int y);
	//Run once each fram
	void Update();
	//Event handling
	void HandleEvents(SDL_Event &event);
	//Move the player
	void Move(float deltaT);
	//Draw the player
	void Draw();
	//Mouse event handling
	void OnMouseDown();
	void OnMouseUp();
	void OnMouseEnter();
	void OnMouseExit();
	//Setters and getters

private:
	//Disable copy-construction
	Player(const Player &a);
	Player& operator = (const Player &a);

private:
	Image mImage;
	Debugger *dbg;
};

#endif