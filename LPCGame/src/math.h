#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "vectors.h"
#include "rect.h"

/**
*	A math utility function namespace
*/
namespace Math{
	///Describes a direction
	enum { UP, DOWN, LEFT, RIGHT};
	/**
	*   Takes two vectors (points) and returns the distance between them
	*	@param a: first point
	*	@param b: second point
	*	@return: the distance
	*/
	float Distance(const Vector2f &a, const Vector2f &b);
	/**
	*	Check if two rectangles are near each other, and return the side of
	*	@param A: the rectangle we want to see
	*	@param B: the rectangle we want to see if a is close too
	*	@param tolerance: the tolerance distance to accept for "nearness"
	*	@return: the enumerator representing the side of Rect A that's within tolerance of B, if none return -1
	*/
	int RectNearRect(const Rectf &a, const Rectf &b, int tolerance);
	/**
	*	Check collision between to rectangles
	*	@param A first rectangle
	*	@param B second rectangle
	*	@param return: T if collision, F if no collision
	*/
	bool CheckCollision(const Rectf &a, const Rectf &b);
}

#endif