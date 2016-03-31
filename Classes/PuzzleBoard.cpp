/*





*/
#include "PuzzleBoard.h"



PuzzleBoard::PuzzleBoard()
{
	; // empty
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


/*Run through each element of the vector list and remove the last tile*/
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
