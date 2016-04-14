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
	settingsScene->addChild(settingsLayer, -50);
	settingsLayer->initLayer();

	// return the scene
	return settingsScene;
}


Settings::Settings()
{
	; // EMpty
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


	return true;
}

