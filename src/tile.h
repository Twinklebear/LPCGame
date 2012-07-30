#ifndef TILE_H
#define TILE_H

#include "../externals/json/json.h"
#include "rect.h"

const int TILE_WIDTH  = 32;
const int TILE_HEIGHT = 32;

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
	*/
	Tile(Recti box, bool solid, int type){
		mBox	= box;
		mSolid	= solid;
		mType	= type;
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
	/**
	*  Save the tile data to a json value
	*  @return Json::Value containing the tile data
	*/
	Json::Value Save(){
		Json::Value val;
		val["box"]   = mBox.Save();
		val["type"]  = mType;
		val["solid"] = mSolid;

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
	}

private:
	Recti mBox;
	bool mSolid;
	int mType;
};

#endif