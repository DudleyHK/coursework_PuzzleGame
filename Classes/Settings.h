/*
// @ -- Detail:
// @ -- Param:
// @ -- Return:
*/
#pragma once
#include "cocos2d.h"

class Settings : public cocos2d::Layer
{
public:
	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene();

	CREATE_FUNC(Settings);

	Settings();
	~Settings();

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Main Menu.
	// @ -- Return: If the layer has been initialised return TRUE.
	virtual bool initLayer();

	void backgroundAndTile();

	void backButton() const;

	// height slider
	// width slider.
	void setSize();


private:
	int heightSegments = 0;
	int widthSegments = 0;
};