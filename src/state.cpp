#include <luabind/luabind.hpp>
#include "externals/json/json.h"
#include "debug.h"
#include "state.h"

State::State() 
	: mManager(nullptr), mCamera(nullptr), mName(""), mExit(false), 
	  mExitCode("quit")//, mCondBool(false)
{
}
State::~State(){}
std::string State::Run(){
	return mExitCode;
}
void State::Init(){
    //Call the script
    if (!mScript.Open())
		return;
	try {
        lua_getglobal(mScript.Get(), "Init");
        if (lua_pcall(mScript.Get(), 0, 0, 0) != 0)
            Debug::Log("State: " + mName + " Init error: " + lua_tostring(mScript.Get(), -1));
		//luabind::call_function<void>(mScript.Get(), "Init");
	}
	catch(...){
	}
}
void State::Free(){
    //Call the script
    if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "Free");
	}
	catch(...){
	}
}
void State::LogicUpdate(){
    //Call the script
    if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "LogicUpdate");
	}
	catch(...){
	}
}
void State::RenderUpdate(){
    //Call the script
    if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "RenderUpdate");
	}
	catch(...){
	}
}
void State::SetExit(std::string val){
	mExit = true;
	mExitCode = val;
}
void State::UnsetExit(){
	mExit = false;
	mExitCode = "quit";
}
std::shared_ptr<EntityManager> State::Manager(){
    return mManager;
}
void State::SetName(std::string name){
	mName = name;
}
std::string State::Name(){
	return mName;
}
Json::Value State::Save(){
	Json::Value val;
	val["entities"] = mManager->Save();
	val["name"]	    = mName;
	val["camera"]   = mCamera->Save();
    val["script"]   = mScript.File();

	return val;
}
void State::Load(Json::Value val){
	mName = val["name"].asString();
	mCamera->Load(val["camera"]);
    mScript.OpenScript(val["script"].asString());
}
int State::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<State>("State")
			.def(constructor<>())
			.def("SetExit", &State::SetExit)
			.def("UnsetExit", &State::UnsetExit)
			.def("SetName", &State::SetName)
			.def("Name", &State::Name)
	];
    return 1;
}