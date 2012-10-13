#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <vector>
#include <string>
#include "../externals/json/json.h"
#include "base.h"
#include "window.h"
#include "image.h"
#include "tile.h"
#include "camera.h"
#include "map.h"

///Allows for editing of a map
/**
*  Lets you edit the map by inserting or removing tiles
*/
class MapEditor : public Map{
public:
	MapEditor();
	~MapEditor();
	/**
	*  Generate a blank map that is x tiles wide and
	*  y tiles tall
	*  @param x The width of the map, in tiles
	*  @param y The height of the map, in tiles
	*/
	void GenerateBlank(int x, int y);
	/**
	*  Insert a tile at the tile located at some x, y point
	*  @param x The x coordinate to insert tile at
	*  @param y The y coordinate to insert tile at
	*  @param tile The tile to insert at the point
	*/
	void Insert(int x, int y, std::string name);
	/**
	*  Remove a tile at some point, really just performs Insert
	*  of the default tile
	*  @param x The x coordinate to clear
	*  @param y The y coordinate to clear
	*/
	void Remove(int x, int y);
};

#endif