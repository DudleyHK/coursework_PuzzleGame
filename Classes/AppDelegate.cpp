#include "AppDelegate.h"


bool AppDelegate::applicationDidFinishLaunching() 
{
	// Obtain access to the game Director
	cocos2d::Director* director = cocos2d::Director::getInstance();

	// Set windows size and resoultion
	cocos2d::GLView* glView = director->getOpenGLView();

	// if the glView hasn't been initialised
	if (!glView)
	{
		// Create the application window
		glView = cocos2d::GLViewImpl::create("Puzzle Game");
		glView->setFrameSize(1280, 720);

		// Set this up via the game Director
		director->setOpenGLView(glView);
	}

	// Create a scenee and run it
	auto menuScene = MainMenu::createScene();
	director->runWithScene(menuScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() 
{

}

void AppDelegate::applicationWillEnterForeground() 
{

}