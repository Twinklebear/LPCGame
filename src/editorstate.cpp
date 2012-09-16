#include <string>
#include <memory>
#include "../externals/json/json.h"
#include "entity.h"
#include "entitymanager.h"
#include "entityeditor.h"
#include "window.h"
#include "input.h"
#include "timer.h"
#include "player.h"
#include "npc.h"
#include "objectbutton.h"
#include "mapeditor.h"
#include "tilebar.h"
#include "editorstate.h"

EditorState::EditorState() : mTileBar(nullptr){
}
EditorState::~EditorState(){
}
std::string EditorState::Run(){
	//Unset events from earlier
	Input::Clear();
	//Cleanup any previous exit settings
	UnsetExit();

	Timer delta;
	bool dragCamera = false;
	delta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("mIntro");
		//Check for mouse dragging of camera
		if (Input::MouseDown(MOUSE::RIGHT) && Input::MouseMotion()){
			Vector2f pan(-Input::GetMotion().xrel, -Input::GetMotion().yrel);
			mCamera->Move(pan);
		}

		//LOGIC
		mCamera->Update();
		mManager->Update();
		mUiManager->Update();

		float deltaT = delta.Restart() / 1000.f;
		mManager->Move(deltaT);
		mUiManager->Move(deltaT);

		//RENDERING
		Window::Clear();
		mMapEditor->Draw(mCamera.get());
		mManager->Draw();
		mUiManager->Draw();

		Window::Present();
	}
	return mExitCode;
}
void EditorState::Init(){
	mMapEditor = std::shared_ptr<MapEditor>(new MapEditor());
	mUiManager = std::shared_ptr<UiObjectManager>(new UiObjectManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());

	EntityEditor *objEditor  = new EntityEditor();
	mTileBar = new TileBar();
	objEditor->Register(mMapEditor);
	objEditor->Register(mTileBar);

	mManager = std::shared_ptr<EntityManager>(objEditor);
	mManager->Register(mCamera);
}
void EditorState::Free(){
	//We don't reset the shared pts b/c then they don't delete the object
	//when destroyed, and we get leaks
	//mMapEditor.reset();
	//mManager.reset();
	//mUiManager.reset();
}
Json::Value EditorState::Save(){
	Json::Value val = State::Save();
	val["map"] = mMapEditor->Save();
	///TODO: I should save/load ui's differently. Perhaps seperate files
	///that contain the different ui's? Ie. game ui, editor ui, etc.
	val["ui"]  =  mUiManager->Save();

	Free();
	return val;
}
void EditorState::Load(Json::Value val){
	Init();
	State::Load(val);
	//Generate map here if some options are passed?
	mMapEditor->Load(val["map"]);
	mMapEditor->GenerateBlank(20, 20);
	mCamera->SetSceneBox(Rectf(0, 0, mMapEditor->Box().w, mMapEditor->Box().h));
	mCamera->SetBox(Rectf(0, 0, mMapEditor->Box().w, mMapEditor->Box().h));

	//Load the ui elements
	Json::Value uiObj = val["ui"];
	for (int i = 0; i < uiObj.size(); ++i){
		//Loading object buttons
		if (uiObj[i]["type"].asString() == "objectbutton"){
			ObjectButton<State> *b = new ObjectButton<State>();
			b->RegisterCallBack(this, &State::SetExit, "");
			b->Load(uiObj[i]);
			std::shared_ptr<Entity> sObj(b);
			mUiManager->Register(sObj);
		}
		if (uiObj[i]["type"].asString() == "tilebar"){
			mTileBar->Load(uiObj[i]);
			std::shared_ptr<Entity> sObj(mTileBar);
			mUiManager->Register(sObj);
		}
	}
}