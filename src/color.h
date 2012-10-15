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
	SDL_Color Get() const;
	///Get the red value
	int R() const;
    ///Set the red value
    void R(int r);
	///Get the green value
	int G() const;
    ///Set the green value
    void G(int g);
	///Get the blue value
	int B() const;
    ///Set the blue value
    void B(int b);
	/**
	*  Save the color data to a Json::Value
	*  @returns Json::Value containing information about the text
	*/
	Json::Value Save() const;
	/**
	*  Load the color data from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);
	/**
	*  Register the Color class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static int RegisterLua(lua_State *l);
	///Operator for comparing colors
	bool operator == (const Color &c) const;

private:
	SDL_Color mColor;
};

#endif