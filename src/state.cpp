#include "../externals/json/json.h"
#include "state.h"

State::State() 
	: mManager(nullptr), mCamera(nullptr), mName(""), mExit(false), mExitCode("quit")
{
}
State::~State(){}
void State::SetExit(std::string val){
	mExit = true;
	mExitCode = val;
}
void State::UnsetExit(){
	mExit = false;
	mExitCode = "quit";
}
Json::Value State::Save(){
	Json::Value val;
	val["objects"]  = mManager->Save();
	val["name"]	    = mName;
	val["camera"]	= mCamera->Save();

	return val;
}
void State::Load(Json::Value val){
	mName = val["name"].asString();
	mCamera->Load(val["camera"]);
}

void State::SetName(std::string name){
	mName = name;
}
std::string State::Name(){
	return mName;
}