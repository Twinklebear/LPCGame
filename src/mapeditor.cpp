#include <vector>
#include <string>
#include "../externals/json/json.h"
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
void MapEditor::Insert(int x, int y, Tile tile){
	try {
		int i = CalculateIndex(x, y);
		tile.SetBox(Recti(mTiles.at(i).Box()));
		mTiles.at(i) = tile;
	}
	catch(...){
		//We just need to catch the error so we don't crash,
		//it should be obvious to user if they click off the map
	}
}
void MapEditor::Remove(int x, int y){
	Tile blank(Recti(0, 0, 0, 0), false, 0);
	Insert(x, y, blank);
}