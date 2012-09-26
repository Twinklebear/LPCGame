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
    else if (module == "Vector2"){
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
    module(mL)[
        def("LPCLoadModule", &LuaScript::RequireModule)
    ];
}
