#include <string>
#include <fstream>
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

//Setup the unordered_map
const LuaScript::TRegisterLuaMap LuaScript::mRegisterLuaFunc = LuaScript::CreateMap();

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
        AddLoaders();
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
    map["AnimatedImage"] = &AnimatedImage::RegisterLua;
    map["Button"]        = &Button::RegisterLua;
    map["Camera"]        = &Camera::RegisterLua;
    map["Color"]         = &Color::RegisterLua;
    map["Entity"]        = &Entity::RegisterLua;
    map["Image"]         = &Image::RegisterLua;
    map["Input"]         = &Input::RegisterLua;
    map["Math"]          = &Math::RegisterLua;
    map["MotionState"]   = &MotionState::RegisterLua;
    map["Physics"]       = &Physics::RegisterLua;
    map["Rect"]          = &Rectf::RegisterLua;
    map["State"]         = &State::RegisterLua;
    map["StateManager"]  = &StateManager::RegisterLua;
    map["Text"]          = &Text::RegisterLua;
    map["Timer"]         = &Timer::RegisterLua;
    map["Vector2"]       = &Vector2f::RegisterLua;
    map["Window"]        = &Window::RegisterLua;
    return map;
}
int LuaScript::RequireModule(lua_State *l){
    //Get the module name
    std::string module = lua_tostring(l, 1);
    //Check if the module name is in the unordered_map
    TRegisterLuaMap::const_iterator found = mRegisterLuaFunc.find(module);
    //If the module requested exists push the registration function on the stack
    if (found != mRegisterLuaFunc.end()){
        lua_pushcfunction(l, mRegisterLuaFunc.at(module));
    }
    else {
        std::string err = "\n\tRequireModule Error: failed to find: " + module + "\n";
        std::cout << err << std::endl;
        lua_pushstring(l, err.c_str());
    }
    return 1;
}
int LuaScript::RequireScript(lua_State *l){
    //Get the script name and check if it's an engine script
    //ie. the name is scripts/*
    std::string script = lua_tostring(l, 1);
    if (script.substr(0, 7) == "scripts"){
        std::string scriptFile = "../res/" + script;
        //If it exists push DoScript onto the stack, if not error
        std::ifstream checkFile(scriptFile.c_str());
        if (checkFile.good()){
            checkFile.close();
            //push the full path back onto the stack for DoScript to use
            lua_pushstring(l, scriptFile.c_str());
            lua_pushcfunction(l, LuaScript::DoScript);
        }
        else {
            std::string err = "\n\tRequireScript Error: Failed to find" + scriptFile + "\n";
            std::cout << err << std::endl;
            lua_pushstring(l, err.c_str());
        }
    }
    else {
        std::string err = "\n\tRequireScript Error: " + script + " not a script\n";
        lua_pushstring(l, err.c_str());
    }
    return 1;
}
int LuaScript::DoScript(lua_State *l){
    //Get the filename and dofile
    std::string script = lua_tostring(l, 0);
    luaL_dofile(l, script.c_str());
    return 1;
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
void LuaScript::AddModuleLoader(){
    //Get the packages table
    lua_getfield(mL, LUA_GLOBALSINDEX, "package");
    //Get the loaders table
    lua_getfield(mL, -1, "loaders");
    //Get rid of the packages table
    lua_remove(mL, -2);

    //Count # of loaders
    int numLoaders = 0;
    lua_pushnil(mL);
    while (lua_next(mL, -2) != 0){
        lua_pop(mL, 1);
        ++numLoaders;
    }
    //Add our function
    lua_pushinteger(mL, numLoaders + 1);
    lua_pushcfunction(mL, &LuaScript::RequireModule);
    lua_rawset(mL, -3);
    //Free table from stack
    lua_pop(mL, 1);
}
void LuaScript::AddScriptLoader(){
    //Get the packages table
    lua_getfield(mL, LUA_GLOBALSINDEX, "package");
    //Get the loaders table
    lua_getfield(mL, -1, "loaders");
    //Get rid of the packages table
    lua_remove(mL, -2);
    
    //Count # of loaders
    int numLoaders = 0;
    lua_pushnil(mL);
    while (lua_next(mL, -2) != 0){
        lua_pop(mL, 1);
        ++numLoaders;
    }
    //Add our function
    lua_pushinteger(mL, numLoaders + 1);
    lua_pushcfunction(mL, &LuaScript::RequireScript);
    lua_rawset(mL, -3);
    //Free table from stack
    lua_pop(mL, 1);
}
void LuaScript::AddLoaders(){
    AddScriptLoader();
    AddModuleLoader();
}