#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "camera.h"
#include "entitymanager.h"
#include "tile.h"
#include "mapeditor.h"
#include "entityeditor.h"

EntityEditor::EntityEditor(){
}
EntityEditor::~EntityEditor(){
	mEntities.clear();
}
void EntityEditor::Update(){
	EntityManager::Update();
	//Will maybe overide update later, so I'm keeping it around for now
}
void EntityEditor::Register(std::shared_ptr<MapEditor> mapEditor){
	mMapEditor = mapEditor;
}
void EntityEditor::Register(TileBar* tileBar){
	mTileBar = tileBar;
}
void EntityEditor::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	//Update the mouse over before checking for clicks
	SDL_MouseMotionEvent tempEvt;
	tempEvt.x = mouseEvent.x;
	tempEvt.y = mouseEvent.y;
	EntityManager::HandleMouseEvent(tempEvt);
	//Find the object that was clicked
	for (std::shared_ptr<Entity> o : mEntities){
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
	if (mapEditor && mTileBar){
		Vector2f mousePos = Math::ToSceneSpace(mCamera, Vector2f(tempEvt.x, tempEvt.y));
		mapEditor->Insert(mousePos.x, mousePos.y, mTileBar->GetSelection());
	}
}