#ifndef TILE_H
#define TILE_H

#include <string>
#include "external/json/json.h"
#include "rect.h"

//TODO: This should be configurable
const int TILE_WIDTH  = 32;
const int TILE_HEIGHT = 32;

///A map tile
/**
*  Describes a simple map tile
*/
class Tile{
public:
	Tile(){}
	/*
	*  Setup the tile with a box, solid property and type
	*  @param box The tile's box
	*  @param solid The tile's solid property
	*  @param type The tile's type, corresponds to its clip number for drawing
	*  @param name The tile's name
	*/
	Tile(Recti box, bool solid, const std::string name){
		mBox	= box;
		mSolid	= solid;
		mName	= name;
	}
	Tile(Json::Value val){
		Load(val);
	}
	///Get the tile's box
	Recti Box() const{
		return mBox;
	}
	///Get the tile's solid value (T/F)
	bool Solid() const{
		return mSolid;
	}
	///Get the tile's name
	std::string Name() const{
		return mName;
	}
	///Get the tile's image location
	std::string Filename() const{
		return mFilename;
	}
	///Set the tile's box
	void SetBox(Recti box){
		mBox = box;
	}
	///Set the tile's solid property
	void SetSolid(bool solid){
		mSolid = solid;
	}
	///Set the tile's name
	void SetName(const std::string name){
		mName = name;
	}
	///Set the tile's name
	void SetFilename(const std::string &file){
		mFilename = file;
	}
	/**
	*  Save the tile data to a json value
	*  @return Json::Value containing the tile data
	*/
	Json::Value Save(){
		Json::Value val;
		val["box"]   = mBox.Save();
		val["solid"] = mSolid;
		val["name"] = mName;

		return val;
	}
	/**
	*  Load the tile from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val){
		mBox.Load(val["box"]);
		mSolid = val["solid"].asBool();
		mName = val["name"].asString();
	}

private:
	Recti mBox;
	bool mSolid;
	std::string mName;
	std::string mFilename;
};

#endif