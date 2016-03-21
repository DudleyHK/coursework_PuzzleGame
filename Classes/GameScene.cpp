/*



https://blackboard.uwe.ac.uk/bbcswebdav/pid-4634231-dt-content-rid-8695402_2/courses/UFCFWA-30-1_15sep_1/Worksheet%2013%283%29.pdf
*/

#include "GameScene.h"
USING_NS_CC;



cocos2d::Scene * GameScene::createScene()
{
	// 'scene' & 'layer' are autoreleased objects
	cocos2d::Scene* playScene = Scene::create();
	auto playLayer = GameScene::create();

	// add layer as a child to a scene
	playScene->addChild(playLayer);
	playLayer->initLayer();

	// return the scene
	return playScene;}


bool GameScene::initLayer()
{
	if (!Layer::init())
	{
		return false;
	}

	//getWindowWidth();
	//getWindowHeight();

	//initBackground();
	sliceImage();

	return true;
}

/*
float GameScene::getWindowWidth()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->windowWidth = visibleSize.width;

	return this->windowWidth; //windowWidth = visibleSize.width;
}
*/

/*
float GameScene::getWindowHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->windowHeight = visibleSize.height;

	return this->windowHeight; //windowHeight = visibleSize.height;
}
*/

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

void GameScene::sliceImage()
{
	//cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	//cocos2d::Vector<Sprite*> segmentList;


	
	auto puzzleSprite = Sprite::create("p_hamsterRunning.jpg");
	puzzleSprite->setAnchorPoint(Vec2(0, 0));
	puzzleSprite->setPosition(Director::getInstance()->getVisibleOrigin());
	//this->addChild(puzzleSprite, 0);

	// get the height and width of a single tile
	int spriteWidth = puzzleSprite->getBoundingBox().size.width;
	int spriteHeight = puzzleSprite->getBoundingBox().size.height;

	// SCALE
	float scaleWidth = 500.0f / spriteWidth;
	float scaleHeight = 500.0f / spriteHeight;

	float scale2W = scaleWidth * 98 / 100;
	float scale2H = scaleHeight * 98 / 100;

	puzzleSprite->setAnchorPoint(Vec2(0, 0));
	puzzleSprite->setPosition(Vec2(0, 0));
	puzzleSprite->setScaleX(scale2W);
	puzzleSprite->setScaleY(scale2H);

	cocos2d::Vec2 tileSize = Vec2(spriteWidth / 4, spriteHeight / 4);
	//cocos2d::Vec2 anchorPoint = Vec2(Vec2::ANCHOR_TOP_LEFT);

	


	// Run through each position in the sprite
	for (unsigned int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float widthPosition = (spriteWidth / 4) * j;
			float heightPosition = (spriteHeight / 4) * i;

			auto image = Sprite::create("p_hamsterRunning.jpg", Rect(widthPosition, (spriteHeight - heightPosition) - tileSize.y, tileSize.x, tileSize.y));
			image->setAnchorPoint(Vec2(0, 0));
			image->setPosition(Vec2((500 / 4) * j, (500 / 4) * i));
			image->setScaleX(scale2W);
			image->setScaleY(scale2H);
			this->addChild(image);

			//segmentList.pushBack(image);
		}
	}







	/*
	// display each segment from the list
	for (unsigned int i = 0 ; i <= 15; i++)
	{
		float widthPosition = (spriteWidth / 4) * i;
		float heightPosition = (spriteHeight / 4) * i;

		segmentList.at(i)->setPosition((i % 4) * tileSize.x,
			(((unsigned int)i / 4) * tileSize.y));						///	WORK OUT WTF THIS IS DOING (other than setting the position)


			// Se the anchore point for each sprite
		segmentList.at(i)->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

		// add the segment to the scene
		this->addChild(segmentList.at(i), 0);
	}
	*/















	/*
	for (unsigned int index = 0; index <= 15 /*total number of segments - 1/; index++)
	{
		/*CREATE AN ARRAY OF IMAGES THAT THE PLAYER CAN PICK AND REPLACE p_hamsterRunning WITH AN IMAGE CODE/
		// Create a sprite
		auto puzzleSprite = Sprite::create("p_hamsterRunning.jpg");
		//auto puzzleSprite = Sprite::createWithSpriteFrameName("p_hamsterRunning.jpg");


		// set scale of image
		float spriteWidth = puzzleSprite->getBoundingBox().size.width;
		float spriteHeight = puzzleSprite->getBoundingBox().size.height;

		float scaleWidth = 500 / spriteWidth ;
		float scaleHeight = 500 / spriteHeight;

		puzzleSprite->setScaleX(scaleWidth);
		puzzleSprite->setScaleY(scaleHeight);




		/*REPLACE THE 4 WITH THE NUMBER OF SEGMENTS/
		// Get the height and width of a segment
		segmentWidth = puzzleSprite->getBoundingBox().size.width / 4;
		segmentHeight = puzzleSprite->getBoundingBox().size.height / 4;

		float xOrigin = (index % 4) * segmentWidth;			// return either 1 or 0
		float yOrigin = ((unsigned int)index / 4) * segmentHeight;

		puzzleSprite->setTextureRect(Rect(xOrigin, yOrigin, segmentWidth, segmentHeight));
		segmentList.pushBack(puzzleSprite);
	}

	// display each segment from the list
	for (unsigned int i = 0 /*total number of segments - 1/; i <= 15; i++)
	{
		segmentList.at(i)->setPosition((i % 4) * segmentWidth, 
			(((unsigned int)i / 4) * visibleSize.height / 4));						///	WORK OUT WTF THIS IS DOING (other than setting the position)


		// Se the anchore point for each sprite
		segmentList.at(i)->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

		// add the segment to the scene
		this->addChild(segmentList.at(i), 0);
	}
	
	// displayPuzzle(segmentList);


	*/
}


/*
// Create function to add and cut segment puzzle
void GameScene::displayPuzzle(Vector<Sprite*>& segmentList)
{
	// display each segment from the list
	for (unsigned int i = 0; i <= 15 /*total number of segments - 1/; i++)
	{
		segmentList[i]->setPosition((i%4) * visibleSize
	}


	
	//auto puzzleImage = Sprite::create("HamsterRunning.jpg");
	//puzzleImage->setScale(1);
	//puzzleImage->setAnchorPoint(Vec2(0,0));
	//puzzleImage->setPosition(Vec2(0, 0));
	//this->addChild(puzzleImage, -5);
	
}
*/



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
