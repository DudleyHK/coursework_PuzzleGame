/*

// @ -- Detail:
// @ -- Param:
// @ -- Return:

*/
#pragma once
#include "GameScene.h"
#include "Settings.h"


class MainMenu : public cocos2d::Layer
{
public:

	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene();

	CREATE_FUNC(MainMenu);

	MainMenu();
	~MainMenu();

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Main Menu.
	// @ -- Return: If the layer has been initialised return TRUE.
	virtual bool initLayer();

	// @ -- Detail: Create the display size of the background and tile. Set them
	//			as children of the scene/ display.
	void backgroundAndTitle();

	// @ -- Detail: Create the sprites for the buttons and there path (callback) when 
	//			selected. Add them as children to the scene/ display.
	void menuButtons();

	// @ -- Detail: These two functions are called when the user selected a button in 
	//			the scene. The menuStartGame() function calls call the Game Scene 
	//			create() function. The menuSettingsCallback() function takes the player
	//			to the Settings menu. The menuCloseCallback() function tells the Director
	//			to end the game safely.
	void menuPlayCallback(cocos2d::Ref* sender);
	void menuSettingsCallback(cocos2d::Ref* sender);
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	Settings* settings = new Settings();
};