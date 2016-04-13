/*



https://blackboard.uwe.ac.uk/bbcswebdav/pid-4634231-dt-content-rid-8695402_2/courses/UFCFWA-30-1_15sep_1/Worksheet%2013%283%29.pdf

Sprite Guide
http://cocos2d-x.org/documentation/programmers-guide/3/index.html

// MAKE ANYTHING THAT ISNT GOING TO BE CHANGED A CONST VARIABLE
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
	addPuzzleBoard();
	//puzzleBoard->shuffleBoard();           ///////////////////// <<<<<<<<<< ========== CONCENTRATE ON SETTINGS MENU BEFORE SHUFFLE!!!
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

	
	//puzzleBoard->shuffleBoard();
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
		if (index == 3)
		{
			//tileList.at(index)->getSprite()->setTag(tags->SPRITE_EMPTY);
		}
		else
		{
			//auto obj = tileList.at(index);
			//tileList.at(index)->getSprite()->setTag(tags->SPRITE_TILE);
		}

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

	return false;
}


void GameScene::checkForEmpty(int tileID)
{
	int n_posID = -1;
	posID = tileList.at(tileID)->getPositionID();// Get the positionID of the tile clicked
	emptyPosID = tileList.at(3)->getPositionID();// Get the positionID of the empty Tile

	// Get the coordinates of the position clicked.
	hIndex = posID / 4;
	wIndex = posID - (4 * hIndex);

	// coordinates of the empty tile position
	int emptyHIndex = emptyPosID / 4;
	int emptyWIndex = emptyPosID - (4 * emptyHIndex);
	


	bool isNegitive = false;
	bool moveX = false;
	bool moveY = false;

	int numberOfTilesToMove = 0;

	// Check the y axis
	if (hIndex == emptyHIndex)
	{
		moveX = true;

		// if the value here is a negitive number we know the value is positive
		numberOfTilesToMove = emptyWIndex - wIndex;

		// check if negitive value
		if (numberOfTilesToMove <= 0)
		{
			// recalculate to get the number of tiles between the empty and selected tiles.  
			numberOfTilesToMove = wIndex - emptyWIndex;

			// this stays false if this is not met.
			isNegitive = true;
		}
	}


	// check the x axis
	if (wIndex == emptyWIndex)
	{
		moveY = true;

		// if the value here is a negitive number we know the value is positive. 
		numberOfTilesToMove = emptyHIndex - hIndex;

		// check if negitive value
		if (numberOfTilesToMove <= 0)
		{
			// recalculate to get the number of values between the selected tile and empty tile. 
			numberOfTilesToMove = hIndex - emptyHIndex;

			isNegitive = true;
		}
	}


	// run through a loop of all the tiles that need to move
	// number of tile between empty and selected. 
	for (int i = 1; i <= numberOfTilesToMove; i++)
	{
		// check if moveX or moveY
		if (!moveX)
		{
			// is it a negitive move
			if (isNegitive)
			{
				// move tiles function using tilerFinder function
				swapTiles(getTileID(hIndex - 1, wIndex), 3);
			}
			else if (!isNegitive)
			{
				swapTiles(getTileID(hIndex + 1, wIndex), 3);
			}
		}
		else if (moveX)
		{
			// is it a negitive move
			if (isNegitive)
			{
				swapTiles(getTileID(hIndex, wIndex - 1), 3);
			}
			else if (!isNegitive)
			{
				swapTiles(getTileID(hIndex, wIndex + 1), 3);
			}
		}
	}
}

int GameScene::getTileID(int _hIndex, int _wIndex)
{
	// run through each coordinate
	for (int h = 0; h < 4; h++)
	{
		for (int w = 0; w < 4; w++)
		{
			// save the coordinate (as it is the position in the list)
			int tileID = (4 * h) + w;

			// check if the postion in the list is the same as the position in the list i want to move to.
			if (tileList.at(tileID)->getTileID() == tileList.at((_hIndex * 4) + _wIndex)->getTileID())
			{
				return tileID;
			}
		}
	}

	return -1;
}


	/*
	checkLeft(posID - 1, &n_posID);
	if (n_posID == -1)
	{
		checkRight(posID + 1, &n_posID);
		if (n_posID == -1)
		{
			
			checkUp(posID + 4 /* 4 = number of seg width/, &n_posID);
			if (n_posID == -1)
			{
				checkDown(posID - 4 /* 4 = number of seg width &n_posID);
				if (n_posID == -1)
				{
					; // empty tile not found, player cannot move this tile
				}
			}
		}
	}
	*/
	//if (n_posID != -1)
	//{
	//	swapTiles(tileID, 3);
	//}

