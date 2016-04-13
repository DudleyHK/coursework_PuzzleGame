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
	void sliceImage();

	// Run through each element of the vector list and remove the last tile
	void setTransparentTile();

	void shuffleTiles();

	// @ -- return:  random number between 1 and 4
	int produceRandValue();

	void getIndexValues(int posID, int* hIndex, int* wIndex);

	bool checkBounds();
	void moveTiles();


private:
	std::vector<SingleTile*> tileList;

	int imageWidth = 0, imageHeight = 0;
	int _hIndex = 0, _wIndex = 0;
	float scaleWidth = 0.0f, scaleHeight = 0.0f;
};
