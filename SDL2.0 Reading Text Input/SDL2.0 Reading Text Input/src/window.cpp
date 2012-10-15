#include <string>
#include <stdexcept>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "window.h"

SDL_Window* Window::mWindow;
SDL_Renderer* Window::mRenderer;
SDL_Rect Window::mBox;
int Window::SCREEN_WIDTH;
int Window::SCREEN_HEIGHT;

void Window::Init(std::string title){
	//initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
    if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");

	//Start up window
	SCREEN_WIDTH = 1280;
	SCREEN_HEIGHT = 720;
	mWindow = nullptr;
	mWindow = SDL_CreateWindow(title.c_str(), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (mWindow == nullptr)
		throw std::runtime_error("Failed to open window");
	//Start up the renderer
	mRenderer = nullptr;
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr)
		throw std::runtime_error("Failed to start renderer");
	//initialize the window box
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = SCREEN_WIDTH;
	mBox.h = SCREEN_HEIGHT;
}
void Window::Quit(){
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
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
	SDL_RenderCopyEx(mRenderer, tex, clip, &dstRect, angle, &(SDL_Point)pivot, flip);
}
SDL_Texture* Window::LoadTexture(std::string file){
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(mRenderer, file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file);
	return tex;
}
SDL_Texture* Window::RenderText(std::string message, std::string fontFile, SDL_Color color, int fontSize){
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
	
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	//We no longer need the font, so we can close it
	TTF_CloseFont(font);

	//Convert the surface to texture and return it
	return texture;
}
void Window::Clear(){
	SDL_RenderClear(mRenderer);
}
void Window::Present(){
	SDL_RenderPresent(mRenderer);
}
void Window::HandleEvents(SDL_Event &e){
}
SDL_Rect Window::Box(){
	//Update the box to match the current window w/h
	SDL_GetWindowSize(mWindow, &mBox.w, &mBox.h);
	return mBox;
}