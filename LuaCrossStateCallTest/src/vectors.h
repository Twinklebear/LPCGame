#ifndef VECTORS_H
#define VECTORS_H

#include <sstream>
#include <string>
#include <lua.hpp>

///A 2D vector
/**
*  A 2D vector
*/
template<class T>
class Vector2 {
public:
	Vector2() : x(0), y(0){
	}
	/**
	*  Setup the vector with an x & y value
	*  @param pX The x value to set
	*  @param pY The y value to set
	*/
	Vector2(T pX, T pY) : x(pX), y(pY){
	}
	/**
	*  Setup the vector with an x & y value
	*  @param pX The x value to set
	*  @param pY The y value to set
	*/
	void Set(T pX, T pY){
		x = pX;
		y = pY;
	}
    void Set(Vector2<T> &v){
        x = v.x;
        y = v.y;
    }
	///Operators
    bool operator == (Vector2<T> val) const {
        return (x == val.x && y == val.y);
    }
	Vector2<T> operator + (Vector2<T> val) const {
		return Vector2<T>(this->x + val.x, this->y + val.y);
	}
	Vector2<T> operator - (Vector2<T> val) const {
		return Vector2<T>(this->x - val.x, this->y - val.y);
	}
	Vector2<T>& operator += (Vector2<T> val){
		this->x += val.x;
		this->y += val.y;
		return *this;
	}
	Vector2<T> operator * (Vector2<T> val) const {
		Vector2<T> a;
		a.x = this->x * val.x;
		a.y = this->y * val.y;
		return a;
	}
	Vector2<T> operator * (float val) const {
		Vector2<T> a;
		a.x = this->x * val;
		a.y = this->y * val;
		return a;
	}
	Vector2<T> operator / (Vector2<T> val) const {
		Vector2<T> a;
		a.x = this->x / val.x;
		a.y = this->y / val.y;
		return a;
	}
	Vector2<T> operator / (float val) const {
		Vector2<T> a;
		a.x = this->x / val;
		a.y = this->y / val;
		return a;
	}
	///Conversions
	operator Vector2<int>() const {
		Vector2<int> vect(x, y);
		return vect;
	}
	operator Vector2<float>() const {
		Vector2<float> vect(x, y);
		return vect;
	}
	operator Vector2<double>() const {
		Vector2<double> vect(x, y);
		return vect;
	}
    operator std::string() const {
        std::stringstream str;
        str << "Vector2f: (x: " << x << ", y: " << y << ")";
        return str.str();
    }

public:
	T x, y;

//Lua functions
public:
    //Open the vector2f lib
    static int luaopen_vector2f(lua_State *l);
    //Add a vector2f to the table. i is relative to top
    static void addVector2f(lua_State *l, int i);
    //i is the stack index
    static Vector2<float>* checkVector2f(lua_State *l, int i = 1);

private:
    static const struct luaL_reg luaVector2fLib[];
    static int newVector2f(lua_State *l);
    static int setVector2f(lua_State *l);
    //Set/Get
    static int getX(lua_State *l);
    static int getY(lua_State *l);
    //__newindex accessor lookup
    static int accessor(lua_State *l);
    static int setX(lua_State *l);
    static int setY(lua_State *l);
    //operators
    static int toString(lua_State *l);
    static int concat(lua_State *l);
    static int equality(lua_State *l);
    static int addition(lua_State *l);
    static int subtraction(lua_State *l);
    static int multiply(lua_State *l);
    static int divide(lua_State *l);

};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

