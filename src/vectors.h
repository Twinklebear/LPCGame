#ifndef VECTORS_H
#define VECTORS_H

#include <string>
#include <sstream>
#include <SDL.h>
#include "externals/json/json.h"

///A 2D vector
/**
*  A 2D vector
*/
template<class T>
class Vector2 {
public:
	Vector2() : x(0), y(0) {
	}
	/**
	*  Setup the vector with an x & y value
	*  @param pX The x value to set
	*  @param pY The y value to set
	*/
	Vector2(T pX, T pY) : x(pX), y(pY) {
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
    /**
    *  Set the vector with the same values as another vector
    *  @param v the vector to get vals from
    */
    void Set(Vector2<T> &v){
        x = v.x;
        y = v.y;
    }
	/**
	*  Save the vector to a Json::Value
	*  @return The Json::Value containg the vector data
	*/
	Json::Value Save(){
		Json::Value val;
		val["x"] = x;
		val["y"] = y;
		return val;
	}
	/**
	*  Load the vector from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val){
		Set(val["x"].asFloat(), val["y"].asFloat());
	}
	///Operators
	Vector2<T> operator + (Vector2<T> val) const {
		return Vector2<T>(x + val.x, y + val.y);
	}
	Vector2<T> operator - (Vector2<T> val) const {
		return Vector2<T>(x - val.x, y - val.y);
	}
	Vector2<T>& operator += (Vector2<T> val){
		x += val.x;
		y += val.y;
		return *this;
	}
    bool operator == (Vector2<T> val) const {
        return (x == val.x && y == val.y);
    }
	Vector2<T> operator * (Vector2<T> val) const {
		Vector2<T> a(x * val.x, y * val.y);
		return a;
	}
	Vector2<T> operator * (float val) const {
		Vector2<T> a(x * val, y * val);
		return a;
	}
	Vector2<T> operator / (Vector2<T> val) const {
		Vector2<T> a(x / val.x, y / val.y);
		return a;
	}
	Vector2<T> operator / (float val) const {
		Vector2<T> a(x / val, y / val);
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
	operator SDL_Point() const {
		SDL_Point p;
		p.x = x;
		p.y = y;
		return p;
	}
    operator std::string() const {
        std::stringstream s;
        s << "Vector2: (x: " << x << ", y: "
            << y << ")";
        return s.str();
    }

public:
	T x, y;
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

#endif