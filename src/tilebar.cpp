#include "base.h"
#include "window.h"
#include "math.h"
#include "input.h"
#include "image.h"
#include "entity.h"
#include "tilebar.h"
#include "rect.h"

TileBar::TileBar() : mSelectedTile(0){
}
TileBar::~TileBar(){
}
void TileBar::Update(){

}
void TileBar::Move(float deltaT){

}
void TileBar::Draw(Camera *cam){

	//Calculate the required height/width of the tilebar
	int box_width = (tilesPerRow * (tileWidth + spacer)) + spacer;
	int box_height = (ceil((float)mTileImage.ClipCount() / tilesPerRow) * (tileHeight + spacer)) + spacer;
	Recti tilebarBox(xOffset,yOffset,box_width,box_height);

	//Draw background
	Window::Draw(&mImage, tilebarBox, &(Recti)mImage.Clip(0));
	
	int x = mTileImage.ClipCount();
	//Draw the tiles
	for (int i = 0; i < mTileImage.ClipCount(); ++i){
		int clip_x = spacer + ((i % tilesPerRow) * (tileWidth + spacer));
		int clip_y = spacer + ((i / tilesPerRow) * (tileHeight + spacer));
		Recti clipBox(clip_x, clip_y, tileWidth, tileHeight);
		
		Window::Draw(&mTileImage, clipBox + tilebarBox.Pos(), 
			&(Recti)mTileImage.Clip(i));
	}

	//Draw the selector
	//Need a better way to save these offsets?
	int selector_x = ((mSelectedTile % tilesPerRow) * (tileWidth + spacer)) + spacer;
	int selector_y = ((mSelectedTile / tilesPerRow) * (tileHeight + spacer)) + spacer;
	Recti selector_box(selector_x,selector_y,box_width,box_height);

	Window::Draw(&mSelector, Recti((selector_box.Pos() 
		+ tilebarBox.Pos() - Vector2i(2, 2)), tileWidth + 4, tileHeight + 4));
}
void TileBar::OnMouseUp(){
	Vector2f mousePos = Input::MousePos();

	//Calculate if an area that could possess a tile was hit
	bool row_hit = ((int)mousePos.y - yOffset) % (tileHeight + spacer) > spacer;
	bool coloumn_hit = ((int)mousePos.x - xOffset) % (tileWidth + spacer) > spacer;

	if (row_hit && coloumn_hit){
		//Calculate which tile was hit
		int row_selected = ((int)mousePos.y - yOffset) / (tileHeight + spacer);
		int coloumn_selected = ((int)mousePos.x - xOffset) / (tileWidth + spacer);
		
		//Calculate the exact tile number
		int tile_num = coloumn_selected + row_selected * tilesPerRow;

		//If the tile exists, set it to selected
		if (tile_num < mTileImage.ClipCount())
			mSelectedTile = tile_num;
	}
}
Tile TileBar::GetSelection(){
	/* TODO   AGHHHGHGHHHGH
	* This works but as of right now there is 
	* no tile system since I made the one here
	* obsolete. 
    * 
	* No 'Solid' or 'Name' is currently in the software
	*/
	Tile x(Recti(0,0,0,0),mSelectedTile,false,"");
	return x;
}
Json::Value TileBar::Save(){
	Json::Value val = Entity::Save();
	val["type"] = "tilebar";
	val["attributes"]["tilesPerRow"] = tilesPerRow;
	val["attributes"]["spacer"] = spacer;
	val["attributes"]["xOffset"] = xOffset;
	val["attributes"]["yOffset"] = yOffset;
	val["attributes"]["tileWidth"] = tileWidth;
	val["attributes"]["tileHeight"] = tileHeight;
	val["selector"]	= mSelector.Save();
	val["tiles"]["image"] = mTileImage.Save();

	return val;
}
void TileBar::Load(Json::Value val){
	Entity::Load(val);
	mSelector.Load(val["selector"]);
	mTileImage.Load(val["tiles"]["image"]);
	tilesPerRow = val["attributes"]["tilesPerRow"].asInt();
	spacer = val["attributes"]["spacer"].asInt();
	xOffset = val["attributes"]["xOffset"].asInt();
	yOffset = val["attributes"]["yOffset"].asInt();
	tileWidth = val["attributes"]["tileWidth"].asInt();
	tileHeight = val["attributes"]["tileHeight"].asInt();

}
