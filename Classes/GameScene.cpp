/*



https://blackboard.uwe.ac.uk/bbcswebdav/pid-4634231-dt-content-rid-8695402_2/courses/UFCFWA-30-1_15sep_1/Worksheet%2013%283%29.pdf

Sprite Guide
http://cocos2d-x.org/documentation/programmers-guide/3/index.html
*/

#include "GameScene.h"

#define TILE_AT_INDEX tileList.at(index)

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
			TILE_AT_INDEX->getSprite()->setTag(Tags::SpriteTags::SPRITE_EMPTY);
		}
		else
		{
			//auto obj = tileList.at(index);
			TILE_AT_INDEX->getSprite()->setTag(Tags::SpriteTags::SPRITE_TILE);
		}

		// display
		this->addChild(TILE_AT_INDEX->getSprite());
	}
}


bool GameScene::getEmptyTilePos(int tileID)
{
	// get the tile ID at n-posID
	real_posID = tileList.at(tileID)->getPositionID();

	// chck if the tile id is 3
	// when found check if its position is equal to n_posID
	if (Tags::SpriteTags::SPRITE_EMPTY == tileList.at(real_posID)->getSprite()->getTag())
	{
		return true;
	}

	return false;
}

void GameScene::checkForEmpty(int posID) // this is currently the same as posID
{

	int tileID = -1;

	/*4 = num of width segs*/

	// these are only needed if the position ID is NOT passed in. 
	hIndex = posID / 4;						// use th posID to check if in bounds
	wIndex = posID - (hIndex * 4);


	 //call functions to check the surrounding positoins return the newPosition to move to
	 //in  each function have a check to see if the positoin is in bounds
	checkLeft(posID - 1, &tileID);
	if (tileID == -1)
	{
		checkRight(posID + 1, &tileID);
		if (tileID == -1)
		{
			checkUp(posID + 4 /* 4 = number of seg width*/, &tileID);
			if (tileID == -1)
			{
				checkDown(posID - 4 /* 4 = number of seg width*/, &tileID);
				if (tileID == -1)
				{
					; // empty tile not found, player cannot move this tile
				}
			}
		}
	}
	if (tileID != -1)
	{
		cocos2d::log("Empty space found");
		
		//int n_tileID = tileList.at(n_posID)->getTileID();
		
	

	/*	call function to move the tiles take two arg take new pos and pos id*/
		swapTiles(posID, tileID);
	}
}


bool GameScene::checkInBounds(int _hIndex, int _wIndex)
{
	// return true if the variables are within the board
	if ((_hIndex < 4 && _hIndex >= 0) &&
		(_wIndex < 4 && _wIndex >= 0))
	{
		return true;
	}

	return false;
}


void GameScene::checkLeft(int _posID, int* tileID)
{
	*tileID = _posID;

	// check 
	// if either of these functions return false
	if (!(checkInBounds(hIndex, (wIndex - 1)) && getEmptyTilePos(*tileID)))
	{
		// set newPos to an unused value
		*tileID = -1;
	}
}

void GameScene::checkRight(int _posID, int* tileID)
{
	*tileID = _posID;

	// if either of these functions return false
	if (!(checkInBounds(hIndex, (wIndex + 1)) && getEmptyTilePos(*tileID)))
	{
		// set newPos to an unused value
		*tileID = -1;
	}
}


void GameScene::checkUp(int _posID, int* tileID)
{
	*tileID = _posID;

	// if either of these functions return false
	if (!(checkInBounds((hIndex + 1), wIndex) && getEmptyTilePos(*tileID)))
	{
		// set newPos to an unused value
		*tileID = -1;
	}
}


void GameScene::checkDown(int _posID, int* tileID)
{
	*tileID = _posID;

	// if either of these functions return false
	if (!(checkInBounds((hIndex - 1), wIndex) && getEmptyTilePos(*tileID)))
	{
		// set newPos to an unused value
		*tileID = -1;
	}
}


