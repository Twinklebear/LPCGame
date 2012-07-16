#ifndef BUTTON_H
#define BUTTON_H

#include "gameobject.h"
#include "image.h"

/*
*  A simple button class, for handling mouse input
*  inherites its mouse event reading functionality from GameObject
*/
class Button : public GameObject{
public:
	Button();
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
	void OnMouseUp() ;
	///On mouse enter
	void OnMouseEnter();
	///On mouse exit
	void OnMouseExit();

private:
	//Disable copy-construction
	Button(const Button &a);
	Button& operator = (const Button &a);

private:
	Image mImage;
	Debugger *dbg;
};

#endif