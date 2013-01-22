#include <fstream>
#include <string>
#include <SDL.h>
#include "debug.h"

std::ofstream Debug::logOut;

void Debug::Init(){
    logOut.open("debug.log");
}
void Debug::Quit(){
    logOut.close();
}
void Debug::Log(const std::string text){
    //Calculate the formatted time since startup
    float sec = SDL_GetTicks() / 1000.0f;
    int hrs = (sec / 3600);
    int min = (sec / 60) - hrs * 3600;
    sec = (int)(sec - hrs * 3600 - min * 60);
    logOut << hrs << ":" << min << ":" << sec << " - " << text << std::endl;
}
