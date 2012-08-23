#include <string>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "math.h"
#include "entity.h"

Entity::Entity() : mMouseOver(false), mL(nullptr){
}
Entity::Entity(std::string script) : mMouseOver(false), mL(nullptr){
	mL = lua_open();
	luaL_openlibs(mL);
	luabind::open(mL);
	//Init my lua modules
	//Input::RegisterLua(mL);
	Entity::RegisterLua(mL);
	luaL_dofile(mL, script.c_str());
}
void Entity::Init(){
	//copy the Object::Init from LuaBind project
}
void Entity::Update(){

}
void Entity::Move(float deltaT){

}
void Entity::Draw(Camera *camera){

}
void Entity::OnMouseDown(){}
void Entity::OnMouseUp(){}
void Entity::OnMouseEnter(){}
void Entity::OnMouseExit(){}
void Entity::CheckMouseOver(const Vector2f &pos){
	//Only trigger OnMouseEnter if the mouse is colliding and wasn't before
	if (Math::CheckCollision(pos, mPhysics.Box()) && !mMouseOver){
		OnMouseEnter();
		mMouseOver = true;
	}
	//Only trigger mouse exit if the mouse was colliding, but isn't anymore
	else if (!Math::CheckCollision(pos, mPhysics.Box()) && mMouseOver){
		OnMouseExit();
		mMouseOver = false;
	}
}
bool Entity::GetMouseOver(){
	return mMouseOver;

}
bool Entity::HasTag(std::string tag){
	return (mTag == tag);
}
Json::Value Entity::Save(){
	Json::Value val;
	val["image"]   = mImage.Save();
	val["physics"] = mPhysics.Save();
	val["tag"]	   = mTag;
	return val;
}
void Entity::Load(Json::Value val){
	mPhysics.Load(val["physics"]);
	mImage.Load(val["image"]);
	mTag = val["tag"].asString();
}
void Entity::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Entity>("Entity")
			.def(constructor<>())
			//.def(constructor<std::string>())
	];
}