#include <vector>
#include "map.h"
#include "gameobject.h"
#include "gameobjectmanager.h"

GameObjectManager::GameObjectManager(){}
GameObjectManager::~GameObjectManager(){
	mGameObjects.clear();
}
void GameObjectManager::Draw(){
	for (GameObject *o : mGameObjects)
		o->Draw();
}
void GameObjectManager::Move(float deltaT){
	for (GameObject *o : mGameObjects)
		o->Move(deltaT);
}
void GameObjectManager::SetCollisionMaps(Map *map){
	for (GameObject *o : mGameObjects)
		o->SetCollisionMap(map->GetLocalCollisionMap(o->Box()));
}
void GameObjectManager::Register(GameObject *obj){
	mGameObjects.push_back(obj);
}