#include <memory>
#include <initializer_list>
#include "../externals/json/json.h"
#include "entity.h"
#include "entitymanager.h"
#include "window.h"
#include "input.h"
#include "button.h"
#include "objectbutton.h"
#include "menustate.h"
#include "statemanager.h"

#include "luac/luacudataparam.h"
#include "luac/luacvector2f.h"

std::string MenuState::Run(){
	//Unset events from earlier
	Input::Clear();
	//Clean up any previous exit settings
	UnsetExit();
    
    //Call the script's Init
    State::Init();
	//Setup the background destination
	Rectf bkgndPos = Math::FromSceneSpace(mCamera, mCamera->SceneBox());

    //Testing the new initializer list call
    //Vector2f v2(15, 2);
    //Will this be ok? All these references to temporaries?
    //mScript.CallFunction("Test2", { &LuaC::Vector2fParam(&Vector2f(10, 10)), &LuaC::Vector2fParam(&v2) });

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

        //Testing shared ptrs
        if (Input::KeyDown(SDL_SCANCODE_1))
            mManager->PrintSharedPtrCount();

        //LOGIC
		mCamera->Update();
		mManager->Update();
        //Call script's logic update
        State::LogicUpdate();

		float deltaT = delta.Restart() / 1000.f;
        mManager->Move(deltaT);
		mCamera->Move(deltaT);

		//RENDERING
		Window::Clear();
		Window::Draw(&mBackground, bkgndPos, &(Recti)mCamera->Box());
		mManager->Draw();

        //Call script's rendering
        State::RenderUpdate();

		//refresh window
		Window::Present();

        Window::ShowAvgFps(false);
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
            std::cout << "about to load entity from file: " << entities[i]["file"].asString() << std::endl;
            //std::shared_ptr<Entity> e = std::make_shared<Entity>(entities[i]["file"].asString());
            std::shared_ptr<Entity> e(new Entity(entities[i]["file"].asString()));
            std::cout << "Entity loaded" << std::endl;
            mManager->Register(e);
            //Maybe pass the shared_ptr in here to be pushed onto the state?
            e->Init();
        }
	}
}