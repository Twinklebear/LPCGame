#ifndef BUTTON_H
#define BUTTON_H

#include "../externals/json/json.h"
#include "gameobject.h"
#include "image.h"
#include "text.h"

/**
*  A simple button class, for handling mouse input will run the registered function
*  when pressed, the button inherites its mouse event reading functionality from GameObject
*/
class Button : public GameObject{
public:
	Button();
	~Button();
	///Update the game object
	void Update();
	/**
	*  Draw the object, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	void Draw(Camera *cam = nullptr);
	/**
	*  Move the object
	*  @param deltaT The elapsed time
	*/
	void Move(float deltaT);
	///On mouse down events
	void OnMouseDown();
	///On mouse up event
	void OnMouseUp();
	///On mouse enter
	void OnMouseEnter();
	///On mouse exit
	void OnMouseExit();
	///On click, run the callback function if one was registered
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
	*  @return The Json::Value containing the object data
	*/
	virtual Json::Value Save();
	/**
	*  Load the object from a json value
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);

private:
	Button(const Button &a);
	Button& operator = (const Button &a);

protected:
	Image mImage;
	Text mText;
	bool mClicked;
	///The callback function pointer & its value
	void (*mFunc)(std::string);
	std::string mParam;
};

#endif