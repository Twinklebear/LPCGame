#ifndef LUARECT_H
#define LUARECT_H

#include <lua.hpp>
#include "vectors.h"

class LuaRect {
public:
    LuaRect();
    LuaRect(float pX, float pY, int pW, int pH);
    void Set(float pX, float pY, int pW, int pH);
    void Set(Vector2f &v);
    Vector2f Pos() const;
    float X() const;
    float Y() const;
    int W() const;
    int H() const;
    //Register the Lua functions
    static int luaopen_luarect(lua_State *l);
    //Add the luaRect at index i to the metatable in state l
    static void addLuaRect(lua_State *l, int i);
    //Check if some data is a LuaRect and return a pointer to it, i = index
    static LuaRect* checkLuaRect(lua_State *l, int i = 1);
    //Operators
    operator std::string() const;

private:
    //The LuaRect member functions
    static const struct luaL_reg luaRectLib[];
    //Create a new luarect
    static int newLuaRect(lua_State *l);
    //Getters and setters
    static int setLuaRect(lua_State *l);
    static int getPos(lua_State *l);
    static int getX(lua_State *l);
    static int getY(lua_State *l);
    static int getW(lua_State *l);
    static int getH(lua_State *l);
    //A setter dispatch for now, since im having
    //trouble with putting a table in __newindex
    static int accessor(lua_State *l);
    static int setPos(lua_State *l);
    static int setX(lua_State *l);
    static int setY(lua_State *l);
    static int setW(lua_State *l);
    static int setH(lua_State *l);
    //Comparison operators
    static int equality(lua_State *l);
    //Arithmetic operators
    //ToString
    static int toString(lua_State *l);
    static int concat(lua_State *l);

public:
    Vector2f pos;
    int w, h;
};

#endif