#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <set>
#include <memory>
#include "../externals/json/json.h"
#include "base.h"
#include "image.h"
#include "tile.h"
#include "camera.h"
#include "tileset.h"
///Handles the tile map
/**
*  Takes care of a simple tile based map
*  TODO: I need to add mapobject types
*/
class Map {
public:
	Map();
	~Map();
	/**
	*  Draw the tiles on the screen, relative to the camera
	*  @param cam The camera so we can get the offsets/check if things are in camera
	*/
	void Draw(std::weak_ptr<Camera> cam);
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
	int CalculateIndex(int x, int y, int w, int h) const;
	/**
	*  Calculate the indices of all the tiles within an area
	*  @param area The area to get tile indices in
	*  @return A set of ints containing the tile indices
	*  @throw Runtime error if the set is empty
	*/
	std::set<int> CalculateIndex(Recti area) const;
	/**
	*  Get the collision map within distance of the target
	*  @param target The target to get the nearby collision map around
	*  @param distance The distance in tiles to return the map of
	*  @return The collision map of local tiles
	*/
	CollisionMap GetCollisionMap(const Recti &target, int distance = 2);
	///Get the map's box
	Recti Box() const;
	///Sets the tileset
	void LoadTileSet(std::shared_ptr<TileSet> ts) { mTileSet = ts; }
    ///Get the map filename
    std::string File() const;
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
    *  Load the map from another file
    *  @param file The file to load the map from
    */
    void Load(const std::string &file);

protected:
	std::vector<Tile> mTiles;
	Recti mBox;
	std::shared_ptr<TileSet> mTileSet;
    std::string mFile;
    //How does this help? It's a pointer to the same camera, so it'll always be equal
	Camera *lastCamera;
	std::set<int> indices;
};

#endif