#ifndef RECT_H
#define RECT_H

#include <stdexcept>
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
	///Operators
	Rect<T>& operator += (Vector2f vec){
		this->pos += vec;
		return *this;
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

private:
	Vector2<T> pos;
	T w, h;
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;

#endif