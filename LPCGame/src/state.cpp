#include "state.h"

State::State(){}
State::~State(){}
void State::SetId(int id){
	mId = id;
}
int State::Id(){
	return mId;
}
void State::SetName(std::string name){
	mName = name;
}
std::string State::Name(){
	return mName;
}