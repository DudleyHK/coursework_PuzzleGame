/*


// @ -- Detail:
// @ -- Param:
// @ -- Return:


*/

#pragma once
#include "cocos2d.h"

///////////////////////////////////////////////// NOTHING HAS BEEN UPDATED
class SingleTile : public cocos2d::Sprite
{
public:
	SingleTile(int heightSegs, int widthSegs);
	~SingleTile();

	/* =====GETTERS AND SETTERS===== */
	void setPuzzleImage(cocos2d::Sprite* img);
	void setImageData(int imgHeight, int imgWidth);
	void setPositionID(int posID);
	void setTileID(int tileID);
	void setTileSize();
	int getTileHeight();
	int getTileWidth();
	int getTileID();
	int getPositionID();
	/* ============================== */

	// @ -- Detail: Create an instance of the class. Notify the object of the image which 
	//			will be used to construct the tile sprite. 
	// @ -- Param: Puzzle image sprite.
	static SingleTile* create(int heightSegs, int widthSegs, cocos2d::Sprite* img);

	// @ -- Detail: Set the size ratios for a single tile.
	// @ -- Param: The coordinates of the tile being created. 
	void initTile(unsigned int hIndex, unsigned int wIndex);

private:
	/* =====WHOLE IMAGE===== */
	cocos2d::Sprite* puzzleImage;
	int imageWidth = 0;
	int imageHeight = 0;
	int heightSegments = 0;
	int widthSegments = 0;
	/* =====SINGLE TILE===== */
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float tileHeight = 0.0f;
	float tileWidth = 0.0f;
	int positionID = 0;
	int tileID = 0;
};