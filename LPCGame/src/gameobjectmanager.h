#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <vector>
#include <memory>
#include "json/json.h"
#include "gameobject.h"
#include "map.h"
#include "camera.h"

//Typedef for a vector of GameObject pointers
//typedef std::vector<GameObject*> GameObjectList;
typedef std::vector<std::shared_ptr<GameObject>> GameObjectList;

/*
 * A class to simplify handling of the objects, and simple
 * collision interactions between them
*/
class GameObjectManager{
public:
	GameObjectManager();
	~GameObjectManager();
	//Draw the game objects
	void Draw();
	//Update the objects
	void Update();
	/*
	*	Move the game objects
	*	@param deltaT: the time elapsed
	*/
	void Move(float deltaT);
	/*
	*	Setup object collision maps
	*	@param map: the map to get the collision maps from
	*/
	void SetCollisionMaps(Map *map);
	/*
	*	Add a gameobject pointer to the list
	*	@param *obj: the object pointer to add
	*/
	void Register(std::shared_ptr<GameObject> obj);
	/*
	*  Handle Mouse clicks, run through the active game objects
	*  find what was clicked, and call it
	*  @param mouseEvent: The mouse event that we're processing
	*/
	void HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent);
	/*
	*  Handle Mouse motion, check if the mouse entered/exited an object
	*  @param mouseEvent: The mouse event that we're processing
	*/
	void HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent);
	/*
	*  Serialize all the game object data to a Json::Value and return it
	*  @returns: The Json::Value containing the gameobject data
	*/
	Json::Value Save();
	/*
	*  Register an object with the manager's camera
	*  @param obj: the object to pass to the camera for focusing
	*/
	void SetCameraFocus(std::shared_ptr<GameObject> obj);

private:
	//Maybe i can have a function that returns a collision map of local entities
	//and simply add that collision map to the local collision map of the tiles
	CollisionMap GetEntityCollisionMap(const Rectf &target, int distance = 2 * TILE_WIDTH);

private:
	GameObjectList mGameObjects;
	Camera mCamera;
};

#endif