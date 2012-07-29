#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "base.h"
#include "window.h"
#include "gameobject.h"

/**
*  A simple camera that can be given a gameobject to focus on
*  and follow, or can be moved manually
*/
class Camera{
public:
	Camera();
	~Camera();
	/**
	*  Register the gameobject to focus on with the camera
	*  @param obj The object for the camera to follow/center on
	*/
	void SetFocus(std::shared_ptr<GameObject> obj);
	///Update the camera's position to keep the object centered
	void Update();
	/**
	*  Check if an Rect is in the camera
	*  @param box The box to check if it's in the camera
	*  @return True if object is in camera
	*/
	bool InCamera(Rectf box) const;
	/**
	*  Set the camera box equal to the Rect passed, a check is performed
	*  to make sure that the camera box isn't bigger than the scene box
	*  if no scene box is set no problem, the check is also done when setting a scene box
	*  @param box The rect to set the camera box too
	*/
	void SetBox(Rectf box);
	///Returns the camera's box
	Rectf Box() const;
	/**
	*  Set the scene's box, a check is done to make sure the camera box
	*  isn't bigger than the scene's box
	*  @param box The box to set the scene box too
	*/
	void SetSceneBox(Rectf box);
	/**
	*  Get the offset needed to apply to objects in the camera,
	*  this offset includes the centering offset and any offset added
	*  from moving the camera
	*  @return a Vector2f that is the offset to apply
	*/
	Vector2f Offset() const;
	/**
	*  Get the offset needed to center the scene in the window
	*  @return a Vector2f containing the offset to apply
	*/
	Vector2f Centering() const;

private:
	std::weak_ptr<GameObject> mFocus;
	Rectf mBox, mSceneBox;
};

#endif