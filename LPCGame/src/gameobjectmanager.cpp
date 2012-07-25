#include <vector>
#include <memory>
#include "json/json.h"
#include "map.h"
#include "gameobject.h"
#include "gameobjectmanager.h"

GameObjectManager::GameObjectManager(){}
GameObjectManager::~GameObjectManager(){
	//for (GameObject *o : mGameObjects)
	//	delete o;
	mGameObjects.clear();
}
void GameObjectManager::Draw(){
	for (std::shared_ptr<GameObject> o : mGameObjects)
		o->Draw();
}
void GameObjectManager::Update(){
	for (std::shared_ptr<GameObject> o : mGameObjects)
		o->Update();
}
void GameObjectManager::Move(float deltaT){
	for (std::shared_ptr<GameObject> o : mGameObjects)
		o->Move(deltaT);
}
void GameObjectManager::SetCollisionMaps(Map *map){
	//TODO: Is there a better way this can be done?
	CollisionMap collMap, entityMap;
	for (std::shared_ptr<GameObject> o : mGameObjects){
		CollisionMap collMap = map->GetCollisionMap(o->Box());
		CollisionMap entityMap = this->GetEntityCollisionMap(o->Box());
		for (Recti r : entityMap)
			collMap.push_back(r);
		o->SetCollisionMap(collMap);

		collMap.clear();
		entityMap.clear();
	}
}
void GameObjectManager::Register(GameObject *obj){
	std::shared_ptr<GameObject> shObj(obj);
	mGameObjects.push_back(shObj);
}
void GameObjectManager::Register(std::shared_ptr<GameObject> obj){
	mGameObjects.push_back(obj);
}
CollisionMap GameObjectManager::GetEntityCollisionMap(const Rectf &target, int distance){
	//TODO: Is there a better way this can be done? Looping through the entities is kind of ok, but
	//definitely not ideal
	CollisionMap entityMap;
	for (std::shared_ptr<GameObject> o : mGameObjects){
		double dist = Math::Distance(target.Pos(), o->Box().Pos());
		if (dist > 0 && dist <= distance)
			entityMap.push_back(o->Box());
	}
	return entityMap;
}
void GameObjectManager::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	//Update the mouse over
	//TODO: Fix this so it works on starting new game too, a mouse over check should be done
	SDL_MouseMotionEvent tempEvt;
	tempEvt.x = mouseEvent.x;
	tempEvt.y = mouseEvent.y;
	HandleMouseEvent(tempEvt);
	//Find the object that was clicked
	for (std::shared_ptr<GameObject> o : mGameObjects){
		if (o->GetMouseOver()){
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
	Vector2f mousePos = Vector2f(mouseEvent.x, mouseEvent.y);
	//Find the object that was clicked
	for (std::shared_ptr<GameObject> o : mGameObjects){
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
void GameObjectManager::Load(Json::Value value){

}