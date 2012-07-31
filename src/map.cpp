#include <vector>
#include <string>
#include <cmath>
#include "../externals/json/json.h"
#include "window.h"
#include "image.h"
#include "tile.h"
#include "camera.h"
#include "map.h"

Map::Map(){
}
Map::~Map(){
	mTiles.clear();
}
void Map::Draw(Camera *cam){
	//Use the camera box to get the indices of all the tiles in visible in camera
	if (cam != nullptr){
		std::vector<int> indices = CalculateIndex(cam->Box());
		for (int i : indices){
			if (i < mTiles.size()){
				Rectf pos = Math::FromSceneSpace(cam, mTiles.at(i).Box());
				Window::Draw(&mImage, pos,
					&(SDL_Rect)mImage.Clip(mTiles.at(i).Type()));
			}
		}
	}
	//If no camera we default to drawing all tiles
	else
		for (int i = 0; i < mTiles.size(); ++i){
			Window::Draw(&mImage, mTiles.at(i).Box(), 
				&(SDL_Rect)mImage.Clip(mTiles.at(i).Type()));
		}
}
Json::Value Map::Save(){
	Json::Value map;
	//Save the map width and height
	map["mBox"]["w"] = mBox.w;
	map["mBox"]["h"] = mBox.h;
	map["image"] = mImage.Save();
	//Save the tiles
	for (int i = 0; i < mTiles.size(); ++i){
		map["tiles"][i] = mTiles.at(i).Save();
	}
	
	return map;
}
void Map::Load(Json::Value val){
	mBox.Set(0, 0, val["mBox"]["w"].asInt(), val["mBox"]["h"].asInt());
	mImage.Load(val["image"]);

	//Load the tiles
	Json::Value tiles = val["tiles"];
	for (int i = 0; i < tiles.size(); ++i){
		Tile tempTile;
		tempTile.Load(tiles[i]);

		mTiles.push_back(tempTile);
	}
}
void Map::GenerateStressMap(Json::Value val){
	int numTiles = val["numTiles"].asInt();
	mImage.Load(val["image"]);
	mBox.Set(0, 0, Window::Box().w, Window::Box().h);
	//Determine the tile w/h to fill the window with numTiles
	int tileSize = sqrt((Window::Box().w * Window::Box().h) / numTiles);
	//Generate the map
	int tPerCol = Window::Box().w / tileSize;
	int col = 0;
	for (int i = 0; i < numTiles; ++i){
		if (i != 0 && i % tPerCol == 0)
			++col;
		Recti tRect(col * tileSize, i % tPerCol * tileSize, tileSize, tileSize);
		Tile tempTile;
		tempTile.SetBox(tRect);
		tempTile.SetSolid(false);
		tempTile.SetType(0);
		mTiles.push_back(tempTile);
	}
}
int Map::CalculateIndex(int x, int y) const{
	//if it's in bounds calculate the index
	if ((x > 0 && x < mBox.W()) && (y > 0 && y < mBox.H())){
		return (x / TILE_WIDTH + (y / TILE_HEIGHT) * (mBox.W() / TILE_WIDTH)); 
	}
	else 
		throw std::runtime_error("Point off map");
}
std::vector<int> Map::CalculateIndex(Recti area) const{
	std::vector<int> tileIndices;
	//run through the area
	for (int y = area.Y(); y <= area.Y() + area.H(); y += TILE_HEIGHT / 2){
		for (int x = area.X(); x <= area.X() + area.W(); x += TILE_WIDTH / 2){
			try{
				int index = CalculateIndex(x, y);
				//make sure it isn't already in the vector
				bool exists = false;
				for (int i = 0; i < tileIndices.size() && !exists; ++i){
					if (index == tileIndices.at(i))
						exists = true;
				}
				if (!exists)
					tileIndices.push_back(index);
			}
			catch (...){
				//the error is more of a notice to keep us adding invalid indices, 
				//so nothing more is needed here
			}
		}
	}
	if (tileIndices.size() != 0)
		return tileIndices;
	else
		throw std::runtime_error("Invalid area");
}
CollisionMap Map::GetCollisionMap(const Recti &target, int distance){
	//get the indices of the desired tiles
	Recti area(target.X() - distance * TILE_WIDTH, target.Y() - distance * TILE_HEIGHT,
		((target.X() + target.W() + distance * TILE_WIDTH) - (target.X() - distance * TILE_WIDTH)),
		((target.Y() + target.H() + distance * TILE_HEIGHT) - (target.Y() - distance * TILE_HEIGHT)));

	std::vector<int> indices;
	try{
		indices = CalculateIndex(area);
	}
	catch (...){
	}
	//Setup the collision map
	CollisionMap localMap;
	for (int i : indices){
		if (i < mTiles.size() && mTiles.at(i).Solid())
			localMap.push_back(mTiles.at(i).Box());
	}
	return localMap;
}
Recti Map::Box() const{
	return mBox;
}