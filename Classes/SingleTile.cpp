/*

*/
#include "SingleTile.h"


SingleTile::SingleTile()
{
	 // do the relevant calculation to get the number of tiles 
}

SingleTile::~SingleTile()
{
	; // Empty
}

SingleTile * SingleTile::create()
{
	SingleTile* singleTile = new SingleTile(/*pass in the relevant settings information*/);

	if (!singleTile->initWithFile("p_hamsterRunning.jpg"))
	{
		CC_SAFE_DELETE(singleTile);
		return nullptr;
	}

	singleTile->autorelease();

	return singleTile;
}

void SingleTile::setImageData(int imgHeight, int imgWidth)
{
	this->imageHeight = imgHeight;
	this->imageWidth = imgWidth;
}

void SingleTile::setPositionID(int _posID)
{
	positionID = _posID;
}

void SingleTile::setTileID(int _tileID)
{
	tileID = _tileID;
}

void SingleTile::setTileSize()
{
	tileHeight = imageHeight / 4;
	tileWidth = imageWidth / 4;
}

int SingleTile::getTileHeight()
{
	return tileHeight;
}

int SingleTile::getTileWidth()
{
	return tileWidth;
}

int SingleTile::getTileID()
{
	return tileID;
}

int SingleTile::getPositionID()
{
	return positionID;
}

void SingleTile::initTile(unsigned int hIndex, unsigned int wIndex)
{
	setTileSize();

	cocos2d::Vec2 tile = cocos2d::Vec2(tileWidth, tileHeight);

	xPosition = tile.x * wIndex;
	yPosition = tile.y * hIndex;
	setScaleX((500.0f / imageWidth) * 0.98);
	setScaleY((500.0f / imageHeight) * 0.98); 


	setTextureRect(cocos2d::Rect(xPosition, (imageHeight - yPosition) - tile.y,
		tile.x, tile.y));

	setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	setPosition(cocos2d::Vec2((500 / 4) * wIndex, (500 / 4) * hIndex));

	positionID = (hIndex * 4) + wIndex;
	tileID = (hIndex * 4) + wIndex;
}