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
bool LuaScript::RequireModule(lua_State *l, std::string module){
    std::cout << "Requiring module: " << module << std::endl;
    if (module == "AnimatedImage"){
        AnimatedImage::RegisterLua(l);
        return true;
    }
    else if (module == "Button"){
        Button::RegisterLua(l);
        return true;
    }
    else if (module == "Camera"){
        Camera::RegisterLua(l);
        return true;
    }
    else if (module == "Color"){
        Color::RegisterLua(l);
        return true;
    }
    else if (module == "Entity"){
        Entity::RegisterLua(l);
        return true;
    }
    else if (module == "Image"){
        Image::RegisterLua(l);
        return true;
    }
    else if (module == "Input"){
        Input::RegisterLua(l);
        return true;
    }
    else if (module == "Math"){
        Math::RegisterLua(l);
        return true;
    }
    else if (module == "MotionState"){
        MotionState::RegisterLua(l);
        return true;
    }
    else if (module == "Physics"){
        Physics::RegisterLua(l);
        return true;
    }
    else if (module == "Rect"){
        Rectf::RegisterLua(l);
        return true;
    }
    else if (module == "State"){
        State::RegisterLua(l);
        return true;
    }
    else if (module == "StateManager"){
        StateManager::RegisterLua(l);
        return true;
    }
    else if (module == "Text"){
        Text::RegisterLua(l);
        return true;
    }
    else if (module == "Timer"){
        Timer::RegisterLua(l);
        return true;
    }
    else if (module == "Vector"){
        Vector2f::RegisterLua(l);
        return true;
    }
    else if (module == "Window"){
        Window::RegisterLua(l);
        return true;
    }
    return false;
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
    //Register the module loader with Lua
    module(mL)[
        def("LPCLoadModule", &LuaScript::RequireModule)
    ];
}
