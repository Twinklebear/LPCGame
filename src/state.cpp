#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
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
}
void State::Free(){
}
void State::SetExit(std::string val){
	mExit = true;
	mExitCode = val;
}
void State::UnsetExit(){
	mExit = false;
	mExitCode = "quit";
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

	return val;
}
void State::Load(Json::Value val){
	mName = val["name"].asString();
	mCamera->Load(val["camera"]);
}
void State::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<State>("State")
			.def(constructor<>())
			.def("SetExit", &State::SetExit)
			.def("UnsetExit", &State::UnsetExit)
			.def("SetName", &State::SetName)
			.def("Name", &State::Name)
	];
}