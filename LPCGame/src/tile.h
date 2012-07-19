#ifndef TILE_H
#define TILE_H

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

		//Debugging
	bool collMapDebug;

private:
	Recti mBox;
	bool mSolid;
	int mType;
};

#endif