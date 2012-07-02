#include "math.h"

float Math::Distance(const Vector2f &a, const Vector2f &b){
	return (float)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2.0));
}
int Math::RectNearRect(const Rectf &a, const Rectf &b, int tolerance){
	//Simple enough to do:
	//we create 4 points for each rect, for A's top we center it in x, and put it at the y
	//and compare A's top to B's bottom to see if the distance is within the tolerance, if it is, return UP
	//to say that A's topside is close to B
	//Point names: rect SIDE, so aT is A's Topside
	Vector2f aT, aB, aR, aL, bT, bB, bR, bL;

	//setup the points
	aT.x = (a.x + a.w) / 2.0f;
	aT.y = a.y;
	aB.x = aT.x;
	aB.y = a.y + a.h;
	aL.x = a.x;
	aL.y = (a.y + a.h) / 2.0f;
	aR.x = a.x + a.w;
	aR.y = aL.y;

	bT.x = (b.x + b.w) / 2.0f;
	bT.y = b.y;
	bB.x = bT.x;
	bB.y = b.y + b.h;
	bL.x = b.x;
	bL.y = (b.y - b.h) / 2.0f;
	bR.x = b.x + b.w;
	bR.y = bL.y;

	//now we check which side of A is closest to the opposite side of B
	//aT near bB, aR near bL, etc.
	if (Distance(aT, bB) <= tolerance) return UP;
	if (Distance(aB, bT) <= tolerance) return DOWN;
	if (Distance(aR, bL) <= tolerance) return RIGHT;
	if (Distance(aL, bR) <= tolerance) return LEFT;

	//if none are near return -1, for fail
	return -1;
}
bool Math::CheckCollision(const Rectf &a, const Rectf &b){
	//Do easy out checks first, as it's more likely that there isn't a collision
	if (a.y + a.h <= b.y)
		return false;
	if (a.y >= b.y + b.h)
		return false;
	if (a.x + a.w <= b.x)
		return false;
	if (a.x >= b.x + b.w)
		return false;
	//if no early outs trigger, there is a collision
	return true;
}