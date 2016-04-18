/*
	Solution: GameScene.cpp
	Author: Dudley Dawes
	Date: 19/04/16
*/

#include "GameScene.h"

cocos2d::Scene * GameScene::createScene(
	int heightSegs, 
	int widthSegs, 
	int imageCode, 
	ImageLib* imgLib)
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* playScene = cocos2d::Scene::create();
	auto playLayer = GameScene::create();

	// add layer as a child to a scene
	playScene->addChild(playLayer, 0);
	playLayer->initLayer(heightSegs, widthSegs, imageCode, imgLib);

	return playScene;
}

GameScene::GameScene()
{
	gameWon = false;
	reshuffCounter = 0;
}

GameScene::~GameScene()
{
	;// empty
}

void GameScene::setGridSize(int heightSegs, int widthSegs)
{
	this->heightSegments = heightSegs;
	this->widthSegments = widthSegs;
	empTileID = widthSegments - 1;

	puzzleBoard->setGridSize(heightSegments, widthSegments);
}

void GameScene::setWindowSize()
{
	cocos2d::Size size = cocos2d::Director::getInstance()->getVisibleSize();
	windowSize = size;
}

void GameScene::setPuzzleImage(int imgCode, ImageLib* imgLib)
{
	this->imageCode = imgCode;
	this->imageLib = imgLib;
	puzzleBoard->setPuzzleImage(imgCode, imgLib);
}

bool GameScene::initLayer(
	int heightSegs, 
	int widthSegs, 
	int imageCode, 
	ImageLib* imgLib)
{
	if (!Layer::init())
	{
		return false;
	}

	setWindowSize();
	setGridSize(heightSegs, widthSegs);
	setPuzzleImage(imageCode, imgLib);

	backgroundAndTile();
	menuOptions();

	addPuzzleBoard();
	addEvent();

	return true;
}

void GameScene::addPuzzleBoard()
{
	puzzleBoard->createImage();
	puzzleBoard->getSpriteList(&tileList);
	puzzleBoard->getDirection();

	// Display puzzle.
	for (unsigned int index = 0; index < tileList.size(); index++)
	{
		this->addChild(tileList.at(index), 2);
	}
}

void GameScene::backgroundAndTile()
{
	// Print out the title
	cocos2d::Label* title = cocos2d::Label::createWithTTF(
		"Puzzle Game",
		"fonts/FunSized.ttf", 60.0f);
	title->setPosition(cocos2d::Vec2(windowSize.width / 2.0f, windowSize.height / 1.1f));
	this->addChild(title, 3);

	// Add bakground
	auto menuBackground = cocos2d::Sprite::create("BambooBackground.JPG ");
	menuBackground->setScale(0.25);
	menuBackground->setAnchorPoint(cocos2d::Vec2(0, 0));
	menuBackground->setPosition(cocos2d::Vec2(0, 0));
	this->addChild(menuBackground, 1);
}

void GameScene::menuOptions()
{
	// restart the game
	cocos2d::MenuItemSprite* resetBoard = new cocos2d::MenuItemSprite();
	resetBoard->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(GameScene::resetCallback, this));

	// exit back to the main menu
	cocos2d::MenuItemSprite* returnToMenu = new cocos2d::MenuItemSprite();
	returnToMenu->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(GameScene::returnCallback, this));

	// reshuffle
	cocos2d::MenuItemSprite* reshuffle = new cocos2d::MenuItemSprite();
	reshuffle->initWithNormalSprite(
		cocos2d::Sprite::create("PlayUnselected.png"),
		cocos2d::Sprite::create("PlaySelected.png"),
		nullptr,
		CC_CALLBACK_1(GameScene::reshuffleCallback, this));

	// Layout
	cocos2d::Menu* options = cocos2d::Menu::create(resetBoard, returnToMenu, nullptr);
	options->setPosition(windowSize.width / 1.15f, windowSize.height / 1.5f);
	options->alignItemsVerticallyWithPadding(50.0f);
	this->addChild(options, 4);

	cocos2d::Menu* reshuffleButton = cocos2d::Menu::create(reshuffle, nullptr);
	reshuffleButton->setPosition(windowSize.width / 1.15f, windowSize.height / 5.0f);
	reshuffleButton->alignItemsVertically();
	this->addChild(reshuffleButton, 4);
}

void GameScene::resetCallback(cocos2d::Ref * sender)
{
	cocos2d::Director::getInstance()->replaceScene(
		cocos2d::TransitionSlideInR::create(1,
			GameScene::createScene(
				heightSegments,
				widthSegments,
				imageCode,
				imageLib)));
}

void GameScene::returnCallback(cocos2d::Ref * sender)
{
	cocos2d::Director::getInstance()->replaceScene(
		cocos2d::TransitionSlideInL::create(1, MainMenu::createScene()));
}

void GameScene::reshuffleCallback(cocos2d::Ref * sender)
{
	if ((!gameWon) && (reshuffCounter < 5))
	{
		puzzleBoard->getDirection();
		reshuffCounter++;
	}
}

