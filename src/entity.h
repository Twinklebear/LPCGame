#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <luabind/luabind.hpp>
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
class Entity{
public:
	Entity();
	/**
	*  Construct the object and load its script
	*  @param script The object's script
	*/
	Entity(std::string script);
	virtual ~Entity();
	/**
	*  Initialize the object
	*/
	virtual void Init();
	///Update the game object
	virtual void Update();
	/**
	*  Move the object
	*  @param deltaT The elapsed time
	*/
	virtual void Move(float deltaT);
	/**
	*  Draw the Entity, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	virtual void Draw(Camera *cam = nullptr);
	///On mouse down events
	virtual void OnMouseDown();
	///On mouse up event
	virtual void OnMouseUp();
	///On mouse enter
	virtual void OnMouseEnter();
	///On mouse exit
	virtual void OnMouseExit();
	/**
	*  Call some desired function 
	*/
	/**
	*  Check if mouse entered the object's box
	*  Updates mMouseOver accordingly
	*  @param pos The mouse pos to check 
	*/
	virtual void CheckMouseOver(const Vector2f &pos);
	///Return T/F is the mouse is over the object
	bool GetMouseOver();
	/**
	*  Set a collision map for the physics member to check against
	*  @param map The collision map
	*/
	void SetCollisionMap(CollisionMap map);
	/**
	*  Open the desired Lua script to be run as the entity's behavior script
	*  @param script The script file to open
	*/
	void OpenScript(std::string script);
	///Get the object's box
	Rectf Box();
	///Set the entity's tag
	void SetTag(std::string tag);
	///Get the entity's tag
	std::string Tag();
	///TODO: How will I save custom entity data from the script?
	/**
	*  Save the Entity data to a json value and return it
	*  The Entity instance of the function takes care of saving
	*  the base object members, physics, image and tags
	*  @return Json::Value containing the Entity data
	*/
	virtual Json::Value Save();
	/**
	*  Load the Entity from a Json::Value
	*  The Entity instance of the function takes care of loading
	*  the base object members, physics, image and tags
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);
	/**
	*  Register the Entity class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static void RegisterLua(lua_State *l);

private:
	///Game objects should not be copy-constructable
	Entity(const Entity &a);
	Entity& operator = (const Entity &a);

protected:
	//Note: Once Lua entity scripting is fully implemented, Image should no longer be a member, but rather
	//should be created and given to the Lua instance to handle if an image is desired
	Image mImage;
	///Handle's the objects physics
	Physics mPhysics;
	///To store tags to identify the object
	std::string mTag;

private:
	bool mMouseOver;
	lua_State *mL;
	std::string mScript;
};

#endif