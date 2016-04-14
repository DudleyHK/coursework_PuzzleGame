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

	void getCoordinates(int posID, int* w, int* h);

	void createImage();
	void sliceImage(cocos2d::Sprite* puzzleImage);

	// Run through each element of the vector list and remove the last tile
	void setTransparentTile();

	// @ -- Detail: Produce a random value 1 - 4
	// @ -- Return: The product of the random value
	int produceRandValue() const;

	void getDirection();

	bool checkInBounds(int w, int h) const;

	int getAdjacentTile() const;

	void swapTiles(int adjacentPosID);


private:
	std::vector<SingleTile*> tileList;

	float scaleWidth = 0.0f;
	float scaleHeight = 0.0f;
	int imageWidth = 0;
	int imageHeight = 0;
	int newIndexW = 0;
	int newIndexH = 0;
	

	const int empTileID = 3;
}; 