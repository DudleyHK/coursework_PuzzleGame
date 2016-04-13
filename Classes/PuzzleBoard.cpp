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

/*void PuzzleBoard::getIndexValues(int posID, int* hIndex, int* wIndex)
{
	*hIndex = posID / 4;
	*wIndex = posID - (*hIndex * 4);
}*/

/*bool PuzzleBoard::checkBounds()
{
	if ((_hIndex < 4 && _hIndex >= 0) &&
		(_wIndex < 4 && _wIndex >= 0))
	{
		return true;
	}
	return false;
}
*/


