/*

*/
#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;

class PlayEnvironment : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();

	PlayEnvironment();
	~PlayEnvironment();

	virtual bool initLayer();
	void initMenu();
	void menuButtons();
	void backgroundAndTitle();

	void menuStartGame(cocos2d::Ref* sender);
	void menuCloseCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(PlayEnvironment);


private:

};