#include <string>
#include <lua.hpp>
#include "src/debug.h"
#include "src/input.h"
#include "luacvector2f.h"
#include "luacinput.h"

int LuaC::InputLib::luaopen_input(lua_State *l){
    //Stack: lib name
    //Register the library as global table "Input"
    luaL_register(l, inputClass.c_str(), luaInputLib);
    //Stack: lib name, table
    openKeyEnum(l);
    openHatEnum(l);
    return 0;
}
const struct luaL_reg LuaC::InputLib::luaInputLib[] = {
    { "keyDown", keyDown },
    { "joystickAvailable", joystickAvailable },
    { "joyAxis", getJoyAxis },
    { "joyButtonDown", getJoyButtonDown },
    { "joyHat", getJoyHat },
    { "joySupportsHaptic", joySupportsHaptic },
    { "getQuit", getQuit },
    { "mousePos", getMousePos },
    { NULL, NULL }
};
void LuaC::InputLib::openKeyEnum(lua_State *l){
    //Stack: lib name, table
    lua_pushinteger(l, SDL_SCANCODE_1);
    lua_setfield(l, -2, "KEY_1");
    lua_pushinteger(l, SDL_SCANCODE_2);
    lua_setfield(l, -2, "KEY_2");
    lua_pushinteger(l, SDL_SCANCODE_3);
    lua_setfield(l, -2, "KEY_3");
    lua_pushinteger(l, SDL_SCANCODE_4);
    lua_setfield(l, -2, "KEY_4");
    lua_pushinteger(l, SDL_SCANCODE_5);
    lua_setfield(l, -2, "KEY_5");
    lua_pushinteger(l, SDL_SCANCODE_6);
    lua_setfield(l, -2, "KEY_6");
    lua_pushinteger(l, SDL_SCANCODE_7);
    lua_setfield(l, -2, "KEY_7");
    lua_pushinteger(l, SDL_SCANCODE_8);
    lua_setfield(l, -2, "KEY_8");
    lua_pushinteger(l, SDL_SCANCODE_9);
    lua_setfield(l, -2, "KEY_9");
    lua_pushinteger(l, SDL_SCANCODE_0);
    lua_setfield(l, -2, "KEY_0");
    lua_pushinteger(l, SDL_SCANCODE_A);
    lua_setfield(l, -2, "KEY_A");
    lua_pushinteger(l, SDL_SCANCODE_B);
    lua_setfield(l, -2, "KEY_B");
    lua_pushinteger(l, SDL_SCANCODE_C);
    lua_setfield(l, -2, "KEY_C");
    lua_pushinteger(l, SDL_SCANCODE_D);
    lua_setfield(l, -2, "KEY_D");
    lua_pushinteger(l, SDL_SCANCODE_E);
    lua_setfield(l, -2, "KEY_E");
    lua_pushinteger(l, SDL_SCANCODE_F);
    lua_setfield(l, -2, "KEY_F");
    lua_pushinteger(l, SDL_SCANCODE_G);
    lua_setfield(l, -2, "KEY_G");
    lua_pushinteger(l, SDL_SCANCODE_H);
    lua_setfield(l, -2, "KEY_H");
    lua_pushinteger(l, SDL_SCANCODE_I);
    lua_setfield(l, -2, "KEY_I");
    lua_pushinteger(l, SDL_SCANCODE_J);
    lua_setfield(l, -2, "KEY_J");
    lua_pushinteger(l, SDL_SCANCODE_K);
    lua_setfield(l, -2, "KEY_K");
    lua_pushinteger(l, SDL_SCANCODE_L);
    lua_setfield(l, -2, "KEY_L");
    lua_pushinteger(l, SDL_SCANCODE_M);
    lua_setfield(l, -2, "KEY_M");
    lua_pushinteger(l, SDL_SCANCODE_N);
    lua_setfield(l, -2, "KEY_N");
    lua_pushinteger(l, SDL_SCANCODE_O);
    lua_setfield(l, -2, "KEY_O");
    lua_pushinteger(l, SDL_SCANCODE_P);
    lua_setfield(l, -2, "KEY_P");
    lua_pushinteger(l, SDL_SCANCODE_Q);
    lua_setfield(l, -2, "KEY_Q");
    lua_pushinteger(l, SDL_SCANCODE_R);
    lua_setfield(l, -2, "KEY_R");
    lua_pushinteger(l, SDL_SCANCODE_S);
    lua_setfield(l, -2, "KEY_S");
    lua_pushinteger(l, SDL_SCANCODE_T);
    lua_setfield(l, -2, "KEY_T");
    lua_pushinteger(l, SDL_SCANCODE_U);
    lua_setfield(l, -2, "KEY_U");
    lua_pushinteger(l, SDL_SCANCODE_V);
    lua_setfield(l, -2, "KEY_V");
    lua_pushinteger(l, SDL_SCANCODE_W);
    lua_setfield(l, -2, "KEY_W");
    lua_pushinteger(l, SDL_SCANCODE_X);
    lua_setfield(l, -2, "KEY_X");
    lua_pushinteger(l, SDL_SCANCODE_Y);
    lua_setfield(l, -2, "KEY_Y");
    lua_pushinteger(l, SDL_SCANCODE_Z);
    lua_setfield(l, -2, "KEY_Z");
    lua_pushinteger(l, SDL_SCANCODE_SPACE);
    lua_setfield(l, -2, "KEY_SPACE");
    lua_pushinteger(l, SDL_SCANCODE_UP);
    lua_setfield(l, -2, "KEY_UP");
    lua_pushinteger(l, SDL_SCANCODE_DOWN);
    lua_setfield(l, -2, "KEY_DOWN");
    lua_pushinteger(l, SDL_SCANCODE_RIGHT);
    lua_setfield(l, -2, "KEY_RIGHT");
    lua_pushinteger(l, SDL_SCANCODE_LEFT);
    lua_setfield(l, -2, "KEY_LEFT");
}
void LuaC::InputLib::openHatEnum(lua_State *l){
    //Stack: lib name, table
    lua_pushinteger(l, SDL_HAT_CENTERED);
    lua_setfield(l, -2, "HAT_CENTERED");
    lua_pushinteger(l, SDL_HAT_UP);
    lua_setfield(l, -2, "HAT_UP");
    lua_pushinteger(l, SDL_HAT_DOWN);
    lua_setfield(l, -2, "HAT_DOWN");
    lua_pushinteger(l, SDL_HAT_RIGHT);
    lua_setfield(l, -2, "HAT_RIGHT");
    lua_pushinteger(l, SDL_HAT_LEFT);
    lua_setfield(l, -2, "HAT_LEFT");
    lua_pushinteger(l, SDL_HAT_RIGHTUP);
    lua_setfield(l, -2, "HAT_RIGHTUP");
    lua_pushinteger(l, SDL_HAT_LEFTUP);
    lua_setfield(l, -2, "HAT_LEFTUP");
    lua_pushinteger(l, SDL_HAT_RIGHTDOWN);
    lua_setfield(l, -2, "HAT_RIGHTDOWN");
    lua_pushinteger(l, SDL_HAT_LEFTDOWN);
    lua_setfield(l, -2, "HAT_LEFTDOWN");
}
int LuaC::InputLib::keyDown(lua_State *l){
    /*
    *  There are 2 possible stacks: 
    *  1. int representing the SDL_SCANCODE to check
    *  2. a string representing the char key to check, ie. 'a'
    */
    //Case 1:
    if (lua_type(l, 1) == LUA_TNUMBER)
        lua_pushboolean(l, Input::KeyDown(luaL_checkint(l, 1)));
    //Case 2:
    else if (lua_type(l, 1) == LUA_TSTRING)
        lua_pushboolean(l, Input::KeyDown(luaL_checkstring(l, 1)));
    //Invalid key
    else {
        Debug::Log("Input.keyDown error: invalid data type for key param");
        lua_pushboolean(l, false);
    }
    return 1;
}
int LuaC::InputLib::joystickAvailable(lua_State *l){
    //Stack: empty
    lua_pushboolean(l, Input::JoystickAvailable());
    return 1;
}
int LuaC::InputLib::getJoyAxis(lua_State *l){
    //Stack: int of the axis to get
    lua_pushnumber(l, Input::GetJoyAxis(luaL_checkint(l, 1)));
    return 1;
}
int LuaC::InputLib::getJoyButtonDown(lua_State *l){
    //Stack: int of the joystick button to get
    lua_pushboolean(l, Input::GetJoyButton(luaL_checkint(l, 1)));
    return 1;
}
int LuaC::InputLib::getJoyHat(lua_State *l){
    //Stack: int of the hat to get
    lua_pushinteger(l, Input::GetJoyHat(luaL_checkint(l, 1)));
    return 1;
}
int LuaC::InputLib::joySupportsHaptic(lua_State *l){
    //Stack: empty
    lua_pushboolean(l, Input::JoySupportsHaptic());
    return 1;
}
int LuaC::InputLib::getQuit(lua_State *l){
    //Stack: empty
    lua_pushboolean(l, Input::Quit());
    return 1;
}
int LuaC::InputLib::getMousePos(lua_State *l){
    Vector2f pos = Input::MousePos();
    Vector2fLib::Push(l, &pos);
    return 1;
}
