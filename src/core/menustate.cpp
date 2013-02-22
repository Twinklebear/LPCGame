#include <memory>
#include "external/json/json.h"
#include "entity.h"
#include "entitymanager.h"
#include "window.h"
#include "input.h"
#include "button.h"
#include "objectbutton.h"
#include "menustate.h"
#include "statemanager.h"

#include "luac/luaref.h"

std::string MenuState::Run(){
	//Unset events from earlier
	Input::Clear();
	//Clean up any previous exit settings
	UnsetExit();
    
    //Call the script's Init
    State::Init();

    //Testing LuaRef function calling
    LuaC::LuaRef refTest(mScript.Get(), "RefTest");
    mScript.FunctionInterface()->CallFunction<void>(refTest, "test ok!");
    mScript.FunctionInterface()->CallFunction<void>(refTest, "test ok!");

    //Testing usage of table references and calling self
    mScript.Reference("testTable");
    mScript.Reference("testTable", "speak");
    mScript.FunctionInterface()->CallFunction<void>(mScript.GetReference("speak"),
        mScript.GetReference("testTable"));

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
        //Call state's rendering for background effects
        State::RenderUpdate();
		mManager->Draw();

		//refresh window
		Window::Present();

        Window::ShowAvgFps(false);
	}
	return mExitCode;
}
void MenuState::Init(){
	mManager = std::make_shared<EntityManager>();
	mCamera  = std::make_shared<Camera>();

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
	Free();
	return val;
}
void MenuState::Load(Json::Value val){
	Init();
	State::Load(val);

    //Load the objects
	Json::Value entities = val["entities"];
	for (int i = 0; i < entities.size(); ++i){
        std::shared_ptr<Entity> e = std::make_shared<Entity>(entities[i]["file"].asString());
        mManager->Register(e);
        e->Init(e);
	}
}