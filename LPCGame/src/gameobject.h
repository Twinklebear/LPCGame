#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "physics.h"

/**
*	Basic definition for a gameobject, has methods for intialization, updating
*	etc.
*/
class GameObject{
public:
	GameObject() {}
	///Create the gameobject, initialize various stuff
	virtual void Start() {}
	///Update the game object
	virtual void Update() {}
	///Draw the game object
	virtual void Draw() {}
	///Move the object
	virtual void Move() {}
	///Destroy the gameobject
	virtual void Destroy() {}
	///Pass a map pointer to the physics object
	void SetCollisionMap(CollisionMap &map){
		mPhysics.SetMap(map);
	}

private:
	//Game objects should not be copy-constructable
	GameObject(const GameObject &a);
	GameObject& operator = (const GameObject &a);

protected:
	Physics mPhysics;
};

#endif