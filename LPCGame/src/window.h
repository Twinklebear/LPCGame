#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "rect.h"
#include "image.h"

/**
*	The window manager class, handles window events and other such stuff
*	related to the window
*/

class Window{
public:
	/**
	*	Setup the window, also load a caption image and phrase if provided
	*	@return true false based on if setup was successful
	*/
	static void Setup();
	/*
	* Quit SDL
	*/
	static void Quit();
	/**
	*	Handle window events such as resizing
	*	@param event: The SDL_Event queue
	*/
	static void HandleEvents(SDL_Event &event);
	///Fill the screen a certain color, to refresh the window
	static void FillWhite();
	static void FillBlack();
	/**
	*	Draw an SDL_Surface to the screen
	*	@param x: the x position to draw too
	*	@param y: the y position to draw too
	*	@param destination: the surface to draw too
	*	@param clips: the clip of the surface to use, default is null
	*/
	static void Draw(const float x, const float y, SDL_Surface *source, SDL_Rect *clip = NULL);
	/**
	*	Draw an Image to screen
	*	@param image: the Image class to draw
	*	@param rect: the rectangle of the object to draw
	*	@param clip: the clip of the image to draw, default is null
	*/
	static void Draw(Image *image, SDL_Rect rect, SDL_Rect *clip = NULL);
	///Flip the screen buffers
	static void Flip();
	///Get windowbox
	static Recti Box();
	const static int FrameRateLimit();

private:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
    static int SCREEN_BPP;
	static int FRAMERATE_LIMIT;
	static Recti mWindowBox;
	static SDL_Surface *mScreen;
};

#endif