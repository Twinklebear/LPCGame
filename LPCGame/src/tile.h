#ifndef TILE_H
#define TILE_H

#include "json/json.h"
#include "rect.h"

const int TILE_WIDTH  = 32;
const int TILE_HEIGHT = 32;

/*
 * Tile: a simple map tile
*/
class Tile{
public:
	Tile(){}
	Tile(Recti box, bool solid, int type){
		mBox	= box;
		mSolid	= solid;
		mType	= type;
	}
	//Setters & getters
	Recti Box() const{
		return mBox;
	}
	bool Solid() const{
		return mSolid;
	}
	int Type() const{
		return mType;
	}
	void SetBox(Recti box){
		mBox = box;
	}
	void SetSolid(bool solid){
		mSolid = solid;
	}
	void SetType(int type){
		mType = type;
	}
	/*
	*  Save the tile data to a json value
	*  @returns: The Json::Value containing the tile data
	*/
	Json::Value Save(){
		Json::Value val;
		val["box"]   = mBox.Save();
		val["type"]  = mType;
		val["solid"] = mSolid;

		return val;
	}
	/*
	*  Load the tile from a Json::Value
	*  @param val: The Json::Value to load from
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