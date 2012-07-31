#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "map.h"
#include "camera.h"

///Typedef for a vector of GameObject shared pointers
typedef std::vector<std::shared_ptr<GameObject>> GameObjectList;

///Handles the GameObjects in the active state
/**
 * A class to simplify handling of the objects, and simple
 * collision interactions between them
*/
class GameObjectManager{
public:
	GameObjectManager();
	~GameObjectManager();
	///Draw the game objects
	virtual void Draw();
	///Update the objects
	virtual void Update();
	/**
	*  Move the game objects
	*  @param deltaT The time elapsed
	*/
	virtual void Move(float deltaT);
	/**
	*  Setup object collision maps
	*  @param map The map to get the collision maps from
	*/
	void SetCollisionMaps(Map *map);
	/**
	*  Register a GameObject to be managed by the manager
	*  @param obj The object to register
	*/
	void Register(std::shared_ptr<GameObject> obj);
	/**
	*  Register the scene camera with the manager so that 
	*  it can be used in checking which objects to deal with
	*  @param camera The scene camera
	*/
	void Register(std::shared_ptr<Camera> camera);
	/**
	*  Handle mouse clicks, run through the active game objects
	*  find what was clicked, and call it
	*  @param mouseEvent The mouse event that we're processing
	*/
	virtual void HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent);
	/**
	*  Handle Mouse motion, check if the mouse entered/exited an object
	*  @param mouseEvent The mouse event that we're processing
	*/
	virtual void HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent);
	/**
	*  Serialize all the game object data to a Json::Value and return it
	*  @return Json::Value containing the gameobject data
	*/
	virtual Json::Value Save();

private:
	/**
	*  Get a collision map of game objects within distance of the target
	*  @param target The object to check for entities near
	*  @param distance The distance to search away from the target for entities
	*  @return A collision map of entities near the target
	*/
	CollisionMap GetEntityCollisionMap(const Rectf &target, int distance = 2 * TILE_WIDTH);

protected:
	///The list of objects in the scene
	GameObjectList mGameObjects;
	std::shared_ptr<Camera> mCamera;
};

#endif