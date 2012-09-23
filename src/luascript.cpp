#include <string>
#include <vector>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "animatedimage.h"
#include "button.h"
#include "camera.h"
#include "color.h"
#include "entity.h"
#include "input.h"
#include "math.h"
#include "motionstate.h"
#include "physics.h"
#include "rect.h"
#include "state.h"
#include "statemanager.h"
#include "text.h"
#include "timer.h"
#include "vectors.h"
#include "window.h"
#include "luascript.h"

LuaScript::LuaScript() : mL(nullptr), mFile(""){
}
LuaScript::LuaScript(std::string script) : mL(nullptr), mFile(""){
	OpenScript(script);
}
LuaScript::~LuaScript(){
	Close();
}
void LuaScript::OpenScript(std::string script){
	//If the new script name is valid, open it
	if (script != ""){
		//Close currently open script if one is open
		Close();
		mFile = script;
		mL = lua_open();
		luaL_openlibs(mL);
		luabind::open(mL);
		LoadModules();
        //insert package.loader function here
        RegisterLua();
		luaL_dofile(mL, mFile.c_str());
	}
}
void LuaScript::Close(){
	if (Open()){
		lua_close(mL);
		mL = nullptr;
	}
}
void LuaScript::LoadModules(){
	for (int m : mModules)
		LoadModule(m);
    ///Override to load all modules
    /*
    for (int i = 0; i <= MODULE::WINDOW; ++i){
        std::cout << i << std::endl;
        LoadModule(i);
    }
    */
}
void LuaScript::LoadModule(int module){
	//Make sure the lua state is valid
	if (!Open())
		return;
	//Find the desired module and register it
	switch(module){
		case MODULE::ANIMATED_IMAGE:
			AnimatedImage::RegisterLua(mL);
			break;
		case MODULE::BUTTON:
			Button::RegisterLua(mL);
			break;
		case MODULE::CAMERA:
			Camera::RegisterLua(mL);
			break;
		case MODULE::COLOR:
			Color::RegisterLua(mL);
			break;
		case MODULE::ENTITY:
			Entity::RegisterLua(mL);
			break;
		case MODULE::IMAGE:
			Image::RegisterLua(mL);
			break;
		case MODULE::INPUT:
			Input::RegisterLua(mL);
			break;
		case MODULE::MATH:
			Math::RegisterLua(mL);
			break;
		case MODULE::MOTION_STATE:
			MotionState::RegisterLua(mL);
			break;
		case MODULE::PHYSICS:
			Physics::RegisterLua(mL);
			break;
		case MODULE::RECT:
			Rect<int>::RegisterLua(mL);
			break;
		case MODULE::STATE:
			State::RegisterLua(mL);
			break;
		case MODULE::STATE_MANAGER:
			StateManager::RegisterLua(mL);
			break;
		case MODULE::TEXT:
			Text::RegisterLua(mL);
			break;
		case MODULE::TIMER:
			Timer::RegisterLua(mL);
			break;
		case MODULE::VECTOR:
			Vector2<float>::RegisterLua(mL);
			break;
		case MODULE::WINDOW:
			Window::RegisterLua(mL);
			break;
		default:
			break;
	}
}
void LuaScript::RequireModule(std::string module){
    if (module == "AnimatedImage")
        LoadModule(MODULE::ANIMATED_IMAGE);
}
lua_State* LuaScript::Get(){
	return mL;
}
std::string LuaScript::File(){
	return mFile;
}
bool LuaScript::Open(){
	return (mL != nullptr);
}
void LuaScript::Load(Json::Value v){
	//Get the list of modules
	for (int i = 0; i < v["modules"].size(); ++i)
		mModules.push_back(v["modules"][i].asInt());
	//Open the script
	OpenScript(v["file"].asString());
}
Json::Value LuaScript::Save(){
	Json::Value v;
	v["file"] = mFile;
	//Save the module list
	for (int i = 0; i < mModules.size(); ++i)
		v["modules"][i] = mModules.at(i);

	return v;
}
void LuaScript::RegisterLua(){
    using namespace luabind;

    module(mL)[
        def("RequireModule", &LuaScript::RequireModule)
    ];

    //execute some lua code to set this function into package.loaders
    luaL_dostring(mL, "table.insert(package.loaders, 2, RequireModule");
    luaL_dostring(mL, "print('Test of adding a package loader function')");
}
