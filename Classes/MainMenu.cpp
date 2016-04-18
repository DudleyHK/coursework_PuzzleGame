/*
	Solution: MainMenu.cpp
	Author: Dudley Dawes
	Date: 19/04/16
*/
#include "MainMenu.h"


cocos2d::Scene* MainMenu::createScene()
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* menuScene = cocos2d::Scene::create();
	auto menuLayer = MainMenu::create();

	menuScene->addChild(menuLayer, 0);
	menuLayer->initLayer();

	return menuScene;
}

void MainMenu::setWindowSize()
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	windowSize = size;
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
	this->addChild(title, 3);

	// Add background
	auto menuBackground = cocos2d::Sprite::create("BambooBackground.JPG ");
	menuBackground->setScale(0.25);
	menuBackground->setAnchorPoint(cocos2d::Vec2(0, 0));
	menuBackground->setPosition(cocos2d::Vec2(0, 0));
	this->addChild(menuBackground, 1);
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

	cocos2d::Menu* buttonLayout = cocos2d::Menu::create(
		runGameScene,
		mainMenuExit,
		nullptr);
	buttonLayout->setPosition(windowSize.width / 5.5f, windowSize.height / 1.5f);
	buttonLayout->alignItemsVerticallyWithPadding(50.0f);
	this->addChild(buttonLayout, 4);

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


	cocos2d::Menu* gridSizeLayout = cocos2d::Menu::create(
		smallGrid,
		mediumGrid,
		largeGrid,
		nullptr);
	gridSizeLayout->setPosition(windowSize.width / 2.0f, windowSize.height / 2.5f);
	gridSizeLayout->alignItemsVerticallyWithPadding(75.0f);
	this->addChild(gridSizeLayout, 4);
}

void MainMenu::selectImg()
{
	imageLib->initLibrary();

	// image button
	cocos2d::MenuItemSprite* img00 = new cocos2d::MenuItemSprite();
	img00->initWithNormalSprite(
		cocos2d::Sprite::create("p_hamsterRunning.jpg"),
		cocos2d::Sprite::create("p_hamsterRunningSelect.jpg"),
		nullptr,
		CC_CALLBACK_1(MainMenu::selectImg00, this));

	// image button
	cocos2d::MenuItemSprite* img01 = new cocos2d::MenuItemSprite();
	img01->initWithNormalSprite(
		cocos2d::Sprite::create("p_mountains.jpg"),
		cocos2d::Sprite::create("p_mountainsSelect.jpg"),
		nullptr,
		CC_CALLBACK_1(MainMenu::selectImg01, this));

	// Place in Scene
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
	this->addChild(imageSelection, 4);
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