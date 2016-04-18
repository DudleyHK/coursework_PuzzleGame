/*
// updatefunction actions
http://www.gamefromscratch.com/post/2014/10/11/Cocos2d-x-Tutorial-Series-Game-loops-Updates-and-Action-Handling.aspx
*/
#include "MainMenu.h"


/*Simply create a new scene and adds our newly created layer to it.
Cocos manages the allocated memory here*/
cocos2d::Scene* MainMenu::createScene()
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* menuScene = cocos2d::Scene::create();
	auto menuLayer = MainMenu::create();


	// add layer as a child to a scene
	menuScene->addChild(menuLayer, -150);
	menuLayer->initLayer();

	// return the scene
	return menuScene;
}

void MainMenu::setWindowSize()
{
	// get width and height of the window
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	windowSize = size;
}


MainMenu::MainMenu()
{
	; // EMpty
}


MainMenu::~MainMenu()
{
	; // Empty
}

bool MainMenu::initLayer()
{
	// if the layer has not been initialised 
	if (!Layer::init())
	{
		return false;
	}

	setWindowSize();
	backgroundAndTitle();
	playAndQuit();
	selectImg();

	return true;
}

void MainMenu::backgroundAndTitle()
{
	// Print out the title
	cocos2d::Label* title = cocos2d::Label::createWithTTF(
		"Puzzle Game", 
		"fonts/FunSized.ttf", 60.0f);
	title->setPosition(cocos2d::Vec2(windowSize.width / 2.0f, windowSize.height / 1.1f));
	this->addChild(title, -50);

	// Add in a menu splash screen
	auto menuBackground = cocos2d::Sprite::create("BambooBackground.JPG ");
	menuBackground->setScale(0.25);
	menuBackground->setAnchorPoint(cocos2d::Vec2(0, 0));
	menuBackground->setPosition(cocos2d::Vec2(0, 0));
	this->addChild(menuBackground, -100);
}


void MainMenu::playAndQuit()
{
	// Create the play game menu item
	cocos2d::MenuItemSprite* runGameScene = new cocos2d::MenuItemSprite();
	runGameScene->initWithNormalSprite(
		cocos2d::Sprite::create("PlayNormal.jpg"),
		cocos2d::Sprite::create("PlaySelected.jpg"),
		nullptr,
		CC_CALLBACK_1(MainMenu::menuPlayCallback, this));


	// Create the exit game menu item, this will exit the app
	cocos2d::MenuItemSprite* mainMenuExit = new cocos2d::MenuItemSprite();
	mainMenuExit->initWithNormalSprite(
		cocos2d::Sprite::create("ExitNormal.png"),
		cocos2d::Sprite::create("ExitSelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	// Create the actual menu and assign the menu to the Puzzle game scene
	cocos2d::Menu* buttonLayout = cocos2d::Menu::create(
		runGameScene,
		mainMenuExit,
		nullptr);
	buttonLayout->setPosition(windowSize.width / 5.5f, windowSize.height / 1.5f);
	buttonLayout->alignItemsVerticallyWithPadding(50.0f);
	this->addChild(buttonLayout, 10);

	// add other buttons
	selectGridSize();
}

void MainMenu::selectGridSize()
{
	cocos2d::MenuItemSprite* smallGrid = new cocos2d::MenuItemSprite();
	smallGrid->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::setupSmallGrid, this));

	cocos2d::MenuItemSprite* mediumGrid = new cocos2d::MenuItemSprite();
	mediumGrid->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::setupMediumGrid, this));

	cocos2d::MenuItemSprite* largeGrid = new cocos2d::MenuItemSprite();
	largeGrid->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(MainMenu::setupLargeGrid, this));

	// Create the actual menu and assign the menu to the Puzzle game scene
	cocos2d::Menu* gridSizeLayout = cocos2d::Menu::create(
		smallGrid,
		mediumGrid,
		largeGrid,
		nullptr);
	gridSizeLayout->setPosition(windowSize.width / 2.0f, windowSize.height / 2.5f);
	gridSizeLayout->alignItemsVerticallyWithPadding(75.0f);
	this->addChild(gridSizeLayout, 10);
}

void MainMenu::selectImg()
{
	imageLib->initLibrary();

	cocos2d::MenuItemSprite* img00 = new cocos2d::MenuItemSprite();
	img00->initWithNormalSprite(
		cocos2d::Sprite::create("p_hamsterRunning.jpg"),
		cocos2d::Sprite::create("p_hamsterRunningSelect.jpg"),
		nullptr,
		CC_CALLBACK_1(MainMenu::selectImg00, this));

	cocos2d::MenuItemSprite* img01 = new cocos2d::MenuItemSprite();
	img01->initWithNormalSprite(
		cocos2d::Sprite::create("p_mountains.jpg"),
		cocos2d::Sprite::create("p_mountainsSelect.jpg"),
		nullptr,
		CC_CALLBACK_1(MainMenu::selectImg01, this));

	// Create the actual menu and assign the menu to the Puzzle game scene
	cocos2d::Menu* imageSelection = cocos2d::Menu::create(img00, img01, nullptr);
	img00->setScaleX((500.0f / imageLib->getPuzzleImg(0)->
		getBoundingBox().size.width) * 0.5);
	img00->setScaleY((500.0f / imageLib->getPuzzleImg(0)->
		getBoundingBox().size.height) * 0.5);
	img01->setScaleX((500.0f / imageLib->getPuzzleImg(1)->
		getBoundingBox().size.width) * 0.5);
	img01->setScaleY((500.0f / imageLib->getPuzzleImg(1)->
		getBoundingBox().size.height) * 0.5);

	imageSelection->setPosition(windowSize.width / 1.15f, windowSize.height / 2.25f);
	imageSelection->alignItemsVerticallyWithPadding(50.0f);
	this->addChild(imageSelection, 10);
}


void MainMenu::menuPlayCallback(cocos2d::Ref* sender)
{
	cocos2d::Director::getInstance()->replaceScene(
		cocos2d::TransitionSlideInR::create(1,
			GameScene::createScene(
				heightSegments,
				widthSegments, 
				imageCode, 
				imageLib)));
}

void MainMenu::menuCloseCallback(cocos2d::Ref* pSender)
{
	cocos2d::Director::getInstance()->end();
}

void MainMenu::setupSmallGrid(cocos2d::Ref* sender)
{
	heightSegments = 3;
	widthSegments = 3;
}

void MainMenu::setupMediumGrid(cocos2d::Ref* sender)
{
	heightSegments = 4;
	widthSegments = 4;
}

void MainMenu::setupLargeGrid(cocos2d::Ref* sender)
{
	heightSegments = 5;
	widthSegments = 5;
}

void MainMenu::selectImg00(cocos2d::Ref* sender)
{
	imageCode = 0;
}

void MainMenu::selectImg01(cocos2d::Ref* sender)
{
	imageCode = 1;
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

