#ifndef RECT_H
#define RECT_H

#include <stdexcept>
#include "SDL.h"
#include "vectors.h"

template<class T>
class Rect{
public:
	Rect(T pX, T pY, T pW, T pH){
		Set(pX, pY, pW, pH);
	}
	Rect(){
		Set(0, 0, 0, 0);
	}
	///Set the rect to some size
	void Set(T pX, T pY, T pW, T pH){
		x = pX;
		y = pY;
		w = pW;
		h = pH;
	}
	///Operators
	void operator += (Vector2f vec){
		x += vec.x;
		y += vec.y;
	}
	///For conversions
	operator SDL_Rect(){
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}
	operator Rect<float>(){
		Rect<float> rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}
	operator Rect<int>(){
		Rect<int> rect;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		return rect;
	}

public:
	T x, y, w, h;
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;

#endif