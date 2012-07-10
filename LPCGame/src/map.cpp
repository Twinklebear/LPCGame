#include <vector>
#include <string>
#include <cmath>
#include "window.h"
#include "image.h"
#include "tile.h"
#include "map.h"

#include <iostream>

Map::Map(){
	//Generate a map with a floor for testing
	mBox.Set(0, 0, 320, 320);

	//for setting y position
    int yPos = 0;
	int mapSize = mBox.W() / TILE_WIDTH;

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
		if (tempTile.Box().Y() > 8 * TILE_HEIGHT || tempTile.Box().X() > 8 * TILE_WIDTH){
			tempTile.SetType(6);
			tempTile.SetSolid(true);
		}
		mTiles.push_back(tempTile);
    }
	LoadImageSheet();
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
	try{
		mImage.LoadImage("images/tiles.png");
	}
	catch(std::runtime_error &e){
	}
	SetClips();
}
void Map::Unload(){
	mTiles.clear();
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
int Map::CalculateIndex(int x, int y){
	//if it's in bounds calculate the index
	if ((x > 0 && x < mBox.W()) && (y > 0 && y < mBox.H())){
		return (x / TILE_WIDTH + (y / TILE_HEIGHT) * (mBox.W() / TILE_WIDTH)); 
	}
	else 
		throw std::runtime_error("Point off map");
}
std::vector<int> Map::CalculateIndex(Recti area){
	std::vector<int> tileIndices;
	//run through the area
	for (int y = area.Y(); y < area.Y() + area.H(); y += TILE_HEIGHT){
		for (int x = area.X(); x < area.X() + area.W(); x += TILE_WIDTH){
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
			catch (std::runtime_error &e){
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
CollisionMap Map::GetLocalCollisionMap(const Recti &target, int distance){
	//get the indices of the desired tiles
	Recti area(target.X() - distance * TILE_WIDTH, target.Y() - distance * TILE_HEIGHT,
				((target.X() + target.W() + distance * TILE_WIDTH) - (target.X() - distance * TILE_WIDTH)),
				((target.Y() + target.H() + distance * TILE_HEIGHT) - (target.Y() - distance * TILE_HEIGHT)));
	std::vector<int> indices;
	try{
		indices = CalculateIndex(area);
	}
	catch (std::runtime_error &e){
	}

	CollisionMap localMap;
	for (int i : indices){
		if (mTiles.at(i).Solid()){
			localMap.push_back(mTiles.at(i).Box());
			std::cout << "tile at: " << i << " added"
				<< " at collisionmap index: " << localMap.size() - 1 << std::endl;
		}
	}
	return localMap;
}
bool Map::SolidTile(int index){
	if (index > mTiles.size())
		return false;
	return mTiles.at(index).Solid();
}