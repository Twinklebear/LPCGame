#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H

#include <string>
#include "../externals/json/json.h"
#include "entity.h"
#include "image.h"
#include "text.h"
#include "button.h"

///A button that can register class member functions
/**
*  A button that is able to register class member functions as its callback
*/
template<class T>
class ObjectButton : public Button {
public:
	ObjectButton() 
		: mObj(nullptr), mObjFunc(nullptr)
	{
		mFunc = nullptr;
	}
	~ObjectButton(){
	}
	/**
	*  Register an object and the object function to call when the button is pressed
	*  @param obj The object context to call the function in
	*  @param func The function on the object to call
	*  @param param The parameter to pass to the function when calling it
	*/
	void RegisterCallBack(T *obj, void (T::*func)(std::string), std::string param){
		mObj	 = obj;
		mObjFunc = func;
		mParam   = param;
		mFunc    = nullptr;
	}
	///Run the registered callback function
	void OnClick(){
		if (mObj != nullptr && mObjFunc != nullptr)
			((mObj)->*(mObjFunc))(mParam);
		else if (mFunc != nullptr)
			mFunc(mParam);
        //Attempt to call the script if one is open
        if (!mScript.Open())
		    return;
	    ///Call the script
	    try{
		    luabind::call_function<void>(mScript.Get(), "OnClick");
	    }
	    catch(...){
	    }
	}
	/**
	*  Save the object data to a json value and return it
	*  @see GameObject::Save for saving of inherited members
	*  @return The Json::Value containing the object data
	*/
	Json::Value Save() const {
		//Unfortunately I can't change the function that's pointed to via loading json
		//as it's code not data, so instead we just save the param
		Json::Value val = Entity::Save();
		val["type"]	   = "objectbutton";
		val["text"]    = mText.Save();
		val["param"]   = mParam;
		
		return val;
	}
	/**
	*  Load the object from a Json::Value
	*  @see GameObject::Load for loading of inherited members
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val){
		Entity::Load(val);
		mParam = val["param"].asString();
		mText.Load(val["text"]);
	}

private:
	T *mObj;
	void (T::*mObjFunc)(std::string);
	std::string mParam;
};

#endif