void GameScene::swapTiles(int posID, int tileID)
{
	// place the current tileID into the position of the empty tile. 
	auto currentTile = tileList.at(tileID);
	auto currentSprite = currentTile->getSprite();
	auto currentTileVec = currentSprite->getPosition();	/// create a vector of the current tile so the empty tile can move to it


	auto emptyTileVec = tileList.at(real_posID)->getSprite()->getPosition();
	auto moveToPosition = cocos2d::MoveTo::create(1, cocos2d::Vec2(emptyTileVec.x, emptyTileVec.y));

	// set the currentSprite posID to n_posId
	currentTile->setPositionID(real_posID);
	currentTile->setTileID(_posID);


	// move the sprTile to teh empty positoin and vis versa
	currentSprite->runAction(moveToPosition);


	/// move the empty tile to the old position of the current tile. 
	/// create empty tile sprite
	auto emptyTile = tileList.at(real_posID);
	auto emptySprite = emptyTile->getSprite();


	auto moveEmptySprite = cocos2d::MoveTo::create(1, cocos2d::Vec2(currentTileVec.x, currentTileVec.y));

	/// set the empty tiles positionID
	emptyTile->setPositionID(posID);
	emptyTile->setTileID(posID);

	emptySprite->runAction(moveEmptySprite);
	 



























//	// passing in tileIDs now.
//	// get the Vec2 position on the empty tile and sprite
//	auto empTile = tileList.at(n_tileID)->getSprite();
//	auto empTilePos = tileList.at(n_tileID)->getSprite()->getPosition();
////	auto empTilePos = n_posID;
//	// get the sprite tile at posID and Vec2 pos
//	auto sprTile = tileList.at(tileID)->getSprite();
//	auto sprTilePos = tileList.at(tileID)->getSprite()->getPosition();
//	//auto sprTilePos = posID;
//
//	// create a move funcition
//	auto moveSpr = cocos2d::MoveTo::create(2, cocos2d::Vec2(empTilePos.x, empTilePos.y));
//	auto moveEmp = cocos2d::MoveTo::create(2, cocos2d::Vec2(sprTilePos.x, sprTilePos.y));
//
//		// move the sprTile to teh empty positoin and vis versa
//		sprTile->runAction(moveSpr);
//		empTile->runAction(moveEmp);
//
//
//
//		///////NNNNEWWW
//		///////NNNNEWWW
//		///////NNNNEWWW
//		//	 set the tiles positionID as the current posID 
//		tileList.at(posID)->setPositionID(n_posID);							
//		tileList.at(n_posID)->setPositionID(posID);
//
//		//set new tag
//		tileList.at(n_posID)->getSprite()->setTag(Tags::SpriteTags::SPRITE_EMPTY);
//		tileList.at(posID)->getSprite()->setTag(Tags::SpriteTags::SPRITE_TILE);


	//// get the Vec2 position on the empty tile and sprite
	//auto empTile = tileList.at(n_posID)->getSprite();
	//auto empTilePos = tileList.at(n_posID)->getSprite()->getPosition();

	//// get the sprite tile at posID and Vec2 pos
	//auto sprTile = tileList.at(posID)->getSprite();
	//auto sprTilePos = tileList.at(posID)->getSprite()->getPosition();

	//// create a move funcition
	//auto moveSpr = cocos2d::MoveTo::create(2, cocos2d::Vec2(empTilePos.x, empTilePos.y));
	//auto moveEmp = cocos2d::MoveTo::create(2, cocos2d::Vec2(sprTilePos.x, sprTilePos.y));

	//int sprActionsRunning = sprTile->getNumberOfRunningActions();
	//int empActionsRunning = empTile->getNumberOfRunningActions();

	//// check if any actions are running
	//if (sprActionsRunning == 0 && empActionsRunning == 0)
	//{
	//	// move the sprTile to teh empty positoin and vis versa
	//	sprTile->runAction(moveSpr);
	//	empTile->runAction(moveEmp);
	//}
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
			//save for variable as global varibale   //this may not ned to be done /////////////////////CHHHECK
			hIndex = heightIndex;
			wIndex = widthIndex;

			//if any sprite contains the point coordinates.
			if (tileList.at((4 * heightIndex) + widthIndex)->getSprite()->
				getBoundingBox().containsPoint(point))
			{
				checkForEmpty(tileList.at((4 * heightIndex) + widthIndex)->getPositionID()); //checkForEmpty(tileList.at((4 * heightIndex) + widthIndex)->getTileID());  /// get the positionID
				return true;
			}
		}
	}
}

//	//use height/ width index (global) to decode the positionID allowing me to find out if what i am about to check is bounds.
//
//	return false;
//}

//bool GameScene::onTouchMove(cocos2d::Touch* click, cocos2d::Event* event)
//{
//	// Get info on where the screen has been clicked
//	cocos2d::Point point = click->getLocationInView();
//
//	//convert these coordinates into world coordinates
//		point = cocos2d::Director::getInstance()->convertToGL(point);
//
//	//run through the tile list
//		for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
//		{
//			for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
//			{
//				//save for variable as global varibale
//					hIndex = heightIndex;
//				wIndex = widthIndex;
//
//				//if any sprite contains the point coordinates.
//					if (tileList.at((4 * heightIndex) + widthIndex)->getSprite()->
//						getBoundingBox().containsPoint(point))
//					{
//						checkForEmpty(tileList.at((4 * heightIndex) + widthIndex)->getTileID());
//						return true;
//					}
//			}
//		}
//
//	//use height / width index(global) to decode the positionID allowing me to find out if what i am about to check is bounds.
//
//		return false;
//}











