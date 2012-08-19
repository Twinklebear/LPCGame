#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <vector>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "base.h"
#include "window.h"
#include "entity.h"

///Describes a simple Camera animation
/**
*  Describes a Camera motion animation, the destination Vector2
*  and the spee to travel there at
*/
struct CameraPan{
	std::string name;
	Vector2i destination;
	int speed;
};

///A camera to draw the scene in
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
	void SetFocus(std::shared_ptr<Entity> obj);
	///Update the camera's position to keep the object centered
	void Update();
	/**
	*  Check if an Rect is in the camera
	*  @param box The box to check if it's in the camera
	*  @return True if object is in camera
	*/
	bool InCamera(Rectf box) const;
	/**
	*  Move the camera by some Vector2
	*  This is used for dragging the camera with the mouse
	*  @param v The distance to move the camera
	*/
	void Move(Vector2f v);
	/**
	*  Move the camera taking into account some elapsed time deltaT
	*  This is used for pan animations
	*  @param deltaT The elapsed time
	*/
	void Move(float deltaT);
	/**
	*  Instruct the camera to play some pre-defined panning
	*  @param name The name of the animation to play, if name not found nothing will happen
	*/
	void Pan(std::string name);
	/**
	*  Get the active scene
	*  @return The name of the scene, "busy" means the camera is panning
	*/
	std::string Scene();
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
	///Get the scene box
	Rectf SceneBox();
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
	/**
	*  Save the camera information to file
	*  @return Json::Value containing the camera's information
	*/
	Json::Value Save();
	/**
	*  Load the camera configuration from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);
	/**
	*  Register the AnimatedImage functions with the lua state
	*  @param l The lua_State to register the module with
	*/
	void RegisterLua(lua_State *l);

private:
	std::weak_ptr<Entity> mFocus;
	Rectf mBox, mSceneBox;
	std::vector<CameraPan> mPans;
	int mActivePan;
	std::string mScene;
};

#endif