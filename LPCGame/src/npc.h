#ifndef NPC_H
#define NPC_H

#include "SDL.h"
#include "json/json.h"
#include "gameobject.h"
#include "rect.h"
#include "vectors.h"
#include "window.h"
#include "image.h"

/*
*	The base NPC class
*/
class Npc : public GameObject {
public:
	Npc();
	~Npc();
	//Run once each frame
	void Update();
	//Handle player movement
	void Move(float deltaT);
	/*
	*  Draw the object, apply an adjustment for the camera if one is desired
	*  @param cam: the camera to adjust for
	*/
	void Draw(Camera *cam = nullptr);
	//Setters & Getters
	void SetMove(int moveDir);
	/*
	*  Save the object data to a json value and return it
	*  @returns: The json value containing the object data
	*/
	Json::Value Save();
	/*
	*  Load the object from a json value
	*  @param value: The json value to load from
	*/
	void Load(Json::Value val);

private:
	//Disable copy construction
	Npc(const Npc &a);
	Npc& operator = (const Npc &a);

private:
	Image mImage;
};

#endif