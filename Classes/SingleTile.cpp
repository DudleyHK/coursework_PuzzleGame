/*
	Solution: SingleTile.cpp
	Author: Dudley Dawes
	Date: 19/04/16
*/
#include "SingleTile.h"


SingleTile::SingleTile(int heightSegs, int widthSegs)
{
	this->heightSegments = heightSegs;
	this->widthSegments = widthSegs;
}

SingleTile::~SingleTile()
{
	; // Empty
}

SingleTile * SingleTile::create(int heightSegs, int widthSegs, cocos2d::Sprite* img)
{
	SingleTile* singleTile = new SingleTile(heightSegs, widthSegs);

	if (!singleTile->initWithTexture(img->getTexture()))
	{
		CC_SAFE_DELETE(singleTile);
		return nullptr;
	}
	singleTile->autorelease();

	return singleTile;
}

void SingleTile::setPuzzleImage(cocos2d::Sprite* img)
{
	this->puzzleImage = img;
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
	tileHeight = imageHeight / heightSegments;
	tileWidth = imageWidth / widthSegments;
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

void SingleTile::initTile(unsigned int hIndex, 	unsigned int wIndex)
{
	setTileSize();

	cocos2d::Vec2 tile = cocos2d::Vec2(tileWidth, tileHeight);
	xPosition = tile.x * wIndex;
	yPosition = tile.y * hIndex;
	setScaleX((500.0f / imageWidth) * 0.98);
	setScaleY((500.0f / imageHeight) * 0.98); 

	setTextureRect(cocos2d::Rect(xPosition, (imageHeight - yPosition) - tile.y, 
		tile.x, tile.y));

	setAnchorPoint(cocos2d::Vec2(0,0));
	setPosition(cocos2d::Vec2(
		(500 / widthSegments) * wIndex, 
		(500 / widthSegments) * hIndex));

	positionID = (hIndex * widthSegments) + wIndex;
	tileID = (hIndex * widthSegments) + wIndex;
}