#include <string>
#include <vector>
#include <unordered_map>
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
#include "luamodule.h"
#include "luascript.h"

//Setup the unordered_map
//const LuaScript::TRegisterLuaMap LuaScript::mRegisterLuaFuncs = LuaScript::CreateMap();

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
        mRegisterLuaFuncs = CreateMap();
		//Close currently open script if one is open
		Close();
		mFile = script;
		mL = lua_open();
		luaL_openlibs(mL);
		luabind::open(mL);
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
LuaScript::TRegisterLuaMap LuaScript::CreateMap(){
    TRegisterLuaMap map;
    map["AnimatedImage"] = LuaModule(&AnimatedImage::RegisterLua);
    map["Button"]        = LuaModule(&Button::RegisterLua);
    map["Camera"]        = LuaModule(&Camera::RegisterLua);
    map["Color"]         = LuaModule(&Color::RegisterLua);
    map["Entity"]        = LuaModule(&Entity::RegisterLua);
    map["Image"]         = LuaModule(&Image::RegisterLua);
    map["Input"]         = LuaModule(&Input::RegisterLua);
    map["Math"]          = LuaModule(&Math::RegisterLua);
    map["MotionState"]   = LuaModule(&MotionState::RegisterLua);
    map["Physics"]       = LuaModule(&Physics::RegisterLua);
    map["Rect"]          = LuaModule(&Rectf::RegisterLua);
    map["State"]         = LuaModule(&State::RegisterLua);
    map["StateManager"]  = LuaModule(&StateManager::RegisterLua);
    map["Text"]          = LuaModule(&Text::RegisterLua);
    map["Timer"]         = LuaModule(&Timer::RegisterLua);
    map["Vector2"]       = LuaModule(&Vector2f::RegisterLua);
    map["Window"]        = LuaModule(&Window::RegisterLua);

    return map;
}
bool LuaScript::RequireModule(lua_State *l, std::string module){
    //Check if the module name is in the unordered_map
    TRegisterLuaMap::const_iterator found = mRegisterLuaFuncs.find(module);
    //If the module requested exists, register it and return true
    if (found != mRegisterLuaFuncs.end()){
        mRegisterLuaFuncs.at(module).Register(l);
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
	//Open the script
	OpenScript(v["file"].asString());
}
Json::Value LuaScript::Save(){
	Json::Value v;
	v["file"] = mFile;
	return v;
}
void LuaScript::RegisterLua(){
    using namespace luabind;
    //Register the module loader with Lua
    module(mL, "LPC")[
        class_<LuaScript>("LuaScript")
            .def(constructor<>())
            .def(constructor<std::string>())
            .def("RequireModule", &LuaScript::RequireModule)

    ];
    globals(mL)["Script"] = this;
}
