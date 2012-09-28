#include <string>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <fstream>
#include "math.h"
#include "luascript.h"
#include "entity.h"

Entity::Entity() : mMouseOver(false), mConfigFile(""){
}
Entity::Entity(std::string script) : mMouseOver(false), mConfigFile(""){
	mScript.OpenScript(script);
}
Entity::~Entity(){
	//Clean up any script memory
	Free();
}
void Entity::Init(){
	//We catch exceptions so that if the function doesn't exist the program 
	//won't crash. This lets us skip implementing functions we don't need
	//int scripts
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "Init", this);
	}
	catch(...){
		std::cout << "Init issue: " << lua_error(mScript.Get()) << std::endl;
	}
}
void Entity::Free(){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "Free");
	}
	catch(...){
	}
}
void Entity::Update(){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "Update");
	}
	catch(...){
	}
}
void Entity::Move(float deltaT){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "Move", deltaT);
	}
	catch(...){
	}
}
void Entity::Draw(Camera *camera){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "Draw", camera);
	}
	catch(...){
	}
}
void Entity::OnMouseDown(){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "OnMouseDown");
	}
	catch(...){
	}
}
void Entity::OnMouseUp(){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "OnMouseUp");
	}
	catch(...){
	}
}
void Entity::OnMouseEnter(){
	if (!mScript.Open())
		return;
	try{
		luabind::call_function<void>(mScript.Get(), "OnMouseEnter");
	}
	catch(...){
	}
}
void Entity::OnMouseExit(){
	if (!mScript.Open())
		return;
	try {
		luabind::call_function<void>(mScript.Get(), "OnMouseExit");
	}
	catch(...){
	}
}
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
Physics* Entity::GetPhysics(){
	return &mPhysics;
}
void Entity::SetCollisionMap(CollisionMap map){
	mPhysics.SetMap(map);
}
Rectf Entity::Box(){
	return mPhysics.Box();
}
void Entity::SetTag(std::string tag){
	mTag = tag;
}
std::string Entity::Tag(){
	return mTag;
}
Json::Value Entity::Save(){
	Json::Value val;
    if (mConfigFile != "")
        val["file"] = mConfigFile;
    else {
	    val["image"]   = mImage.Save();
	    val["physics"] = mPhysics.Save();
	    val["tag"]	   = mTag;
	    val["script"]  = mScript.Save();
	    val["name"]    = mName;
    }
	return val;
}
void Entity::Load(Json::Value val){
    //Load the image from an external entity file
    if (!val["file"].empty() && val["file"].asString() != ""){
        std::cout << "Loading entity from config file: " 
            << val["file"].asString() << std::endl;
        mConfigFile = val["file"].asString();
        std::ifstream fileIn((mConfigFile).c_str(), std::ifstream::binary);
	    if (fileIn){
		    Json::Reader reader;
		    Json::Value root;
		    if (reader.parse(fileIn, root, false)){
                fileIn.close();
                //Load the config data
                Load(root);
                return;
		    }
		    //some debug output, this case should throw
            else {
                fileIn.close();
                //throw std::runtime_error("Failed to parse file: " + configFile); 
                std::cout << "Failed to parse: " << mConfigFile << std::endl;
            }
	    }
        else
            //throw std::runtime_error("Failed to find file: " + configFile);
            std::cout << "Failed to find: " << mConfigFile << std::endl;
    }
    else {
	    mTag  = val["tag"].asString();
	    mName = val["name"].asString();
	    mPhysics.Load(val["physics"]);
	    mImage.Load(val["image"]);
	    mScript.Load(val["script"]);
    }
}
void Entity::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Entity>("Entity")
			.def(constructor<>())
			.def(constructor<std::string>())
			.def("Init", &Entity::Init)
			.def("Free", &Entity::Free)
			.def("Update", &Entity::Update)
			.def("Move", &Entity::Move)
			.def("Draw", &Entity::Draw)
			.def("OnMouseDown", &Entity::OnMouseDown)
			.def("OnMouseUp", &Entity::OnMouseUp)
			.def("OnMouseEnter", &Entity::OnMouseEnter)
			.def("OnMouseExit", &Entity::OnMouseExit)
			.def("GetPhysics", &Entity::GetPhysics)
			.def("Box", &Entity::Box)
			.def("SetTag", &Entity::SetTag)
			.def("Tag", &Entity::Tag)
	];
}