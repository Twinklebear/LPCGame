#include <string>
#include <lua.hpp>

/**
* A handler for a Lua reference, can be constructed to reference 
* some item on the stack or a global with some name
*/
class LuaRef {
public:
    //Blank constructor, set reference to null (LUA_REFNIL)
    LuaRef() : mRef(LUA_REFNIL) {}
    //Store the reference to the item at index i on the lua_State l
    LuaRef(lua_State *l, int i);
    //Store the reference to a global with some name in a lua_State l
    LuaRef(lua_State *l, std::string name);
    //Unref the the item
    ~LuaRef();
    //Push the reference onto the top of the state it's in
    void Push();

private:
    //The reference number
    int mRef;
    //The state the reference is in
    lua_State *mState;
};
