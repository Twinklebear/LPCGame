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
void State::SetName(std::string name){
	mName = name;
}
std::string State::Name(){
	return mName;
}