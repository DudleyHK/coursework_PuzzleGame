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
	bool getEmptyTilePos(int _posID);		// function which return the Vec2 of the empty tile
	void checkForEmpty(int posID);

	bool checkInBounds(int _hIndex, int _wIndex);
	void checkLeft(int _posID, int* tileID);
	void checkRight(int _posID, int* tileID);
	void checkUp(int _posID, int* tileID);
	void checkDown(int _posID, int* tileID);

	void swapTiles(int posID, int tileID);
	void swapVectorElements(std::vector<SingleTile>, std::vector<SingleTile>);
	void addEvent();
	bool onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event);
	//bool onTouchMove(cocos2d::Touch* click, cocos2d::Event* event);

	//void initBackground();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	std::vector<SingleTile*> tileList;
	PuzzleBoard* puzzleBoard = new PuzzleBoard;									///////////////NEW KEYWORD

	int hIndex;
	int wIndex;

	int elementInListWhereEmptyPosIDIs;
	int tileID;									////////////////// CHECK IT OUT / CLEAN UP
	int n_tileID;
	int testID;					// posID

};
