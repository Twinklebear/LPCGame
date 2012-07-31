#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "../externals/json/json.h"
#include "base.h"
#include "window.h"
#include "image.h"
#include "tile.h"
#include "camera.h"

///Handles the tile map
/**
*  Takes care of a simple tile based map
*  TODO: I need to add mapobject types
*/
class Map{
public:
	Map();
	~Map();
	/**
	*  Draw the tiles on the screen, relative to the camera
	*  @param cam The camera so we can get the offsets/check if things are in camera
	*/
	void Draw(Camera *cam = nullptr);
	/**
	*  Save the map data to a Json::Value
	*  @return The map data as a Json::Value
	*/
	Json::Value Save();
	/**
	*  Load the map from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);
	/**
	*  Generate a stress testing map with a specified number of tiles
	*  @param val The Json::Value to load the stress test from
	*/
	void GenerateStressMap(Json::Value val);
	/**
	*  Calculate the index of the tile at the point
	*  @param x The point's x coordinate
	*  @param y The point's y coordinate
	*  @return The index of the tile at the point
	*  @throw Runtime Error if the point is off the map, must catch this
	*/
	int CalculateIndex(int x, int y) const;
	/**
	*  Calculate the indices of all the tiles within an area
	*  @param area The area to get tile indices in
	*  @return A vector of ints containing the tile indices
	*/
	std::vector<int> CalculateIndex(Recti area) const;
	/**
	*  Get the collision map within distance of the target
	*  @param target The target to get the nearby collision map around
	*  @param distance The distance in tiles to return the map of
	*  @return The collision map of local tiles
	*/
	CollisionMap GetCollisionMap(const Recti &target, int distance = 2);
	///Get the map's box
	Recti Box() const;

protected:
	std::vector<Tile> mTiles;
	Image mImage;
	Recti mBox;
};

#endif