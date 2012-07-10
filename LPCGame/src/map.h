#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "window.h"
#include "image.h"
#include "tile.h"

///A collision map of solid tiles/objects
typedef std::vector<Recti> CollisionMap;
/*
 *	Map: handles the a tile based map and its various functions
 */
class Map{
public:
	Map();
	/**
	*	Construct map and load a mapfile
	*	@param mapFile: the file to load
	*/
	Map(std::string mapFile);
	~Map();
	/**
	*	Draw the tiles on the screen, relative to the camera
	*	@param camera: the camera rectangle, default is the window box
	*/
	void Draw(const Recti &camera = Recti(0, 0, Window::Box().W(), Window::Box().H()));
	/**
	*	Load a map file
	*	@param mapFile: the file to load
	*/
	void LoadFile(std::string mapFile);
	/**
	*	Load the image file
	*/
	void LoadImageSheet();
	/**
	*	Unload the active map
	*/
	void Unload();
	///Calculate the index of the tile at some point & return it
	int CalculateIndex(int x, int y);
	///Calculate the indeces enclosed in a rectangle
	std::vector<int> CalculateIndex(Recti area);
	/**
	*	Get the collision map within distance of the target
	*	@param target: the target to get the nearby collision map around
	*	@param distance: the distance in tiles to return the map of
	*	@return: the nearby collision map
	*/
	CollisionMap GetLocalCollisionMap(const Recti &target, int distance = 2);
	//FOR DEBUGGING: Check if tile at some index is solid or not
	bool SolidTile(int index);

private:
	///Setup clips for the image
	void SetClips();

private:
	std::vector<Tile> mTiles;
	Image mImage;
	Recti mBox;
};

#endif