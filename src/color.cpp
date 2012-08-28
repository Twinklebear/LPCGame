#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "color.h"

Color::Color(){
	Set(0, 0, 0);
}
Color::Color(int r, int g, int b){
	Set(r, g, b);
}
Color::~Color(){
}
void Color::Set(int r, int g, int b){
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
}
SDL_Color Color::Get(){
	return mColor;
}
int Color::R(){
	return mColor.r;
}
int Color::G(){
	return mColor.g;
}
int Color::B(){
	return mColor.b;
}
Json::Value Color::Save(){
	Json::Value v;
	v["r"] = mColor.r;
	v["g"] = mColor.g;
	v["b"] = mColor.b;
	return v;
}
void Color::Load(Json::Value val){
	Set(val["r"].asInt(), val["g"].asInt(), val["b"].asInt());
}
bool Color::operator == (Color c) const{
	return (mColor.r == c.R() && mColor.b == c.B() && mColor.g == c.G());
}
void Color::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Color>("Color")
			.def(constructor<>())
			.def(constructor<int, int, int>())
			.def("Set", &Color::Set)
	];
}