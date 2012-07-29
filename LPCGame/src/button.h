#ifndef BUTTON_H
#define BUTTON_H

#include "gameobject.h"
#include "image.h"
#include "text.h"

/*
*  A simple button class, for handling mouse input will run the registered function
*  when pressed, the button inherites its mouse event reading functionality from GameObject
*/
class Button : public GameObject{
public:
	Button();
	~Button();
	///Update the game object
	void Update();
	/*
	*  Draw the object, apply an adjustment for the camera if one is desired
	*  @param cam: the camera to adjust for
	*/
	void Draw(Camera *cam = nullptr);
	///Move the object
	void Move(float deltaT);
	///On mouse down events
	void OnMouseDown();
	///On mouse up event
	void OnMouseUp();
	///On mouse enter
	void OnMouseEnter();
	///On mouse exit
	void OnMouseExit();
	//On click, run the callback function if one was registered
	virtual void OnClick();
	/*
	*  Register a non-member function as the callback function to run when the
	*  button is pressed
	*  @param f: the function to call
	*/
	void RegisterCallBack(void (*f)(std::string), std::string param);
	/*
	*  Save the object data to a json value and return it
	*  @returns: The json value containing the object data
	*/
	virtual Json::Value Save();
	/*
	*  Load the object from a json value
	*  @param value: The json value to load from
	*/
	virtual void Load(Json::Value val);

private:
	//Disable copy-construction
	Button(const Button &a);
	Button& operator = (const Button &a);

protected:
	Image mImage;
	Text mText;
	bool mClicked;
	//The callback function pointer & its value
	void (*mFunc)(std::string);
	std::string mParam;
};

#endif