#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "base.h"
#include "window.h"
#include "gameobject.h"

/*
*  A simple camera that can be given a gameobject to focus on
*  and follow, or can be moved manually
*/
class Camera{
public:
	Camera();
	~Camera();
	/*
	*  Register the gameobject to focus on with the camera
	*  @param obj: the object for the camera to follow/center on
	*/
	void SetFocus(std::shared_ptr<GameObject> obj);
	//Update the camera's position to keep the object centered
	void Update();
	/*
	*  Check if an Rect is in the camera
	*  @param box: the box to check if it's in the camera
	*  @returns: True if object is in camera
	*/
	bool InCamera(Rectf box) const;
	//Setters & Getters
	void SetBox(Rectf box);
	Rectf Box() const;
	void SetSceneBox(Rectf box);
	//Returns the offset to apply to objects that should be scrolling
	Vector2f Offset() const;
	//An offset to center the images
	Vector2f Centering() const;

private:
	std::weak_ptr<GameObject> mFocus;
	//TODO: Should scene box be a pointer to the state's scene box?
	//that way if it's updated the camera will update as well
	Rectf mBox, mSceneBox;
};

#endif