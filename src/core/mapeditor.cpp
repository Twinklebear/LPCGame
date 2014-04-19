#include <vector>
#include <string>
#include "external/json/json.h"
#include "base.h"
#include "window.h"
#include "image.h"
#include "tile.h"
#include "camera.h"
#include "map.h"
#include "mapeditor.h"

MapEditor::MapEditor(){
}
MapEditor::~MapEditor(){
	mTiles.clear();
}
void MapEditor::GenerateBlank(std::string tilename){
	mTiles.clear();
	//Setup the tiles
	int tW = 32, tH = 32;
	//Set the mapbox
	mBox.Set(0, 0, rows * tW, columns * tH);
	int tPerRow = rows;
	int row = 0;

	for (int i = 0; i < rows * columns; ++i){
		if (i != 0 && i % tPerRow == 0)
			++row;
		Recti tRect(i % tPerRow * tW, row * tH, tW, tH);
		Tile tempTile;
		tempTile.SetBox(tRect);
		tempTile.SetSolid(false);
		tempTile.SetName(tilename);
		mTiles.push_back(tempTile);
	}
}
void MapEditor::Insert(int x, int y, std::string tilename){
	//Find the tile location of where they clicked
	int i = CalculateIndex(x, y, mBox.w, mBox.h);

	//If found, set the new tile, and rebuild the map.
    if (i > -1) {
	    mTiles.at(i).SetName(tilename);
		RebuildMap();
	}
}
void MapEditor::Remove(int x, int y){
	Tile blank(Recti(0, 0, 0, 0), false, "");
	Insert(x, y, "");
}