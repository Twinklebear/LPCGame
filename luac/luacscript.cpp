#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <lua.hpp>
#include "src/debug.h"
#include "src/animatedimage.h"
#include "src/button.h"
#include "src/camera.h"
#include "src/color.h"
#include "src/entity.h"
#include "src/input.h"
#include "src/math.h"
#include "src/motionstate.h"
#include "src/physics.h"
#include "src/rect.h"
#include "src/state.h"
#include "src/statemanager.h"
#include "src/text.h"
#include "src/timer.h"
#include "src/vectors.h"
#include "src/window.h"
#include "src/luascript.h"
#include "luac/luacscript.h"

const LuaC::LuaScript::TLuaLibs LuaC::LuaScript::sLuaLibs = LuaC::LuaScript::CreateLibMap();
const LuaC::LuaScript::TTableAdders LuaC::LuaScript::sTableAdders = LuaC::LuaScript::CreateAdderMap();

int LuaC::LuaScript::stackDump(lua_State *l){
    std::stringstream ss;
    ss << "Stack: ";
    for (int i = 1, top = lua_gettop(l); i <= top; ++i){
        int t = lua_type(l, i);
        ss << "@" << i << ": ";
        switch (t) {
            //Strings
            case LUA_TSTRING:
                ss << lua_tostring(l, i);
                break;
            //Bools
            case LUA_TBOOLEAN:
                ss << (lua_toboolean(l, i) ? "True" : "False");
                break;
            //Numbers
            case LUA_TNUMBER:
                ss << lua_tonumber(l, i);
                break;
            //Other (userdata)
            default:
                ss << lua_typename(l, t) << "(" << readType(l, i) << ")";
                break;
        }
        ss << ", ";
    }
    ss << std::endl;
    Debug::Log(ss.str());
    return 0;
}
std::string LuaC::LuaScript::readType(lua_State *l, int i){
    //Stack: some # of params, i corresponds to the udata we want to identify
    std::string type = "";
    //Get the metatable of udata at index i
    if (lua_getmetatable(l, i)){
        //Stack: stuff, udata's metatable
        //Get the "type" field
        lua_getfield(l, -1, "type");
        //Stack: stuff, udata metatable, typename
        //Get the type from the stack
        type = luaL_checkstring(l, -1);
    }
    //Stack: stuff, udata metatable, typename
    //Stack contains the typename and its metatable, pop them off
    lua_pop(l, 2);
    return type;
}
int LuaC::LuaScript::requireLib(lua_State *l){
    //Try to look up the module desired, if it's one of ours load it, if not error
    std::string module = lua_tostring(l, -1);
    LuaC::LuaScript::TLuaLibs::const_iterator fnd = sLuaLibs.find(module);
    if (fnd != sLuaLibs.end())
        lua_pushcfunction(l, sLuaLibs.at(module));
    else {
        std::string err = "requireLib Error: Failed to find: "
            + module + "\n";
        lua_pushstring(l, err.c_str());
    }
    return 1;
}
int LuaC::LuaScript::requireScript(lua_State *l){
    //Check if the script is an engine script, if yes push DoScript, if no error
    std::string script = lua_tostring(l, -1);
    if (script.substr(0, 7) == "scripts"){
        std::string scriptFile = "../res/" + script;
        std::ifstream checkFile(scriptFile.c_str());
        if (checkFile.good()){
            checkFile.close();
            lua_pushstring(l, scriptFile.c_str());
            lua_pushcfunction(l, LuaC::LuaScript::doScript);
        }
        else {
            std::string err = "LuaCScript::RequireScript Error: Failed to find: " 
                + scriptFile + "\n";
            std::cout << err << std::endl;
            lua_pushstring(l, err.c_str());
        }
    }
    //If not an engine script, nothing to return
    else 
        return 0;
    //If we found script or failed to load engine script we've got a result to return
    return 1;
}
std::vector<std::string> LuaC::LuaScript::checkUserData(lua_State *l){
    //l stack: params
    //We want to step through and record the typenames of the userdata
    std::vector<std::string> udata;
    for (int i = 1, top = lua_gettop(l); i <= top; ++i){
        int t = lua_type(l, i);
        std::string luaTName = lua_typename(l, t);
        //If we find some userdata, read the type and store it
        if (luaTName == "userdata")
            udata.push_back(readType(l, i));
    }
    return udata;
}
void LuaC::LuaScript::setUserData(lua_State *l, std::vector<std::string> types){
    //l stack: params
    //Step through and find udata, and register it according to the value at the vector
    //after each registration, increment vector pos
    std::vector<std::string>::const_iterator iter = types.begin();
    for (int i = 1, top = lua_gettop(l); i <= top; ++i && iter != types.end()){
        int t = lua_type(l, i);
        std::string luaTName = lua_typename(l, t);
        //If we find some userdata, read the type and register it accordingly
        if (luaTName == "userdata"){
            sTableAdders.at(*iter)(l, (i - top - 1));
            ++iter;
        }
    }
}
int LuaC::LuaScript::doScript(lua_State *l){
    std::string script = lua_tostring(l, 0);
    luaL_dofile(l, script.c_str());
    //Stack still has the initial string we called with scripts/blah, so remove it
    lua_pop(l, 1);
    return 0;
}
LuaC::LuaScript::TLuaLibs LuaC::LuaScript::CreateLibMap(){
    TLuaLibs map;
    map["AnimatedImage"] = &AnimatedImage::RegisterLua;
    map["Button"]        = &Button::RegisterLua;
    map["Camera"]        = &Camera::RegisterLua;
    map["Color"]         = &Color::RegisterLua;
    map["Debug"]         = &Debug::RegisterLua;
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
LuaC::LuaScript::TTableAdders LuaC::LuaScript::CreateAdderMap(){
    TTableAdders map;
    //Add table adders
    return map;
}
