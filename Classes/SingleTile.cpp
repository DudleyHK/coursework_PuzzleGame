/*




*/
#include "cocos2d.h"
#include "SingleTile.h"


SingleTile::SingleTile()
{
	; // empty
}

SingleTile::~SingleTile()
{
	; // empty
}


void SingleTile::setImageInfomation(float xScale, float yScale, int ySize)
{
	this->scaleWidth = xScale;
	this->scaleHeight = yScale;
	this->imageHeight = ySize;
}


void SingleTile::setNewPosition(float xPos, float yPos)
{
	this->xPosition = xPos;
	this->yPosition = yPos;
}


void SingleTile::createTile(Vec2 tile, unsigned int widthIndex, unsigned int heightIndex)
{
	// create a tile from the image
	auto newTile = cocos2d::Sprite::create("p_hamsterRunning.jpg",
	cocos2d::Rect(xPosition, (imageHeight - yPosition) - tile.y, tile.x, tile.y));

	newTile->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	newTile->setPosition(Vec2((500 / 4) * widthIndex, (500 / 4) * heightIndex));
	newTile->setScaleX(scaleWidth);
	newTile->setScaleY(scaleHeight);
}
