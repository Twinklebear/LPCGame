#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"
#include "../externals/json/json.h"
#include "base.h"
#include "physics.h"
#include "map.h"
#include "image.h"

///A base class for GameObjects to inherit from
/**
*  Base class for gameobjects, has methods for intialization, updating
*  setting colliison maps, mouse interaction, etc.
*/
class GameObject{
public:
	GameObject();
	virtual ~GameObject() {};
	///Update the game object
	virtual void Update() = 0;
	/**
	*  Move the object
	*  @param deltaT The elapsed time
	*/
	virtual void Move(float deltaT) = 0;
	/**
	*  Draw the gameobject, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	virtual void Draw(Camera *cam = nullptr) = 0;
	///On mouse down events
	virtual void OnMouseDown();
	///On mouse up event
	virtual void OnMouseUp();
	///On mouse enter
	virtual void OnMouseEnter();
	///On mouse exit
	virtual void OnMouseExit();
	/**
	*  Check if mouse entered the object's box
	*  Updates mMouseOver accordingly
	*  @param pos The mouse pos to check 
	*/
	void CheckMouseOver(const Vector2f &pos);
	///Return T/F is the mouse is over the object
	bool GetMouseOver();
	/**
	*  Check if the gameobject has the tag
	*  @param tag The tag to check for
	*  @return True if the object has the tag
	*/
	bool HasTag(std::string tag);
	/**
	*  Save the gameobject data to a json value and return it
	*  The GameObject instance of the function takes care of saving
	*  the base object members, physics, image and tags
	*  @return Json::Value containing the gameobject data
	*/
	virtual Json::Value Save();
	/**
	*  Load the gameobject from a Json::Value
	*  The GameObject instance of the function takes care of loading
	*  the base object members, physics, image and tags
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);
	/**
	*  Set a collision map for the physics member to check against
	*  @param map The collision map
	*/
	void SetCollisionMap(CollisionMap map){
		mPhysics.SetMap(map);
	}
	///Get the object's box
	Rectf Box(){
		return mPhysics.Box();
	}

private:
	///Game objects should not be copy-constructable
	GameObject(const GameObject &a);
	GameObject& operator = (const GameObject &a);

protected:
	Image mImage;
	///Handle's the objects physics
	Physics mPhysics;
	///To store tags to identify the object
	std::string mTag;

private:
	bool mMouseOver;
};

#endif