/*
// At this point I know that the empty tile is not next to the click tile. 
void GameScene::checkTilesBetweenY(int hIndex) // param doesnt need
{
												// TILEID AND POSITIONID ARE THE WRONG WAY ROUND HERE
	char operatorChar = '0';
	int currentTileID = 0;
	int n_posID = posID;  // this means it skips the first value
	int counter = 0;
	bool emptyFound = false;

	
	// While not at the end.
	while(!emptyFound)
	{
		// for the first iteration skip this statement
		if (counter != 0)
		{
			if (emptyPosID > posID)
			{
				n_posID++;
			}
			else
			{
				n_posID--;
			}
		}

		// increment
		counter++;

		// decode to retrieve coordinates (the tileID)
		int _hIndex = n_posID / 4;
		int _wIndex = n_posID - (4 * _hIndex);

		// get the tileID of the current positionID being assest.
		currentTileID = (4 * _hIndex) + _wIndex;

		if (currentTileID < 3)
		{
			// add this value to a list.
			posIDList.push_back(n_posID);
		}
		else
		{
			emptyFound = true;
		}
	}
}
*/

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
	int selecTempPosID = 0;
	int empTempPosID = 0;

	// set a temp variable
	empTempPosID = tileList.at(emptyID)->getPositionID();

	// replace the empty posID with the selected posID
	tileList.at(emptyID)->setPositionID(tileList.at(tileID)->getPositionID());

	// set the posID in the selected tile to the value of posID
	tileList.at(tileID)->setPositionID(empTempPosID);


	auto moveSelectedTile = cocos2d::MoveTo::create(0.1, cocos2d::Point(
		tileList.at(tileID)->getPositionX(), 
		tileList.at(tileID)->getPositionY()));
	auto moveEmptyTile = cocos2d::MoveTo::create(0.1, cocos2d::Point(
		tileList.at(emptyID)->getPositionX(),
		tileList.at(emptyID)->getPositionY()));

	tileList.at(tileID)->runAction(moveSelectedTile);
	tileList.at(tileID)->runAction(moveEmptyTile);





	/*
	int listSize = posIDList.size();

	// for each pos in list
	for (unsigned int index = 0; index < listSize; index++)
	{
		// save current value as last value in list
		int currentValue = posIDList.back();

		// decode to get coordinates.
		int _hIndex = currentValue / 4;
		int _wIndex = currentValue - (4 * _hIndex);

		// save the new tileID
		int currentTileID = (4 * _hIndex) + _wIndex;				// IS THIS NESSECARY



	//	// Create some temp Rect values here to save the positions of the tiles that are being looked at. 
	//	// Instead of using move to , swap the Rect values.

	//	// Get values of the individual sprite position
		auto selectedSprite = tileList.at(currentTileID);
	//	float selectedSpritePosX = selectedSprite->getPositionX();
	//	float selectedSpritePosY = selectedSprite->getPositionY();

	//	// size
	//	float selectedSpriteHeight = selectedSprite->getTileHeight();
	//	float selectedSpriteWidth = selectedSprite->getTileWidth();

	//	// create a rect value
	////	auto selectedRect = cocos2d::Rect(selectedSprite->getPositionX(), selectedSprite->getPositionY(),   /// this may not be needed.
	////		selectedSprite->getTileWidth(), selectedSprite->getTileHeight());

	//	// Do the same for the empty tile
	//	// Get values of the individual sprite position
		auto emptySprite = tileList.at(3);
	//	float emptySpritePosX = emptySprite->getPositionX();
	//	float emptySpritePosY = emptySprite->getPositionY();

	//	// size
		float emptySpriteHeight = emptySprite->getTileHeight();
		float emptySpriteWidth = emptySprite->getTileWidth();

		// create a rect value
	//	auto selectedRect = cocos2d::Rect(emptySprite->getPositionX(), emptySprite->getPositionY(),   /// this may not be needed.
	//		emptySprite->getTileWidth(), emptySprite->getTileHeight());

		float tempX = selectedSprite->getPositionX();
		float tempY = selectedSprite->getPositionY();
		int tempID = tileList.at(currentTileID)->getPositionID();

		// swap the two Rect variables.
		selectedSprite->setPositionX(emptySprite->getPositionX());
		selectedSprite->setPositionY(emptySprite->getPositionY());

		emptySprite->setPositionX(tempX);
		emptySprite->setPositionY(tempY);

		//// set the position value as new positions
		tileList.at(currentTileID)->setPositionID(tileList.at(emptyID)->getPositionID());

		//// set the tile positions as new positions
		tileList.at(emptyID)->setPositionID(tempID);

		//// delete last element of list
		posIDList.pop_back();
		*/
}















		////selected sprite 
		//auto selectedSprite = tileList.at(currentTileID);
		//auto selectedSpritePosition = tileList.at(currentTileID)->getPosition();

		//// empty sprite
		//auto emptySprite = tileList.at(emptyID);
		//auto emptySpritePosition = tileList.at(emptyID)->getPosition();

		//// create move function
		//auto moveEmptySprite = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(selectedSpritePosition.x, selectedSpritePosition.y));
		//auto moveSelectedSprite = cocos2d::MoveTo::create(0.1, cocos2d::Vec2(emptySpritePosition.x, emptySpritePosition.y));
		//
		//int temp = tileList.at(tileID)->getPositionID();

		//// action
		//selectedSprite->runAction(moveSelectedSprite);
		//emptySprite->runAction(moveEmptySprite);

		//// set the position value as new positions
		//tileList.at(tileID)->setPositionID(tileList.at(emptyID)->getPositionID());

		//// set the tile positions as new positions
		//tileList.at(emptyID)->setPositionID(temp);

		//// delete last element of list
		//posIDList.pop_back();

