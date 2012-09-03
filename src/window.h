#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <luabind/luabind.hpp>
#include "image.h"
#include "animatedimage.h"
#include "rect.h"
#include "text.h"
#include "color.h"

///Handles the window
/**
*  Window management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Window {
public:
    //Constructor and destructor do nothing, class is purely static
    Window();
    ~Window();
	/**
	*  Initialize SDL, setup the window and renderer
	*  @param title The window title
	*/
	static void Init(std::string title = "Window");
	///Quit SDL and destroy the window and renderer
	static void Quit();
	/**
	*  Draw a texture to the screen with optional stretching applied
	*  @param x The x coordinate to draw too
	*  @param y The y coordinate to draw too
	*  @param tex The SDL_Texture* to draw
	*  @param clip The clip rect to apply to the texture, if desired
	*  @param w The width to draw the texture with, def val is flag to get it from the texture
	*  @param h The height to draw the texture with, def val is flag to get it from the texture
	*  @param angle The angle to rotate the image in degrees, default is 0
	*  @param pivot The point to rotate around, default (0, 0) corresponds to destination rect center,
	*               offsets correspond to distance from image center
	*  @param flip The flip to apply to the image, default is none
	*  @note Why are there copies of this function instead of default paramaters? LuaBind doesn't seem
	*        to recognize default paramaters, or I didn't figure it out and as such had to write
	*        a version of the function for each call
	*/
	static void Draw(int x, int y, SDL_Texture *tex, SDL_Rect *clip = NULL, int w = -1, int h = -1,
		float angle = 0.0, Vector2f pivot = Vector2f(0, 0), SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	*  Draw an Image to the screen and apply some rotation and flip if desired
	*  @param image The image to draw
	*  @param dstRect The destination rectangle to draw too 
	*  @param clip The clip rect to apply to the texture
	*  @param angle The angle to rotate the image in degrees
	*  @param pivot The point to rotate around, note: default (0, 0) corresponds to destination rect center,
	*               offsets correspond to distance from image center
	*  @param flip The flip to apply to the image, default is none
	*/
	static void Draw(Image *image, const Rectf &dstRect, Recti *clip,
		float angle, Vector2f pivot = Vector2f(0, 0), int flip = SDL_FLIP_NONE);
	/**
	*  Draw an Image to the screen with no extra effects
	*  @param image The image to draw
	*  @param dstRect The destination rectangle to draw too 
	*/
	static void Draw(Image *image, const Rectf &dstRect);
	/**
	*  Drawn an Image to the screen with some clip applied
	*  the version passing with reference is for testing only
	*  @param image The image to draw
	*  @param dstRect The destination rectangle to draw too
	*  @param clip The clip to apply to the image
	*/
	static void Draw(Image *image, const Rectf &dstRect, Recti *clip);
    /**
    *  Draw an AnimatedImage object to the screen using the active animation clip
    *  @param img The AnimatedImage to draw
    *  @param dstRect The destination rect to draw too
    */
    static void Draw(AnimatedImage* img, const Rectf &dstRect);
	/**
	*  Draw an AnimatedImage object to the screen using the active animation clip and apply
    *  some rotation and flip if desired
    *  @param img The AnimatedImage to draw
	*  @param dstRect The destination rectangle to draw too 
	*  @param angle The angle to rotate the image in degrees
	*  @param pivot The point to rotate around, note: default (0, 0) corresponds to destination rect center,
	*               offsets correspond to distance from image center
	*  @param flip The flip to apply to the image, default is none
	*/
    static void Draw(AnimatedImage* img, const Rectf &dstRect, float angle, 
                     Vector2f pivot = Vector2f(0, 0), int flip = SDL_FLIP_NONE);
	/**
	*  Draw a Text object to the screen at some position
	*  @param text The text type to draw
	*  @param dstRect The destination rect to draw too, w and h vals will be queried from texture
	*  @param angle The angle to rotate the image in degrees, default is 0
	*  @param pivot The point to rotate around, default (0, 0) corresponds to destination rect center,
	*               offsets correspond to distance from image center
	*  @param flip The flip to apply to the image, default is none
	*/
	static void Draw(Text *text, const Rectf &dstRect, float angle = 0.0, Vector2f pivot = Vector2f(0, 0),
		int flip = SDL_FLIP_NONE);
	/**
	*  Load an image file as a SDL_Texture and return it
	*  @param file The image file to load
	*  @return SDL_Texture* of the texture loaded
	*/
	static SDL_Texture* LoadTexture(std::string file);
	/*
	*  Generate a texture containing the message we want to display
	*  @param message The message we want to display
	*  @param fontFile The font we want to use to render the text
	*  @param color The color we want the text to be
	*  @param fontSize The size we want the font to be
	*  @return An SDL_Texture containing the rendered message
	*/
	static SDL_Texture* RenderText(std::string message, std::string fontFile, Color color, int fontSize);
	/**
	*  Convert an SDL_Surface to a texture and return the texture and free the surface
	*  @param surf The SDL_Surface* to be converted
	*  @return The SDL_Texture* created from the surface
	*/
	static SDL_Texture* SurfaceToTexture(SDL_Surface *surf);
	/**
	*  Load an Image and its configuration file if one can be found and return a pointer to it
	*  @see Window::FreeImage for releasing Image memory
	*  @param file The image file to load, config file must be a json file of the same name in same folder
	*/
	static Image* LoadImage(const std::string &file);
	/**
	*  Load an AnimatedImage and its configuration file if one can be found and return a pointer to it
	*  @see Window::FreeImage for releasing Image memory
	*  @param file The image file to load, config file must be a json file of the same name in same folder
	*/
	static AnimatedImage* LoadAnimatedImage(const std::string &file);
    /**
    *  Open up an Image or AnimatedImage config file and return the Json::Value
    *  @param file The filename of the image, the JSON filename will be parsed out of it
    *  @return Json::Value containing the data from the file
    */
    static Json::Value LoadImageConfig(const std::string &file);
	/**
	*  Free an Image
	*  @param img The Image to destroy
	*/
	static void FreeImage(Image* img);
	/**
	*  Free an AnimatedImage
	*  @param img The Image to destroy
	*/
	static void FreeImage(AnimatedImage* img);
	///Clear the renderer
	static void Clear();
	///Present the renderer, ie. update screen
	static void Present();
	/**
	*  Handle window events
	*  @param e The SDL_Event to handle
	*/
	static void HandleEvents(SDL_Event &e);
	///Get the window's box
	static Recti Box();
	/**
	*  Register the Window class with the lua state
	*  @param l The lua_State to register the module with
	*/
	static void RegisterLua(lua_State *l);

private:
	static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
	static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer;
	static Recti mBox;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
};

#endif