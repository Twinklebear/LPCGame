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
	*	@param a: the rectangle we want to see
	*	@param b: the rectangle we want to see if a is close too
	*	@param tolerance: the tolerance distance to accept for "nearness", default is 0, ie 'touching'
	*	@return: the enumerator representing the side of Rect A that's within tolerance of B, if none return -1
	*/
	int RectNearRect(const Rectf &a, const Rectf &b, int tolerance = 0);
	/**
	*	Check collision between to rectangles
	*	@param a first rectangle
	*	@param b second rectangle
	*	@return: T if collision, F if no collision
	*/
	bool CheckCollision(const Rectf &a, const Rectf &b);
	/**
	*	Check collision between a point and a rectangle
	*	ie. if the point is inside/on edge of the rectangle
	*	@param p: the point
	*	@param r: the rectangle
	*	@return: T if point is in the rectangle
	*/
	bool CheckCollision(const Vector2f &p, const Rectf &r);
}

#endif