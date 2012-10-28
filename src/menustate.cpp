#include <memory>
#include "../externals/json/json.h"
#include "entity.h"
#include "entitymanager.h"
#include "window.h"
#include "input.h"
#include "button.h"
#include "objectbutton.h"
#include "menustate.h"
#include "statemanager.h"

MenuState::MenuState(){
}
MenuState::~MenuState(){
}
std::string MenuState::Run(){
	//Unset events from earlier
	Input::Clear();
	//Clean up any previous exit settings
	UnsetExit();

	//Setup the background destination
	Rectf bkgndPos = Math::FromSceneSpace(mCamera.get(), mCamera->SceneBox());

	Timer delta;
	delta.Start();
	while (!mExit){
		//EVENT POLLING
		Input::PollEvent();
		if (Input::Quit())
			SetExit("quit");
		if (Input::KeyDown(SDL_SCANCODE_ESCAPE))
			SetExit("quit");

		//Testing camera panning
		if (Input::KeyDown(SDL_SCANCODE_SPACE) && mCamera->Scene() == "def")
			mCamera->Pan("test");
		else if (Input::KeyDown(SDL_SCANCODE_SPACE) && mCamera->Scene() == "test")
			mCamera->Pan("def");

        //Testing why this bullshit crash happens
        if (Input::KeyDown(SDL_SCANCODE_1)){
            std::shared_ptr<Entity> e = mManager->GetEntity("quitbutton");
            std::cout << "Found entity: " << e->Name() << std::endl;
        }

		//LOGIC
		mCamera->Update();
		mManager->Update();
        //Call script's logic update
        State::LogicUpdate();

		float deltaT = delta.Restart() / 1000.f;
		mCamera->Move(deltaT);

		//RENDERING
		Window::Clear();
		Window::Draw(&mBackground, bkgndPos, &(Recti)mCamera->Box());
		mManager->Draw();

        //Call script's rendering
        State::RenderUpdate();

		//refresh window
		Window::Present();
	}
	return mExitCode;
}
void MenuState::Init(){
	mManager = std::shared_ptr<EntityManager>(new EntityManager());
	mCamera  = std::shared_ptr<Camera>(new Camera());

	mManager->Register(mCamera);
}
void MenuState::Free(){
	//We don't reset the shared pts b/c then they don't delete the object
	//when destroyed, and we get leaks
	//mCamera.reset()
	//mManager.reset();
    //Call script's Free
    State::Free();
}
Json::Value MenuState::Save(){
	Json::Value val = State::Save();
	val["background"] = mBackground.File();

	Free();
	return val;
}
void MenuState::Load(Json::Value val){
	Init();
	State::Load(val);
	mBackground.Load(val["background"].asString());

    //Load the objects
	Json::Value entities = val["entities"];
	for (int i = 0; i < entities.size(); ++i){
		//Loading object buttons
		if (entities[i]["type"].asString() == "objectbutton"){
			ObjectButton<State> *b = new ObjectButton<State>();
			b->RegisterCallBack(this, &State::SetExit, "");
			b->Load(entities[i]);
			std::shared_ptr<Entity> sObj(b);
			mManager->Register(sObj);
		}
        //Loading scripted entities
        else {
            Entity *e = new Entity();
            e->Load(entities[i]["file"].asString());
            e->Init();
            std::shared_ptr<Entity> sObj(e);
            mManager->Register(sObj);
        }
	}
    //Call the script's Init
    State::Init();
}