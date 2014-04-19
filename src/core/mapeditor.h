#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <vector>
#include <string>
#include "external/json/json.h"
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
	*  Generate a blank map
	*  @param tilename The name of default tile
	*/
	void GenerateBlank(std::string tilename);
	/**
	*  Insert a tile at the tile located at some x, y point
	*  @param x The x coordinate to insert tile at
	*  @param y The y coordinate to insert tile at
	*  @param tilename The tile to insert at the point
	*/
	void Insert(int x, int y, std::string tilename);
	/**
	*  Remove a tile at some point, really just performs Insert
	*  of the default tile
	*  @param x The x coordinate to clear
	*  @param y The y coordinate to clear
	*/
	void Remove(int x, int y);
};

#endif