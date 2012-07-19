#ifndef BUTTON_H
#define BUTTON_H

#include "gameobject.h"
#include "image.h"

/*
*  A simple button class, for handling mouse input will run the registered function
*  when pressed, the button inherites its mouse event reading functionality from GameObject
*/
class Button : public GameObject{
public:
	Button();
	Button(int x, int y, std::string text = "", int w = 0, int h = 0);
	~Button();
	///Initialize the button
	void Start(int x = 0, int y = 0);
	///Update the game object
	void Update();
	///Draw the game object
	void Draw();
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
	void OnClick();
	/*
	*  Register an object and the object function to call when the button is pressed
	*  @param obj: The object context to call the function in
	*  @prarm func: The function on the object to call
	*  TODO: Need a better way to have buttons that handle non-static member functions
	*/
	/*
	void RegisterCallBack(object *obj, void (object::*func)()){
		mObj = obj;
		mObjFunc = func;
		mFunc = nullptr;
	}
	*/
	/*
	*  Register a non-member function as the callback function to run when the
	*  button is pressed
	*  @param f: the function to call
	*/
	void RegisterCallBack(void (*f)());

private:
	//Disable copy-construction
	Button(const Button &a);
	Button& operator = (const Button &a);

private:
	Image mImage;
	bool mClicked;
	//The callback function pointer
	void (*mFunc)();
};

#endif