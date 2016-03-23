/*





*/
#pragma once
#include "PuzzleBoard.h"


class SingleTile : public PuzzleBoard
{
public:
	SingleTile();
	~SingleTile();

private:
	float xPosition = 0.0f, yPosition = 0.0f;			//NEW WIDTHPOS AND HIEGHTPOS


};


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
		it to the scene as a chile object */
		auto tile = Sprite::create("p_hamsterRunning.jpg", Rect(widthPosition,
			(imageHeight - heightPosition) - imageTile.y, imageTile.x, imageTile.y));

		tile->setAnchorPoint(Vec2(0, 0));
		tile->setPosition(Vec2((500 / 4) * widthIndex, (500 / 4) * heightIndex));
		tile->setScaleX(scaleWidth);
		tile->setScaleY(scaleHeight);

		puzzleTiles.pushBack(tile);
	}
}