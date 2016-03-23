/*





*/
#pragma once
#include "cocos2d.h"
//#include "ImageLibrary.h"
#include <vector>

USING_NS_CC;
//using namespace ImageLib;

class PuzzleBoard
{
public:
	PuzzleBoard();
	~PuzzleBoard();

	void init(/*Sprite* img*/);
	void getImage(cocos2d::Vector<Sprite*> *tileList);

	void createImage();													///// PuzzleBoard function
	void sliceImage();													/////
	void makeTileTransparent();

	


private:
	cocos2d::Vector<Sprite*> puzzleTiles;
	// cocos2d::Sprite* puzzleImage;


	int imageWidth = 0, imageHeight = 0;
	float scaleWidth = 0.0f, scaleHeight = 0.0f;


};
