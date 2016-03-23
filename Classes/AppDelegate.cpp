#include "AppDelegate.h"


bool AppDelegate::applicationDidFinishLaunching() 
{
	// Obtain access to the game Director
	cocos2d::Director* director = Director::getInstance();

	// Set windows size and resoultion
	cocos2d::GLView* glView = director->getOpenGLView();

	// if the glView hasn't been initialised
	if (!glView)
	{
		// Create the application window
		glView = GLViewImpl::create("Puzzle Game");
		glView->setFrameSize(1280, 720);

		// Set this up via the game Director
		director->setOpenGLView(glView);
	}

	// Create a scenee and run it
	auto mainMenu = MainMenu::createScene();
	director->runWithScene(mainMenu);


	return true;
}

void AppDelegate::applicationDidEnterBackground() 
{

}

void AppDelegate::applicationWillEnterForeground() 
{

}