#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H

#include <string>
#include "json/json.h"
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
	void RegisterCallBack(T *obj, void (T::*func)(std::string), std::string param){
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
	/*
	*  Save the object data to a json value and return it
	*  @returns: The json value containing the object data
	*/
	Json::Value Save(){
		//Unfortunately I can't change the function that's pointed to via loading json
		//as it's code not data, so instead we just save the param
		Json::Value val;
		val["type"]	 = "objectbutton";
		val["text"]  = mText.Save();
		val["x"]	 = mPhysics.Box().X();
		val["y"]	 = mPhysics.Box().Y();
		val["param"] = mParam;
		
		return val;
	}
	/*
	*  Load the object from a json value
	*  @param value: The json value to load from
	*/
	void Load(Json::Value value){
		mParam = value["param"].asString();
		mText.Load(value["text"]);
		Start(value["x"].asInt(), value["y"].asInt());
	}

private:
	T *mObj;
	void (T::*mObjFunc)(std::string);
	std::string mParam;
};

#endif