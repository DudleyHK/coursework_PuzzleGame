/*



*/
#pragma once
#include "cocos2d.h"
#include <vector>


class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	
	virtual bool initLayer();
	float getWindowWidth();
	float getWindowHeight();

	void initBackground();
	void displayPuzzle(Vector<Sprite*> *segList);

	void sliceImage();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	float windowWidth = 0, windowHeight = 0;
	

};
