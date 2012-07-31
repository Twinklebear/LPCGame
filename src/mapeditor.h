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

class MapEditor : public Map{
	MapEditor();
	~MapEditor();
	/**
	*  Insert a tile at the tile located at some x, y point
	*  @param x The x coordinate to insert tile at
	*  @param y The y coordinate to insert tile at
	*  @param tile The tile to insert at the point
	*/
	void Insert(int x, int y, Tile tile);
	/**
	*  Remove a tile at some point, really just performs Insert
	*  of the default tile
	*  @param x The x coordinate to clear
	*  @param y The y coordinate to clear
	*/
	void Remove(int x, int y);
};

#endif