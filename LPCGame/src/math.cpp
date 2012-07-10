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
	aT.x = (a.X() + a.W()) / 2.0f;
	aT.y = a.Y();
	aB.x = aT.x;
	aB.y = a.Y() + a.H();
	aL.x = a.X();
	aL.y = (a.Y() + a.H()) / 2.0f;
	aR.x = a.X() + a.W();
	aR.y = aL.y;

	bT.x = (b.X() + b.W()) / 2.0f;
	bT.y = b.Y();
	bB.x = bT.x;
	bB.y = b.Y() + b.H();
	bL.x = b.X();
	bL.y = (b.Y() - b.H()) / 2.0f;
	bR.x = b.X() + b.W();
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
	if (a.Y() + a.H() <= b.Y())
		return false;
	if (a.Y() >= b.Y() + b.H())
		return false;
	if (a.X() + a.Y() <= b.X())
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