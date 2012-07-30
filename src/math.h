#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "base.h"

///A math utility function namespace
/**
*  A math utility function namespace
*/
namespace Math{
	///Describes a direction
	enum { UP, DOWN, LEFT, RIGHT};
	/**
	*  Takes two vectors (points) and returns the distance between them
	*  @param a First point
	*  @param b Second point
	*  @return The distance
	*/
	float Distance(const Vector2f &a, const Vector2f &b);
	/**
	*  Clamp the value x between the range min and max
	*  @param x The value to clamp
	*  @param min The minimum value x can be
	*  @param max The max value x can be
	*  @return x if it is in range, or max if x is above, min if x is below
	*/
	float Clamp(const float x, const float min, const float max);
	/**
	*  Check if two rectangles are near each other and
	*  return the side of a that's near b
	*  TODO: Implement an early out for this function if the rect's are too far
	*  @param a The first Rect
	*  @param b The Rect to see if a is near
	*  @param tolerance The max distance the Rect's can be from each other, default is 0
	*  @return The enumerator representing the side of Rect A that's within tolerance of B, if none return -1
	*/
	int RectNearRect(const Rectf &a, const Rectf &b, int tolerance = 0);
	/**
	*  Check collision between two rectangles
	*  @param a First Rect
	*  @param b Second Rect
	*  @return T if collision, F otherwise
	*/
	bool CheckCollision(const Rectf &a, const Rectf &b);
	/**
	*  Check collision between a Vector and a rectangle
	*  ie. if the point is inside/on edge of the rectangle
	*  @param p The Vector2 (point)
	*  @param r The Rect
	*  @return T if point is in the rectangle
	*/
	bool CheckCollision(const Vector2f &p, const Rectf &r);
	/**
	*  Transform a vector from window space into scene space
	*  @param cam The camera/scene space to convert the vector to
	*  @param v The Vector2 to convert to scene space
	*  @return The Vector2 transformed to scene space
	*/
	Vector2f ToSceneSpace(const Camera *cam, const Vector2f &v);
	/**
	*  Transform a rect into scene space from window space
	*  @param cam The camera/scene space to convert the vector to
	*  @param r The Rect to convert to scene space
	*  @return The Rect with its pos value transformed to scene space
	*/
	Rectf ToSceneSpace(const Camera *cam, const Rectf &r);
	/**
	*  Transform a vector from scene space into window space
	*  @param cam The camera/scene space to convert the vector to
	*  @param v The Vector2 to convert to window space
	*  @return The Vector2 transformed to window space
	*/
	Vector2f FromSceneSpace(const Camera *cam, const Vector2f &v);
	/**
	*  Transform a rect from scene space to window space
	*  @param cam The camera/scene space to convert the vector to
	*  @param r The Rect to convert to window space
	*  @return The Rect with its pos value converted to window space
	*/
	Rectf FromSceneSpace(const Camera *cam, const Rectf &r);
}

#endif