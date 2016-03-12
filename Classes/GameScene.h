/*



*/
#pragma once
#include "cocos2d.h"


class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	
	virtual bool init();

	float getWindowWidth();
	float getWindowHeight();


	void initBackground();

	void addPuzzle();



private:
	float windowWidth = 0, windowHeight = 0;

};
