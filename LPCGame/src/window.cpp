#include <stdexcept>
#include "SDL.h"
#include "SDL_ttf.h"
#include "rect.h"
#include "window.h"
#include "image.h"
#include <mutex>
#include <iostream>

int Window::SCREEN_WIDTH;
int Window::SCREEN_HEIGHT;
int Window::SCREEN_BPP;
int Window::FRAMERATE_LIMIT;
Recti Window::mWindowBox;
SDL_Surface *Window::mScreen;

void Window::Setup(){
    //initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
    if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");
    //Set screen width, height and BPP
    SCREEN_WIDTH	= 1280;
    SCREEN_HEIGHT	= 720;
	SCREEN_BPP		= 32;
	FRAMERATE_LIMIT = 60;

    //setup the screen
	mScreen = nullptr;
	mScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	if (mScreen == nullptr)
		throw std::runtime_error("Failed to setup screen");
    
	//set the windowBox
    mWindowBox.Set(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	//set the window caption
	SDL_WM_SetCaption("Game", NULL);
	//fill the screen white
	SDL_FillRect(mScreen, &mScreen->clip_rect, SDL_MapRGB(mScreen->format, 0xFF, 0xFF, 0xFF));
}
void Window::HandleEvents(SDL_Event &event){
    if (event.type == SDL_VIDEORESIZE){
        mScreen = SDL_SetVideoMode(event.resize.w, event.resize.h, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
		mWindowBox.Set(0, 0, event.resize.w, event.resize.h);
	}
}
void Window::FillWhite(){
	SDL_FillRect(mScreen, &mScreen->clip_rect, SDL_MapRGB(mScreen->format, 0xFF, 0xFF, 0xFF));
}
void Window::FillBlack(){
	SDL_FillRect(mScreen, &mScreen->clip_rect, SDL_MapRGB(mScreen->format, 0, 0, 0));
}
void Window::Draw(const float x, const float y, SDL_Surface *source, SDL_Rect *clip){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, clip, mScreen, &offset);
}
void Window::Draw(Image *image, SDL_Rect &rect, SDL_Rect *clip){
	SDL_BlitSurface(image->Surface(), clip, mScreen, &rect);
}
void Window::Flip(){
	if (SDL_Flip(mScreen) == -1){
		throw std::runtime_error("Window flip failed");
		std::cout << "flip failed" << std::endl;
	}
}
Recti Window::Box(){
	return mWindowBox;
}
int Window::FrameRateLimit(){
	return FRAMERATE_LIMIT;
}