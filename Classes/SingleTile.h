/*





*/
#pragma once
#include "cocos2d.h"


class SingleTile
{
public:
	SingleTile();
	~SingleTile();

	void setNewPosition(float xPos, float yPos);
	void setImageInfomation(float xScale, float yScale, int ySize);
	void setPositionID(int posID);
	void setTileID(int tileID);
	int getTileID();
	int getPositionID();
	cocos2d::Sprite* getSprite();

	void createTile(cocos2d::Vec2 tile, unsigned int widthIndex, unsigned int heightIndex);
	


private:
	float xPosition = 0.0f, yPosition = 0.0f;	
	float scaleWidth = 0.0f, scaleHeight = 0.0f;
	int imageHeight = 0;

	cocos2d::Sprite* sprite;

	int positionID;
	int tileID;

};

/*
// Run through each position in the sprite
for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
{
	for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
	{
		/// create new instances of tiles
		/// add them to the list. 

		float widthPosition = imageTile.x * widthIndex;
		float heightPosition = imageTile.y * heightIndex;

		/* Create a tile, set anchor point and position, scale the tile and finally add
		it to the scene as a chile object /
		auto tile = Sprite::create("p_hamsterRunning.jpg", Rect(widthPosition,
			(imageHeight - heightPosition) - imageTile.y, imageTile.x, imageTile.y));

		tile->setAnchorPoint(Vec2(0, 0));
		tile->setPosition(Vec2((500 / 4) * widthIndex, (500 / 4) * heightIndex));
		tile->setScaleX(scaleWidth);
		tile->setScaleY(scaleHeight);

		puzzleTiles.pushBack(tile);
	}
}
*/