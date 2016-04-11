/*
	Solution: Main Menu Class
	Author: Dudley Dawes
*/
#include "MainMenu.h"

cocos2d::Scene * MainMenu::createScene()
{
	cocos2d::Scene* menuScene = cocos2d::Scene::create();
	auto menuLayer = MainMenu::create();

	menuScene->addChild(menuLayer);
	menuLayer->initLayer();

	return menuScene;
}

MainMenu::MainMenu()
{
	; // Empty
}

MainMenu::~MainMenu()
{
	; // Empty
}

bool MainMenu::initLayer()
{
	if (!Layer::init())
	{
		return false;
	}

	backgroundAndTitle();
	menuButtons();
	return true;
}

void MainMenu::backgroundAndTitle()
{
	// Print out the title
	cocos2d::Label* title = cocos2d::Label::createWithTTF("Puzzle Game", "fonts/FunSized.ttf", 40);
	title->setPosition(cocos2d::Vec2(320, 400));
	this->addChild(title, 1);

	// Add in a menu splash screen
	auto menuBackground = cocos2d::Sprite::create("WoodFence.png");
	menuBackground->setScale(1.5);
	menuBackground->setAnchorPoint(cocos2d::Vec2(0, 0));
	menuBackground->setPosition(cocos2d::Vec2(0, 0));
	this->addChild(menuBackground, -50);
}

void MainMenu::menuButtons()
{
	// Play Button
	cocos2d::MenuItemSprite* playButton = new cocos2d::MenuItemSprite();
	playButton->initWithNormalSprite(
		cocos2d::Sprite::create("PlayNormal.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::menuPlayGame, this));

	// Settings Button
	cocos2d::MenuItemSprite* settingsButton = new cocos2d::MenuItemSprite();
	settingsButton->initWithNormalSprite(
		cocos2d::Sprite::create("SettingsNormal.png"),
		cocos2d::Sprite::create("SettingsSelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::menuSettingMenu, this));

	// Exit Button
	cocos2d::MenuItemSprite* exitButton = new cocos2d::MenuItemSprite();
	exitButton->initWithNormalSprite(
		cocos2d::Sprite::create("ExitNormal.png"),
		cocos2d::Sprite::create("ExitSelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::menuEndGame, this));

	// Initialise the layer.
	cocos2d::Menu* menu = cocos2d::Menu::create(playButton, exitButton,
		settingsButton, nullptr);
	menu->alignItemsVertically();
	this->addChild(menu, -10);
}

void MainMenu::menuPlayGame(cocos2d::Ref* sender)
{
	// change the type of transition between the scenes
	cocos2d::Director::getInstance()->replaceScene(
		cocos2d::TransitionSlideInR::create(2, GameScene::createScene()));
}

void MainMenu::menuSettingMenu(cocos2d::Ref* sender)
{
	cocos2d::Director::getInstance()->replaceScene(
		cocos2d::TransitionSlideInR::create(2, Settings::createScene()));
}

void MainMenu::menuEndGame(cocos2d::Ref* pSender)
{
	cocos2d::Director::getInstance()->end();
}




/*

//Creating new scene
cocos2d::Scene * HelloWorld::createScene()
{
// 'scene' & 'layer' are autoreleased objects
cocos2d::Scene *scene = Scene::create();
auto layer = HelloWorld::create();

//add layer as a child to scenee
scene->addChild(layer);

//cocos2d::Menu* menu = Menu::create(mainMenuStartGame, mainMenuExit, nullptr);

layer->initMenu();


//return the scene
return scene;
}


/**** Work Sheet 12
bool HelloWorld::init()
{
// If the layer has NOT been initialised
if (!Layer::init())
{
return false;
}

// get width and height of the window
cocos2d::Size size = Director::getInstance()->getVisibleSize();
size.width;
size.height;

// create label, set position and add to layer
cocos2d::Label *label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
label->setPosition(Vec2(320, 400));
this->addChild(label, 0);

// Add Hello World splash screen
auto helloWorldSprite = Sprite::create("HelloWorld.png");
helloWorldSprite->setPosition(Vec2(320, 240));
this->addChild(helloWorldSprite, 1);


// add in the character sprite
auto characterSprite = Sprite::create("CharacterSprite.png");
characterSprite->setPosition(Vec2(100, 100));
this->addChild(characterSprite, 100);



return true;
}



// Work sheet 13
void HelloWorld::initMenu()
{
// create the first menu item, this will exit the app.
MenuItemSprite* mainMenuExit = new MenuItemSprite();
mainMenuExit->initWithNormalSprite(
Sprite::create("CloseNormal.png"),
Sprite::create("CloseSelected.png"),
nullptr,
CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));


// THIS IS NOT NEEDED AT THE MO
// create label, set position and add to layer
cocos2d::Label *label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
label->setPosition(Vec2(320, 400));
this->addChild(label, 0);


// create a meun item based on a string, it will launch the game scene
MenuItemFont* mainMenuStartGame = MenuItemFont::create(
"Play Game",
CC_CALLBACK_1(HelloWorld::mainMenuStartGame, this));


// create the actual menu and assign the menu to the world scene
//cocos2d::Menu* menu = Menu::createWithItem(mainMenuExit);    // ORIGINAL
cocos2d::Menu* menu = Menu::create(mainMenuStartGame, mainMenuExit, nullptr);
menu->alignItemsVertically();
this->addChild(menu, 1);
}


void HelloWorld::mainMenuStartGame(cocos2d::Ref* sender)
{
// optional - change the type of transition
Director::getInstance()->replaceScene(
TransitionFlipY::create(2, MyGameScene::createScene()));
}



void HelloWorld::menuCloseCallback(cocos2d::Ref * pSender)
{
;
}


void HelloWorld::mainMenuExit()
{
; // no nothing
}

*/

