#ifndef RECT_H
#define RECT_H

#include <stdexcept>
#include "json/json.h"
#include "SDL.h"
#include "vectors.h"

template<class T>
class Rect{
public:
	Rect(){
		Set(0, 0, 0, 0);
	}
	Rect(T pX, T pY, T pW, T pH){
		Set(pX, pY, pW, pH);
	}
	Rect(Vector2<T> pPos, T pW, T pH){
		Set(pPos, pW, pH);
	}
	///Set the rect to some size
	void Set(T pX, T pY, T pW, T pH){
		//pos = Vector2<T>(pX, pY);
		pos.x = pX;
		pos.y = pY;
		w = pW;
		h = pH;
	}
	void Set(Vector2<T> pPos, T pW, T pH){
		pos = pPos;
		w = pW;
		h = pH;
	}
	void Set(T pX, T pY){
		pos.x = pX;
		pos.y = pY;
	}
	void Set(Vector2<T> pPos){
		pos = pPos;
	}
	Vector2<T> Pos() const{
		return pos;
	}
	T X() const{
		return pos.x;
	}
	T Y() const{
		return pos.y;
	}
	T W() const{
		return w;
	}
	T H() const{
		return h;
	}
	/*
	*  Save the box's properties to a Json::Value and return it
	*  @returns: The Json::Value containing the box's properties
	*/
	Json::Value Save(){
		Json::Value val;
		val["x"] = pos.x;
		val["y"] = pos.y;
		val["w"] = w;
		val["h"] = h;
		return val;
	}
	/*
	*  Load the box's properties from a Json::Value
	*  @param val: The Json::Value containing the properties to load
	*/
	void Load(Json::Value val){
		Set(val["x"].asInt(), val["y"].asInt(),
			val["w"].asInt(), val["h"].asInt());
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
	//For conversions
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