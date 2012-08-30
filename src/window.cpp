#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <luabind/luabind.hpp>
#include "rect.h"
#include "image.h"
#include "window.h"

//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::mWindow 
	= std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Window::mRenderer
	= std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
//other static members
Recti Window::mBox;
int Window::SCREEN_WIDTH;
int Window::SCREEN_HEIGHT;

Window::~Window(){}
void Window::Init(std::string title){
	//initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
    if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");

	//Start up window
	SCREEN_WIDTH = 1280;
	SCREEN_HEIGHT = 720;
	//TODO: Solve the resized window issues
	mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, 
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN));// | SDL_WINDOW_RESIZABLE));
	//if window failed to create
	if (mWindow == nullptr)
		throw std::runtime_error("Failed to open window");

	//Start up the renderer
	mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	//Make sure it went ok
	if (mRenderer == nullptr)
		throw std::runtime_error("Failed to start renderer");
	//initialize the window box
	mBox.Set(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Window::Quit(){
	TTF_Quit();
	SDL_Quit();
}
void Window::Draw(int x, int y, SDL_Texture *tex, SDL_Rect *clip, int w, int h,
				  float angle, Vector2f pivot, SDL_RendererFlip flip)
{
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	//Setup desired width and height properties
	if (w == -1 && h == -1)
		SDL_QueryTexture(tex, NULL, NULL, &dstRect.w, &dstRect.h);
	else {
		dstRect.w = w;
		dstRect.h = h;
	}
	//Calculate the pivot point as an offset from image center
	pivot.x = dstRect.w / 2 + pivot.x;
	pivot.y = dstRect.h / 2 + pivot.y;

	//Draw the texture
	SDL_RenderCopyEx(mRenderer.get(), tex, clip, &dstRect, angle, &(SDL_Point)pivot, flip);
}
void Window::Draw(Image *image, const Rectf &dstRect, Recti *clip, float angle, 
				  Vector2f pivot, int flip)
{
	//We don't want to attempt to dereference a NULL ptr to do the conversion cast
	//so we must check it here
	SDL_Rect *ptrClip = NULL;
	if (clip != NULL)
		ptrClip = &(SDL_Rect)*clip;

	Draw(dstRect.X(), dstRect.Y(), image->Texture(), ptrClip, dstRect.w, dstRect.h);
}
void Window::Draw(Image *image, const Rectf& dstRect){
	Draw(image, dstRect, NULL);
}
void Window::Draw(Text *text, const Rectf &dstRect, float angle, Vector2f pivot, int flip)
{
	int w = 0;
	int h = 0;
	text->Size(w, h);
	Draw(dstRect.X(), dstRect.Y(), text->Texture(), NULL, w, h);
}
SDL_Texture* Window::LoadTexture(std::string file){
	SDL_Texture *tex = nullptr;
	tex = IMG_LoadTexture(mRenderer.get(), file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file);
	return tex;
}
SDL_Texture* Window::RenderText(std::string message, std::string fontFile, Color color, int fontSize){
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
	
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color.Get());
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}
SDL_Texture* Window::SurfaceToTexture(SDL_Surface *surf){
	SDL_Texture *tex = nullptr;
	tex = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
	if (tex == nullptr)
		throw std::runtime_error("Failed to convert surface");
	SDL_FreeSurface(surf);
	return tex;
}
void Window::Clear(){
	SDL_RenderClear(mRenderer.get());
}
void Window::Present(){
	SDL_RenderPresent(mRenderer.get());
}
void Window::HandleEvents(SDL_Event &e){
}
Recti Window::Box(){
	//Update the box to match the current window w/h
	SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h);
	return mBox;
}
void Window::RegisterLua(lua_State *l){
	using namespace luabind;

	module(l, "LPC")[
		class_<Window>("Window")
			.scope[
				//Note: These binding methods don't allow for default paramaters to have an effect, as such
				//I must define an individual function each time
				def("Draw", (void (*)(Image*, const Rectf&))&Window::Draw),
				def("Draw", (void (*)(Image*, const Rectf&, Recti*, float, Vector2f, int))&Window::Draw),
				def("Draw", (void (*)(Text*, const Rectf&, float, Vector2f, int))&Window::Draw),
				def("Clear", &Window::Clear),
				def("Present", &Window::Present),
				def("Box", &Window::Box)
			]
			.enum_("RendererFlip")[
				value("FLIP_NONE", SDL_FLIP_NONE),
				value("FLIP_HORIZ", SDL_FLIP_HORIZONTAL),
				value("FLIP_VERT", SDL_FLIP_VERTICAL)
			]
	];
}
