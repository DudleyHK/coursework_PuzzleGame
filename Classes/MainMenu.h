/*

*/
#pragma once
#include "GameScene.h"
USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();

	MainMenu();
	~MainMenu();

	virtual bool initLayer();
	void initMenu();
	void menuButtons();
	void backgroundAndTitle();

	void menuStartGame(cocos2d::Ref* sender);
	void menuCloseCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(MainMenu);


private:

};