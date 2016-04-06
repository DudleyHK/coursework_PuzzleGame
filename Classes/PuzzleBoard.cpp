/*





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

// @ param - image file and the number of height/ width segments to be sliced
void PuzzleBoard::init (/*Sprite* img // This may only have to be a code now*/ )
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

	// Scale width and height, and reduce its size by 2%
	scaleWidth = (500.0f / imageWidth) * 0.98;
	scaleHeight = (500.0f / imageHeight) * 0.98;

	sliceImage();
}

/*This funciton needs to replace 4 with the number of width segments
and number of height segments set in the settings function*/
void PuzzleBoard::sliceImage()
{
	// set the size for a single tile (Tell the tile object how big it will need to be)
	cocos2d::Vec2 tile = cocos2d::Vec2(imageWidth / 4, imageHeight / 4);

	// Run through each tile that needs to be created. 
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			// Create an instance of the single tile object (create new tile)
			SingleTile* singleTile = new SingleTile;								//////////// NEW KEYWPORD

			// get position points of new tile
			float xPosition = tile.x * widthIndex;
			float yPosition = tile.y * heightIndex;

			singleTile->setImageInfomation(scaleWidth, scaleHeight, imageHeight);
			singleTile->setNewPosition(xPosition, yPosition);

			// draw image tile 
			singleTile->createTile(tile, widthIndex, heightIndex);

			// Add object to list. 
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
			tileList.at(index)->getSprite()->setOpacity(0);
		}
	}
}

void PuzzleBoard::shuffleTiles()
{
	int randVal = 0;
	int hIndex = 0;
	int wIndex = 0;


	// empty tile has a constant tileID of 3
	int posID = tileList.at(3)->getPositionID();
	getIndexValues(posID, &hIndex, &wIndex);

	bool inBounds = false;
	while (!inBounds)
	{
		randVal = produceRandValue();

		switch (randVal)
		{
		case 1: // Swap above position
			_hIndex = hIndex + 1;
			_wIndex = wIndex;
			break;

		case 2:// Swap left position
			_hIndex = hIndex;
			_wIndex = wIndex - 1;
			break;

		case 3:// Swap right position
			_hIndex = hIndex;
			_wIndex = wIndex + 1;
			break;

		case 4:// Swap below position
			_hIndex = hIndex - 1;
			_wIndex = wIndex;
			break;

		default:
			; // empty
			break;
		}

		inBounds = checkBounds();
	}
}

void PuzzleBoard::moveTiles()
{
	int _tileID = (4 * _hIndex) + _wIndex;

	//selected sprite
	auto selectedSprite = tileList.at(_tileID)->getSprite();
	auto selectedSpritePosition = tileList.at(_tileID)->getSprite()->getPosition();

	// empty sprite
	auto emptySprite = tileList.at(3)->getSprite();
	auto emptySpritePosition = tileList.at(3)->getSprite()->getPosition();

	auto moveEmptySprite = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(selectedSpritePosition.x, selectedSpritePosition.y));
	auto moveSelectedSprite = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(emptySpritePosition.x, emptySpritePosition.y));

	// are any actions running?
	//int spriteActionsRunning = selectedSprite->getNumberOfRunningActions();
	//	int emptyActionsRunning = emptySprite->getNumberOfRunningActions();

	//if (spriteActionsRunning == 0 && emptyActionsRunning == 0)
	//	{
	int temp = tileList.at(_tileID)->getPositionID();

	selectedSprite->runAction(moveSelectedSprite);
	emptySprite->runAction(moveEmptySprite);

	// set the position value as new positions
	tileList.at(_tileID)->setPositionID(tileList.at(3)->getPositionID());

	// set the tile positions as new positions
	tileList.at(3)->setPositionID(temp);

	//}

	emptySprite->stopAction(moveEmptySprite);
	selectedSprite->stopAction(moveSelectedSprite);
	//
}


void PuzzleBoard::getIndexValues(int posID, int* hIndex, int* wIndex)
{
	*hIndex = posID / 4;
	*wIndex = posID - (*hIndex * 4);
}

bool PuzzleBoard::checkBounds()
{
	if ((_hIndex < 4 && _hIndex >= 0) &&
		(_wIndex < 4 && _wIndex >= 0))
	{
		return true;
	}
	return false;
}

int PuzzleBoard::produceRandValue()
{
	return rand() % 4 + 1;
}



