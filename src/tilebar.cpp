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
void TileBar::Draw(Camera *cam){
	//Calculate the number of tiles
	int tile_count = mTileSet->Size();

	//Calculate the required height/width of the tilebar
	int box_width = (tilesPerRow * (tileWidth + spacer)) + spacer;
	int box_height = (ceil((float)tile_count / tilesPerRow) * (tileHeight + spacer)) + spacer;
	Recti tilebarBox(xOffset,yOffset,box_width,box_height);

	//Draw background
	Window::Draw(&mImage, tilebarBox, &(Recti)mImage.Clip(0));
	
	//Draw the tiles
	std::map<std::string, Tile>::iterator it;
	std::map<std::string, Tile>::iterator begin = mTileSet->Begin();
	std::map<std::string, Tile>::iterator end = mTileSet->End();
	int i = 0;
	for (it = begin ;it != end; it++){
		int clip_x = spacer + ((i % tilesPerRow) * (tileWidth + spacer));
		int clip_y = spacer + ((i / tilesPerRow) * (tileHeight + spacer));
		Recti clipBox(clip_x, clip_y, tileWidth, tileHeight);
		Window::DrawTexture(mTileSet->Texture(it->first), clipBox + tilebarBox.Pos(), &(Recti)mTileSet->Clip(it->first));
		if (mSelectedTile == i)
			mSelectedTileName = it->first; //Set the selected tile name.
		++i;
	}	

	//Draw the selector
	int selector_x = ((mSelectedTile % tilesPerRow) * (tileWidth + spacer)) + spacer;
	int selector_y = ((mSelectedTile / tilesPerRow) * (tileHeight + spacer)) + spacer;
	Recti selector_box(selector_x,selector_y,box_width,box_height);
	Window::Draw(&mSelector, Recti((selector_box.Pos() + tilebarBox.Pos() - Vector2i(2, 2)), tileWidth + 4, tileHeight + 4));
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
		if (tile_num < mTileSet->Size())
			mSelectedTile = tile_num;
	}
}
std::string TileBar::GetSelection(){
	return mSelectedTileName;
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

	return val;
}
void TileBar::Load(Json::Value val){
	Entity::Load(val);
	mSelector.Load(val["selector"]);
	tilesPerRow = val["attributes"]["tilesPerRow"].asInt();
	spacer = val["attributes"]["spacer"].asInt();
	xOffset = val["attributes"]["xOffset"].asInt();
	yOffset = val["attributes"]["yOffset"].asInt();
	tileWidth = val["attributes"]["tileWidth"].asInt();
	tileHeight = val["attributes"]["tileHeight"].asInt();

}
