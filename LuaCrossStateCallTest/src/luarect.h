#ifndef LUARECT_H
#define LUARECT_H

#include <lua.hpp>

class LuaRect {
public:
    LuaRect();
    LuaRect(int pX, int pY, int pW, int pH);
    void Set(int pX, int pY, int pW, int pH);
    int X();
    int Y();
    int W();
    int H();
    //Register the Lua functions
    static int luaopen_luarect(lua_State *l);
    //Add the luaRect at index i to the metatable in state l
    static void addLuaRect(lua_State *l, int i);

private:
    //Check if some data is a LuaRect and return a pointer to it
    static LuaRect* checkLuaRect(lua_State *l, int i = 1);
    //The LuaRect functions
    static const struct luaL_reg luaRectLib_f[];
    //The LuaRect member functions
    static const struct luaL_reg luaRectLib_m[];
    //Create a new luarect
    static int newLuaRect(lua_State *l);
    //Getters and setters
    static int setLuaRect(lua_State *l);
    static int getX(lua_State *l);
    static int getY(lua_State *l);
    static int getW(lua_State *l);
    static int getH(lua_State *l);
    //A setter dispatch for now, since im having
    //trouble with putting a table in __newindex
    static int accessor(lua_State *l);
    static int setX(lua_State *l);
    static int setY(lua_State *l);
    static int setW(lua_State *l);
    static int setH(lua_State *l);
    //For getting type via metatable
    static int type(lua_State *l);
    //Comparison operators
    static int equality(lua_State *l);
    //Arithmetic operators
    //ToString
    static int toString(lua_State *l);

public:
    int x, y, w, h;
};

#endif