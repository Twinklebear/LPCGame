#ifndef LUAC_FUNCTIONINTERFACE
#define LUAC_FUNCTIONINTERFACE

#include <lua.hpp>
#include "core/debug.h"
#include "luacdata.h"
#include "luac/luacanimatedimage.h"
#include "luac/luaccamera.h"
#include "luac/luaccolor.h"
#include "luac/luacentity.h"
#include "luac/luacimage.h"
#include "luac/luacphysics.h"
#include "luac/luacrectf.h"
#include "luac/luacreflib.h"
#include "luac/luactext.h"
#include "luac/luactimer.h"
#include "luac/luacvector2f.h"

///A namespace for storing the Lua C API code
/**
*  A namespace to store the various functions for interacting with
*  Lua via the Lua C API
*/
namespace LuaC {
    /*
    * A class for handling calling functions on a Lua state
    */
    class FunctionInterface {
    public:
        /**
        * Setup the interface giving it a state to call on and a 
        * script file name to log in case of errors
        * @param l The Lua state to call functions in
        * @param file The script file name to log in case of error
        */
        FunctionInterface(lua_State *l, std::string file) : mL(l), mFile(file) {};
        ///Default constructor: set state ptr to nullptr and file name to empty string
        FunctionInterface() : mL(nullptr), mFile("") {};
        /**
        * Call a function with some number of params (default 0) and get a
        * return value of type R back
        * @param R The return type to get
        * @param fcn The name of the function being called
        * @param nParam The number of parameters being passed, default 0
        */
        template<class R>
        R CallFunction(std::string fcn, int nParam = 0){
            //if no params, get the function
            if (nParam == 0)
                lua_getglobal(mL, fcn.c_str());

            if (lua_pcall(mL, nParam, 1, 0) != 0){
                Debug::Log("Error calling: " + fcn + " in file " + mFile + lua_tostring(mL, -1));
                LuaC::LuaScriptLib::StackDump(mL);
            }            
            return LuaC::DataLib<R>::GetCopy(mL, -1);
        }
        /**
        * Void specialization of CallFunction, call a function that
        * returns nothing (void)
        * @param fcn The name of the function being called
        * @param nParam The number of parameters being passed, default 0
        */
        template<>
        void CallFunction(std::string fcn, int nParam){
            //if no params, get the function
            if (nParam == 0)
                lua_getglobal(mL, fcn.c_str());

            if (lua_pcall(mL, nParam, 0, 0) != 0){
                Debug::Log("Error calling: " + fcn + " in file " + mFile + lua_tostring(mL, -1));
                LuaC::LuaScriptLib::StackDump(mL);
            }
        }
        /**
        * Call a function fcn on the script specifying any desired number of parameters
        * since this is the first level of recursion we get the function, then push
        * on the first parameter and recurse through the parameter pack pushing each one on
        * @param fcn The function to call
        * @param param The first parameter to push onto the state
        * @param args The variadic template parameter pack
        */
        template<class R, class T, class... Args>
        R CallFunction(std::string fcn, T param, Args... args){
            lua_getglobal(mL, fcn.c_str());
            DataLib<T>::Push(mL, param);
            return Call<R>(fcn, 1, args...);
        }
        /**
        * Call a function fcn on the script specifying any desired number of parameters
        * since this is the first level of recursion we get the function, then push
        * on the first parameter and recurse through the parameter pack pushing each one on
        * @param fcn A LuaRef of the function to call
        * @param param The first parameter to push onto the state
        * @param args The variadic template parameter pack
        */
        template<class R, class T, class... Args>
        R CallFunction(LuaRef fcn, T param, Args... args){
            fcn.Push(mL);
            DataLib<T>::Push(mL, param);
            return Call<R>("LuaRefFcn", 1, args...);
        }

    private:
        /**
        * The general recursion function for stepping through the parameters
        * we take a parameter from the pack, push it on, increment nParam and 
        * repeat until we have one left
        * @param fcn The function name, kept around for debug logging purposes
        * @param nParam The number of parameters we're calling the function with
        * @param param The current param being pushed onto the state
        * @param args The remaining parameters to be pushed on
        */
        template<class R, class T, class... Args>
        R Call(std::string fcn, int nParam, T param, Args... args){
            DataLib<T>::Push(mL, param);
            ++nParam;
            return Call<R>(fcn, nParam, args...);
        }
        /**
        * The final recursion function, we push on the last parameter and then
        * call to CallFunction<R> to actually call the function
        * @param fcn The function name, kept around for debug logging purposes
        * @param nParam The number of parameters to call the function with. After this
        *       function call it's equal to the number of params we pushed into the state
        * @param param The final paremeter to push
        */
        template<class R, class T>
        R Call(std::string fcn, int nParam, T param){
            DataLib<T>::Push(mL, param);
            ++nParam;
            return CallFunction<R>(fcn, nParam);
        }
        /**
        * If only one parameter was specified we skip to the final recursion step and
        * just call the function
        * @param fcn The function name, kept for logging purposes
        * @param nParam The number of params to call the function with
        */
        template<class R>
        R Call(std::string fcn, int nParam){
            return CallFunction<R>(fcn, nParam);
        }

    private:
        lua_State *mL;
        std::string mFile;
    };
}

#endif