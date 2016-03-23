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


/*
void PuzzleBoard::getImage(Vector<Sprite*> *tileList)
{
	//*tileList = this->puzzleTiles;
}
*/


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
	auto puzzleImage = Sprite::create("p_hamsterRunning.jpg");
	puzzleImage->setAnchorPoint(Vec2(0, 0));
	puzzleImage->setPosition(Director::getInstance()->getVisibleOrigin());

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
	cocos2d::Vec2 tile = Vec2(imageWidth / 4, imageHeight / 4);

	// Run through each tile that needs to be created. 
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			// Create an instance of the single tile object (create new tile)
			SingleTile* singleTile = new SingleTile;

			// get position points of new tile
			float xPosition = tile.x * widthIndex;
			float yPosition = tile.y * heightIndex;


			singleTile->setImageInfomation(scaleWidth, scaleHeight, imageHeight);
			singleTile->setNewPosition(xPosition, yPosition);

			// draw image tile 
			singleTile->createTile(tile, widthIndex, heightIndex); 

			// EITHER HERE OR AT THE END OF createTile() I NEED TO PUSHBACK ONTO THE tileList.
		}
	}


	/*
	// Get the size of a single tile 
	cocos2d::Vec2 imageTile = Vec2(imageWidth / 4, imageHeight / 4);

	// pass in imageTile via paramater

	// Run through each position in the sprite
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			/// create new instances of tiles
			/// add them to the list. 
			
			float widthPosition = imageTile.x * widthIndex;
			float heightPosition = imageTile.y * heightIndex;




			// Create a tile, set anchor point and position, scale the tile

			auto tile = Sprite::create("p_hamsterRunning.jpg", Rect(widthPosition,
				(imageHeight - heightPosition) - imageTile.y, imageTile.x, imageTile.y));

			tile->setAnchorPoint(Vec2(0, 0));
			tile->setPosition(Vec2((500 / 4) * widthIndex, (500 / 4) * heightIndex));
			tile->setScaleX(scaleWidth);
			tile->setScaleY(scaleHeight);

			puzzleTiles.pushBack(tile);
		}
	}

	makeTileTransparent();

	*/
}

/*
/*Run through each element of the vector list and remove the last tile
void PuzzleBoard::makeTileTransparent()
{
	for (int index = 0; index <= puzzleTiles.size(); index++)
	{
		/*The number of width segmenets - 1/
		if (index == 3)
		{
			puzzleTiles.at(index)->setOpacity(0);					//////////////CHECK THIS
		}
	}
}
*/
