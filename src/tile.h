#ifndef TILE_H
#define TILE_H
#include <string>
#include "../externals/json/json.h"
#include "rect.h"

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
	Tile(Recti box, int type, bool solid, std::string name){
		mBox	= box;
		mSolid	= solid;
		mType	= type;
		mName	= name;
	}
	///Get the tile's box
	Recti Box() const{
		return mBox;
	}
	///Get the tile's solid value (T/F)
	bool Solid() const{
		return mSolid;
	}
	///Get the tile's type
	int Type() const{
		return mType;
	}
	///Get the tile's name
	std::string Name() const{
		return mName;
	}
	///Set the tile's box
	void SetBox(Recti box){
		mBox = box;
	}
	///Set the tile's solid property
	void SetSolid(bool solid){
		mSolid = solid;
	}
	///Set the tile's type
	void SetType(int type){
		mType = type;
	}
	///Set the tile's name
	void SetName(std::string name){
		mName = name;
	}

	/**
	*  Save the tile data to a json value
	*  @return Json::Value containing the tile data
	*/
	Json::Value Save(){
		Json::Value val;
		val["box"]   = mBox.Save();
		val["type"]  = mType;
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
		mType = val["type"].asInt();
		mSolid = val["solid"].asBool();
		mName = val["name"].asString();
	}

private:
	Recti mBox;
	bool mSolid;
	int mType;
	std::string mName;
};

#endif