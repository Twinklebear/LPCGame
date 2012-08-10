#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "../externals/json/json.h"
#include "gameobject.h"
#include "window.h"
#include "base.h"
#include "image.h"
#include "animatedimage.h"

///The player
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
	*  Save the object data to a json value and return it
	*  @see GameObject::Save for saving of inherited members
	*  @return The Json::Value containing the object data
	*/
	Json::Value Save();
	/**
	*  Load the object from a Json::Value
	*  @see GameObject::Load for loading of inherited members
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);

private:
	///Disable copy-construction
	Player(const Player &a);
	Player& operator = (const Player &a);

private:
	AnimatedImage mAnimatedImage;
};

#endif