const struct luaL_reg Vector2f::luaVector2fLib[] = {
    { "set", Vector2f::setVector2f },
    { "x", Vector2f::getX },
    { "y", Vector2f::getY },
    { "__newindex", Vector2f::accessor },
    { "__tostring", Vector2f::toString },
    { "__concat", Vector2f::concat },
    { "__eq", Vector2f::equality },
    { "__add", Vector2f::addition },
    { "__sub", Vector2f::subtraction },
    { "__mul", Vector2f::multiply },
    { "__div", Vector2f::divide },
    { NULL, NULL }
};
template<class T>
int Vector2<T>::luaopen_vector2f(lua_State *l){
    //Stack: lib name
    //Push the metatable to contain the fcns onto the stack
    luaL_newmetatable(l, "LPC.Vector2f");
    //Copy metatable from -1 to the top
    lua_pushvalue(l, -1);
    //Set table at -2 key of __index = top of stack
    //ie. LPC.LuaRect.__index = table containing luaRectLib_m
    lua_setfield(l, -2, "__index");
    //Register the lib to the metatable at top of stack
    luaL_register(l, NULL, luaVector2fLib);
    //Stack: lib name, metatable
    //Add type identifier to the metatable
    lua_pushstring(l, "Vector2f");
    lua_setfield(l, -2, "type");
    //Stack: lib name, metatable
    //Setup the LuaRect table, for making LuaRects
    lua_newtable(l);
    //Stack: lib name, metatable, table
    //Push the new fcn
    lua_pushcfunction(l, newVector2f);
    //Stack: lib name, metatable, table, newLuaRect fcn
    //Now newLuaRect fcn is @ key __call in the table
    lua_setfield(l, -2, "__call");
    //Stack: lib name, metatable, table
    //We want to set the table containing __call to be the metatable
    //of the LuaRect metatable
    lua_setmetatable(l, -2);
    //Stack: lib name, metatable
    //Name our metatable and make it global
    lua_setglobal(l, "Vector2f");
    //Stack: lib name
    return 0;
}
template<class T>
void Vector2<T>::addVector2f(lua_State *l, int i){
    //Given stack containing unknown amount of things along with the udata
    //udata is at index i
    luaL_getmetatable(l, "LPC.Vector2f");
    //Now stack is ??? with the metatable at top
    //So we know the index of our rect is bumped down 1 more so we adjust
    //and set the table
    lua_setmetatable(l, i - 1);
}
template<class T>
Vector2<float>* Vector2<T>::checkVector2f(lua_State *l, int i = 1){
    return (Vector2<float>*)luaL_checkudata(l, i, "LPC.Vector2f");
}
template<class T>
int Vector2<T>::newVector2f(lua_State *l){
    //Stack: table, params if desired
    //remove the table
    lua_remove(l, 1);
    bool initVals = (lua_gettop(l) == 2);
    Vector2f *v = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    if (initVals){
        v->Set(luaL_checknumber(l, 1), luaL_checknumber(l, 2));
        //Remove params from stack
        for (int i = 0; i < 2; ++i)
            lua_remove(l, 1);
    }
    else
        v->Set(0, 0);
    addVector2f(l, -1);
    return 1;
}
template<class T>
int Vector2<T>::setVector2f(lua_State *l){
    //Stack: udata (vector2f), val for x, val for y
    Vector2f *v = checkVector2f(l);
    lua_remove(l, 1);
    //Stack: val for x, val for y
    v->Set(luaL_checknumber(l, 1), luaL_checknumber(l, 2));
    lua_pop(l, 2);
    //Stack: empty
    return 0;
}
template<class T>
int Vector2<T>::getX(lua_State *l){
    //Stack: udata (vector2f)
    Vector2f *v = checkVector2f(l);
    lua_pop(l, 1);
    lua_pushnumber(l, v->x);
    //Stack: val of x
    return 1;
}
template<class T>
int Vector2<T>::getY(lua_State *l){
    //Stack: udata (vector2f)
    Vector2f *v = checkVector2f(l);
    lua_pop(l, 1);
    lua_pushnumber(l, v->y);
    //Stack: val of x
    return 1;
}
template<class T>
int Vector2<T>::accessor(lua_State *l){
    //Stack: udata (vector2f), string of index to set, val to set
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
        default:
            break;
    }
    return 0;
}
template<class T>
int Vector2<T>::setX(lua_State *l){
    //Stack: udata (vector2f), val for x
    Vector2f *v = checkVector2f(l);
    float x = luaL_checknumber(l, 2);
    v->x = x;
    lua_pop(l, 2);    
    return 0;
}
template<class T>
int Vector2<T>::setY(lua_State *l){
    //Stack: udata (vector2f), val for y
    Vector2f *v = checkVector2f(l);
    float y = luaL_checknumber(l, 2);
    v->y = y;
    lua_pop(l, 2);    
    return 0;
}
template<class T>
int Vector2<T>::toString(lua_State *l){
    //Stack: udata (vector2f)
    Vector2f *v = checkVector2f(l);
    lua_pop(l, 1);
    lua_pushstring(l, ((std::string)(*v)).c_str());
    //Stack: the description string
    return 1;
}
template<class T>
int Vector2<T>::concat(lua_State *l){
    /*
    *  Stack has 2 possible configurations that we must
    *  detect and pick the right location to read the udata
    *  1. string, udata (vector2f)
    *  2. udata (vector2f), string
    */
    //Config 1
    if (lua_type(l, 1) == LUA_TSTRING){
        //Read the vector and pop it off
        Vector2f *v = checkVector2f(l, 2);
        std::string str = luaL_checkstring(l, 1);
        lua_pop(l, 2);
        //stack: empty
        //Push on string + description string
        lua_pushstring(l, (str + (std::string)(*v)).c_str());
    }
    //Config 2
    else {
        //Read the vector and pop it off
        Vector2f *v = checkVector2f(l, 1);
        std::string str = luaL_checkstring(l, 2);
        lua_pop(l, 2);
        //stack: empty
        //Push on string + description string
        lua_pushstring(l, ((std::string)(*v) + str).c_str());
    }
    return 1;
}
template<class T>
int Vector2<T>::equality(lua_State *l){
    //Stack: udata (vector2f), udata (vector2f)
    Vector2f *v = checkVector2f(l);
    Vector2f *v2 = checkVector2f(l, 2);
    lua_pop(l, 2);
    //Stack: empty
    lua_pushboolean(l, v == v2);
    return 1;
}
template<class T>
int Vector2<T>::addition(lua_State *l){
    //Stack: udata (vector2f), udata (vector2f)
    Vector2f *v = checkVector2f(l);
    Vector2f *v2 = checkVector2f(l, 2);
    lua_pop(l, 2);
    Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    result->Set(v->x + v2->x, v->y + v2->y);
    addVector2f(l, -1);
    return 1;
}
template<class T>
int Vector2<T>::subtraction(lua_State *l){
    //Stack: udata (vector2f), udata (vector2f)
    Vector2f *v = checkVector2f(l);
    Vector2f *v2 = checkVector2f(l, 2);
    lua_pop(l, 2);
    Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
    result->Set(v->x - v2->x, v->y - v2->y);
    addVector2f(l, -1);
    return 1;
}
template<class T>
int Vector2<T>::multiply(lua_State *l){
    /*
    *  There are 3 possible stacks we may get
    *  1. number, udata (Vector2f)
    *  2. udata (Vector2f), number
    *  3. udata (Vector2f), udata (Vector2f)
    */
    //Check for case 1
    if (lua_type(l, 1) == LUA_TNUMBER){
        Vector2f *v = (Vector2f*)checkVector2f(l, 2);
        float num = luaL_checknumber(l, 1);
        lua_pop(l, 2);
        Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        result->Set(v->x * num, v->y * num);
    }
    //Case 2
    else if (lua_type(l, 2) == LUA_TNUMBER){
        Vector2f *v = (Vector2f*)checkVector2f(l);
        float num = luaL_checknumber(l, 2);
        lua_pop(l, 2);
        Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        result->Set(v->x * num, v->y * num);
    }
    //Case 3
    else {
        Vector2f *v = checkVector2f(l);
        Vector2f *v2 = checkVector2f(l, 2);
        lua_pop(l, 2);
        Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        result->Set(v->x * v2->x, v->y * v2->y);
    }
    addVector2f(l, -1);
    return 1;
}
template<class T>
int Vector2<T>::divide(lua_State *l){
    /*
    *  There are 2 possible stacks we may get
    *  1. number, udata (Vector2f)
    *  2. udata (Vector2f), udata (Vector2f)
    */
    //Case 1
    if (lua_type(l, 1) == LUA_TNUMBER){
        Vector2f *v = checkVector2f(l, 2);
        float num = luaL_checknumber(l, 1);
        lua_pop(l, 2);
        Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        result->Set(v->x / num, v->y / num);
    }
    //Case 2
    else {
        Vector2f *v = checkVector2f(l);
        Vector2f *v2 = checkVector2f(l, 2);
        lua_pop(l, 2);
        Vector2f *result = (Vector2f*)lua_newuserdata(l, sizeof(Vector2f));
        result->Set(v->x / v2->x, v->y / v2->y);
    }
    addVector2f(l, -1);
    return 1;
}

#endif