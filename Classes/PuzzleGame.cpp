/*


http://www.cocos2d-x.org/wiki/Coordinate_System

https://blackboard.uwe.ac.uk/bbcswebdav/pid-4625508-dt-content-rid-8627132_2/courses/UFCFWA-30-1_15sep_1/Worksheet%2012.pdf // Work sheet 12
*/
#include "PuzzleGame.h"


/*Simply create a new scene and adds our newly created layer to it.
Cocos manages the allocated memory here*/
cocos2d::Scene * PuzzleGame::createScene()
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* menuScene = Scene::create();
	auto menuLayer = PuzzleGame::create();

	// add layer as a child to a scene
	menuScene->addChild(menuLayer);
	menuLayer->initLayer();

	// return the scene
	return menuScene;
}

PuzzleGame::PuzzleGame()
{
	; // EMpty
}

PuzzleGame::~PuzzleGame()
{
	; // Empty
}



bool PuzzleGame::initLayer()
{
	// if the layer has not been initialised 
	if (!Layer::init())
	{
		return false;
	}

	initMenu();

	return true;
}



void PuzzleGame::initMenu()
{
	backgroundAndTitle();
	menuButtons();
}


void PuzzleGame::backgroundAndTitle()
{
	// Print out the title
	cocos2d::Label* title = Label::createWithTTF("Puzzle Game", "fonts/FunSized.ttf", 40);
	title->setPosition(Vec2(320, 400));
	this->addChild(title, 1);


	// Add in a menu splash screen
	auto menuBackground = Sprite::create("WoodFence.png");
	menuBackground->setScale(1.5);
	menuBackground->setAnchorPoint(Vec2(0, 0));
	menuBackground->setPosition(Vec2(0, 0));
	this->addChild(menuBackground, -50);
}



void PuzzleGame::menuButtons()
{
	// Create the play game menu item
	MenuItemSprite* runGameScene = new MenuItemSprite();
	runGameScene->initWithNormalSprite(
		Sprite::create("PlayUnselected.png"),
		Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(PuzzleGame::menuStartGame, this));


	// Create the exit game menu item, this will exit the app
	MenuItemSprite* mainMenuExit = new MenuItemSprite();
	mainMenuExit->initWithNormalSprite(
		Sprite::create("ExitNormal.png"),
		Sprite::create("ExitSelected.png"),
		nullptr,
		CC_CALLBACK_1(PuzzleGame::menuCloseCallback, this));


	// Create the actual menu and assign the menu to the Puzzle game scene
	cocos2d::Menu* menu = Menu::create(runGameScene, mainMenuExit, nullptr);
	menu->alignItemsVertically();
	this->addChild(menu, -10);
}


void PuzzleGame::menuStartGame(cocos2d::Ref* sender)
{
	// change the type of transition between the scenes
	cocos2d::Director::getInstance()->replaceScene(
		TransitionSlideInR::create(2, GameScene::createScene()));
}


/*This function will ask the director to correctly end the application 
if the window is closed*/
void PuzzleGame::menuCloseCallback(cocos2d::Ref* pSender)
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

