#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"

///A light wrapper around SDL_Color
/**
*  A wrapper around the RGB SDL_Color to make it a bit nicer to use
*  and make it easier to expose it to Lua via LuaBind
*/
class Color {
public:
	///Construct the color with default (black) color
	Color();
	/**
	*  Construct the color with some desired color
	*  @param r The red color value, 0-255
	*  @param g The green color value, 0-255
	*  @param b The blue color value, 0-255
	*/
	Color(int r, int g, int b);
	~Color();
	/**
	*  Set the color to some RGB value
	*  @param r The red color value, 0-255
	*  @param g The green color value, 0-255
	*  @param b The blue color value, 0-255
	*/
	void Set(int r, int g, int b);
	///Get the SDL_Color
	SDL_Color Get();
	///Get the red value
	int R();
	///Get the green value
	int G();
	///Get the blue value
	int B();
	/**
	*  Save the color data to a Json::Value
	*  @returns Json::Value containing information about the text
	*/
	Json::Value Save();
	/**
	*  Load the color data from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);
	/**
	*  Register the Color class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static void RegisterLua(lua_State *l);
	///Operator for comparing colors
	bool operator == (Color c) const;

private:
	SDL_Color mColor;
};

#endif