#include <vector>
#include <set>
#include <string>
#include <cmath>
#include <SDL_image.h>
#include "external/json/json.h"
#include "window.h"
#include "image.h"
#include "tile.h"
#include "camera.h"
#include "jsonhandler.h"
#include "map.h"

Map::Map() : filename(""), mapTexture(nullptr) {
}
Map::~Map(){
	mTiles.clear();
}
void Map::Draw(std::weak_ptr<Camera> cam){
	if (mapTexture == nullptr){
		RebuildMap();
	}

	auto cameraShared = cam.lock();

	Rectf pos(cameraShared->Centering().x, cameraShared->Centering().y, cameraShared->Box().w, cameraShared->Box().h);
	Window::DrawTexture(mapTexture, pos);
}
void Map::RebuildMap(){
	//Create empty surface to be used as the canvas for the map texture
	SDL_Surface* newMap = SDL_CreateRGBSurface(0, rows * TILE_WIDTH, columns * TILE_HEIGHT, 32, 0, 0, 0, 0);
	std::map<std::string,SDL_Surface*> mymap;

	if (newMap < 0)
		std::cout << SDL_GetError() << std::endl;

	//Blit each tile onto the map's surface
	for (int i = 0; i < mTiles.size(); i++){
		SDL_Surface* surf;

		//Get the surface for the current tile
		std::string file = mTileSet.get()->File(mTiles[i].Name()).c_str();
		std::map<std::string,SDL_Surface*>::const_iterator found = mymap.find(file);
		if (found == mymap.end()){
			mymap[file] = IMG_Load(file.c_str());
			surf = mymap[file];
		}
		else
			surf = found->second;

		//Display error if surface isn't found
		if (surf < 0)
			std::cout << SDL_GetError() << std::endl;

		//Determine boxes for the Blit
		// rectFrom is the cordinates for the tile from the TileSet image
		// rectTo is the cordinates on the map which the tile image will be placed 
		Rectf rectTo = mTiles[i].Box();
		Rectf rectFrom = mTileSet->Clip(mTiles[i].Name());
		SDL_Rect rectToSDL = {rectTo.pos.x, rectTo.pos.y, rectTo.h, rectTo.w};
		SDL_Rect rectFromSDL = {rectFrom.pos.x, rectFrom.pos.y, rectFrom.h,	rectFrom.w};

		//Preform Blit
		if (SDL_BlitSurface(surf, &rectFromSDL, newMap, &rectToSDL))
			std::cout << SDL_GetError() << std::endl;
	}

	//Destory the old map.
	if (mapTexture != nullptr)
		SDL_DestroyTexture(mapTexture);

	//Set the new map
	mapTexture = Window::SurfaceToTexture(newMap);

	//Free the surfaces
	for(std::map<std::string,SDL_Surface*>::iterator it = mymap.begin(); it != mymap.end(); it++)
		SDL_FreeSurface(it->second);
	mymap.clear();
}
void Map::GenerateStressMap(Json::Value val){
	int numTiles = val["numTiles"].asInt();
	//mImage.Load(val["image"]);
	mBox.Set(0, 0, Window::Box().w, Window::Box().h);
	//Determine the tile w/h to fill the window with numTiles
	int tileSize = sqrtf((Window::Box().w * Window::Box().h) / numTiles);
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
		mTiles.push_back(tempTile);
	}
}
int Map::CalculateIndex(int x, int y, int w, int h) const{
	//if it's in bounds calculate the index
	if ((x > 0 && x < w) && (y > 0 && y < h)){
		return (x / TILE_WIDTH + (y / TILE_HEIGHT) * (w / TILE_WIDTH)); 
	}
	else{ 
		return -1;
	}
}
std::set<int> Map::CalculateIndex(Recti area) const{
	std::set<int> tileIndices;
	//TODO: How can this be done without all the for loops?
    //Generating these beforehand so that there does not
	//have to be so many calls during the future loops
	int area_x = area.pos.x;
	int area_y = area.pos.y;
	int area_w = area.w;
	int area_h = area.h;
	int mbox_w = mBox.w;
	int mbox_h = mBox.h;
	std::set<int>::iterator it = tileIndices.begin();
	int lastIndex = -1;
	for (int y = area_y; y <= area_y + area_h; y += TILE_HEIGHT / 2){
		for (int x = area_x; x <= area_x + area_w; x += TILE_WIDTH / 2){
			//find the appropriate index and place it with the tiles
			int index = CalculateIndex(x, y, mbox_w, mbox_h);
			if (index >= 0 && index != lastIndex){
				tileIndices.insert(it, index);
				lastIndex = index;
			}
		}
	}
	return tileIndices;
}
CollisionMap Map::GetCollisionMap(const Recti &target, int distance){
	//get the indices of the desired tiles
	Recti area(target.pos.x - distance * TILE_WIDTH, target.pos.y - distance * TILE_HEIGHT,
		((target.pos.x + target.w + distance * TILE_WIDTH) - (target.pos.x - distance * TILE_WIDTH)),
		((target.pos.y + target.h + distance * TILE_HEIGHT) - (target.pos.y - distance * TILE_HEIGHT)));

	std::set<int> indices = CalculateIndex(area);
	//Setup the collision map
	CollisionMap localMap;
	for (int i : indices){
		if (i < mTiles.size() && mTileSet->Solid(mTiles.at(i).Name()))
			localMap.push_back(mTiles.at(i).Box());
	}
	return localMap;
}
Recti Map::Box() const {
	return mBox;
}
std::string Map::Filename() const {
    return filename;
}
void Map::Save(){
    JsonHandler jsonHandler(filename);

	Json::Value map;
	//Save the map width and height
	map["rows"] = rows;
	map["columns"] = columns;

	//Save the tiles
	for (int i = 0; i < mTiles.size(); ++i)
		map["tiles"][mTiles.at(i).Name()].append(i);

    jsonHandler.Write(map);
}
void Map::Load(const std::string &file){
	//Read map file
	JsonHandler handler(file);
	Json::Value map = handler.Read();

	filename = file;

	rows = map["rows"].asInt();
	columns = map["columns"].asInt();

	//Build the map for all tiles
	for (int i = 0; i < rows * columns; i++){
		Tile tempTile;
		mTiles.push_back(tempTile);
	}

	//Update map for each tile. They won't come in order, thats why we had to build the map first.
	for (int i = 0; i < map["tiles"].size(); i++){
		std::string name = map["tiles"].getMemberNames()[i];
		for (int x = 0; x < map["tiles"][name].size(); x++){
			int tileNumber = map["tiles"][name][x].asInt();
			Rectf box(tileNumber % columns * 32, tileNumber / columns * 32,32,32);
			mTiles[tileNumber].SetName(name);
			mTiles[tileNumber].SetBox(box);
		}
	}

	//Set the box accordingly
	mBox.Set(0, 0, columns * 32, rows * 32);
}