void GameScene::addEvent()
{
	// create a mouse listener and hook into our event callback function
	auto clickListener = cocos2d::EventListenerTouchOneByOne::create();

	clickListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);

	// register event listener to receive events. 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);
}

bool GameScene::onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event)
{
	// Get info on where the screen has been clicked
	cocos2d::Point point = click->getLocationInView();

	// convert these coordinates into world coordinates
	point = cocos2d::Director::getInstance()->convertToGL(point);

	for (unsigned int heightIndex = 0; heightIndex < (unsigned int)heightSegments; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < (unsigned int)widthSegments; widthIndex++)
		{
			//if any sprite contains the point coordinates.
			if (tileList.at((widthSegments * heightIndex) + widthIndex)->
				getBoundingBox().containsPoint(point))
			{
				checkForEmpty((widthSegments * heightIndex) + widthIndex);

				return true;
			}
		}
	}
	return false;
}

void GameScene::checkForEmpty(int tileID)
{
	int n_posID = -1;
	int posID = tileList.at(tileID)->getPositionID();
	
	hIndex = posID / widthSegments;
	wIndex = posID - (widthSegments * hIndex);

	checkLeft(posID - 1, &n_posID);
	if (n_posID == -1)
	{
		checkRight(posID + 1, &n_posID);
		if (n_posID == -1)
		{
			checkUp(posID + widthSegments, &n_posID);
			if (n_posID == -1)
			{
				checkDown(posID - widthSegments, &n_posID);
				if (n_posID == -1)
				{
					; // empty tile not found, player cannot move this tile
				}
			}
		}
	}
	if (n_posID != -1)
	{
		swapTiles(tileID);
	}
}

void GameScene::checkLeft(int _posID, int* const  n_posID)
{
	*n_posID = _posID;

	if (!(puzzleBoard->checkInBounds(hIndex, (wIndex - 1)) && getEmptyTilePos(*n_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

void GameScene::checkRight(int _posID, int* const n_posID)
{
	*n_posID = _posID;

	if (!(puzzleBoard->checkInBounds(hIndex, (wIndex + 1)) && getEmptyTilePos(_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

void GameScene::checkUp(int _posID, int* const n_posID)
{
	*n_posID = _posID;

	if (!(puzzleBoard->checkInBounds((hIndex + 1), wIndex) && getEmptyTilePos(_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

void GameScene::checkDown(int _posID, int* const n_posID)
{
	*n_posID = _posID;

	if (!(puzzleBoard->checkInBounds((hIndex - 1), wIndex) && getEmptyTilePos(_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

bool GameScene::getEmptyTilePos(int _posID)
{
	if (_posID == tileList.at(empTileID)->getPositionID())
	{
		return true;
	}
	return false;
}

void GameScene::swapTiles(int tileID)
{
	if (!gameWon)
	{
		auto selectedSprite = tileList.at(tileID);
		cocos2d::Vec2 selectedSpritePosition = tileList.at(tileID)->getPosition();

		auto emptySprite = tileList.at(empTileID);
		cocos2d::Vec2 emptySpritePosition = tileList.at(empTileID)->getPosition();

		auto moveEmptySprite = cocos2d::MoveTo::create(0.1f, cocos2d::Vec2(
			selectedSpritePosition.x,
			selectedSpritePosition.y));
		auto moveSelectedSprite = cocos2d::MoveTo::create(0.1f, cocos2d::Vec2(
			emptySpritePosition.x,
			emptySpritePosition.y));

		if (selectedSprite->getNumberOfRunningActions() == 0 &&
			emptySprite->getNumberOfRunningActions() == 0)
		{
			int temp = tileList.at(tileID)->getPositionID();

			selectedSprite->runAction(moveSelectedSprite);
			emptySprite->runAction(moveEmptySprite);

			// set the position value as new positions
			tileList.at(tileID)->setPositionID(tileList.at(empTileID)->getPositionID());

			// set the tile positions as new positions
			tileList.at(empTileID)->setPositionID(temp);
		}
	}

	numOfMoves++;

	// check to see if the board is complete at this point
	if (boardComplete())
	{
		gameWon = true;

		// Print message
		cocos2d::Label* congrats = cocos2d::Label::createWithTTF(
			"CONGRATULATIONS!",
			"fonts/FunSized.ttf", 40.0f);
		congrats->setPosition(cocos2d::Vec2(windowSize.width / 2.0f, windowSize.height / 2.0f));
		this->addChild(congrats, 3);

		cocos2d::Label* win = cocos2d::Label::createWithTTF(
			"YOU WIN!!",
			"fonts/FunSized.ttf", 40.0f);
		win->setPosition(cocos2d::Vec2(windowSize.width / 2.0f, windowSize.height / 2.5f));
		this->addChild(win, 3);
	}
}


bool GameScene::boardComplete()
{
	int rightPlace = 0;
	puzzleBoard->getCorrectTiles(&rightPlace);

	if (rightPlace == tileList.size())
	{
		return true;
	}
	return false;
}