#ifndef TILEBAR_H
#define TILEBAR_H

#include <memory>
#include "base.h"
#include "window.h"
#include "image.h"
#include "tile.h"
#include "entity.h"

///A class for selecting which tile to place in the editor
/**
*  A ui element for the editor that enable selection of desired
*  tiles/objects/etc to be placed into the map while editing
*/
///Planning: Can probably make this class similar to how I did it previously
class TileBar: public Entity {
public:
	TileBar();
	~TileBar();
	/**
	*  Draw the tilebar, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	void Draw(std::weak_ptr<Camera> cam) override;
	///On mouse up event
	void OnMouseDown() override;
	/**
	*  Get the selected tile type
	*  @return The tile type that is currently selected
	*/
	std::string GetSelection();
	/**
	*  Load the tilebar properties from a Json::Value
	*    tilesPerRow - The amount of tiles in each row.
	*    spacer      - The amount of space between edges in the tilebar. 
	*    xOffset     - The amount of offset in the X direction from the top left.
	*    yOffset     - The amount of offset in the Y direction from the top left.
	*    tileWidth   - The width of the tiles to be displayed in the tilebar.
	*    tileHeight  - The height of the tiles to be displayed in the tilebar.
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);
	/**
	*  Allows the tileset to be used in the tilebar
	*  @param The tileset as defined previously.
	*/
	void LoadTileSet(std::shared_ptr<TileSet> ts){ mTileSet = ts; }
	/**
	*  Save the tilebar data to a json value and return it
	*  @return Json::Value containing the tilebar data
	*/
	virtual Json::Value Save() const;
private:
	enum Pane { TILE, OBJECT, ENTITY };

private:
	//predefined variables from the tilebar json entry
	int tilesPerRow;
	int spacer;
	int xOffset;
	int yOffset;
	int tileWidth;
	int tileHeight;

	//info related to the selected tile
	Image mSelector;
	int mSelectedTile;
	std::string mSelectedTileName;

	//pointer to the tileset
	std::shared_ptr<TileSet> mTileSet;
};

#endif