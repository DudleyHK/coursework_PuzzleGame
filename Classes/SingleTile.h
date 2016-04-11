/*


// @ -- Detail:
// @ -- Param:
// @ -- Return:


*/
#pragma once
#include "cocos2d.h"


class SingleTile : public cocos2d::Sprite
{
public:
	SingleTile();
	~SingleTile();

	// @ -- Detail: Create an instance of the class. Notify the object of the image which 
	//					will be used to construct the tile sprite. 
	// @ -- Param: Puzzle image sprite.
	static SingleTile* create();

	// @ -- Detail: Give the object information about the puzzle image being used.
	// @ -- Param: The height and width along the x and y axis of the whole image.
	void setImageData(int imgHeight, int imgWidth);

	// @ -- Detail: 
	// @ -- Param: The coordinates of the tile being created. 
	void initTile(unsigned int hIndex, unsigned int wIndex);

	//void setNewPosition(float xPos, float yPos);
	//void setImageInfomation(float xScale, float yScale, int ySize);
	void setPositionID(int posID);
	void setTileID(int tileID);
	int getTileID();
	int getPositionID();

private:
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float scaleWidth = 0.0f;
	float scaleHeight = 0.0f;
	int imageWidth = 0;
	int imageHeight = 0;
	int positionID = 0;
	int tileID = 0;
};