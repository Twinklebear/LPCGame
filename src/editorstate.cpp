#include <string>
#include <memory>
#include "../externals/json/json.h"
#include "gameobject.h"
#include "gameobjectmanager.h"
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
/**
*  Run the state
*  @return The next state to run, returning quit exits program
*/
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
		//mMapEditor->Draw(mCamera.get());
		mMapEditor->Draw();
		mManager->Draw();
		mUiManager->Draw();

		Window::Present();
	}
	return mExitCode;
}
/**
*  Write the state data to a Json::Value and return it so it can
*  be loaded later
*  @see State::Save for saving of inherited members
*  @return Json::Value containing the state's data
*/
Json::Value EditorState::Save(){
	Json::Value val = State::Save();
	val["map"] = mMapEditor->Save();
	//TODO: I should save/load ui's differently. Perhaps seperate files
	//that contain the different ui's? Ie. game ui, editor ui, etc.
	val["ui"]  =  mUiManager->Save();

	Free();
	return val;
}
/**
*  Load the state data from a Json::Value
*  @see State::Load for loading of inherited members
*  @param val The Json::Value containing the data to load 
*/
void EditorState::Load(Json::Value val){
	Init();
	State::Load(val);
	//Generate map here if some options are passed?
	mMapEditor->Load(val["map"]);
	mMapEditor->GenerateBlank(20, 20);
	mCamera->SetSceneBox(Rectf(0, 0, mMapEditor->Box().w, mMapEditor->Box().h));
}
///Initialize state memory
void EditorState::Init(){
	mMapEditor = std::shared_ptr<MapEditor>(new MapEditor());
	//mManager   = std::shared_ptr<GameObjectManager>(new GameObjectEditor());
	mManager   = std::shared_ptr<GameObjectManager>(new GameObjectManager());
	mUiManager = std::shared_ptr<UiObjectManager>(new UiObjectManager());
	mCamera    = std::shared_ptr<Camera>(new Camera());

	mManager->Register(mCamera);
	Input::RegisterManager(mManager);
	Input::RegisterManager(mUiManager);
}
///Free state memory
void EditorState::Free(){
	Input::FreeManagers();
	mMapEditor.reset();
	mManager.reset();
	mUiManager.reset();
}