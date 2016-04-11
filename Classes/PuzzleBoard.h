/*





*/
#pragma once
#include "cocos2d.h"
#include "SingleTile.h"
#include <cstdlib>
#include <ctime>
#include <vector>


class PuzzleBoard
{
public:
	PuzzleBoard();
	~PuzzleBoard();

	void init(/*Sprite* img*/);
	void getSpriteList(std::vector<SingleTile*> *list);

	void createImage();
	void sliceImage(cocos2d::Sprite* puzzleImage);

	// Run through each element of the vector list and remove the last tile
	void setTransparentTile();

	// @ -- return:  random number between 1 and 4
	int produceRandValue();

	void shuffleBoard();

	bool checkInBounds(int _hIndex, int _wIndex);

	cocos2d::MoveTo* getMoveAction(cocos2d::Sprite* currentTile);
	


private:
	std::vector<SingleTile*> tileList;
	std::vector<cocos2d::Sprite*> tilesToMove;

	int imageWidth = 0, imageHeight = 0;
	int hIndex = 0, Index = 0;
	int _hIndex = 0, _wIndex = 0;
	float scaleWidth = 0.0f, scaleHeight = 0.0f;
};
