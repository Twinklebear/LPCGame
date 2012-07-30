#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "../externals/json/json.h"
#include "gameobject.h"
#include "window.h"
#include "base.h"
#include "image.h"

/**
*  The player class, for handling the player
*/
class Player : public GameObject{
public:
	Player();
	~Player();
	///Run once each fram
	void Update();
	/**
	*  Move the object
	*  @param deltaT The elapsed time
	*/
	void Move(float deltaT);
	/**
	*  Draw the gameobject, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	void Draw(Camera *cam = nullptr);
	/**
	*  Save the gameobject data to a json value and return it
	*  @return Json::Value containing the gameobject data
	*/
	Json::Value Save();
	/**
	*  Load the gameobject from a json value
	*  @param val The json value to load from
	*/
	void Load(Json::Value val);

private:
	///Disable copy-construction
	Player(const Player &a);
	Player& operator = (const Player &a);

private:
	Image mImage;
};

#endif