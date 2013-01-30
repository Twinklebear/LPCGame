#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include "external/json/json.h"
#include "rect.h"
#include "tile.h"
#include "vectors.h"

/**
*  A class for storing and retreiving tiles
*/
typedef std::unordered_map<std::string, Tile> mTileSetMap;
typedef std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> mImageSetMap;
class TileSet {
public:
	TileSet();
	/**
	*  Setup the TileSet class, if a filename is passed load the image
	*  @param file The filename
	*  @see Window::LoadTileSet for the loading function
	*/
	TileSet(const std::string &file);
	/**
	*  Empty
	*/
	~TileSet();
	/**
	*  Adds an image to the tileset, and parses it's .json file
	*  into the tileset
	*  @param file The filename for the image
	*/
	virtual void Add(const std::string &file);
	/**
	*  Gets pointer to the SDL_Texture that is associated with
	*  the passed tile name.
	*  @param tile The name of the tile in the tileset
	*  @return SDL_Texture* A pointer to the associated iamge
	*/
	virtual SDL_Texture* Texture(const std::string &tile);
	/**
	*  Gets the Recti (Box) that is associated with the passed 
	*  tile name.
	*  @param tile The name of the tile in the tileset
	*  @return Recti A box for the associated iamge
	*/
	virtual Recti Clip(const std::string &tile);
	/**
	*  Gets the filename of the image that is associated 
	*  with the passed tile name.
	*  @param tile The name of the tile in the tileset
	*  @return Recti A box for the associated iamge
	*/
	virtual std::string File(const std::string &tile);
	/**
	*  Gets the bool Solid property of the tile.
	*  @param tile The name of the tile in the tileset
	*  @return bool true/false for the solid state of a tile
	*/
	virtual bool Solid(const std::string &tile);
	/**
	*  Returns the size of the tileset
	*  @return int The size of the tileset
	*/
	int Size() { return mTileSet.size(); }
	/**
	*  Returns the begining iterator of the tileset
	*  @return iterator The beinging of the tileset.
	*/
	mTileSetMap::iterator Begin() { return mTileSet.begin(); }
	/**
	*  Returns the end iterator of the tileset
	*  @return iterator The beinging of the tileset.
	*/
	mTileSetMap::iterator End() { return mTileSet.end(); }
	/**
	*  Load an image and its properties from a Json::Value into the tileset
	*  @param val The Json::Value to load from
	*/
	virtual void Load(Json::Value val);	
	/**
	*  Save the tileset data to a json value and return it
	*  @return Json::Value containing the tilebar data
	*/	
	Json::Value Save();

private:
	///Disable image copy construction
	TileSet(const TileSet &a);
	TileSet& operator = (const TileSet &a);

	void ParseImageJson(Json::Value val, const std::string &file);

protected:
	mTileSetMap mTileSet;
	mImageSetMap mImageSet;
	mTileSetMap::iterator mTileSetBegin;
	mTileSetMap::iterator mTileSetEnd;
	mImageSetMap::iterator mImageSetBegin;
	mImageSetMap::iterator mImageSetEnd;

	SDL_Texture* lastTexture;
	std::string lastTextureName;

	Tile lastTile;
	std::string lastTileName;


};

#endif