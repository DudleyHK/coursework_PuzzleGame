/*



https://blackboard.uwe.ac.uk/bbcswebdav/pid-4634231-dt-content-rid-8695402_2/courses/UFCFWA-30-1_15sep_1/Worksheet%2013%283%29.pdf

Sprite Guide
http://cocos2d-x.org/documentation/programmers-guide/3/index.html
*/

#include "GameScene.h"


cocos2d::Scene * GameScene::createScene()
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* playScene = Scene::create();
	auto playLayer = GameScene::create();

	// add layer as a child to a scene
	playScene->addChild(playLayer);
	playLayer->initLayer();

	// return the scene
	return playScene;
}


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

	//getWindowWidth();
	//getWindowHeight();

	//initBackground();
	//sliceImage();

	addImageToScene();

	return true;
}



void GameScene::addImageToScene()
{
	createPuzzle->init();
	createPuzzle->getImage(puzzleTiles);

	 

	// Display
	for (unsigned int index = GameScene::puzzleTiles.size(); index >= 0; index--)
	{
		this->addChild(puzzleTiles.at(index), -10);
	}
}



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
