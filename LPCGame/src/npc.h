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
	//Load images/setup the Npc
	void Start(int x, int y);
	//Run once each frame
	void Update();
	//Handle player movement
	void Move(float deltaT);
	//Draw the player
	void Draw();
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
	void Load(Json::Value value);

private:
	//Disable copy construction
	Npc(const Npc &a);
	Npc& operator = (const Npc &a);

private:
	Image mImage;
};

#endif