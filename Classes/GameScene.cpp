/*




*/

#include "GameScene.h"
USING_NS_CC;



cocos2d::Scene* GameScene::createScene()
{
	// 'scene' & 'layer' are an autoreleased objects
	cocos2d::Scene* gameScene = Scene::create();
	auto gameLayer = GameScene::create();

	//add layer as a child object
	gameScene->addChild(gameLayer);

	//return scene
	return gameScene;
}



bool GameScene::init()
{
	getWindowWidth();
	getWindowHeight();

	initBackground();

	return true;
}


float GameScene::getWindowWidth()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->windowWidth = visibleSize.width;

	return this->windowWidth; //windowWidth = visibleSize.width;
}


float GameScene::getWindowHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->windowHeight = visibleSize.height;

	return this->windowHeight; //windowHeight = visibleSize.height;
}


void GameScene::initBackground()
{
	auto backdrop = Sprite::create("PatternPictureFrame.jpg");
	backdrop->setScale(1);
	backdrop->setAnchorPoint(Vec2(0, 0));
	backdrop->setPosition(Vec2(0, 0));
	this->addChild(backdrop, -50);

	addPuzzle();
}


// Create function to add and cut segment puzzle
void GameScene::addPuzzle()
{
	auto puzzleImage = Sprite::create("HamsterRunning.png");
	puzzleImage->setScale(1);
	puzzleImage->setAnchorPoint(Vec2(windowWidth / 2, windowHeight / 2));
	puzzleImage->setPosition(Vec2(0, 0));
	this->addChild(puzzleImage, -5);
}



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