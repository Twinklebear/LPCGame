#include <vector>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "uiobjectmanager.h"

UiObjectManager::UiObjectManager(){
}
UiObjectManager::~UiObjectManager(){
}
void UiObjectManager::Draw(){
	for (std::shared_ptr<GameObject> o : mGameObjects)
		o->Draw();
}
void UiObjectManager::Update(){
	//Check for mouse events
	CheckMouseEvents();
	//Update objects
	for (std::shared_ptr<GameObject> o : mGameObjects)
		o->Update();
}
void UiObjectManager::Move(float deltaT){
	for (std::shared_ptr<GameObject> o : mGameObjects)
		o->Move(deltaT);
}
void UiObjectManager::HandleMouseEvent(const SDL_MouseButtonEvent &mouseEvent){
	//Update the mouse over before checking for clicks
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
void UiObjectManager::HandleMouseEvent(const SDL_MouseMotionEvent &mouseEvent){
	Vector2f mousePos = Vector2f(mouseEvent.x, mouseEvent.y);
	//Find the object that has the mouse over it
	for (std::shared_ptr<GameObject> o : mGameObjects){
			o->CheckMouseOver(mousePos);
	}
}