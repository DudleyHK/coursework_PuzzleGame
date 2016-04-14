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

// @ param - image file and the number of height/ width segments to be sliced
void PuzzleBoard::init(/*Sprite* img // This may only have to be a code now*/)
{
	// Vector List
	//if (!puzzleTiles.empty())
	//{
	//	puzzleTiles.clear();
	//}

	createImage();
}

void PuzzleBoard::createImage()
{
	/* Create a sprite, set its anchor point and set its position to a position
	on the screen relative to the size resolution of the window*/
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
	int newIndexW = 0;
	int newIndexH = 0;
	
	bool isValid = false;

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
		}


		if(checkInBounds(newIndexW, newIndexH))
		{
			isValid = true;
		}
	}

	adjacentPosID = getAdjacentTile(newIndexW, newIndexH);
}


int PuzzleBoard::getAdjacentTile(int newIndexW, int newIndexH) const
{
	// run loop to find the index in the list which has the same coordinates
	// as i have passed in
	for (unsigned int index = 0; index < tileList.size(); index++)
	{
		// when we get to theat positoin in the list. 
		if((newIndexH * 4) + newIndexW == index)
		{
			// return its posID
			return tileList.at(index)->getPositionID();
		}
	}
	return -1;
}


// create a function that takes the adjacentPosID and the emptyPosID with these values I can swap the posIDs of both tiles.
// and change their posX, posY before the game begins.









