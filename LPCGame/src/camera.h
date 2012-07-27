#ifndef CAMERA_H
#define CAMERA_H

#include "window.h"
#include "rect.h"
#include "gameobject.h"

/*
*  A simple camera that can be given a gameobject to focus on
*  and follow, or can be moved manually
*/
class Camera{
public:
	Camera();
	~Camera();

private:
	std::shared_ptr<GameObject> mFocus;
	Rectf mBox;
};

#endif