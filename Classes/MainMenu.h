/*
	Solution: MainMenu.h
	Author: Dudley Dawes
	Date: 19/04/16
*/
#pragma once
#include "GameScene.h"
#include "ImageLibrary.h"


class MainMenu : public cocos2d::Layer
{
public:
	CREATE_FUNC(MainMenu);
	MainMenu();
	~MainMenu();

	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene();


	/* =====GETTERS AND SETTERS===== */
	void setWindowSize();
	/* ============================== */
	

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Main Menu.
	// @ -- Return: If the layer has been initialised return TRUE.
	bool initLayer();

	// @ -- Detail: Create the display size of the background and tile. Set them
	//			as children of the scene/ display.
	void backgroundAndTitle();

	// @ -- Detail: Create the sprites for the buttons and their path (callback) when 
	//			selected. Add them as children to the scene/ display.
	void playAndQuit();

	// @ -- Detail: Add buttons to the screen. When clicked call functions which set 
	//			new height/ width segment values. Place these buttons in the scene.
	void selectGridSize();

	// @ -- Detail: Call a function to init the image library. Add the puzzle images
	//			to the scene as buttons. Place them on the scene. 
	void selectImg();

	// @ -- Detail: These functions are called when the user selected a button in 
	//			the scene. The menuStartGame() function calls call the Game Scene 
	//			create() function. The menuCloseCallback() function tells the Director
	//			to end the game safely. The setup() functions change the value of height/
	//			width segments values and the selectImg() function change the image code.
	void menuPlayCallback(cocos2d::Ref* sender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void setupSmallGrid(cocos2d::Ref* sender);
	void setupMediumGrid(cocos2d::Ref* sender);
	void setupLargeGrid(cocos2d::Ref* sender);
	void selectImg00(cocos2d::Ref* sender);
	void selectImg01(cocos2d::Ref* sender);

private:
	// Always begin game with default settings
	int heightSegments = 4;
	int widthSegments = 4;
	int imageCode = 0;

	ImageLib* imageLib = new ImageLib();
	cocos2d::Size windowSize;
};