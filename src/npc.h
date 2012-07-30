#ifndef NPC_H
#define NPC_H

#include "SDL.h"
#include "../externals/json/json.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"

/**
*  The base NPC class
*/
class Npc : public GameObject {
public:
	Npc();
	~Npc();
	///Run once each frame
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
	*  Give the npc a direction to move in
	*  @param moveDir The direction to move in @see Math enum
	*/
	void SetMove(int moveDir);
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
	///Disable copy construction
	Npc(const Npc &a);
	Npc& operator = (const Npc &a);

private:
	Image mImage;
};

#endif