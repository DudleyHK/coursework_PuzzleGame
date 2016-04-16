/*


*/
#include "Settings.h"

class MainMenu;


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
	addOptions();
	//addSliders();

	return true;
}


int const Settings::getHeightSeg()
{
	return heightSegments;
}

int const Settings::getWidthSeg()
{
	return widthSegments;
}


void Settings::backgroundAndTile()
{
	// Print out the title
	cocos2d::Label* title = cocos2d::Label::createWithTTF("Settings", "fonts/FunSized.ttf", 40);
	title->setPosition(cocos2d::Vec2(320, 400));
	this->addChild(title, -50);

	// This is the chance to print the background for the scene
}


void Settings::addOptions()
{
	// four buttons // 
	// back button
	// 3x sizes; 3x3, 5x5 and 6x7

	// Return to menu
	cocos2d::MenuItemSprite* returnButton = new cocos2d::MenuItemSprite();
	returnButton->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(Settings::returnCallback, this));





	// Create the actual menu and assign the menu to the Puzzle game scene
	cocos2d::Menu* settingsMenu = cocos2d::Menu::create(
		smallGrid,
		mediumGrid,
		largeGrid,
		returnButton,
		nullptr);
	settingsMenu->alignItemsVertically();
	this->addChild(settingsMenu, 10);

}


void Settings::returnCallback(cocos2d::Ref* sender)
{
	//cocos2d::Director::getInstance()->add
}


void Settings::setupSmallGrid(cocos2d::Ref* sender)
{
	heightSegments = 3;
	widthSegments = 3;
}

void Settings::setupMediumGrid(cocos2d::Ref* sender) 
{
	heightSegments = 4;
	widthSegments = 4;
}

void Settings::setupLargeGrid(cocos2d::Ref* sender)
{
	heightSegments = 5;
	widthSegments = 6;
}

/*
void Settings::addSliders()
{
	auto heightSlider = cocos2d::ui::Slider::create();
	heightSlider->loadBarTexture("Slider_Back.png");
	heightSlider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable");
	heightSlider->loadProgressBarTexture("Slider_PressBar.png");

	heightSlider->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType click)
	{
		switch (click)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			cocos2d::log("SliderMoved");
			break;
		default:
			break;
		}
	});

	this->addChild(heightSlider, 10);


	/*auto slider = Slider::create();
	slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
	slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider->loadProgressBarTexture("Slider_PressBar.png");

	slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
	break;
	case ui::Widget::TouchEventType::ENDED:
	std::cout << "slider moved" << std::endl;
	break;
	default:
	break;
	}
	});

	this->addChild(slider);/
}

*/

