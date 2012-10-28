#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "input.h"
#include "map.h"
#include "entity.h"
#include "entitymanager.h"

EntityManager::EntityManager()
	: mCamera(nullptr)
{}
EntityManager::~EntityManager(){
	mEntities.clear();
}
void EntityManager::Draw(){
	for (std::shared_ptr<Entity> o : mEntities){
        if (o->Render()){
            //Check for Ui/Non-Ui elements
            if (o->IsUiElement())
                o->Draw();
		    else if (mCamera->InCamera(o->Box()))
    			o->Draw(mCamera.get());
        }
	}
}
void EntityManager::Update(){
	//Check for mouse events
	CheckMouseEvents();
	//Call object's update functions
	for (std::shared_ptr<Entity> o : mEntities){
        //Check for Ui/Non-Ui elements
        if (o->IsUiElement())
            o->Update();
		else if (mCamera->InCamera(o->Box()))
    		o->Update();
	}
}
void EntityManager::Move(float deltaT){
	for (std::shared_ptr<Entity> o : mEntities){
		//Check for Ui/Non-Ui elements
        if (o->IsUiElement())
            o->Move(deltaT);
		else if (mCamera->InCamera(o->Box()))
    		o->Move(deltaT);
	}
}
void EntityManager::SetCollisionMaps(Map *map){
	//TODO: Is there a better way this can be done?
	CollisionMap collMap, entityMap;
	for (std::shared_ptr<Entity> o : mEntities){
		if (!o->IsUiElement() && mCamera->InCamera(o->Box())){
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
void EntityManager::Register(std::shared_ptr<Entity> obj){
	mEntities.push_back(obj);
}
void EntityManager::Register(std::shared_ptr<Camera> camera){
	mCamera.reset();
	mCamera = camera;
}
CollisionMap EntityManager::GetEntityCollisionMap(const Rectf &target, int distance){
	//TODO: Is there a better way this can be done? Looping through the entities is kind of ok, but
	//definitely not ideal
	CollisionMap entityMap;
	for (std::shared_ptr<Entity> o : mEntities){
		if (!o->IsUiElement() && mCamera->InCamera(o->Box())){
			double dist = Math::Distance(target.Pos(), o->Box().Pos());
			if (dist > 0 && dist <= distance)
				entityMap.push_back(o->Box());
		}
	}
	return entityMap;
}
void EntityManager::CheckMouseEvents(){
	//Check for mouse motion
	if (Input::MouseMotion())
		HandleMouseEvent(Input::GetMotion());
	//Check for clicks
	if (Input::MouseClick(MOUSE::LEFT))
		HandleMouseEvent(Input::GetClick());
}
void EntityManager::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	//Update the mouse over before checking for clicks
	SDL_MouseMotionEvent tempEvt;
	tempEvt.x = mouseEvent.x;
	tempEvt.y = mouseEvent.y;
	HandleMouseEvent(tempEvt);
	//Find the object that was clicked
	for (std::shared_ptr<Entity> o : mEntities){
		if ((o->IsUiElement() || mCamera->InCamera(o->Box())) && o->GetMouseOver()){
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
void EntityManager::HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent){
	//Vector2f mousePos = Math::ToSceneSpace(mCamera.get(), Vector2f(mouseEvent.x, mouseEvent.y));
    Vector2f mousePos(mouseEvent.x, mouseEvent.y);
	//Find the object that has the mouse over it
	for (std::shared_ptr<Entity> o : mEntities){
        //Check for Ui/Non-Ui elements
        if (o->IsUiElement()){
            if (Math::CheckCollision(mousePos, o->Box()) && !o->GetMouseOver())
                o->OnMouseEnter();
            else if (!Math::CheckCollision(mousePos, o->Box()) && o->GetMouseOver())
                o->OnMouseExit();
        }
        //If it's an object in the scene we must bump the collision box into
        //window space to check against the window space mouse pos
		else if (mCamera->InCamera(o->Box())){
            Rectf box = Math::FromSceneSpace(mCamera.get(), o->Box());
    		if (Math::CheckCollision(mousePos, box) && !o->GetMouseOver())
                o->OnMouseEnter();
            else if (!Math::CheckCollision(mousePos, box) && o->GetMouseOver())
                o->OnMouseExit();
        }
	}
}
Json::Value EntityManager::Save(){
	Json::Value val;
	//Run through and save all the game objects
	for (int i = 0; i < mEntities.size(); ++i){
		val[i] = (mEntities.at(i))->Save();
	}
	return val;
}