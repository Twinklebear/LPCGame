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
void TileBar::Draw(std::weak_ptr<Camera> cam){
	//Calculate the number of tiles
	int tile_count = mTileSet->Size();

	//Calculate the required height/width of the tilebar
	int box_width = (tilesPerRow * (tileWidth + spacer)) + spacer;
	int box_height = (ceil((float)tile_count / tilesPerRow) * (tileHeight + spacer)) + spacer;
	Recti tilebarBox(xOffset,yOffset,box_width,box_height);

	//Draw background
	Window::Draw(&mImage, tilebarBox, &(Recti)mImage.Clip(0));
	
	//Draw the tiles
	mTileSetMap::iterator it;
	mTileSetMap::iterator begin = mTileSet->Begin();
	mTileSetMap::iterator end = mTileSet->End();
	int i = 0;
	for (it = begin ;it != end; it++){
		int clip_x = spacer + ((i % tilesPerRow) * (tileWidth + spacer));
		int clip_y = spacer + ((i / tilesPerRow) * (tileHeight + spacer));
		Recti clipBox(clip_x, clip_y, tileWidth, tileHeight);
		Window::DrawTexture(mTileSet->Texture(it->first), clipBox + tilebarBox.pos, &(Recti)mTileSet->Clip(it->first));
		if (mSelectedTile == i)
			mSelectedTileName = it->first; //Set the selected tile name.
		++i;
	}	

	Color white(255,255,255);
    //Can we cache these? Creating a text object is not so fast.
	Text name(mSelectedTileName, "../res/fonts/SourceSansPro-Regular.ttf", white, 20);
	Text solid(mTileSet->Solid(mSelectedTileName) ? "Solid: True" : "Solid: False", "../res/fonts/SourceSansPro-Regular.ttf", white, 14);
	Text file(mTileSet->File(mSelectedTileName), "../res/fonts/SourceSansPro-Regular.ttf", white, 14);

	Rectf asdf(xOffset, yOffset + box_height, 200, 200);
	Rectf asdf2(xOffset, yOffset + box_height + 20, 200, 200);
	Rectf asdf3(xOffset, yOffset + box_height + 34, 200, 200);
	Window::Draw(&name, asdf);
	Window::Draw(&solid, asdf2);
	Window::Draw(&file, asdf3);

	//Draw the selector
	int selector_x = ((mSelectedTile % tilesPerRow) * (tileWidth + spacer)) + spacer;
	int selector_y = ((mSelectedTile / tilesPerRow) * (tileHeight + spacer)) + spacer;
	Recti selector_box(selector_x,selector_y,box_width,box_height);
	Window::Draw(&mSelector, Recti((selector_box.pos + tilebarBox.pos - Vector2i(2, 2)), tileWidth + 4, tileHeight + 4));
}
void TileBar::OnMouseDown(){
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
Json::Value TileBar::Save() const{
	Json::Value val = Entity::Save();
	val["type"] = "tilebar";
	val["attributes"]["tilesPerRow"] = tilesPerRow;
	val["attributes"]["spacer"] = spacer;
	val["attributes"]["xOffset"] = xOffset;
	val["attributes"]["yOffset"] = yOffset;
	val["attributes"]["tileWidth"] = tileWidth;
	val["attributes"]["tileHeight"] = tileHeight;
	val["selector"]	= mSelector.File();

	return val;
}
void TileBar::Load(Json::Value val){
	Entity::Load(val);
	mSelector.Load(val["selector"].asString());
	tilesPerRow = val["attributes"]["tilesPerRow"].asInt();
	spacer = val["attributes"]["spacer"].asInt();
	xOffset = val["attributes"]["xOffset"].asInt();
	yOffset = val["attributes"]["yOffset"].asInt();
	tileWidth = val["attributes"]["tileWidth"].asInt();
	tileHeight = val["attributes"]["tileHeight"].asInt();

}
