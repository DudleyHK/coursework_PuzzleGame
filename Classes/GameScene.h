/*



*/
#pragma once
#include "cocos2d.h"
#include "PuzzleBoard.h"
#include "Tags.h"
#include <vector>


class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	
	GameScene();
	~GameScene();

	
	virtual bool initLayer();

	void addPuzzleBoard();
	bool getEmptyTilePos(int n_posID);		// function which return the Vec2 of the empty tile
	void checkForEmpty(int tileID);

	bool checkInBounds(int _hIndex, int _wIndex);
	void checkLeft(unsigned int _posID, int* n_posID);
	void checkRight(unsigned int _posID, int* n_posID);
	void checkUp(unsigned int _posID, int* n_posID);
	void checkDown(unsigned int _posID, int* n_posID);

	void swapTiles(unsigned int posID, int n_posID);
	void addEvent();
	bool onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event);
	bool onTouchMove(cocos2d::Touch* click, cocos2d::Event* event);

	//void initBackground();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	std::vector<SingleTile*> tileList;
	PuzzleBoard* puzzleBoard = new PuzzleBoard;									///////////////NEW KEYWORD

	int hIndex;
	int wIndex;

};
