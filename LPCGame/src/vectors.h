#ifndef VECTORS_H
#define VECTORS_H

///A simple vector
template<class T>
class Vector2{
public:
	Vector2(T pX, T pY){
		Set(pX, pY);
	}
	Vector2(){
		Set(0, 0);
	}
	///Set the vector to some value
	void Set(T pX, T pY){
		x = pX;
		y = pY;
	}
	///Operators
	Vector2<T> operator + (Vector2<T> val){
		Vector2<T> a;
		a.x = this->x + val.x;
		a.y = this->y + val.y;
		return a;
	}
	Vector2<T> operator * (Vector2<T> val){
		Vector2<T> a;
		a.x = this->x * val.x;
		a.y = this->y * val.y;
		return a;
	}
	Vector2<T> operator * (float val){
		Vector2<T> a;
		a.x = this->x * val;
		a.y = this->y * val;
		return a;
	}

public:
	T x, y;
};

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

#endif