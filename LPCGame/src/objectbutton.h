#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H

#include "gameobject.h"
#include "image.h"
#include "text.h"
#include "button.h"

/*
*  A button that is able to register class member functions as its callback
*/
template<class T>
class ObjectButton : public Button{
public:
	ObjectButton() 
		: mObj(nullptr), mObjFunc(nullptr)
	{
		mFunc = nullptr;
	}
	ObjectButton(int x, int y, std::string text, int w = 0, int h = 0)
		: mObj(nullptr), mObjFunc(nullptr)
	{
		mFunc = nullptr;
		SDL_Color col;
		col.r = 0;
		col.g = 0;
		col.b = 0;
		mText.Setup(text, "fonts/LiberationSans-Regular.ttf", col, 25);
		Start(x, y);
	}
	~ObjectButton(){
	}
	/*
	*  Register an object and the object function to call when the button is pressed
	*  @param obj: The object context to call the function in
	*  @param func: The function on the object to call
	*  @param param: The parameter to pass to the function when calling it
	*  TODO: Need a better way to have buttons that handle non-static member functions
	*/
	void RegisterCallBack(T *obj, void (T::*func)(int), int param){
		mObj	 = obj;
		mObjFunc = func;
		mParam   = param;
		mFunc    = nullptr;
	}
	//Run the registered callback function
	void OnClick(){
		if (mObj != nullptr && mObjFunc != nullptr)
			((mObj)->*(mObjFunc))(mParam);
		else if (mFunc != nullptr)
			mFunc(mParam);
	}

private:
	T *mObj;
	void (T::*mObjFunc)(int);
	int mParam;
};

#endif