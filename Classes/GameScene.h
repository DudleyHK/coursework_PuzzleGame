/*



*/
#pragma once
#include "cocos2d.h"
#include "PuzzleBoard.h"
#include "GameEventListener.h"
USING_NS_CC;


class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	
	GameScene();
	~GameScene();

	virtual bool initLayer();
	void getTileInfo(cocos2d::Vector<cocos2d::Sprite*> *list);
	void addImageToScene();
	void addEvent();
	//void initBackground();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	cocos2d::Vector<Sprite*> puzzleTiles;

};
