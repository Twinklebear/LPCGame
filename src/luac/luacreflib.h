#ifndef LUACREFLIB_H
#define LUACREFLIB_H

#include <lua.hpp>
#include "luacdata.h"
#include "luaref.h"

namespace LuaC {
    /**
    * Class for simplifying interaction with LuaRefs in relation
    * to pushing them to the Lua State's stack
    * Note that the only valid operation to be performed with
    * a LuaRef is pushing it onto the stack or making it a global
    * and an assert is in place to check that the state is the 
    * same as the one the reference exists in
    */
    class LuaRefLib : public DataLib<LuaRef> {
    public:
        ///Override Allocate to make it do nothing
        static LuaRef* Allocate(lua_State *l);
        /**
        * Push the Lua reference to the top of the state
        * @param obj The LuaRef to push
        * @param l The Lua state to push onto
        */
        static void Push(lua_State *l, const LuaRef obj);
        /**
        * Push the Lua reference as a global with some name
        * @param obj The LuaRef to push
        * @param l The Lua state to push onto
        * @param name The name to assign to the global
        */
        static void Push(lua_State *l, const LuaRef obj, std::string name);
        ///Override copy to do nothing
        static void Copy(lua_State *from, int idx, lua_State *too);
        ///Override check to do nothing
        static LuaRef* Check(lua_State *l, int i);
        ///Override get copy to do nothing
        static LuaRef GetCopy(lua_State *l, int i);
    };
}

#endif