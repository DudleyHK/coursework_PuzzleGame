/*




*/
#include "GameEventListener.h"



//GameEventListener::GameEventListener()
//{
//	; // empty
//}
//
//GameEventListener::~GameEventListener()
//{
//	; // empty
//}


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