/*
	//selected sprite
	auto selectedSprite = tileList.at(tileID);
	auto selectedSpritePosition = tileList.at(tileID)->getPosition();

	// empty sprite
	auto emptySprite = tileList.at(emptyID);
	auto emptySpritePosition = tileList.at(emptyID)->getPosition();

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
	*/


// WORKSHEET CODE
/*
cocos2d::Scene* MyGameScene::createScene()
{
// 'scene' & 'Layer' are an autoreleased objects
cocos2d::Scene* scene = Scene::create();
auto layer = MyGameScene::create();

// add layer as a child to the scene
scene->addChild(layer);

// return the scene
return scene;
}


bool MyGameScene::init()
{

// add sprite to the game
SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
initBackground();
initPlayer();


return true;
}


void MyGameScene::initBackground()
{
// Create scene backdrop
auto backdrop = Sprite::create("BackDrop.png");
backdrop->setScale(0.80);
backdrop->setAnchorPoint(Vec2(0, 0));
backdrop->setPosition(Vec2(0, 0));
this->addChild(backdrop, 0);
}

void MyGameScene::initPlayer()
{
auto sprite = Sprite::createWithSpriteFrameName("m_idle.png");
this->addChild(sprite);
sprite->setPosition(25, 80);
sprite->setTag(1);


//create the lisener for the keyboard event, the callback funciton and add it the scenes event dispatcher
cocos2d::EventListenerKeyboard* lisener = EventListenerKeyboard::create();
lisener->onKeyPressed = CC_CALLBACK_2(MyGameScene::onKeyPressed, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(lisener, sprite);

//create the lisener for the keyboard event, the callback funciton and add it the scenes event dispatcher
cocos2d::EventListenerKeyboard* lisenerTwo= EventListenerKeyboard::create();
lisenerTwo->onKeyReleased = CC_CALLBACK_2(MyGameScene::onKeyReleased, this);
_eventDispatcher->addEventListenerWithSceneGraphPriority(lisenerTwo, sprite);
}


void MyGameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
// we're going to use the tag to identify the player sprite
//	if (event->getCurrentTarget()->getTag() == 1)
//{

//if space is pressed, we're going to jump
if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
{
Sprite* sprite = static_cast<cocos2d::Sprite*>(event->getCurrentTarget());


// create our custom sprite actin to jump
MySpriteAction* act1 = MySpriteAction::create(
sprite, SpriteFrameCache::getInstance()->getSpriteFrameByName("m_jump1.png"));


// create a second one to revert to the idele pose
MySpriteAction* act2 = MySpriteAction::create(
sprite, SpriteFrameCache::getInstance()->getSpriteFrameByName("m_idle.png"));

// the JumpBy is a cocos action, we can the nrun it on the sprite
cocos2d::JumpBy* jump = JumpBy::create(0.5, Vec2(0, 0), 100, 1);

//as per the lecture, we can combine actions to make a sequence
cocos2d::Sequence* sequence = Sequence::create(act1,jump, act2, nullptr);
event->getCurrentTarget()->runAction(sequence);
}


if (keycode == EventKeyboard::KeyCode::KEY_D)
{
// covnert our event into the player sprite
Sprite * sprite =
static_cast<cocos2d::Sprite*>(event->getCurrentTarget());

// covered in lecture 19
cocos2d::MoveBy* move = MoveBy::create(0.1, Vec2(5, 0));
cocos2d::RepeatForever* moveLoop = RepeatForever::create(move);
moveLoop->setTag(2);
sprite->runAction(moveLoop);

//we need to create a series of frames for the animation
Vector<SpriteFrame*> frames;
frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("m_run5.png"));
frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("m_run6.png"));
frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("m_run7.png"));
frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("m_run8.png"));
frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("m_run9.png"));

//using the frames above we generate an animation action and set it to repeat forever
cocos2d::Animation* animation = Animation::createWithSpriteFrames(frames, 0.1);
cocos2d::RepeatForever* action = RepeatForever::create(Animate::create(animation));
action->setTag(2);
sprite->runAction(action);


// WOULD BE NICE TO MAKE IT A SEQUENCE
}

return;
//}
}

void MyGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
if (event->getCurrentTarget()->getTag() == 1)
{
if (keycode == EventKeyboard::KeyCode::KEY_D)
{
// covnert our event into the player sprite
Sprite * sprite =
static_cast<cocos2d::Sprite*>(event->getCurrentTarget());
sprite->stopAllActionsByTag(2);
}
}
}

*/
