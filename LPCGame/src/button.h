#ifndef BUTTON_H
#define BUTTON_H

#include "gameobject.h"
#include "image.h"

/*
*  A simple button class, for handling mouse input will run the registered function
*  when pressed, the button inherites its mouse event reading functionality from GameObject
*/
//template <class object>
class Button : public GameObject{
public:
	Button(){
		//mObj	 = nullptr;
		//mObjFunc = nullptr;
		mFunc    = nullptr;
		mClicked = false;
	}
	~Button(){}
	///Initialize the button
	void Start(int x = 0, int y = 0){
		Rectf box(x, y, 200, 100);
		mPhysics.SetBox(box);
		//setup physical constants
		PhysicalConstants physConst;
		physConst.hSpeed	= 0;
		physConst.hAccel	= 0;
		mPhysics.SetPhysConstants(physConst);
		mClicked = false;

		mImage.LoadImage("images/200x100button.png");
		//Setup image clips
		std::vector<Recti> clips;
		clips.push_back(Recti(0, 0, 200, 100));
		clips.push_back(Recti(0, 100, 200, 100));
		mImage.SetClips(clips);
	}
	///Update the game object
	void Update(){}
	///Draw the game object
	void Draw(){
		if (!mClicked)
			Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(0));
		else
			Window::Draw(&mImage, (SDL_Rect)mPhysics.Box(), &(SDL_Rect)mImage.Clip(1));
	}
	///Move the object
	void Move(float deltaT){}
	///On mouse down events
	void OnMouseDown(){
		mClicked = true;
	}
	///On mouse up event
	void OnMouseUp(){
		if (mClicked)
			OnClick();
		mClicked = false;
		//Run the button activity here
	}
	///On mouse enter
	void OnMouseEnter(){
		//maybe a lighter highlight?
	}
	///On mouse exit
	void OnMouseExit(){
		mClicked = false;
	}
	//On click, run the callback function if one was registered
	void OnClick(){
		if (mFunc != nullptr)
			mFunc();
		//else if (mObj != nullptr && mObjFunc != nullptr)
		//	((mObj).*(mObjFunc))();
	}
	/*
	*  Register an object and the object function to call when the button is pressed
	*  @param obj: The object context to call the function in
	*  @prarm func: The function on the object to call
	*/
	/*
	void RegisterCallBack(object *obj, void (object::*func)()){
		mObj = obj;
		mObjFunc = func;
		mFunc = nullptr;
	*/
	/*
	*  Register a non-member function as the callback function to run when the
	*  button is pressed
	*  @param f: the function to call
	*/
	void RegisterCallBack(void (*f)()){
		mFunc = f;
		//mObj = nullptr;
		//mObjFunc = nullptr;
	}

private:
	//Disable copy-construction
	Button(const Button &a);
	Button& operator = (const Button &a);

private:
	Image mImage;
	bool mClicked;
	//The callback object & function pointers
	//object *mObj;
	//void (object::*mObjFunc)();
	void (*mFunc)();
};

#endif