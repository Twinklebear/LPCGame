#include <luabind/luabind.hpp>
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
const struct luaL_reg LuaRect::luaRectLib_m[] = {
    { "set", setLuaRect },
    { "getX", getX },
    { "getY", getY },
    { "getW", getW },
    { "getH", getH },
    { NULL, NULL }
};
//Open the library
int LuaRect::luaopen_luarect(lua_State *l){
    luaL_newmetatable(l, "LPC.LuaRect");
    //Setup the metatable for object oriented access, ie r:getX()
    lua_pushvalue(l, -1);
    lua_setfield(l, -2, "__index");
    luaL_register(l, NULL, luaRectLib_m);
    //Register the regular functions as well
    luaL_register(l, "LuaRect", luaRectLib_f);
    return 1;
}
//Create a new luarect
int LuaRect::newLuaRect(lua_State *l){
    LuaRect *r = (LuaRect*)lua_newuserdata(l, sizeof(LuaRect));
    //Set the metatable appropriately
    luaL_getmetatable(l, "LPC.LuaRect");
    lua_setmetatable(l, -2);
    return 1;
}
int LuaRect::addLuaRect(lua_State *l){
    LuaRect *r = (LuaRect*)lua_touserdata(l, 1);
    luaL_argcheck(l, r != NULL, 1, "LuaRect expected");
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
    //check x, y, w, h
    int val[4];
    val[0] = luaL_checkint(l, 2);
    val[1] = luaL_checkint(l, 3);
    val[2] = luaL_checkint(l, 4);
    val[3] = luaL_checkint(l, 5);
    //Check that we got a LuaRect
    r->Set(val[0], val[1], val[2], val[3]);
    return 0;
}
int LuaRect::getX(lua_State *l){
    LuaRect *r = checkLuaRect(l);
    lua_pushinteger(l, r->X());
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