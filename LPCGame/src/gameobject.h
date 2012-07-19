#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "vectors.h"
#include "rect.h"
#include "physics.h"

/**
*	Basic definition for a gameobject, has methods for intialization, updating
*	etc.
*/
class GameObject{
public:
	GameObject();
	virtual ~GameObject() {};
	///Create the gameobject, initialize various stuff
	virtual void Start(int x = 0, int y = 0) = 0;
	///Update the game object
	virtual void Update() = 0;
	///Draw the game object
	virtual void Draw() = 0;
	///Move the object
	virtual void Move(float deltaT) = 0;
	///On mouse down events
	virtual void OnMouseDown();
	///On mouse up event
	virtual void OnMouseUp();
	///On mouse enter
	virtual void OnMouseEnter();
	///On mouse exit
	virtual void OnMouseExit();
	///Check if mouse entered the object's box
	void CheckMouseOver(const Vector2f &pos);
	///Return T/F is the mouse is over the object
	bool GetMouseOver();
	///Check if mouse exited the object's box
	///Destroy the gameobject
	//virtual void Destroy() = 0;
	//TODO: A button wouldn't need this method, should i create a rigidbody type?
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

private:
	//Track if mouse is over the object
	bool mMouseOver;
};

#endif