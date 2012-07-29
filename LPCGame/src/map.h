#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "json/json.h"
#include "window.h"
#include "rect.h"
#include "image.h"
#include "tile.h"
#include "camera.h"

///A collision map of solid tiles/objects
typedef std::vector<Recti> CollisionMap;
/*
 *	Map: handles the a tile based map and its various functions
 */
class Map{
public:
	Map();
	~Map();
	/**
	*  Draw the tiles on the screen, relative to the camera
	*  @param cam: the camera rectangle, default is the window box
	*/
	void Draw(Camera *cam = nullptr);
	/**
	*  Save the map data to a Json::Value
	*  @return: The serialized map data as a Json::Value
	*/
	Json::Value Save();
	/*
	*  Load the map from a Json::Value
	*  @param val: The Json::Value to load from
	*/
	void Load(Json::Value val);
	/**
	*  Unload the active map
	*/
	void Unload();
	///Calculate the index of the tile at some point & return it
	int CalculateIndex(int x, int y) const;
	///Calculate the indeces enclosed in a rectangle
	std::vector<int> CalculateIndex(Recti area) const;
	/**
	*  Get the collision map within distance of the target
	*  @param target: the target to get the nearby collision map around
	*  @param distance: the distance in tiles to return the map of
	*  @return: the nearby collision map
	*/
	CollisionMap GetCollisionMap(const Recti &target, int distance = 2);

private:
	std::vector<Tile> mTiles;
	Image mImage;
	Recti mBox;
};

#endif