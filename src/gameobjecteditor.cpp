#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "camera.h"
#include "gameobjectmanager.h"
#include "tile.h"
#include "mapeditor.h"
#include "gameobjecteditor.h"

GameObjectEditor::GameObjectEditor(){

}
GameObjectEditor::~GameObjectEditor(){
	mGameObjects.clear();
}
void GameObjectEditor::Draw(){
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->Draw(mCamera.get());
	}
}
void GameObjectEditor::Update(){
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->Update();
	}
}
void GameObjectEditor::Move(float deltaT){
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->Move(deltaT);
	}
}
void GameObjectEditor::Register(std::shared_ptr<MapEditor> mapEditor){
	mMapEditor = mapEditor;
}
void GameObjectEditor::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	//Update the mouse over before checking for clicks
	SDL_MouseMotionEvent tempEvt;
	tempEvt.x = mouseEvent.x;
	tempEvt.y = mouseEvent.y;
	HandleMouseEvent(tempEvt);
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
	std::shared_ptr<MapEditor> s = mMapEditor.lock();
	if (s){
		Vector2f mousePos = Math::ToSceneSpace(mCamera.get(), Vector2f(tempEvt.x, tempEvt.y));
		Tile temp(Recti(mousePos.x, mousePos.y, 32, 32), 5, true);
		s->Insert(mousePos.x, mousePos.y, temp);
	}
}
void GameObjectEditor::HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent){
	Vector2f mousePos = Math::ToSceneSpace(mCamera.get(), Vector2f(mouseEvent.x, mouseEvent.y));
	//Find the object that has the mouse over it
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->CheckMouseOver(mousePos);
	}
}