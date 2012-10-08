#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "base.h"
#include "physics.h"
#include "map.h"
#include "image.h"
#include "luascript.h"

///The Entity class, to provide functions that call to attached Lua scripts
/**
*  Base class for Entities, has functions that simply provide a call to
*  the function of the same name on the Entity's attached Lua script
*/
class Entity {
public:
	Entity();
	/**
	*  Construct the Entity and load its script
	*  @param script The object's script
	*/
	Entity(std::string script);
	virtual ~Entity();
	//Initialize the object
	virtual void Init();
	//Free the object's memory
	virtual void Free();
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
	*  Check if mouse entered the object's box
	*  Updates mMouseOver accordingly
	*  @param pos The mouse pos to check 
	*/
	virtual void CheckMouseOver(const Vector2f &pos);
	///Return T/F is the mouse is over the object
	bool GetMouseOver();
	/**
	*  Get a pointer to the object's Physics component, for use in allowing
	*  it to be gotten and used in a script
	*  @return A pointer to the entity's Physics member
	*/
	Physics* GetPhysics();
	/**
	*  Set a collision map for the physics member to check against
	*  @param map The collision map
	*/
	void SetCollisionMap(CollisionMap map);
	///Get the object's box
	Rectf Box();
	///Set the entity's tag
	void SetTag(std::string tag);
	///Get the entity's tag
	std::string Tag();
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
	static int RegisterLua(lua_State *l);

private:
	///Game objects should not be copy-constructable
	Entity(const Entity &a);
	Entity& operator = (const Entity &a);

protected:
	///Note: Once Lua entity scripting is fully implemented, Image should no longer be a member, but rather
	///should be created and given to the Lua instance to handle if an image is desired
	Image mImage;
	///Handle's the objects physics
	Physics mPhysics;
	///A general tag for the entity
	std::string mTag;
	///The entity's name
	std::string mName;
    //The entity's file name
    std::string mConfigFile;
	///For tracking mouse over
	bool mMouseOver;
	///The entity's lua script
	LuaScript mScript;
};

#endif