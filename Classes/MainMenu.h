/*

// @ -- Detail:
// @ -- Param:
// @ -- Return:

*/
#pragma once
#include "GameScene.h"
#include "ImageLibrary.h"


///////////////////////////////////////////////// NOTHING HAS BEEN UPDATED
class MainMenu : public cocos2d::Layer
{
public:

	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene();

	void setWindowSize();

	CREATE_FUNC(MainMenu);

	MainMenu();
	~MainMenu();

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Main Menu.
	// @ -- Return: If the layer has been initialised return TRUE.
	bool initLayer();

	// @ -- Detail: Create the display size of the background and tile. Set them
	//			as children of the scene/ display.
	void backgroundAndTitle();

	// @ -- Detail: Create the sprites for the buttons and there path (callback) when 
	//			selected. Add them as children to the scene/ display.
	void playAndQuit();/////update


	void selectGridSize();

	void selectImg();

	// @ -- Detail: These two functions are called when the user selected a button in 
	//			the scene. The menuStartGame() function calls call the Game Scene 
	//			create() function. The menuSettingsCallback() function takes the player
	//			to the Settings menu. The menuCloseCallback() function tells the Director
	//			to end the game safely.
	void menuPlayCallback(cocos2d::Ref* sender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void setupSmallGrid(cocos2d::Ref* sender);
	void setupMediumGrid(cocos2d::Ref* sender);
	void setupLargeGrid(cocos2d::Ref* sender);
	void selectImg00(cocos2d::Ref* sender);
	void selectImg01(cocos2d::Ref* sender); // update

private:
	// Always begin game with default settings
	int heightSegments = 4;
	int widthSegments = 4;
	int imageCode = 0;

	ImageLib* imageLib = new ImageLib();
	cocos2d::Size windowSize;
};