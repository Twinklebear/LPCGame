#ifndef NPC_H
#define NPC_H

#include "SDL.h"
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
	//Mouse event handling
	void OnMouseDown();
	void OnMouseUp();
	void OnMouseEnter();
	void OnMouseExit();
	//Setters & Getters
	void SetMove(int moveDir);

private:
	//Disable copy construction
	Npc(const Npc &a);
	Npc& operator = (const Npc &a);

private:
	Image mImage;
};

#endif