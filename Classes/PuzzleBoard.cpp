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

int PuzzleBoard::produceRandValue()
{
	return rand() % 4 + 1;
}


void PuzzleBoard::shuffleBoard()
{
	int counter = 10;
	while (counter > 0)
	{
		// get the position of the empty tile
		int posID = tileList.at(3)->getPositionID();
		int _posID = 0;

		bool inBounds = false;
		while (!inBounds)
		{
			int randValue = produceRandValue();

			switch (randValue)
			{
			case 1: // check above
				_posID = posID + 4;
				break;
			case 2:// check below
				_posID = posID - 4;
				break;
			case 3:// check left
				_posID = posID - 1;
				break;
			case 4:// check right
				_posID = posID + 1;
				break;
			default:
				; // empty
				break;
			}

			// Decode the new positionID to get the x/y coordinates. 
			inBounds = checkInBounds((_posID / 4), (_posID - ((_posID / 4) * 4)));
		} // END INBOUNDS WHILE

		int _tileID = 0;

		for (unsigned int index = 0; index < tileList.size(); index++)
		{
			// find the tileID of the tile at the position next to the empty tile
			if (tileList.at(index)->getPositionID() == _posID)
			{
				_tileID = index;
				break;
			}
		}
			//selected sprite
		auto selectedSprite = tileList.at(_tileID);
		auto selectedSpritePosition = tileList.at(_tileID)->getPosition();

		// empty sprite
		auto emptySprite = tileList.at(3);
		auto emptySpritePosition = tileList.at(3)->getPosition();

		auto moveEmptySprite = cocos2d::MoveBy::create(0.1, cocos2d::Vec2(selectedSpritePosition.x, selectedSpritePosition.y));
		auto moveSelectedSprite = cocos2d::MoveBy::create(0.1, cocos2d::Vec2(emptySpritePosition.x, emptySpritePosition.y));

	

		//tilesToMove.push_back(selectedSprite);
		//tilesToMove.push_back(emptySprite);
	

		// are any actions running?
	//	int spriteActionsRunning = selectedSprite->getNumberOfRunningActions();
	//	int emptyActionsRunning = emptySprite->getNumberOfRunningActions();

	//	if (spriteActionsRunning == 0 && emptyActionsRunning == 0)
	//	{
			int temp = tileList.at(_tileID)->getPositionID();

			//selectedSprite->run     //(moveSelectedSprite);
		//	emptySprite->       //(moveEmptySprite);

			// set the position value as new positions
			tileList.at(_tileID)->setPositionID(tileList.at(3)->getPositionID());

			// set the tile positions as new positions
			tileList.at(3)->setPositionID(temp);
		//}
		counter--;
	} // WHILE COUNTER END

	/*
	for (unsigned int index = 0; index < tilesToMove.size(); index++)
	{
		auto currentSprite = tilesToMove.at(index)->get
		auto currentSpritePosition = tilesToMove.at(index)->getSpriteFrame();

		auto moveSprite = cocos2d::MoveBy::create(0.1, cocos2d::Vec2(currentSpritePosition.x, currentSpritePosition.y));

		currentSprite->runAction(moveSprite);
	}
	*/
}


bool PuzzleBoard::checkInBounds(int _hIndex, int _wIndex)
{
	if ((_hIndex < 4 && _hIndex >= 0) &&
		(_wIndex < 4 && _wIndex >= 0))
	{
		return true;
	}
	return false;
}

