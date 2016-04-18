/*
	Solution: PuzzleBoard.cpp
	Author: Dudley Dawes
	Date: 19/04/16
*/
#include "PuzzleBoard.h"

PuzzleBoard::PuzzleBoard()
{
	srand((unsigned int)(time(0)));
}

PuzzleBoard::~PuzzleBoard()
{
	; // Empty
}

void PuzzleBoard::getSpriteList(std::vector<SingleTile*> *tileList)
{
	*tileList = this->tileList;
}

void PuzzleBoard::getCoordinates(int emptyPosID, int* const h, int* const w)
{
	*h = emptyPosID / widthSegments;
	*w = emptyPosID - (*h * widthSegments);
}

void PuzzleBoard::setGridSize(int heightSegs, int widthSegs)
{
	heightSegments = heightSegs;
	widthSegments = widthSegs;

	empTileID = widthSegments - 1;
}

void PuzzleBoard::setPuzzleImage(int imgCode, ImageLib* imgLib)
{
	this->imageCode = imgCode;
	puzzleImage = cocos2d::Sprite::createWithTexture(
		imgLib->getPuzzleImg(imageCode)->getTexture());
}

void PuzzleBoard::createImage()
{
	puzzleImage->setAnchorPoint(cocos2d::Vec2(0, 0));
	puzzleImage->setPosition(cocos2d::Director::getInstance()->getVisibleOrigin());

	imageWidth = puzzleImage->getBoundingBox().size.width;
	imageHeight = puzzleImage->getBoundingBox().size.height;

	sliceImage(puzzleImage);
}

void PuzzleBoard::sliceImage(cocos2d::Sprite* puzzleImage)
{
	// Run through each tile that needs to be created. 
	for (unsigned int heightIndex = 0; heightIndex < (unsigned int) heightSegments;
	heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < (unsigned int) widthSegments;
		widthIndex++)
		{
			SingleTile* singleTile = SingleTile::create(
				heightSegments, 
				widthSegments, 
				puzzleImage);

			singleTile->setImageData(imageHeight, imageWidth);
			singleTile->initTile(heightIndex, widthIndex);

			tileList.push_back(singleTile);
		}
	}

	setTransparentTile();
}

void PuzzleBoard::setTransparentTile()
{
	for (unsigned int index = 0; index <= tileList.size(); index++)
	{
		if (index == (widthSegments - 1))
		{
			tileList.at(index)->setOpacity(0);
		}
	}
}

int PuzzleBoard::produceRandValue() const
{
	return rand() % 4 + 1;
}


bool PuzzleBoard::checkInBounds(int w, int h) const
{
	if ((h < heightSegments && h >= 0) &&
		(w < widthSegments && w >= 0))
	{
		return true;
	}
	return false;
}


void PuzzleBoard::getDirection()
{
	int randValue = 0;
	int adjacentTileID = 0;
	int adjacentPosID = 0;
	int emptyPosID = 0;
	int empIndexW = 0;
	int empIndexH = 0;
	int rightPlace = 0;
	bool isValid = false;

	// number of shuffles
	for (int numberOfShuffles = 0; numberOfShuffles < 100; numberOfShuffles++)
	{
		isValid = false;

		emptyPosID = tileList.at(empTileID)->getPositionID();
		getCoordinates(emptyPosID, &empIndexH, &empIndexW);

		// While a value space is not found. 
		while (!isValid)
		{
			randValue = produceRandValue();

			switch (randValue)
			{
			case 1: // Up 
				newIndexW = empIndexW;
				newIndexH = empIndexH + 1;
				break;
			case 2: // Down
				newIndexW = empIndexW;
				newIndexH = empIndexH - 1;
				break;
			case 3: // Left
				newIndexW = empIndexW - 1;
				newIndexH = empIndexH;
				break;
			case 4: // Right
				newIndexW = empIndexW + 1;
				newIndexH = empIndexH;
				break;
			default:
				break;
			} // END SWITCH

			adjacentTileID = getAdjacentTileID(&adjacentPosID);
			if (adjacentTileID != -1)
			{
				isValid = checkInBounds(newIndexW, newIndexH);
			}
		} // END WHILE

		swap(adjacentTileID, adjacentPosID);
		getCorrectTiles(&rightPlace);

		// check how many positions are placed correctely
		if (rightPlace == tileList.size())
		{
			numberOfShuffles--; // decrement shuffle counter
		}
	} // END SHUFFLE
}

int PuzzleBoard::getAdjacentTileID(int* const adjacentPosID)
{
	*adjacentPosID = (newIndexH * widthSegments) + newIndexW;

	for (unsigned int index = 0; index < tileList.size(); index++)
	{
		if (tileList.at(index)->getPositionID() == *adjacentPosID)
		{
			return index;
		}
	}
	return -1;
}

void PuzzleBoard::swap(int adjacentTileID, int adjacentPosID)
{
	/* =========================SWAP POSITIONS==================================== */
	// save the values into temp variables
	float tempEmpPosX = tileList.at(empTileID)->getPositionX();
	float tempEmpPosY = tileList.at(empTileID)->getPositionY();

	// swap the empty posX and posY for the adjacent posX and posY
	tileList.at(empTileID)->setPositionX(
		tileList.at(adjacentTileID)->getPositionX());

	tileList.at(empTileID)->setPositionY(
		tileList.at(adjacentTileID)->getPositionY());

	// set the tile in the adjacent position to the position of the emptytile
	tileList.at(adjacentTileID)->setPositionX(tempEmpPosX);
	tileList.at(adjacentTileID)->setPositionY(tempEmpPosY);

	/* ============================SWAP POSITION IDs============================== */
	int tempAdjPosID = adjacentPosID;

	// set the adjacent positions posID to the positionID of the emptyTile
	tileList.at(adjacentTileID)->setPositionID(
		tileList.at(empTileID)->getPositionID());

	// set the tile positions as new positions
	tileList.at(empTileID)->setPositionID(tempAdjPosID);
}


void PuzzleBoard::getCorrectTiles(int* const rightPlace)
{
	*rightPlace = 0;

	for (unsigned int index = 0; index < tileList.size(); index++)
	{
		if (tileList.at(index)->getTileID() == tileList.at(index)->getPositionID())
		{
			*rightPlace += 1;
		}
	}
}