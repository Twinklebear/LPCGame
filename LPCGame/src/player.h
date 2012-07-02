#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"

const int PLAYER_WIDTH	= 32;
const int PLAYER_HEIGHT = 32;
const int PLAYER_HSPEED = 300;
const int PLAYER_HACCEL = 700;

/*
*	The player class, for handling the player
*/
class Player : public GameObject{
public:
	//Construct the player
	Player();
	//Destroy Player
	~Player();
	//Event handling
	void HandleEvents(SDL_Event &event);
	//Move the player
	void Move(float deltaT);
	//Draw the player
	void Draw();
	//Setters and getters
	Rectf Box();

private:
	//Disable copy-construction
	Player(const Player &a);
	Player& operator = (const Player &a);

private:
	Image mImage;
};

#endif