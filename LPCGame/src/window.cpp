#include <string>
#include <stdexcept>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "rect.h"
#include "image.h"
#include "window.h"

SDL_Window* Window::mWindow;
SDL_Renderer* Window::mRenderer;
Recti Window::mBox;
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
	mBox.Set(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Window::Quit(){
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_Quit();
	SDL_Quit();
}
void Window::Draw(int x, int y, SDL_Texture *tex, SDL_Rect *clip, int w, int h){
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	//Setup desired width and height properties
	if (w == -1 && h == -1)
		SDL_QueryTexture(tex, NULL, NULL, &dstRect.w, &dstRect.h);
	else if (h == -1){
		//Will this crash?
		SDL_QueryTexture(tex, NULL, NULL, NULL, &dstRect.h);
		dstRect.w = w;
	}
	else if (w == -1){
		//Will this crash?
		SDL_QueryTexture(tex, NULL, NULL, &dstRect.w, NULL);
		dstRect.h = h;
	}
	else {
		dstRect.w = w;
		dstRect.h = h;
	}
	//Draw the texture
	SDL_RenderCopy(mRenderer, tex, clip, &dstRect);
}
void Window::Draw(Image *image, const SDL_Rect &dstRect, SDL_Rect *clip){
	Draw(dstRect.x, dstRect.y, image->Texture(), clip, dstRect.w, dstRect.h);
}
void Window::Draw(Text *text, SDL_Rect dstRect){
	text->GetSize(dstRect.w, dstRect.h);
	Draw(dstRect.x, dstRect.y, text->Texture(), NULL, dstRect.w, dstRect.h);
}
SDL_Texture* Window::LoadTexture(std::string file){
	SDL_Texture *tex = nullptr;
	tex = IMG_LoadTexture(mRenderer, file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file);
	return tex;
}
SDL_Texture* Window::SurfaceToTexture(SDL_Surface *surf){
	SDL_Texture *tex = nullptr;
	tex = SDL_CreateTextureFromSurface(mRenderer, surf);
	if (tex == nullptr)
		throw std::runtime_error("Failed to convert surface");
	SDL_FreeSurface(surf);
	return tex;
}
void Window::Clear(){
	SDL_RenderClear(mRenderer);
}
void Window::Present(){
	SDL_RenderPresent(mRenderer);
}
void Window::HandleEvents(SDL_Event &e){
}
Recti Window::Box(){
	//Update the box to match the current window w/h
	SDL_GetWindowSize(mWindow, &mBox.w, &mBox.h);
	return mBox;
}