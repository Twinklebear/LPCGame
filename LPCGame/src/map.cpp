#include <vector>
#include <string>
#include <cmath>
#include "window.h"
#include "image.h"
#include "tile.h"
#include "map.h"

Map::Map(){
	//Generate a map with a floor for testing
	mBox.w = Window::Box().w;
	mBox.h = Window::Box().h;

	//for setting y position
    int yPos = 0;
	int mapSize = mBox.w / TILE_WIDTH;

    for (int i = 0; i < pow(mapSize, 2); ++i){
        Tile tempTile;
		tempTile.SetSolid(false);
		tempTile.SetType(0);
        //setup position
        if (i != 0 && i % mapSize == 0){
            yPos += TILE_HEIGHT;
		}
		tempTile.SetBox(Recti((i % mapSize) * TILE_WIDTH, 
							  yPos, TILE_WIDTH, TILE_HEIGHT));
		if (tempTile.Box().y > 400){
			tempTile.SetType(6);
			tempTile.SetSolid(true);
		}
		mTiles.push_back(tempTile);
    }
	LoadImageSheet();
	UpdateCollisionMap();
}
Map::Map(std::string mapFile){
}
Map::~Map(){
	Unload();
}
void Map::Draw(const Recti &camera){
	//TODO: Need a better way to draw the map that reduces draw calls
	for (int i = 0; i < mTiles.size(); ++i)
		Window::Draw(&mImage, (SDL_Rect)mTiles.at(i).Box(), &(SDL_Rect)mImage.Clip(mTiles.at(i).Type()));
}
void Map::LoadFile(std::string mapFile){
}
void Map::LoadImageSheet(){
	mImage.LoadImage("images/tiles.png");
	SetClips();
}
void Map::Unload(){
	mTiles.clear();
	ClearCollisionMap();
}
void Map::UpdateCollisionMap(){
	ClearCollisionMap();
	SetCollisionMap();
}
void Map::SetClips(){
	std::vector<Recti> clips;
	int column = 0;
	for (int i = 0; i < 8; ++i){
		if (i != 0 && i % 3 == 0)
			++column;
		Recti clipRect(column * TILE_WIDTH, (i % 3) * TILE_HEIGHT,
					   TILE_WIDTH, TILE_HEIGHT);
		clips.push_back(clipRect);
	}
	mImage.SetClips(clips);
}
void Map::SetCollisionMap(){
	ClearCollisionMap();
	for (auto i : mTiles){
		if (i.Solid())
			mCollisionMap.push_back(new Recti(i.Box()));
	}
}
void Map::ClearCollisionMap(){
	for (auto i : mCollisionMap)
		delete i;
	mCollisionMap.clear();
}
int Map::CalculateIndex(int x, int y){
	//if it's in bounds calculate the index
	if ((x >= 0 && x <= mBox.w) && (y >= 0 && y <= mBox.h)){
		return (x / TILE_WIDTH + (y / TILE_HEIGHT) * (mBox.w / TILE_WIDTH)); 
	}
	else 
		throw std::runtime_error("Point off map");
}
std::vector<int> Map::CalculateIndex(Recti area){
	std::vector<int> tileIndices;
	//run through the area
	for (int y = area.y; y < area.y + area.h; y += TILE_HEIGHT){
		for (int x = area.x; x < area.x + area.w; x += TILE_WIDTH){
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
CollisionMap* Map::GetCollisionMap(){
	return &mCollisionMap;
}
CollisionMap Map::GetLocalCollisionMap(const Recti &target, int distance){
	//get the indices of the desired tiles
	Recti area(target.x - distance * TILE_WIDTH, target.y - distance * TILE_HEIGHT,
				((target.x + target.w + distance * TILE_WIDTH) - (target.x - distance * TILE_WIDTH)),
				((target.y + target.h + distance * TILE_HEIGHT) - (target.y - distance * TILE_HEIGHT)));
	std::vector<int> indices = CalculateIndex(area);
	CollisionMap localMap;
	//add the references
	for (int i : indices){
		if (mTiles.at(i).Solid())
			localMap.push_back(mCollisionMap.at(i));
	}
	return localMap;
}