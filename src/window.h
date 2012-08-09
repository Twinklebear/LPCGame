#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include "image.h"
#include "rect.h"
#include "text.h"

///Handles the window
/**
*  Window management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Window{
public:
	///Destructor: calls Quit to free the memory
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
	*/
	static void Draw(int x, int y, SDL_Texture *tex, SDL_Rect *clip = NULL, int w = -1, int h = -1,
		float angle = 0.0, Vector2f pivot = Vector2f(0, 0), SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	*  Draw an image type to the screen
	*  @param image The image to draw
	*  @param dstRect The destination rectangle to draw too 
	*  @param clip The clip rect to apply to the texture, if desired
	*  @param angle The angle to rotate the image in degrees, default is 0
	*  @param pivot The point to rotate around, default (0, 0) corresponds to destination rect center,
	*               offsets correspond to distance from image center
	*  @param flip The flip to apply to the image, default is none
	*/
	static void Draw(Image *image, const SDL_Rect &dstRect, SDL_Rect *clip = NULL,
		float angle = 0.0, Vector2f pivot = Vector2f(0, 0), SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	*  Draw a text type to the screen at some position
	*  @param text The text type to draw
	*  @param dstRect The destination rect to draw too, w and h vals will be queried from texture
	*  @param angle The angle to rotate the image in degrees, default is 0
	*  @param pivot The point to rotate around, default (0, 0) corresponds to destination rect center,
	*               offsets correspond to distance from image center
	*  @param flip The flip to apply to the image, default is none
	*/
	static void Draw(Text *text, SDL_Rect dstRect, float angle = 0.0, Vector2f pivot = Vector2f(0, 0),
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	/**
	*  Load an image file as a SDL_Texture and return it
	*  @param file The image file to load
	*  @return SDL_Texture* of the texture loaded
	*/
	static SDL_Texture* LoadTexture(std::string file);
	/**
	*  Convert an SDL_Surface to a texture and return the texture and free the surface
	*  @param surf The SDL_Surface* to be converted
	*  @return The SDL_Texture* created from the surface
	*/
	static SDL_Texture* SurfaceToTexture(SDL_Surface *surf);
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

private:
	static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> mWindow;
	static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> mRenderer;
	static Recti mBox;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
};

#endif