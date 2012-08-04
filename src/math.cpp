#include "base.h"
#include "camera.h"
#include "math.h"

float Math::Distance(const Vector2f &a, const Vector2f &b){
	return (float)sqrt(pow(b.x - a.x, 2.0) + pow(b.y - a.y, 2.0));
}
float Math::Clamp(const float x, const float min, const float max){
	if (x >= max)
		return max;
	if (x <= min)
		return min;
	return x;
}
float Math::Magnitude(const Vector2f &v){
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
Vector2f Math::Normalize(const Vector2f &v){
	return (v / Magnitude(v));
}
Vector2f Math::Lerp(const Vector2f &start, const Vector2f &end, float percent){
	return (start + (end - start) * percent);
}
int Math::RectNearRect(const Rectf &a, const Rectf &b, int tolerance){
	//Simple enough to do:
	//we create 4 points for each rect, for A's top we center it in x, and put it at the y
	//and compare A's top to B's bottom to see if the distance is within the tolerance, if it is, return UP
	//to say that A's topside is close to B
	//Point names: rect SIDE, so aT is A's Topside
	Vector2f aSides[4], bSides[4];

	//setup the points
	aSides[UP].x	= a.X() + a.W() / 2.0f;
	aSides[UP].y	= a.Y();
	aSides[DOWN].x	= aSides[UP].x;
	aSides[DOWN].y	= a.Y() + a.H();
	aSides[LEFT].x	= a.X();
	aSides[LEFT].y	= a.Y() + a.H() / 2.0f;
	aSides[RIGHT].x = a.X() + a.W();
	aSides[RIGHT].y = aSides[LEFT].y;

	bSides[UP].x	= b.X() + b.W() / 2.0f;
	bSides[UP].y	= b.Y();
	bSides[DOWN].x	= bSides[UP].x;
	bSides[DOWN].y	= b.Y() + b.H();
	bSides[LEFT].x	= b.X();
	bSides[LEFT].y	= b.Y() + b.H() / 2.0f;
	bSides[RIGHT].x = b.X() + b.W();
	bSides[RIGHT].y = bSides[LEFT].y;

	//now we check which side of A is closest to the opposite side of B
	//aT near bB, aR near bL, etc.
	if (Distance(aSides[UP]	  , bSides[DOWN])  <= tolerance) return UP;
	if (Distance(aSides[DOWN] , bSides[UP])    <= tolerance) return DOWN;
	if (Distance(aSides[RIGHT], bSides[LEFT])  <= tolerance) return RIGHT;
	if (Distance(aSides[LEFT] , bSides[RIGHT]) <= tolerance) return LEFT;

	//if none are near return -1, for fail
	return -1;
}
bool Math::CheckCollision(const Rectf &a, const Rectf &b){
	//Do easy out checks first, as it's more likely that there isn't a collision
	if (a.Y() + a.H() <= b.Y())
		return false;
	if (a.Y() >= b.Y() + b.H())
		return false;
	if (a.X() + a.W() <= b.X())
		return false;
	if (a.X() >= b.X() + b.W())
		return false;
	//if no early outs trigger, there is a collision
	return true;
}
bool Math::CheckCollision(const Vector2f &p, const Rectf &r){
	if ((p.x > r.X() && p.x < r.X() + r.W()) && (p.y > r.Y() && p.y < r.Y() + r.H()))
		return true;
	return false;
}
Vector2f Math::ToSceneSpace(const Camera *cam, const Vector2f &v){
	return v + cam->Offset();
}
Rectf Math::ToSceneSpace(const Camera *cam, const Rectf &r){
	return Rectf(ToSceneSpace(cam, r.pos), r.w, r.h);
}
Vector2f Math::FromSceneSpace(const Camera *cam, const Vector2f &v){
	return v - cam->Offset();
}
Rectf Math::FromSceneSpace(const Camera *cam, const Rectf &r){
	return Rectf(FromSceneSpace(cam, r.pos), r.w, r.h);
}
