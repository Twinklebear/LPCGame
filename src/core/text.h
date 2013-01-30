#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <stdexcept>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include "external/json/json.h"
#include "rect.h"
#include "color.h"

///Handles drawing some text
/**
*  A simple class for drawing a string to a texture with some color
*  and a specified TTF_Font and font size
*/
class Text {
public:
	Text();
	/**
	*  Setup the text object with a message, font and font size
	*  @param message The message to be displayed
	*  @param font The font file to use
	*  @param fontSize The font size to use, default is 30
	*  @param color The color of font to use, default is black
	*/
	Text(std::string message, std::string font, Color color, int fontSize = 30);
	~Text();
	/**
	*  Set a message, font and font size
	*  @param message The message to be displayed
	*  @param font The font file to use
	*  @param fontSize The font size to use, default is 30
	*  @param color The color of font to use, default is black
	*/
	void Set(std::string message, std::string font, Color color, int fontSize = 30);
	/**
	*  Set a message for the text, checks to make sure message is different before
	*  rendering the new message
	*  @param message The message to display
	*/
	void SetMessage(std::string message);
	/**
	*  Set a font for the text to use, checks to make sure font is different
	*  before loading the new font and rendering message
	*  @param font The font file to use
	*/
	void SetFont(std::string font);
	/**
	*  Set the font size to use, checks to make sure size is different before
	*  reloading the font with the new size
	*  @param fontSize The font size to use
	*/
	void SetFontSize(int fontSize);
	/**
	*  Set the font color to use, checks to make sure color is different
	*  before redrawing
	*  @param color The color to use
	*/
	void SetColor(Color color);
    /**
    *  Get the message text being displayed
    *  @return the message
    */
    std::string GetMessage();
    /**
    *  Get the font file currently being used
    *  @return the font file path
    */
    std::string GetFont();
    /**
    *  Get the font size currently being used
    *  @return the current font size
    */
    int GetFontSize();
    /**
    *  Get the current text color
    *  @return the text color
    */
    Color GetColor();
	/**
	*  Get the texture pointer of the font, used for the window's draw functions
	*  @see Window
	*  @return The message's SDL_Texture pointer
	*/
	SDL_Texture* Texture();
	/**
	*  Get a rect containing the message texture's width and height
	*  @return Recti containing the width and height of the message
	*/
	Recti Size() const;
	/**
	*  Store the width and height values of the texture in the values passed
	*  @param w The value to store the width in
	*  @param h The value to store the height in
	*/
	void Size(int *w, int *h = NULL) const;
    ///Get the width of the text
    int W() const;
    ///Get the height
    int H() const;
	/**
	*  Save the text data to a Json::Value
	*  @returns Json::Value containing information about the text
	*/
	Json::Value Save() const;
	/**
	*  Load the text data from a Json::Value
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);

private:
	///Disable copy construction
	Text(const Text &a);
	Text& operator = (const Text &a);

private:
	std::shared_ptr<SDL_Texture> mTex;
	std::string mMessage, mFontFile;
	int mFontSize;
    Color mColor;
};

#endif