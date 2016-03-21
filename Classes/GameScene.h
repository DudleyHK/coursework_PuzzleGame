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

	// @param pass via reference as vectors take up huge amaount of memory.
	// @param if you don't want to modify the Vector add the "const" modifier
	//void displayPuzzle(Vector<Sprite*>&);


	void sliceImage();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
//	float widthPosition = 0, heightPosition = 0;
	

};
