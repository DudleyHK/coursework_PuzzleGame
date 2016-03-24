/*





*/
#pragma once
#include "cocos2d.h"
#include "SingleTile.h"
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
	//void makeTileTransparent();


private:
	std::vector<SingleTile*> tileList;

	int imageWidth = 0, imageHeight = 0;
	float scaleWidth = 0.0f, scaleHeight = 0.0f;


};
