/*
// @ -- Detail:
// @ -- Param:
// @ -- Return:
*/
#pragma once
#include "ui\UISlider.h"
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

	int const getHeightSeg();
	int const getWidthSeg();

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Main Menu.
	// @ -- Return: If the layer has been initialised return TRUE.
	virtual bool initLayer();

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void backgroundAndTile();


	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void addSliders();

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void setSize();

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void addOptions();

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void returnCallback(cocos2d::Ref* sender);
	void setupSmallGrid(cocos2d::Ref* sender);
	void setupMediumGrid(cocos2d::Ref* sender);
	void setupLargeGrid(cocos2d::Ref* sender);


private:
	// Game starts with these values set as a defualt game 4x4
	int heightSegments = 0;
	int widthSegments = 0;
};