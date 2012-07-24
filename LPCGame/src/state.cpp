#include "state.h"

State::State() : mName(""){}
State::~State(){}
void State::SetName(std::string name){
	mName = name;
}
std::string State::Name(){
	return mName;
}