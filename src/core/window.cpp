#include <string>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "rect.h"
#include "image.h"
#include "animatedimage.h"
#include "debug.h"
#include "window.h"

//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::mWindow 
    = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Window::mRenderer
    = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
Timer Window::mTimer;
int Window::mFrame;
//other static members
Recti Window::mBox;
int Window::SCREEN_WIDTH;
int Window::SCREEN_HEIGHT;

void Window::Init(std::string title){
    //initialize all SDL subsystems, need error handling here because
    //we should quit if this fails, since we'll crash anyways
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

    mTimer.Start();
}
void Window::Quit(){
    TTF_Quit();
    SDL_Quit();
}
void Window::DrawTexture(SDL_Texture *tex, const Rectf &dstRect, Recti *clip,
                    float angle, Vector2f pivot, SDL_RendererFlip flip)
{
    //Calculate the pivot point as an offset from image center
    pivot.x += dstRect.w / 2;
    pivot.y += dstRect.h / 2;
    //Make sure we don't try to convert a NULL clip rect
    SDL_Rect *ptrClip = NULL;
    if (clip != NULL)
        ptrClip = &(SDL_Rect)*clip;

    //Draw the texture
    SDL_RenderCopyEx(mRenderer.get(), tex, ptrClip, &(SDL_Rect)dstRect, angle, &(SDL_Point)pivot, flip);
}
void Window::Draw(Image *image, const Rectf &dstRect, Recti *clip, 
                    float angle, Vector2f pivot, int flip)
{
    if (clip == NULL)
        clip = &image->Clip();
   DrawTexture(image->Texture(), dstRect, clip, angle, pivot, (SDL_RendererFlip)flip);
}
void Window::Draw(AnimatedImage* img, const Rectf &dstRect, float angle, 
                    Vector2f pivot, int flip)
{
    Draw(img, dstRect, &img->Clip(), angle, pivot, flip);
}
void Window::Draw(Text *text, const Rectf &dstRect, float angle, 
                    Vector2f pivot, int flip)
{
    int w = 0;
    int h = 0;
    text->Size(&w, &h);
    Rectf dst(dstRect.X(), dstRect.Y(), w, h);
    DrawTexture(text->Texture(), dst, NULL);
}
//void Window::Draw(Text *text, const Rectf &dstRect){
//    Draw(text, dstRect, 0.0);
//}
SDL_Texture* Window::LoadTexture(std::string file){
    SDL_Texture *tex = nullptr;
    tex = IMG_LoadTexture(mRenderer.get(), file.c_str());
    if (tex == nullptr)
        Debug::Log("Failed to load image: " + file + " - " + IMG_GetError());
    return tex;
}
SDL_Texture* Window::RenderText(std::string message, std::string fontFile, 
                                Color color, int fontSize)
{
    //Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
        Debug::Log("Failed to load font: " + fontFile + " - " + TTF_GetError());
    
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
        Debug::Log("Failed to convert surface");
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
void Window::ShowAvgFps(bool log){
    ++mFrame;
    if (mTimer.Ticks() > 5000){
        float fps = mFrame / (mTimer.Ticks() / 5000.0f);
        std::stringstream ss;
        ss << "Average FPS: " << fps;
        if (log)
            Debug::Log(ss.str());
        else
            std::cout << ss.str() << std::endl;

        mTimer.Start();
        mFrame = 0;
    }
}
