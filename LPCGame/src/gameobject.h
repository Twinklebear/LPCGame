#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "physics.h"

/**
*	Basic definition for a gameobject, has methods for intialization, updating
*	etc.
*/
class GameObject{
public:
	GameObject() {};
	///Create the gameobject, initialize various stuff
	virtual void Start(int x = 0, int y = 0) = 0;
	///Update the game object
	//virtual void Update() = 0;
	///Draw the game object
	virtual void Draw() = 0;
	///Move the object
	virtual void Move(float) = 0;
	///Destroy the gameobject
	//virtual void Destroy() = 0;
	///Pass a map pointer to the physics object
	void SetCollisionMap(CollisionMap map){
		mPhysics.SetMap(map);
	}
	Rectf Box(){
		return mPhysics.Box();
	}

private:
	//Game objects should not be copy-constructable
	GameObject(const GameObject &a);
	GameObject& operator = (const GameObject &a);

protected:
	Physics mPhysics;
};

#endif