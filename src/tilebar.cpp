#include "base.h"
#include "window.h"
#include "math.h"
#include "input.h"
#include "image.h"
#include "entity.h"
#include "tilebar.h"

TileBar::TileBar() : mSelectedTile(0){
}
TileBar::~TileBar(){
}
void TileBar::Update(){

}
void TileBar::Move(float deltaT){

}
void TileBar::Draw(Camera *cam){
	//Draw background
	Window::Draw(&mImage, mPhysics.Box(), &(Recti)mImage.Clip(0));
	//Draw the tiles
	for (int i = 0; i < mTiles.size(); ++i){
		Window::Draw(&mTileImage, mTiles.at(i).Box() + mPhysics.Box().Pos(), 
			&(Recti)mTileImage.Clip(mTiles.at(i).Type()));
	}
	//Draw the selector
	//Need a better way to save these offsets?
	Window::Draw(&mSelector, Recti((mTiles.at(mSelectedTile).Box().Pos() 
		+ mPhysics.Box().Pos() - Vector2i(2, 2)), 36, 36));
}
void TileBar::OnMouseUp(){
	Vector2f mousePos = Input::MousePos();
	//On mouse up select the tile that's highlighted
	for (int i = 0; i < mTiles.size(); ++i){
		if (Math::CheckCollision(mousePos, (mTiles.at(i).Box() + mPhysics.Box().Pos()))){
			mSelectedTile = i;
			return;
		}
	}
}
Tile TileBar::GetSelection(){
	return mTiles.at(mSelectedTile);
}
Json::Value TileBar::Save(){
	Json::Value val = Entity::Save();
	val["selector"]	= mSelector.Save();
	val["tiles"]["image"] = mTileImage.Save();
	val["type"] = "tilebar";
	//Save the tiles
	for (int i = 0; i < mTiles.size(); ++i){
		val["tiles"]["list"][i] = mTiles.at(i).Save();
	}
	return val;
}
void TileBar::Load(Json::Value val){
	Entity::Load(val);
	mSelector.Load(val["selector"]);
	mTileImage.Load(val["tiles"]["image"]);
	//Load up the tile positions
	for (int i = 0; i < val["tiles"]["list"].size(); ++i){
		Tile tempTile;
		tempTile.Load(val["tiles"]["list"][i]);
		mTiles.push_back(tempTile);
	}
}
