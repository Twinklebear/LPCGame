#include <array>
#include <memory>
#include <fstream>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "rect.h"
#include "tileset.h"
#include "window.h"

TileSet::TileSet()
{
}
TileSet::~TileSet(){
}
void TileSet::Load(Json::Value val){
	int size = val.size();
	if (size > 0){
		for (int i = 0; i < size; i++)
			Add(val[i]["file"].asString());
	}
}
void TileSet::Add(const std::string &file){
	//Get just the config name
	unsigned int a = file.rfind('.');
	std::string configFile = file.substr(0, a) + ".json";

	//Add this image
	std::shared_ptr<SDL_Texture> newTexture;
	newTexture.reset(Window::LoadTexture(file), SDL_DestroyTexture);
	mImages[file] = newTexture;

	//Parse the .json file
	std::ifstream fileIn((configFile).c_str(), std::ifstream::binary);
	if (fileIn){
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(fileIn, root, false)){
			
            //Load the config data
            ParseImageJson(root, file);
		}
        else
			//some debug output, this case should throw
            throw std::runtime_error("Failed to parse file: " + configFile); 

		fileIn.close();

	}
    else
        throw std::runtime_error("Failed to find file: " + configFile);
}
SDL_Texture* TileSet::Texture(const std::string &file){
	return (SDL_Texture*)mImages[mTileSet[file].Filename()].get();
}
Recti TileSet::Clip(const std::string &file){
	std::map<std::string, Tile>::const_iterator it;
	it = mTileSet.find(file);
	if (it != mTileSet.end())
		return mTileSet[file].Box();
	Recti nullRecti(0,0,0,0);
	return nullRecti;
}
bool TileSet::Solid(const std::string &file){
	return mTileSet[file].Solid();
}
void TileSet::ParseImageJson(Json::Value val, const std::string &file){
	unsigned int a = file.rfind('.');
	unsigned int b = file.rfind('/');
	std::string fileName = file.substr(b+1,a-b-1);

	if (val.isMember("clips")){
		int size = val["clips"].size();
		for (int i = 0; i < size; ++i){
			Json::Value tile = val["clips"][i];

			//Create new tile
			Tile newTile(tile);
			newTile.SetFilename(file);
			
			//Add tile to tileset
			std::string tileSetEntry = fileName + " - " + tile["name"].asString();
			mTileSet[tileSetEntry] = newTile;

		}
	}
}
Json::Value TileSet::Save() {
	Json::Value val;
	
	int i = 0;
	for(std::map<std::string, std::shared_ptr<SDL_Texture>>::iterator it = mImages.begin(); it != mImages.end(); it++)
	{
		val[i]["file"] = it->first;
	}
	return val;
}
