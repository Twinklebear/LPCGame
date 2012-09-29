#ifndef TILEBAR_H
#define TILEBAR_H

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
	///Update the game object
	void Update();
	/**
	*  Move the object
	*  @param deltaT The elapsed time
	*/
	void Move(float deltaT);
	/**
	*  Draw the gameobject, apply an adjustment for the camera if one is desired
	*  @param cam The camera to adjust for
	*/
	void Draw(Camera *cam = nullptr);
	///On mouse up event
	void OnMouseUp();
	/**
	*  Get the selected tile type
	*  @return The tile type that is currently selected
	*/
	Tile GetSelection();
	/**
	*  Check if the tile selection bar is active
	*  @return T/F if the tile pane is active
	*/
	bool TilePaneActive();
	/**
	*  Get the selected object
	*  @return The selected MapObject to place
	*  Note: Not currently used, as MapObjects aren't implemented
	*/
	//Object GetObjectSelection();
	/**
	*  Check if the object selection bar is active
	*  @return T/F if the object pane is active
	*/
	//bool ObjectPaneActive();
	/**
	*  Get the selected entity (GameObject) to place on the map
	*  @return The GameObject to add to the map
	*/
	//GameObject GetEntitySelection();
	/**
	*  Check if the entity selection bar is active
	*  @return T/F if the entity bar is active
	*/
	//bool EntityPaneActive();
	/**
	*  Save the gameobject data to a json value and return it
	*  The GameObject instance of the function takes care of saving
	*  the base object members, physics, image and tags
	*  @return Json::Value containing the gameobject data
	*/
	Json::Value Save();
	/**
	*  Load the gameobject from a Json::Value
	*  The GameObject instance of the function takes care of loading
	*  the base object members, physics, image and tags
	*  @param val The Json::Value to load from
	*/
	void Load(Json::Value val);

private:
	enum Pane { TILE, OBJECT, ENTITY };

private:
	Image mTileImage;
	Image mSelector;
	std::vector<Tile> mTiles;
	int mSelectedTile;
	int mActivePane;

	int tilesPerRow;
	int spacer;
	int xOffset;
	int yOffset;
	int tileWidth;
	int tileHeight;

};

#endif