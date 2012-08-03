#include <string>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
#include "gameobjecteditor.h"
#include "window.h"
#include "input.h"
#include "timer.h"
#include "player.h"
#include "npc.h"
#include "objectbutton.h"
#include "mapeditor.h"
#include "editorstate.h"

EditorState::EditorState(){
}
EditorState::~EditorState(){
}
std::string EditorState::Run(){
	//Unset quits from earlier
	Input::ClearQuit();
	//Cleanup any previous exit settings
	UnsetExit();

	Timer delta;
	delta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("mIntro");

		///LOGIC
		mCamera->Update();
		mManager->Update();
		mUiManager->Update();

		float deltaT = delta.GetTicks() / 1000.f;
		mManager->Move(deltaT);
		mUiManager->Move(deltaT);

		delta.Start();

		///RENDERING
		Window::Clear();
		mMapEditor->Draw(mCamera.get());
		mManager->Draw();
		mUiManager->Draw();

		Window::Present();
	}
	Input::ClearKeys();

	return mExitCode;
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
			std::shared_ptr<GameObject> sObj(b);
			mUiManager->Register(sObj);
		}
	}
}
void EditorState::Init(){
	mMapEditor = std::shared_ptr<MapEditor>(new MapEditor());
	mUiManager = std::shared_ptr<UiObjectManager>(new UiObjectManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());

	GameObjectEditor *objEditor  = new GameObjectEditor();
	objEditor->Register(mMapEditor);
	//objEditor->Register(mCamera); //Why doesn't this work?

	mManager = std::shared_ptr<GameObjectManager>(objEditor);
	mManager->Register(mCamera);

	Input::RegisterManager(mManager);
	Input::RegisterManager(mUiManager);
}
void EditorState::Free(){
	Input::FreeManagers();
	mMapEditor.reset();
	mManager.reset();
	mUiManager.reset();
}