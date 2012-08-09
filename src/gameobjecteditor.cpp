#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "camera.h"
#include "gameobjectmanager.h"
#include "tile.h"
#include "mapeditor.h"
#include "gameobjecteditor.h"

#include "debugger.h"

GameObjectEditor::GameObjectEditor(){

}
GameObjectEditor::~GameObjectEditor(){
	mGameObjects.clear();
}
void GameObjectEditor::Update(){
	GameObjectManager::Update();
	//Will maybe overide update later, so I'm keeping it around for now
}
void GameObjectEditor::Register(std::shared_ptr<MapEditor> mapEditor){
	mMapEditor = mapEditor;
}
void GameObjectEditor::Register(TileBar* tileBar){
	mTileBar = tileBar;
}
void GameObjectEditor::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	//Update the mouse over before checking for clicks
	SDL_MouseMotionEvent tempEvt;
	tempEvt.x = mouseEvent.x;
	tempEvt.y = mouseEvent.y;
	GameObjectManager::HandleMouseEvent(tempEvt);
	//Find the object that was clicked
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()) && o->GetMouseOver()){
			switch (mouseEvent.type){
				case SDL_MOUSEBUTTONDOWN:
					o->OnMouseDown();
					break;
				case SDL_MOUSEBUTTONUP:
					o->OnMouseUp();
					break;
				default:
					break;
			}
		}
	}
	//Place a tile on map
	std::shared_ptr<MapEditor> mapEditor = mMapEditor.lock();
	if (mTileBar == nullptr)
		Debugger::Write("Tile bar is nullptr!");
	if (mapEditor && mTileBar){
		Debugger::Write("Placing a tile");
		Vector2f mousePos = Math::ToSceneSpace(mCamera.get(), Vector2f(tempEvt.x, tempEvt.y));
		mapEditor->Insert(mousePos.x, mousePos.y, mTileBar->GetSelection());
	}
}