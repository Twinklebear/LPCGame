#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>
#include <memory>
#include "SDL.h"
#include "image.h"
#include "rect.h"
#include "text.h"

/*
*  Window management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Window{
public:
	/*
	*  Initialize SDL, setup the window and renderer
	*  @param title: the window title
	*/
	static void Init(std::string title = "Window");
	/*
	*  Quit SDL and destroy the window and renderer
	*/
	static void Quit();
	/*
	*  Draw a texture to the screen, with no scaling applied
	*  @param x: The x coordinate to draw too
	*  @param y: The y coordinate to draw too
	*  @param tex: The SDL_Texture* to draw
	*  @param clip: The clip rect to apply to the texture, if desired
	*  @param w: The width to draw the texture with, def val -1 is flag to get val from the texture
	*  @param h: The height to draw the texture with, def val -1 is flag to get val from the texture
	*/
	static void Draw(int x, int y, SDL_Texture *tex, SDL_Rect *clip = NULL, int w = -1, int h = -1);
	/*
	*  Draw an image to the screen
	*  @param image: The image to draw
	*  @param dstRect: The destination rectangle to draw too 
	*  @param clip: The clip rect to apply to the texture, if desired
	*/
	static void Draw(Image *image, const SDL_Rect &dstRect, SDL_Rect *clip = NULL);
	/*
	*  Draw a text type to the screen at some position
	*  @param text: The text type to draw
	*  @param dstRect: The destination rect to draw too, w and h vals will be queried from texture
	*/
	static void Draw(Text *text, SDL_Rect dstRect);
	/*
	*  Load an image file into an SDL_Texture and return it
	*  @param file: the image file to load
	*  @return SDL_Texture* of the texture loaded
	*/
	static SDL_Texture* LoadTexture(std::string file);
	/*
	*  Convert an SDL_Surface to a texture and return the texture
	*  will also free the surface
	*  @param surf: The SDL_Surface* to be converted
	*  @returns: The SDL_Texture* created from the surface
	*/
	static SDL_Texture* SurfaceToTexture(SDL_Surface *surf);
	/*
	*  Clear the renderer
	*/
	static void Clear();
	/*
	*  Render the renderer to window
	*/
	static void Present();
	/*
	*  Handle window events
	*/
	static void HandleEvents(SDL_Event &e);
	/*
	*  Return the window box
	*/
	static Recti Box();

private:
	static std::shared_ptr<SDL_Window> mWindow;
	static std::shared_ptr<SDL_Renderer> mRenderer;
	static Recti mBox;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
};

#endif