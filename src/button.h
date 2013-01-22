#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "../externals/json/json.h"
#include "entity.h"
#include "image.h"
#include "text.h"

///A clickable ui Button, can run a static/non-member function when clicked
/**
*  A simple button class, for handling mouse input will run the registered function
*  when pressed, the button inherites its mouse event reading functionality from GameObject
*/
class Button : public Entity {
public:
	Button();
	/**
	*  Construct the Button and load its script
	*  @param script The object's script
	*/
	Button(std::string script);
	~Button();
	/**
	*  Draw the object, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	void Draw(std::weak_ptr<Camera> camera);
	///On click, run the callback function if one was registered
	///This should call a Lua script function, OnClick as well
	virtual void OnClick();
	/**
	*  Register a non-member function as the callback function to run when the
	*  button is pressed
	*  @param f The function to call, must be a function returning void and taking a string
	*  @param param The param to pass to the function
	*/
	void RegisterCallBack(void (*f)(std::string), std::string param);
	/**
	*  Save the object data to a json value and return it
	*  @see GameObject::Save for saving of inherited members
	*  @return The Json::Value containing the object data
	*/
	virtual Json::Value Save();
	/**
	*  Load the object from a Json::Value
	*  @see GameObject::Load for loading of inherited members
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);

protected:
	Text mText;
	///The callback function pointer & its value
	void (*mFunc)(std::string);
	std::string mParam;
};

#endif