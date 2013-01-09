#include <string>
#include <lua.hpp>
#include "src/timer.h"
#include "luacscript.h"
#include "luactimer.h"

int LuaC::TimerLib::luaopen_timer(lua_State *l){
    return LuaScriptLib::LuaOpenLib(l, timerMeta, timerClass, luaTimerLib, newTimer);
}
const luaL_reg LuaC::TimerLib::luaTimerLib[] = {
    { "start", start },
    { "stop", stop },
    { "pause", pause },
    { "unpause", unpause },
    { "restart", restart },
    { "ticks", ticks },
    { "started", started },
    { "paused", paused },
    { NULL, NULL }
};
int LuaC::TimerLib::newTimer(lua_State *l){
    //Stack: table (Timer)
    Allocate(l);
    return 1;
}
int LuaC::TimerLib::start(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    t->Start();
    return 0;
}
int LuaC::TimerLib::stop(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    t->Stop();
    return 0;
}
int LuaC::TimerLib::pause(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    t->Pause();
    return 0;
}
int LuaC::TimerLib::unpause(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    t->Unpause();
    return 0;
}
int LuaC::TimerLib::restart(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    lua_pushinteger(l, t->Restart());
    return 1;
}
int LuaC::TimerLib::ticks(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    lua_pushinteger(l, t->Ticks());
    return 1;
}
int LuaC::TimerLib::started(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    lua_pushboolean(l, t->Started());
    return 1;
}
int LuaC::TimerLib::paused(lua_State *l){
    //Stack: userdata (Timer)
    Timer *t = Check(l, 1);
    lua_pushboolean(l, t->Paused());
    return 1;
}