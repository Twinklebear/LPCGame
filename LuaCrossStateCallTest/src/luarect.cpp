#include <iostream>
#include <lua.hpp>
#include "luacscript.h"
#include "luarect.h"

LuaRect::LuaRect() : x(0), y(0), w(0), h(0){
}
LuaRect::LuaRect(int pX, int pY, int pW, int pH)
    : x(pX), y(pY), w(pW), h(pH)
{
}
void LuaRect::Set(int pX, int pY, int pW, int pH){
    x = pX;
    y = pY;
    w = pW;
    h = pH;
}
int LuaRect::X(){
    return x;
}
int LuaRect::Y(){
    return y;
}
int LuaRect::W(){
    return w;
}
int LuaRect::H(){
    return h;
}
const struct luaL_reg LuaRect::luaRectLib_f[] = {
    { "new", newLuaRect },
    { "add", addLuaRect },
    { NULL, NULL }
};
const struct luaL_reg LuaRect::luaRectLib_s[] = {
    { "x", setX },
    { "y", setY },
    { NULL, NULL }
};
const struct luaL_reg LuaRect::luaRectLib_m[] = {
    { "set", setLuaRect },
    { "type", type },
    { "x", getX },
    { "y", getY },
    { "w", getW },
    { "h", getH },
    { "accessor", accessor },
    { NULL, NULL }
};
//Open the library
int LuaRect::luaopen_luarect(lua_State *l){
    //Push the metatable onto the stack
    luaL_newmetatable(l, "LPC.LuaRect");
    //Push __index to be used as a table key
    //we want to register metatable.__index = metatable
    lua_pushstring(l, "__index");
    //Copy metatable from -2 to the top
    lua_pushvalue(l, -2);
    //Set table at __index = metatable, ie. metatable.__index = metatable
    lua_settable(l, -3);
    //Register our member functions with this lib
    luaL_openlib(l, NULL, luaRectLib_m, 0);
    //Register the __newindex index so we can do stuff like r.x = 10 and such
    //Push the key we want
    lua_pushstring(l, "__newindex");
    //We want setVal to be the function we call, so push that so we ccan
    //get it from table
    lua_pushstring(l, "accessor");
    //Get from table at -3 at key "accessor", ie. the function
    lua_gettable(l, -3);
    //Set table at key __newindex the value at top of stack
    //which will be the function setVal
    lua_settable(l, -3);
    //Register the regular functions as well
    luaL_register(l, "LuaRect", luaRectLib_f);
    return 1;
}
//Create a new luarect
int LuaRect::newLuaRect(lua_State *l){
    //If some initial x, y, w, h desired check for it
    bool initVals = (lua_gettop(l) == 4);
    LuaRect *r = (LuaRect*)lua_newuserdata(l, sizeof(LuaRect));
    //Get the values to initialize the rect with from the stack
    if (initVals){
        r->Set(luaL_checkint(l, 1), luaL_checkint(l, 2),
            luaL_checkint(l, 3), luaL_checkint(l, 4));
        //Remove the values from the stack
        for (int i = 0; i < 4; ++i)
            lua_remove(l, 1);
    }
    else
        r->Set(0, 0, 0, 0);
    //Set the metatable appropriately
    luaL_getmetatable(l, "LPC.LuaRect");
    lua_setmetatable(l, -2);
    return 1;
}
int LuaRect::addLuaRect(lua_State *l){
    luaL_getmetatable(l, "LPC.LuaRect");
    lua_setmetatable(l, -2);
    return 0;
}
//Check if some data is a LuaRect and return pointer to it
LuaRect* LuaRect::checkLuaRect(lua_State *l){
    return (LuaRect*)luaL_checkudata(l, 1, "LPC.LuaRect");
}
int LuaRect::setLuaRect(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    luaL_argcheck(l, r != NULL, 1, "Error: LuaRect expected");
    //Set the values
    r->Set(luaL_checkint(l, 2), luaL_checkint(l, 3),
        luaL_checkint(l, 4), luaL_checkint(l, 5));
    return 0;
}
int LuaRect::getX(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    lua_pushinteger(l, r->x);
    return 1;
}
int LuaRect::getY(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    lua_pushinteger(l, r->Y());
    return 1;
}
int LuaRect::getW(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    lua_pushinteger(l, r->W());
    return 1;
}
int LuaRect::getH(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    lua_pushinteger(l, r->H());
    return 1;
}
int LuaRect::accessor(lua_State *l){
    //Get the param to change "x", "y", so on and then remove it
    std::string val = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    std::cout << "Accessor called on property: " << val << std::endl;
    LuaCScript::stackDump(l);
    //If two items on the stack we want to set, if one we want to get
    bool get = (lua_gettop(l) == 1);
    switch (val.at(0)){
        case 'x':
            get ? getX(l) : setX(l);
            break;
        case 'y':
            get ? getY(l) : setY(l);
            break;
        case 'w':
            get ? getW(l) : setW(l);
            break;
        case 'h':
            get ? getH(l) : setH(l);
            break;
        default:
            break;
    }
    return (get ? 1 : 0);
}
int LuaRect::setX(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    r->Set(luaL_checkint(l, -1), r->y, r->w, r->h);
    //Clean up the stack
    lua_pop(l, -1);
    return 0;
}
int LuaRect::setY(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    r->Set(r->x, luaL_checkint(l, -1), r->w, r->h);
    //Clean up the stack
    lua_pop(l, -1);
    return 0;
}
int LuaRect::setW(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    r->Set(r->x, r->y, luaL_checkint(l, -1), r->h);
    //Clean up the stack
    return 0;
}
int LuaRect::setH(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    r->Set(r->x, r->y, r->w, luaL_checkint(l, -1));
    //Clean up the stack
    return 0;
}
int LuaRect::type(lua_State *l){
    lua_pushstring(l, "LuaRect");
    return 1;
}