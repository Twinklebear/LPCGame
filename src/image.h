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
	*  Load an image from a file
	*  @param file The file to load
	*  @see Window::LoadImage for the loading function
	*/
	void LoadImage(const std::string& file);
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
	*  Returns the number of clips in the image
	*  @return int The number of clips.
	*/
	int ClipCount();
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
	Recti Clip(int clipNum);
	/**
	*  Save an image's properties to a Json::Value and return it
	*  @return Json::Value containing the information about the image
	*/
	virtual Json::Value Save();
	/**
	*  Load an image and its properties from a Json::Value
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);
	/**
	*  Load an Image's settings from a Json::Value
	*  @note This will probably replace Load when the switch is done
	*/
	virtual void LoadConfig(Json::Value val);
	/**
	*  Register the Image class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static void RegisterLua(lua_State *l);

protected:
    /**
    *  Parse an Image config file based on the image's file name and read
    *  the JSON formatted data from it
    *  @param file The image filename
    *  @return A Json::Value containing the file data
    */
    void LoadImageConfig(const std::string &file);

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