/*



https://blackboard.uwe.ac.uk/bbcswebdav/pid-4634231-dt-content-rid-8695402_2/courses/UFCFWA-30-1_15sep_1/Worksheet%2013%283%29.pdf

Sprite Guide
http://cocos2d-x.org/documentation/programmers-guide/3/index.html
*/

#include "GameScene.h"

cocos2d::Scene * GameScene::createScene()
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* playScene = cocos2d::Scene::create();
	auto playLayer = GameScene::create();

	// add layer as a child to a scene
playScene->addChild(playLayer);
playLayer->initLayer();

// return the scene
return playScene;
}


/* CREATE_FUNC(GameScene) --- create scene with parameters
GameScene* GameScene::create(int hi)
{
	GameScene *pRet = new(std::nothrow) GameScene();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
*/

GameScene::GameScene()
{
	; // Empty
}

GameScene::~GameScene()
{
	; // Empty
}

bool GameScene::initLayer()
{
	if (!Layer::init())
	{
		return false;
	}

	//initBackground();

	addPuzzleBoard();
	//shuffleTiles();
	addEvent();

	return true;
}

void GameScene::addPuzzleBoard()
{
	puzzleBoard->init();
	puzzleBoard->getSpriteList(&tileList);

	// Display puzzle.
	for (unsigned int index = 0; index < tileList.size(); index++)
	{
		// display
		this->addChild(tileList.at(index));
	}
}

void GameScene::addEvent()
{
	// create a mouse listener and hook into our event callback function
	auto clickListener = cocos2d::EventListenerTouchOneByOne::create();

	clickListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	//clickListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMove, this);

	// register event listener to receive events. addEventListener... basically means we want this event to be updated as much as possible
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);



	//cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(clickListener, -1);
}

bool GameScene::onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event)
{
	// Get info on where the screen has been clicked
	cocos2d::Point point = click->getLocationInView();

	// convert these coordinates into world coordinates
	point = cocos2d::Director::getInstance()->convertToGL(point);

	// run through the tile list
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			//if any sprite contains the point coordinates.
			if (tileList.at((4 * heightIndex) + widthIndex)->
				getBoundingBox().containsPoint(point))
			{
				checkForEmpty((4 * heightIndex) + widthIndex); 

				return true;
			}
		}
	}
}

void GameScene::checkForEmpty(int tileID) // this is currently the same as posID
{
	int n_posID = -1;
	int posID = tileList.at(tileID)->getPositionID();

	//save for variable as global varibale   //this may not ned to be done /////////////////////CHHHECK
	hIndex = posID / 4;
	wIndex = posID - (4 * hIndex);

	checkLeft(posID - 1, &n_posID);
	if (n_posID == -1)
	{
		checkRight(posID + 1, &n_posID);
		if (n_posID == -1)
		{
			checkUp(posID + 4 /* 4 = number of seg width*/, &n_posID);
			if (n_posID == -1)
			{
				checkDown(posID - 4 /* 4 = number of seg width*/, &n_posID);
				if (n_posID == -1)
				{
					; // empty tile not found, player cannot move this tile
				}
			}
		}
	}
	if (n_posID != -1)
	{
		swapTiles(tileID, 3);
	}
}

void GameScene::checkLeft(int _posID, int* n_posID)
{
	*n_posID = _posID;

	// check 
	// if either of these functions return false
	if (!(checkInBounds(hIndex, (wIndex - 1)) && getEmptyTilePos(*n_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

void GameScene::checkRight(int _posID, int* n_posID)
{
	*n_posID = _posID;

	// if either of these functions return false
	if (!(checkInBounds(hIndex, (wIndex + 1)) && getEmptyTilePos(_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

void GameScene::checkUp(int _posID, int* n_posID)
{
	*n_posID = _posID;

	// if either of these functions return false
	if (!(checkInBounds((hIndex + 1), wIndex) && getEmptyTilePos(_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

void GameScene::checkDown(int _posID, int* n_posID)
{
	*n_posID = _posID;

	// if either of these functions return false
	if (!(checkInBounds((hIndex - 1), wIndex) && getEmptyTilePos(_posID)))
	{
		// set newPos to an unused value
		*n_posID = -1;
	}
}

bool GameScene::getEmptyTilePos(int n_posID)
{
	if (n_posID == tileList.at(3)->getPositionID())
	{
		return true;
	}
	return false;
}

bool GameScene::checkInBounds(int _hIndex, int _wIndex)
{
	
	if ((_hIndex < 4 && _hIndex >= 0) &&
		(_wIndex < 4 && _wIndex >= 0))
	{
		return true;
	}
	return false;
}

void GameScene::swapTiles(int tileID, int emptyID)
{
	//selected sprite
	auto selectedSprite = tileList.at(tileID);
	cocos2d::Vec2 selectedSpritePosition = tileList.at(tileID)->getPosition();

	// empty sprite
	auto emptySprite = tileList.at(emptyID);
	cocos2d::Vec2 emptySpritePosition = tileList.at(emptyID)->getPosition();

	auto moveEmptySprite = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(selectedSpritePosition.x, selectedSpritePosition.y));
	auto moveSelectedSprite = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(emptySpritePosition.x, emptySpritePosition.y));

	// are any actions running?
	int spriteActionsRunning = selectedSprite->getNumberOfRunningActions();
	int emptyActionsRunning = emptySprite->getNumberOfRunningActions();

	if (spriteActionsRunning == 0 && emptyActionsRunning == 0)
	{
		int temp = tileList.at(tileID)->getPositionID();

		selectedSprite->runAction(moveSelectedSprite);
		emptySprite->runAction(moveEmptySprite);

		// set the position value as new positions
		tileList.at(tileID)->setPositionID(tileList.at(emptyID)->getPositionID());

		// set the tile positions as new positions
		tileList.at(emptyID)->setPositionID(temp);
	}
}