#ifndef RECT_H
#define RECT_H

#include <stdexcept>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include "../externals/json/json.h"
#include "SDL.h"
#include "vectors.h"

///A rectangle
/**
*  Describes a rectangle, can use ints, floats or doubles
*  to represent its values
*/
template<class T>
class Rect{
public:
	Rect(){
		Set(0, 0, 0, 0);
	}
	/**
	*  Construct the rect and set its properties
	*  @param pX The x position
	*  @param pY The y position
	*  @param pW The width
	*  @param pH The height
	*/
	Rect(T pX, T pY, T pW, T pH){
		Set(pX, pY, pW, pH);
	}
	/**
	*  Construct the rect and set its properties
	*  @param pPos The position, as a vector
	*  @param pW The width
	*  @param pH The height
	*/
	Rect(Vector2<T> pPos, T pW, T pH){
		Set(pPos, pW, pH);
	}
	/**
	*  Set the rect's properties
	*  @param pX The x position
	*  @param pY The y position
	*  @param pW The width
	*  @param pH The height
	*/
	void Set(T pX, T pY, T pW, T pH){
		pos.x = pX;
		pos.y = pY;
		w = pW;
		h = pH;
	}
	/**
	*  Set the rect's properties
	*  @param pPos The position, as a vector
	*  @param pW The width
	*  @param pH The height
	*/
	void Set(Vector2<T> pPos, T pW, T pH){
		pos = pPos;
		w = pW;
		h = pH;
	}
	/**
	*  Set the rect's position
	*  @param pX The x position
	*  @param pY The y position
	*/
	void Set(T pX, T pY){
		pos.x = pX;
		pos.y = pY;
	}
	/**
	*  Set the rect's position
	*  @param pPos The position vector
	*/
	void Set(Vector2<T> pPos){
		pos = pPos;
	}
	///Get the rect's position vector
	Vector2<T> Pos() const{
		return pos;
	}
	///Get x value
	T X() const{
		return pos.x;
	}
	///Get y value
	T Y() const{
		return pos.y;
	}
	///Get width
	T W() const{
		return w;
	}
	///Get height
	T H() const{
		return h;
	}
	/**
	*  Save the box's properties to a Json::Value and return it
	*  @return Json::Value containing the box's properties
	*/
	Json::Value Save(){
		Json::Value val;
		val["x"] = pos.x;
		val["y"] = pos.y;
		val["w"] = w;
		val["h"] = h;
		return val;
	}
	/**
	*  Load the box's properties from a Json::Value
	*  @param val The Json::Value containing the properties to load
	*/
	void Load(Json::Value val){
		Set(val["x"].asInt(), val["y"].asInt(),
			val["w"].asInt(), val["h"].asInt());
	}
	/**
	*  Register the Rect class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static void RegisterLua(lua_State *l){
		using namespace luabind;
		///Does Lua/LuaBind support templates?
		module(l, "LPC")[
			//For Rect<float>
			class_<Rect<float>>("Rectf")
				.def(constructor<>())
				.def(constructor<float, float, float, float>())
				.def(constructor<Vector2f, float, float>())
				.def("Set", (void (Rect<float>::*)(float, float, float, float))&Rect<float>::Set)
				.def("Set", (void (Rect<float::*)(Vector2f, float, float))&Rect<float>::Set)
				.def("Set", (void (Rect<float::*)(float, float))&Rect::<float>::Set)
				.def("Set", (void (Rect<float::*)(Vector2f))&Rect::<float>::Set)
				.def("Pos", &Rect<float>::Pos)
				.def("X", &Rect<float>::X)
				.def("Y", &Rect<float>::Y)
				.def("W", &Rect<float>::W)
				.def("H", &Rect<float>::H)
				.def(const_self + Vector2f())
				.def(const_self - Vector2f()),
			//For Rect<int>
			class_<Rect<int>>("Recti")
				.def(constructor<>())
				.def(constructor<int, int, int, int>())
				.def(constructor<Vector2f, int, int>())
				.def("Set", (void (Rect<int>::*)(int, int, int, int))&Rect<int>::Set)
				.def("Set", (void (Rect<int::*)(Vector2f, int, int))&Rect<int>::Set)
				.def("Set", (void (Rect<int::*)(int, int))&Rect::<int>::Set)
				.def("Set", (void (Rect<int::*)(Vector2f))&Rect::<int>::Set)
				.def("Pos", &Rect<int>::Pos)
				.def("X", &Rect<int>::X)
				.def("Y", &Rect<int>::Y)
				.def("W", &Rect<int>::W)
				.def("H", &Rect<int>::H)
				.def(const_self + Vector2i())
				.def(const_self - Vector2i())
		];
	}
	///Operators
	Rect<T>& operator += (Vector2f vec){
		this->pos += vec;
		return *this;
	}
	Rect<T> operator + (const Vector2f v) const{
		return Rect<T>(pos.x + v.x, pos.y + v.y, w, h);
	}
	Rect<T> operator - (const Vector2f v) const{
		return Rect<T>(pos.x - v.x, pos.y - v.y, w, h);
	}
	///For conversions
	operator SDL_Rect(){
		SDL_Rect rect;
		rect.x = pos.x;
		rect.y = pos.y;
		rect.w = w;
		rect.h = h;
		return rect;
	}
	operator Rect<float>(){
		Rect<float> rect(pos, w, h);
		return rect;
	}
	operator Rect<int>(){
		Rect<int> rect(pos, w, h);
		return rect;
	}

public:
	Vector2<T> pos;
	T w, h;
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;

#endif