// ONLY MOVE TILE IF MOUSE MOVES
/*
bool GameScene::onTouchMove(cocos2d::Touch* click, cocos2d::Event* event)
{
	// Get info on where the screen has been clicked
	cocos2d::Point point = click->getLocationInView();

	 convert these coordinates into world coordinates
	point = cocos2d::Director::getInstance()->convertToGL(point);

	 run through the tile list
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			save for variable as global varibale
			hIndex = heightIndex;
			wIndex = widthIndex;

			if any sprite contains the point coordinates.
			if (tileList.at((4 * heightIndex) + widthIndex)->getSprite()->
				getBoundingBox().containsPoint(point))
			{
				checkForEmpty(tileList.at((4 * heightIndex) + widthIndex)->getTileID());
				return true;
			}
		}
	}

	use height/ width index (global) to decode the positionID allowing me to find out if what i am about to check is bounds.

	return false;
}
//bool GameScene::onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event)
//{
//	// return listener sceneGraphPriority node
//	auto bounds = event->getCurrentTarget()->getBoundingBox();
//
//	//// get the tag of the sprite that has been clicked. 
//	//for (int index = 0; index < GameScene::tileList.size(); index++)
//	//{
//	//	auto obj = tileList.at(index);
//	//	int tag = obj->returnSprite()->getTag();
//	//}
//
//	// get coordinates at point of click
//	cocos2d::Point touch = click->getLocationInView();
//	touch = cocos2d::Director::getInstance()->convertToGL(touch);
//
//	// go through tileList
//	for (unsigned int i = 0; i < tileList.size(); i++)
//	{
//		// if any of the sprites in the list contain the click point (touch)
//		if (tileList.at(i)->returnSprite()->getBoundingBox().containsPoint(touch))
//		{
//			// move the sprite
//			cocos2d::MoveBy* move = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2(5, 0));
//			tileList.at(i)->returnSprite()->runAction(move);
//			return true;
//		}
//	}
//
//	return false;
//}
*/







//// ONE WAY TO DO EVENT LISTENER
/*  
// return listener sceneGraphPriority node
auto target = static_cast <cocos2d::Sprite*>(event->getCurrentTarget());

// get the position of the current point relative to the button
cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
cocos2d::Size s = target->getContentSize();
cocos2d::Rect r = cocos2d::Rect(0, 0, s.width, s.height);

// Check the click area
if (r.containsPoint(locationInNode))
{
target->setOpacity(0);
return true;
}
*/
///// EVENTLISTENER
/*

void GameEventListener::onMouseDown(cocos2d::EventMouse * mouse)
{

// we need the mouses location and the sprites bounding box
cocos2d::Vec2 p = mouse->getLocation();
cocos2d::Rect t = tile->getBoundingBox();

//check if the mouse is within the imageTile
if (t.containsPoint(p))
{
cocos2d::MoveBy* move = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2(5, 0));
}
}


void GameEventListener::onMouseRelease(cocos2d::EventMouse * mouse)
{
// If the mouse is being pressed

// if the sprite is over the empty position

// place the sprite at that position


}

*/
// INIT BACKGROUND FUNCTION
/*
void GameScene::initBackground()
{
	auto backdrop = Sprite::create("PatternPictureFrame.jpg");
	backdrop->setScale(1);
	backdrop->setAnchorPoint(Vec2(0, 0));
	backdrop->setPosition(Vec2(0, 0));
	this->addChild(backdrop, -50);

	addPuzzleImage();
}
*/
// SLICE IMAGE FUNCTION
/*
void GameScene::sliceImage()
{
	/ create a sprite, set its anchor point and set its position to a position
	 on the screen relative to the size resolution of the window/
	auto puzzleImage = Sprite::create("p_hamsterRunning.jpg");
	puzzleImage->setAnchorPoint(Vec2(0, 0));
	puzzleImage->setPosition(Director::getInstance()->getVisibleOrigin());

	// set the height and width of the image
	int imageWidth = puzzleImage->getBoundingBox().size.width;
	int imageHeight = puzzleImage->getBoundingBox().size.height;

	// Scale width and height, and reduce its size by 2%
	float scaleWidth = (500.0f / imageWidth) * 0.98;
	float scaleHeight = (500.0f / imageHeight) * 0.98;

	// Get the size of a single tile 
	cocos2d::Vec2 imageTile = Vec2(imageWidth / 4, imageHeight / 4);


	// Run through each position in the sprite
	for (unsigned int heightIndex = 0; heightIndex < 4; heightIndex++)
	{
		for (unsigned int widthIndex = 0; widthIndex < 4; widthIndex++)
		{
			float widthPosition = imageTile.x * widthIndex;
			float heightPosition = imageTile.y * heightIndex;

			/* Create a tile, set anchor point and position, scale the tile and finally add
			it to the scene as a chile object/
			auto tile = Sprite::create("p_hamsterRunning.jpg", Rect(widthPosition,
				(imageHeight - heightPosition) - imageTile.y, imageTile.x, imageTile.y));

			tile->setAnchorPoint(Vec2(0, 0));
			tile->setPosition(Vec2((500 / 4) * widthIndex, (500 / 4) * heightIndex));
			tile->setScaleX(scaleWidth);
			tile->setScaleY(scaleHeight);
			this->addChild(tile);
		}
	}
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
