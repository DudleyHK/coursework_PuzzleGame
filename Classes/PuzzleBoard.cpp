/*





*/
#include "PuzzleBoard.h"



PuzzleBoard::PuzzleBoard()
{
	srand((unsigned int)time(nullptr));
}

PuzzleBoard::~PuzzleBoard()
{
	; // Empty
}

void PuzzleBoard::getSpriteList(std::vector<SingleTile*> *tileList)
{
	*tileList = this->tileList;
}

void PuzzleBoard::getCoordinates(int posID, int* w, int* h)
{
	*h  = posID / 4;
	*w = posID - (4 * *h);
}

void PuzzleBoard::createImage()
{
	auto puzzleImage = cocos2d::Sprite::create("p_hamsterRunning.jpg");
	puzzleImage->setAnchorPoint(cocos2d::Vec2(0, 0));
	puzzleImage->setPosition(cocos2d::Director::getInstance()->getVisibleOrigin());

	// set the height and width of the image
	imageWidth = puzzleImage->getBoundingBox().size.width;
	imageHeight = puzzleImage->getBoundingBox().size.height;

	sliceImage(puzzleImage);
}

/*This funciton needs to replace 4 with the number of width segments
and number of height segments set in the settings function*/
void PuzzleBoard::sliceImage(cocos2d::Sprite* puzzleImage)
{
	// Run through each tile that needs to be created. 
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			SingleTile* singleTile = SingleTile::create();

			//cocos2d::Sprite::create(puzzleImage/*pass in the relevant settings information*/);//////////// NEW KEYWPORD	//////////// NEW KEYWPORD	//////////// NEW KEYWPORD
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
		/*The number of width segmenets - 1*/			//////CHECK
		if (index == 3)
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
	if ((h < 4 && h >= 0) &&
		(w < 4 && w >= 0))
	{
		return true;
	}
	return false;
}


void PuzzleBoard::getDirection()
{
	int randValue = 0;
	int adjacentPosID = 0;
	int emptyPosID = 0;
	int empIndexW = 0;
	int empIndexH = 0;
	bool isValid = false;
	

	for (int i = 0; i < 100; i++)
	{
		isValid = false;

		emptyPosID = tileList.at(empTileID)->getPositionID();
		getCoordinates(emptyPosID, &empIndexW, &empIndexH);

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
			isValid = checkInBounds(newIndexW, newIndexH);
		} // END WHILE

		adjacentPosID = tileList.at((newIndexH * 4) + newIndexW)->getPositionID();
		swap(adjacentPosID);
	} // END FOR
}

void PuzzleBoard::swap(int adjacentPosID)
{	
	/* =========================SWAP POSITIONS==================================== */
	// save the values into temp variables
	float tempEmpPosX = tileList.at(empTileID)->getPositionX();
	float tempEmpPosY = tileList.at(empTileID)->getPositionY();

	// swap the empty posX and posY for the adjacent posX and posY
	tileList.at(empTileID)->setPositionX(
		tileList.at((newIndexH * 4) + newIndexW)->getPositionX());

	tileList.at(empTileID)->setPositionY(
		tileList.at((newIndexH * 4) + newIndexW)->getPositionY());

	// set the tile in the adjacent position to the position of the emptytile
	tileList.at((newIndexH * 4) + newIndexW)->setPositionX(tempEmpPosX);
	tileList.at((newIndexH * 4) + newIndexW)->setPositionY(tempEmpPosY);

	/* ============================SWAP POSITION IDs============================== */
	int tempAdjPosID = adjacentPosID;

	// set the adjacent positions posID to the positionID of the emptyTile
	tileList.at((newIndexH * 4) + newIndexW)->setPositionID(
		tileList.at(empTileID)->getPositionID());

	// set the tile positions as new positions
	tileList.at(empTileID)->setPositionID(tempAdjPosID);
}










