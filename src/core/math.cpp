#include <cmath>
#include <memory>
#include "base.h"
#include "debug.h"
#include "camera.h"
#include "math.h"

float Math::Distance(const Vector2f &a, const Vector2f &b){
	return sqrtf(powf(b.x - a.x, 2.0) + powf(b.y - a.y, 2.0));
}
float Math::Clamp(const float x, const float min, const float max){
	if (x >= max)
		return max;
	if (x <= min)
		return min;
	return x;
}
float Math::Magnitude(const Vector2f &v){
	return sqrtf(powf(v.x, 2) + powf(v.y, 2));
}
Vector2f Math::Normalize(const Vector2f &v){
    //Catch case where vector is 0, 0
    if (Magnitude(v) == 0)
        return Vector2f(0, 0);
	return (v / Magnitude(v));
}
Vector2f Math::Lerp(const Vector2f &start, const Vector2f &end, float percent){
	return (start + (end - start) * percent);
}
Vector2f Math::ForwardVector(float degrees){
	Vector2f v;
	float rad = (degrees * 3.14) / 180;
	v.x = cosf(rad);
	v.y = sinf(rad);
	return v;
}
int Math::RectNearRect(const Rectf &a, const Rectf &b, int tolerance){
	//Simple enough to do:
	//we create 4 points for each rect, for A's top we center it in x, and put it at the y
	//and compare A's top to B's bottom to see if the distance is within the tolerance, if it is, return UP
	//to say that A's topside is close to B
	//Point names: rect SIDE, so aT is A's Topside
	Vector2f aSides[4], bSides[4];

	//setup the points
	aSides[UP].x	= a.pos.x + a.w / 2.0f;
	aSides[UP].y	= a.pos.y;
	aSides[DOWN].x	= aSides[UP].x;
	aSides[DOWN].y	= a.pos.y + a.h;
	aSides[LEFT].x	= a.pos.x;
	aSides[LEFT].y	= a.pos.y + a.h / 2.0f;
	aSides[RIGHT].x = a.pos.x + a.w;
	aSides[RIGHT].y = aSides[LEFT].y;

	bSides[UP].x	= b.pos.x + b.w / 2.0f;
	bSides[UP].y	= b.pos.y;
	bSides[DOWN].x	= bSides[UP].x;
	bSides[DOWN].y	= b.pos.y + b.h;
	bSides[LEFT].x	= b.pos.x;
	bSides[LEFT].y	= b.pos.y + b.h / 2.0f;
	bSides[RIGHT].x = b.pos.x + b.w;
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
	if (a.pos.y + a.h <= b.pos.y)
		return false;
	if (a.pos.y >= b.pos.y + b.h)
		return false;
	if (a.pos.x + a.w <= b.pos.x)
		return false;
	if (a.pos.x >= b.pos.x + b.w)
		return false;
	//if no early outs trigger, there is a collision
	return true;
}
bool Math::CheckCollision(const Vector2f &p, const Rectf &r){
	if ((p.x > r.pos.x && p.x < r.pos.x + r.w) && (p.y > r.pos.y && p.y < r.pos.y + r.h))
		return true;
	return false;
}
Vector2f Math::ToSceneSpace(const std::weak_ptr<Camera> cam, const Vector2f &v){
    if (!cam.expired()){
        auto c = cam.lock();
        return v + c->Offset();
    }
    Debug::Log("Math::ToSceneSpace vector error: Camera expired");
    return v;
}
Rectf Math::ToSceneSpace(const std::weak_ptr<Camera> cam, const Rectf &r){
	return Rectf(ToSceneSpace(cam, r.pos), r.w, r.h);
}
Vector2f Math::FromSceneSpace(const std::weak_ptr<Camera> cam, const Vector2f &v){
	if (!cam.expired()){
        auto c = cam.lock();
        return v - c->Offset();
    }
    Debug::Log("Math::FromSceneSpace vector error: Camera expired");
    return v;
}
Rectf Math::FromSceneSpace(const std::weak_ptr<Camera> cam, const Rectf &r){
	return Rectf(FromSceneSpace(cam, r.pos), r.w, r.h);
}
