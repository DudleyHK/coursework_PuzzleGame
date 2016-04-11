/*


*/
# include "Settings.h"



Settings::Settings()
{
	; // Empty
}

Settings::~Settings()
{
	; // Settings
}

cocos2d::Scene * Settings::createScene()
{
	cocos2d::Scene* settingsScene= cocos2d::Scene::create();
	auto settingsLayer = Settings::create();

	// add layer as a child to a scene
	settingsScene->addChild(settingsLayer);
	//settingsLayer->initLayer();

	// return the scene
	return settingsScene;
}

bool Settings::initLayer()
{
	if (!Layer::init())
	{
		return false;
	}



	return true;
}