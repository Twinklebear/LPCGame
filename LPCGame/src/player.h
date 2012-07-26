#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "json/json.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"

/*
*	The player class, for handling the player
*/
class Player : public GameObject{
public:
	Player();
	~Player();
	//Run once each fram
	void Update();
	//Move the player
	void Move(float deltaT);
	//Draw the player
	void Draw();
	/*
	*  Save the object data to a json value and return it
	*  @returns: The json value containing the object data
	*/
	Json::Value Save();
	/*
	*  Load the object from a json value
	*  @param val: The json value to load from
	*/
	void Load(Json::Value val);

private:
	//Disable copy-construction
	Player(const Player &a);
	Player& operator = (const Player &a);

private:
	Image mImage;
};

#endif