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
	void addEvent();
	bool onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event);
	//bool onTouchMove(cocos2d::Touch* click, cocos2d::Event* event);
	void checkForEmpty(int tileID);
	void checkLeft(int _posID, int* tileID);
	void checkRight(int _posID, int* tileID);
	void checkUp(int _posID, int* tileID);
	void checkDown(int _posID, int* tileID);
	bool getEmptyTilePos(int n_posID);

	// @ -- param:	take height and width of the position being checked.
	bool checkInBounds(int _hIndex, int _wIndex);

	void swapTiles(int posID, int tileID);


	//void initBackground();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	std::vector<SingleTile*> tileList;

	PuzzleBoard* puzzleBoard = new PuzzleBoard;									///////////////NEW KEYWORD

	int hIndex = 0, wIndex = 0;

};
