/*





*/
#pragma once
#include "cocos2d.h"
#include "GameScene.h"


class GameEventListener : public GameScene
{
public:
	GameEventListener() = default;
	~GameEventListener() = default;

	void setTileInfo(cocos2d::Sprite* puzzleTile);
	void addEvents();

	void onMouseDown(cocos2d::EventMouse * mouse);
	void onMouseRelease(cocos2d::EventMouse * mouse);

private:
	cocos2d::Sprite* tile;
};
