#include <string>
#include <stdexcept>
#include "SDL.h"

class Vector2f{
public:
	Vector2f(float x, float y){
		this->x = x;
		this->y = y;
	}
	operator SDL_Point() const {
		SDL_Point p;
		p.x = x;
		p.y = y;
		return p;
	}

public:
	float x, y;
};

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
	/*
	*  Load an image file into an SDL_Texture and return it
	*  @param file: the image file to load
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
	static SDL_Texture* RenderText(std::string message, std::string fontFile, SDL_Color color, int fontSize);
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
	static SDL_Rect Box();

private:
	static SDL_Window *mWindow;
	static SDL_Renderer *mRenderer;
	//TODO: Replace with Rect<int>
	static SDL_Rect mBox;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
};