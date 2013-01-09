#include <string>
#include <sstream>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include "externals/json/json.h"
#include "color.h"

Color::Color() {
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
SDL_Color Color::Get() const {
	return mColor;
}
int Color::R() const {
	return mColor.r;
}
void Color::R(int r){
    mColor.r = r;
}
int Color::G() const {
	return mColor.g;
}
void Color::G(int g){
    mColor.g = g;
}
int Color::B() const {
	return mColor.b;
}
void Color::B(int b){
    mColor.b = b;
}
Json::Value Color::Save() const {
	Json::Value v;
	v["r"] = mColor.r;
	v["g"] = mColor.g;
	v["b"] = mColor.b;
	return v;
}
void Color::Load(Json::Value val){
	Set(val["r"].asInt(), val["g"].asInt(), val["b"].asInt());
}
bool Color::operator == (const Color &c) const {
	return ((int)mColor.r == c.R() && (int)mColor.b == c.B() && (int)mColor.g == c.G());
}
Color::operator std::string() const {
    std::stringstream s;
    s << "Color: (r: " << (int)mColor.r << ", g: " << (int)mColor.g
        << ", b: " << (int)mColor.b << ")";
    return s.str();
}
int Color::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Color>("Color")
			.def(constructor<>())
			.def(constructor<int, int, int>())
			.def("Set", &Color::Set)
			.def("R", (int (Color::*)() const)&Color::R)
            .def("R", (void (Color::*)(int))&Color::R)
			.def("G", (int (Color::*)() const)&Color::G)
            .def("G", (void (Color::*)(int))&Color::G)
			.def("B", (int (Color::*)() const)&Color::B)
            .def("B", (void (Color::*)(int))&Color::B)
            //operators
            .def(const_self == other<Color>())
	];
    return 1;
}