#include <iostream>
#include <string>
#include <sstream>
#include <lua.hpp>
#include "luacscript.h"
#include "luarect.h"

LuaRect::LuaRect() : w(0), h(0){
}
LuaRect::LuaRect(float pX, float pY, int pW, int pH)
    : w(pW), h(pH)
{
    pos.Set(pX, pY);
}
void LuaRect::Set(float pX, float pY, int pW, int pH){
    pos.Set(pX, pY);
    w = pW;
    h = pH;
}
void LuaRect::Set(Vector2f &v){
    pos = v;
}
Vector2f LuaRect::Pos() const {
    return pos;
}
float LuaRect::X() const {
    return pos.x;
}
float LuaRect::Y() const {
    return pos.y;
}
int LuaRect::W() const {
    return w;
}
int LuaRect::H() const {
    return h;
}
LuaRect::operator std::string() const {
    std::stringstream str;
    str << "LuaRect: (" << (std::string)pos
        << ", w: " << w << ", h: " << h << ")";
    return str.str();
}
const struct luaL_reg LuaRect::luaRectLib[] = {
    { "set", setLuaRect },
    { "pos", getPos },
    { "x", getX },
    { "y", getY },
    { "w", getW },
    { "h", getH },
    { "__newindex", accessor },
    { "__eq", equality },
    { "__tostring", toString },
    { "__concat", concat },
    { NULL, NULL }
};
int LuaRect::luaopen_luarect(lua_State *l){
    //Stack: lib name
    //Push the metatable to contain the fcns onto the stack
    luaL_newmetatable(l, "LPC.LuaRect");
    //Copy metatable from -1 to the top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack
    //ie. LPC.LuaRect.__index = table containing luaRectLib_m
    lua_setfield(l, -2, "__index");
    //Register the lib to the metatable at top of stack
    luaL_register(l, NULL, luaRectLib);
    //Stack: lib name, metatable
    //Pushing on a typename string so we can ID the metatable
    lua_pushstring(l, "LuaRect");
    //Stack: lib name, metatable, string
    lua_setfield(l, -2, "type");
    //Stack: lib name, metatable
    //Setup the LuaRect table, for making LuaRects
    lua_newtable(l);
    //Stack: lib name, metatable, table
    //Push the new fcn
    lua_pushcfunction(l, newLuaRect);
    //Stack: lib name, metatable, table, newLuaRect fcn
    //Now newLuaRect fcn is @ key __call in the table
    lua_setfield(l, -2, "__call");
    //Stack: lib name, metatable, table
    //We want to set the table containing __call to be the metatable
    //of the LuaRect metatable
    lua_setmetatable(l, -2);
    //Stack: lib name, metatable

    //Testing pushing an enum type
    lua_pushinteger(l, 10);
    //Stack: lib name, metatable, 10
    //Set the table field of the name of enum we want
    //So now LuaRect.ENUM = 10
    lua_setfield(l, -2, "ENUM");

    //Stack: lib name, metatable
    //Name our metatable and make it global
    lua_setglobal(l, "LuaRect");
    //Stack: lib name
    return 0;
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
int LuaRect::newLuaRect(lua_State *l){
    //Stack: table, params if desired
    //Pop the table off
    lua_remove(l, 1);
    //If some initial x, y, w, h desired check for it
    bool initVals = (lua_gettop(l) == 4);
    LuaRect *r = (LuaRect*)lua_newuserdata(l, sizeof(LuaRect));
    //Get the values to initialize the rect with from the stack
    if (initVals){
        r->Set(luaL_checknumber(l, 1), luaL_checknumber(l, 2),
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
int LuaRect::setLuaRect(lua_State *l){
    //Stack: udata, x, y, w, h
    LuaRect *r = checkLuaRect(l);
    lua_remove(l, 1);
    //Stack: x, y, w, h
    //Set the values
    r->Set(luaL_checknumber(l, 1), luaL_checknumber(l, 2),
        luaL_checkint(l, 3), luaL_checkint(l, 4));
    lua_pop(l, 4);
    //Stack: empty
    return 0;
}
int LuaRect::getPos(lua_State *l){
    //Stack: udata (LuaRect)
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    //Make a new Vector2f udata and set its value to r->pos
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    //Stack: udata (Vector2f)
    //Add it to the metatable
    Vector2f::addVector2f(l, -1);
    v->Set(r->pos);
    return 1;
}
int LuaRect::getX(lua_State *l){
    //Stack: udata
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    lua_pushnumber(l, r->X());
    //Stack: val of x
    return 1;
}
int LuaRect::getY(lua_State *l){
    //Stack: udata
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    lua_pushnumber(l, r->Y());
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
            return setX(l);
        case 'y':
            return setY(l);
        case 'w':
            return setW(l);
        case 'h':
            return setH(l);
        case 'p':
            return setPos(l);
        default:
            return 0;
    }
}
int LuaRect::setPos(lua_State *l){
    //Stack: udata (rect), udata (vector2f)
    LuaRect *r = checkLuaRect(l, 1);
    Vector2f *v = Vector2f::checkVector2f(l, 2);
    r->Set(*v);
    //Clean up stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setX(lua_State *l){
    //Stack: udata, val to set as x
    LuaRect *r = checkLuaRect(l);
    r->Set(luaL_checknumber(l, 2), r->pos.y, r->w, r->h);
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setY(lua_State *l){
    //Stack: udata, val to set as y
    LuaRect *r = checkLuaRect(l);
    r->Set(r->pos.x, luaL_checknumber(l, 2), r->w, r->h);
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setW(lua_State *l){
    //Stack: udata, val to set as w
    LuaRect *r = checkLuaRect(l);
    r->Set(r->pos.x, r->pos.y, luaL_checkint(l, 2), r->h);
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::setH(lua_State *l){
    //Stack: udata, val to set as h
    LuaRect *r = checkLuaRect(l);
    r->Set(r->pos.x, r->pos.y, r->w, luaL_checkint(l, 2));
    //Clean up the stack
    lua_pop(l, 2);
    return 0;
}
int LuaRect::equality(lua_State *l){
    //Stack: rect1 rect2
    //The comparison rect1 == rect2 is desired
    LuaRect *r = checkLuaRect(l);
    LuaRect *r2 = checkLuaRect(l, 2);
    lua_pop(l, 2);
    //Stack: empty
    lua_pushboolean(l, (r->pos == r2->pos && r->w == r2->w && r->h == r2->h));
    return 1;
}
int LuaRect::toString(lua_State *l){
    //Stack: rect1
    //We want to return a string describing the rect
    LuaRect *r = checkLuaRect(l);
    lua_pop(l, 1);
    //Stack: empty
    std::stringstream str;
    str << "Rect: ( " << (std::string)(r->pos)
        << ", w: " << r->w << ", h: " << r->h << ")";
    lua_pushstring(l, str.str().c_str());
    //Stack: the description string
    return 1;
}
int LuaRect::concat(lua_State *l){
    /*
    *  Stack has 2 possible configurations that we must
    *  detect and pick the right location to read the udata
    *  1. string, udata (LuaRect)
    *  2. udata (LuaRect), string
    */
    //Config 1
    if (lua_type(l, 1) == LUA_TSTRING){
        //Read the vector and pop it off
        LuaRect *r = checkLuaRect(l, 2);
        std::string str = luaL_checkstring(l, 1);
        lua_pop(l, 2);
        //stack: empty
        //Push on string + description string
        lua_pushstring(l, (str + (std::string)(*r)).c_str());
    }
    //Config 2
    else {
        //Read the vector and pop it off
        LuaRect *r = checkLuaRect(l, 1);
        std::string str = luaL_checkstring(l, 2);
        lua_pop(l, 2);
        //stack: empty
        //Push on string + description string
        lua_pushstring(l, ((std::string)(*r) + str).c_str());
    }
    return 1;
}
