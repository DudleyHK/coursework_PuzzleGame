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

/*
//(SingleTile* singleTile, cocos2d::Vec2 tileSize,unsigned int hIndex, unsigned int wIndex)
Sprite * Sprite::create()
{
	SingleTile* singleTile = new SingleTile(/*pass in the relevant settings information/);

	if (!singleTile->init())
	{
		CC_SAFE_DELETE(singleTile);
		return nullptr;
	}

	singleTile->autorelease();

	return singleTile;
}
*/

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

void SingleTile::setTileID(int _tileID)
{
	tileID = _tileID;
}

void SingleTile::setPositionID(int _posID)
{
	positionID = _posID;
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
	// set the size for a single tile (Tell the tile object how big it will need to be)
	cocos2d::Vec2 tile = cocos2d::Vec2(imageWidth / 4, imageHeight / 4);

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

	/*
	// Scale width and height, and reduce its size by 2%
	scaleWidth = (500.0f / imageWidth) * 0.98;
	scaleHeight = (500.0f / imageHeight) * 0.98;

	*/


	// create a tile from the image
	//auto newTile = cocos2d::Sprite::create("p_hamsterRunning.jpg", cocos2d::Rect()
	/*cocos2d::Rect(xPosition, (imageHeight - yPosition) - tile.y, tile.x, tile.y));*/


	/*
	newTile->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	newTile->setPosition(cocos2d::Vec2((500 / 4) * widthIndex, (500 / 4) * heightIndex));
	newTile->setScaleX(scaleWidth);
	newTile->setScaleY(scaleHeight);

	// set position
	positionID = (heightIndex * 4) + widthIndex;
	tileID = (heightIndex * 4) + widthIndex;

	// save the sprite 
	sprite = newTile;
	*/

	/*


	// get position points of new tile
	float xPosition = tile.x * widthIndex;
	float yPosition = tile.y * heightIndex;

	singleTile->setImageInfomation(scaleWidth, scaleHeight, imageHeight);
	singleTile->setNewPosition(xPosition, yPosition);

	// draw image tile
	singleTile->initTile(tile, widthIndex, heightIndex);

	*/
}
