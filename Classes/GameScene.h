/*



*/
#pragma once
#include "cocos2d.h"
#include "CreatePuzzle.h"
USING_NS_CC;


class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	
	GameScene();
	~GameScene();

	virtual bool initLayer();
	void addImageToScene();

	//void initBackground();
	//void sliceImage();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
//	float widthPosition = 0, heightPosition = 0;
	cocos2d::Vector<Sprite*> puzzleTiles;

	CreatePuzzle* createPuzzle = new CreatePuzzle;								////// NEW KEYWORD
};
