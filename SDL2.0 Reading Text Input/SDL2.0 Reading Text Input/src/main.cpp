#include <SDL.h>
#include <iostream>
#include <string>
#include "window.h"

#undef main
int main(int argc, char** argv){
	Window::Init("Text entry test");

	SDL_Texture *textTexture;
	SDL_Color textColor = { 255, 255, 255 };
	std::string text = "";

	SDL_Event e;
	bool quit = false;
	bool editing = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT)
				quit = true;
			//Start entry
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
				if (!editing){
					SDL_StartTextInput();
					editing = true;
				}
				else {
					SDL_StopTextInput();
					std::cout << "Inputted: " << text << std::endl;
					text.clear();
					editing = false;
				}
			}
			//Recognize backspace key
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE){
				text.pop_back();
			}
			//Read text input
			if (e.type == SDL_TEXTINPUT)
				text += e.text.text;
			if (e.type == SDL_TEXTEDITING){
				//A bit unclear on what they're doing there
			}
		}
		//Re-render the text
		textTexture = Window::RenderText(text, "font.ttf", textColor, 35);

		Window::Clear();
		Window::Draw(100, 100, textTexture);
		Window::Present();
	}
	SDL_DestroyTexture(textTexture);
	Window::Quit();

	return 0;
}