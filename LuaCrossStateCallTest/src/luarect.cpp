#include <iostream>
#include <string>
#include <sstream>
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
    { "__call", newLuaRect },
    { NULL, NULL }
};
const struct luaL_reg LuaRect::luaRectLib_m[] = {
    { "set", setLuaRect },
    { "type", type },
    { "x", getX },
    { "y", getY },
    { "w", getW },
    { "h", getH },
    { "__newindex", accessor },
    { "__eq", equality },
    { "__tostring", toString },
    { NULL, NULL }
};
int LuaRect::luaopen_luarect(lua_State *l){
    //Push the metatable onto the stack
    luaL_newmetatable(l, "LPC.LuaRect");
    //Copy metatable from -1 to the top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack
    //ie. LPC.LuaRect.__index = table containing luaRectLib_m
    lua_setfield(l, -2, "__index");
    //Register the lib to the metatable at top of stack
    luaL_register(l, NULL, luaRectLib_m);
    //Stack: module name, __index metatable

    std::cout << "A--";
    LuaCScript::stackDump(l);
    //Setup the LuaRect table, for making LuaRects
    lua_newtable(l, 1);
    //Stack: module name, __index metatable, table
    std::cout << "B--";
    LuaCScript::stackDump(l);
    
    //Push the new fcn
    lua_pushcfunction(l, newLuaRect);
    std::cout << "C--";
    //Stack: module name, __index metatable, table, newLuaRect fcn
    LuaCScript::stackDump(l);
    //Now newLuaRect fcn is @ key __call in the table
    lua_setfield(l, -2, "__call");
    std::cout << "D--";
    //Stack: module name, __index metatable, table
    LuaCScript::stackDump(l);
    lua_setmetatable(l, -2);
    std::cout << "E--";
    LuaCScript::stackDump(l);
        //Testing pushing an enum type
    lua_pushinteger(l, 10);
    std::cout << "F--";
    LuaCScript::stackDump(l);
    lua_setfield(l, -2, "ENUM");
    std::cout << "G--";
    LuaCScript::stackDump(l);

    lua_setglobal(l, "LuaRect");
    return 1;
}
int LuaRect::newLuaRect(lua_State *l){
    //Pop the table off
    lua_remove(l, 1);
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
    addLuaRect(l, -1);
    return 1;
}
void LuaRect::addLuaRect(lua_State *l, int i){
    //Given stack containing unknown amount of things along with the udata
    //udata is at index i
    luaL_getmetatable(l, "LPC.LuaRect");
    //Now stack is ??? with the metatable at top
    //So we know the index of our rect is bumped down 1 more so we adjust
    //and set the table
    lua_setmetatable(l, i - 1);
}
//Check if some data is a LuaRect and return pointer to it
LuaRect* LuaRect::checkLuaRect(lua_State *l, int i){
    return (LuaRect*)luaL_checkudata(l, i, "LPC.LuaRect");
}
int LuaRect::setLuaRect(lua_State *l){
    //Stack: udata, x, y, w, h
    LuaRect *r = checkLuaRect(l);
    luaL_argcheck(l, r != NULL, 1, "Error: LuaRect expected");
    lua_remove(l, 1);
    //Stack: x, y, w, h
    //Set the values
    r->Set(luaL_checkint(l, 1), luaL_checkint(l, 2),
        luaL_checkint(l, 3), luaL_checkint(l, 4));
    lua_pop(l, 4);
    //Stack: empty
    return 0;
}
int LuaRect::getX(lua_State *l){
    //Stack: udata
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    lua_pushinteger(l, r->x);
    //Stack: val of x
    return 1;
}
int LuaRect::getY(lua_State *l){
    //Stack: udata
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    lua_pushinteger(l, r->Y());
    //Stack: val of y
    return 1;
}
int LuaRect::getW(lua_State *l){
    //Stack: udata
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    lua_pushinteger(l, r->W());
    //Stack: val of w
    return 1;
}
int LuaRect::getH(lua_State *l){
    //Stack: udata
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    lua_pushinteger(l, r->H());
    //Stack: value of h
    return 1;
}
int LuaRect::accessor(lua_State *l){
    //Stack: udata, string of index to set, val to set
    //Get the index to set "x", "y", so on and then remove it
    std::string val = luaL_checkstring(l, 2);
    lua_remove(l, 2);
    //Stack: udata, val to set
    switch (val.at(0)){
        case 'x':
            setX(l);
            break;
        case 'y':
            setY(l);
            break;
        case 'w':
            setW(l);
            break;
        case 'h':
            setH(l);
            break;
        default:
            break;
    }
    //Set takes care of setting the val and cleaning up the stack
    return 0;
}
int LuaRect::setX(lua_State *l){
    //Stack: udata, val to set as x
    LuaRect *r = checkLuaRect(l);
    r->Set(luaL_checkint(l, 2), r->y, r->w, r->h);
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setY(lua_State *l){
    //Stack: udata, val to set as y
    LuaRect *r = checkLuaRect(l);
    r->Set(r->x, luaL_checkint(l, 2), r->w, r->h);
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setW(lua_State *l){
    //Stack: udata, val to set as w
    LuaRect *r = checkLuaRect(l);
    r->Set(r->x, r->y, luaL_checkint(l, 2), r->h);
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setH(lua_State *l){
    //Stack: udata, val to set as h
    LuaRect *r = checkLuaRect(l);
    r->Set(r->x, r->y, r->w, luaL_checkint(l, 2));
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::type(lua_State *l){
    //Stack: udata
    lua_pop(l, 1);
    lua_pushstring(l, "LuaRect");
    //Stack: string "LuaRect"
    return 1;
}
int LuaRect::equality(lua_State *l){
    //Stack: rect1 rect2
    //The comparison rect1 == rect2 is desired
    LuaRect *r = checkLuaRect(l);
    LuaRect *r2 = checkLuaRect(l, 2);
    lua_pop(l, 2);
    //Stack: empty
    lua_pushboolean(l, (r->x == r2->x && r->y == r2->y && r->w == r2->w && r->h == r2->h));
    return 1;
}
int LuaRect::toString(lua_State *l){
    //Stack: rect1
    //We want to return a string describing the rect
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    //Stack: empty
    std::stringstream str;
    str << "Rect: (x: " << r->x << ", y: " << r->y
        << ", w: " << r->w << ", h: " << r->h << ")";
    lua_pushstring(l, str.str().c_str());
    //Stack: the description string
    return 1;
}
