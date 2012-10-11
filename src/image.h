#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "../externals/json/json.h"
#include "rect.h"
#include "vectors.h"

///Wrapper around the SDL_Texture to make things easier
/**
*  A wrapper around the SDL_Texture class to make using images
*  and setting clips or loading/saving them easier
*/
class Image {
public:
	Image();
	/**
	*  Setup the Image class, if a filename is passed load the image
	*  @param file The filename
	*  @see Window::LoadImage for the loading function
	*/
	Image(const std::string &file);
	/**
	*  Free the clips vector, b/c the SDL_Surface is a shared ptr 
	*  it's cleaned up automatically
	*/
	~Image();
	/**
	*  Set the image's clips to the vector passed
	*  @param clips The clips to use for the image
	*
	*  TODO: Will Lua be able to pass a vector to C++? Will a Lua array convert ok?
	*  curious what will happen here
	*/
	void SetClips(const std::vector<Recti> &clips);
	/**
	*  Generate clips based on the desired width and height of each clip
	*  and the size of the image, note that this will only work for uniform
	*  clip sizes
	*  @param cW The desired width of each clip
	*  @param cH The desired height of each clip
	*/
	void GenClips(int cW, int cH);
	/**
	*  Get the raw SDL_Texture pointer, this is only used inside the Window's draw
	*  functions as SDL expects a regular SDL_Texture pointer to draw
	*  @see Window
	*  @return SDL_Texture pointer to the image's texture
	*/
	SDL_Texture* Texture();
	/**
	*  Get the rect for a desired clipnum
	*  @param clipNum The clip number to get the box of
	*/
	Recti Clip(int clipNum) const;
    ///Get the Image filename
    std::string File() const;
	/**
	*  Save an Image's properties to a Json formatted file
    *  @param file The file to save to
	*/
	virtual void Save(const std::string &file) const;
    /**
    *  Load an Image and it's config data from a filename
    *  @param file The file to load from, the config file will be file.json
    *  @see Window::LoadTexture for the texture loading function
    */
    virtual void Load(const std::string &file);
	/**
	*  Register the Image class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static int RegisterLua(lua_State *l);

protected:
    /**
	*  Load an Image's properties from a Json::Value
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);
    /**
    *  Write the clips to a Json::Value and return it
    *  @return a Json::Value containing the clips information
    */
    Json::Value SaveClips() const;

private:
	///Disable image copy construction
	Image(const Image &a);
	Image& operator = (const Image &a);

protected:
	std::shared_ptr<SDL_Texture> mTexture;
	std::string mFile;
	Recti *mClips;
	int mNumClips;
	//std::vector<Recti> mClips;
};

#endif