/*

*/
#pragma once
#include "GameScene.h"

class MainMenu : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	MainMenu();
	~MainMenu();

	virtual bool initLayer();
	void backgroundAndTitle();
	void menuButtons();

	void menuStartGame(cocos2d::Ref* sender);
	void menuCloseCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(MainMenu);


private:

};