#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <stdexcept>
#include "SDL.h"
#include "SDL_ttf.h"
#include "rect.h"

/*
*  A simple class for drawing some TTF text
*/
class Text{
public:
	Text();
	/*
	*  Setup the text object with a message, font and font size
	*  @param message: The message to be displayed
	*  @param font: The font file to use
	*  @param fontSize: The font size to use, default is 30
	*  @param color: The color of font to use, default is black
	*/
	Text(std::string message, std::string font, SDL_Color color, int fontSize = 30);
	~Text();
	/*
	*  Set a message, font and font size
	*  @param message: The message to be displayed
	*  @param font: The font file to use
	*  @param fontSize: The font size to use, default is 30
	*  @param color: The color of font to use, default is black
	*/
	void Setup(std::string message, std::string font, SDL_Color color, int fontSize = 30);
	/*
	*  Set a message for the text
	*  @param message: The message to display
	*/
	void SetMessage(std::string message);
	/*
	*  Set a font for the text to use
	*  @param font: The font file to use
	*/
	void SetFont(std::string font);
	/*
	*  Set the font size to use
	*  @param fontSize: The font size to use
	*/
	void SetFontSize(int fontSize);
	/*
	*  Set the font color to use
	*  @param color: The color to use
	*/
	void SetColor(SDL_Color color);
	/*
	*  Get the texture pointer of the font for drawing
	*  @returns: The message texture
	*/
	SDL_Texture* Texture();
	/*
	*  Get a rect containing the message textures width and height
	*  @returns: A Recti containing the width and height of the message
	*/
	Recti GetSize();
	/*
	*  Store the width and height values of the texture in the values passed
	*  @param w: The value to store the width in
	*  @param h: The value to store the height in
	*/
	void GetSize(int &w, int &h);

private:
	//Disable copy construction
	Text(const Text&a);
	Text& operator = (const Text &a);

private:
	TTF_Font *mFont;
	SDL_Texture *mTex;
	SDL_Color mColor;
	std::string mMessage, mFontFile;
	int mFontSize;
};

#endif