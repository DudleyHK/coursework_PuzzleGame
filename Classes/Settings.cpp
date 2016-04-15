/*


*/
#include "Settings.h"


/*Simply create a new scene and adds our newly created layer to it.
Cocos manages the allocated memory here*/
cocos2d::Scene* Settings::createScene()
{
	cocos2d::Scene* settingsScene = cocos2d::Scene::create();
	auto settingsLayer = Settings::create();


	// add layer as a child to a scene
	settingsScene->addChild(settingsLayer, -150);
	settingsLayer->initLayer();

	// return the scene
	return settingsScene;
}


Settings::Settings()
{
	; // Empty
}


Settings::~Settings()
{
	; // Empty
}



bool Settings::initLayer()
{
	// if the layer has not been initialised 
	if (!Layer::init())
	{
		return false;
	}

	backgroundAndTile();

	return true;
}

void Settings::backgroundAndTile()
{
	// Print out the title
	cocos2d::Label* title = cocos2d::Label::createWithTTF("Settings", "fonts/FunSized.ttf", 40);
	title->setPosition(cocos2d::Vec2(320, 400));
	this->addChild(title, -50);

	// This is the chance to print the background for the scene
}

