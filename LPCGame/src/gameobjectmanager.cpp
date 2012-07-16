#include <vector>
#include "map.h"
#include "gameobject.h"
#include "gameobjectmanager.h"

GameObjectManager::GameObjectManager(){
	dbg = new Debugger("Manager.txt");
}
GameObjectManager::~GameObjectManager(){
	mGameObjects.clear();
	delete dbg;
}
void GameObjectManager::Draw(){
	for (GameObject *o : mGameObjects)
		o->Draw();
}
void GameObjectManager::Update(){
	for (GameObject *o : mGameObjects)
		o->Update();
}
void GameObjectManager::Move(float deltaT){
	for (GameObject *o : mGameObjects)
		o->Move(deltaT);
}
void GameObjectManager::SetCollisionMaps(Map *map){
	//TODO: Is there a better way this can be done?
	CollisionMap collMap, entityMap;
	for (GameObject *o : mGameObjects){
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
	mGameObjects.push_back(obj);
}
CollisionMap GameObjectManager::GetEntityCollisionMap(const Rectf &target, int distance){
	//TODO: Is there a better way this can be done? Looping through the entities is kind of ok, but
	//definitely not ideal
	CollisionMap entityMap;
	for (GameObject *o : mGameObjects){
		double dist = Math::Distance(target.Pos(), o->Box().Pos());
		if (dist > 0 && dist <= distance)
			entityMap.push_back(o->Box());
	}
	return entityMap;
}
void GameObjectManager::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	Vector2f mousePos = Vector2f(mouseEvent.x, mouseEvent.y);
	dbg->Write("Manager got mouse event");
	//Find the object that was clicked
	for (GameObject *o : mGameObjects){
		if (Math::CheckCollision(mousePos, o->Box())){
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