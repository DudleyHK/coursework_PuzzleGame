/*



*/
#pragma once
#include "cocos2d.h"
#include <vector>
#include "PuzzleBoard.h"


class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	
	GameScene();
	~GameScene();

	virtual bool initLayer();

	void addImageToScene();
	//void addEvent();
	//void initBackground();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	std::vector<SingleTile*> tileList;
	PuzzleBoard* puzzleBoard = new PuzzleBoard;									///////////////NEW KEYWORD

};
