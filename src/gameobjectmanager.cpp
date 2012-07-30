#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "map.h"
#include "gameobject.h"
#include "gameobjectmanager.h"

GameObjectManager::GameObjectManager(){}
GameObjectManager::~GameObjectManager(){
	mGameObjects.clear();
}
void GameObjectManager::Draw(){
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->Draw(mCamera.get());
	}
}
void GameObjectManager::Update(){
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->Update();
	}
}
void GameObjectManager::Move(float deltaT){
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->Move(deltaT);
	}
}
void GameObjectManager::SetCollisionMaps(Map *map){
	//TODO: Is there a better way this can be done?
	CollisionMap collMap, entityMap;
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box())){
			CollisionMap collMap = map->GetCollisionMap(o->Box());
			CollisionMap entityMap = this->GetEntityCollisionMap(o->Box());
			for (Recti r : entityMap)
				collMap.push_back(r);

			o->SetCollisionMap(collMap);
			collMap.clear();
			entityMap.clear();
		}
	}
}
void GameObjectManager::Register(std::shared_ptr<GameObject> obj){
	mGameObjects.push_back(obj);
}
void GameObjectManager::Register(std::shared_ptr<Camera> camera){
	mCamera.reset();
	mCamera = camera;
}
CollisionMap GameObjectManager::GetEntityCollisionMap(const Rectf &target, int distance){
	//TODO: Is there a better way this can be done? Looping through the entities is kind of ok, but
	//definitely not ideal
	CollisionMap entityMap;
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box())){
			double dist = Math::Distance(target.Pos(), o->Box().Pos());
			if (dist > 0 && dist <= distance)
				entityMap.push_back(o->Box());
		}
	}
	return entityMap;
}
void GameObjectManager::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
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
}
void GameObjectManager::HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent){
	Vector2f mousePos = Math::ToSceneSpace(mCamera.get(), Vector2f(mouseEvent.x, mouseEvent.y));
	//Find the object that was clicked
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (mCamera->InCamera(o->Box()))
			o->CheckMouseOver(mousePos);
	}
}
Json::Value GameObjectManager::Save(){
	Json::Value val;
	//Run through and save all the game objects
	for (int i = 0; i < mGameObjects.size(); ++i){
		val[i] = mGameObjects.at(i)->Save();
	}
	return val;
}