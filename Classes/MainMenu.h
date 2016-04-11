/*

*/
#pragma once
#include "GameScene.h"
#include "Settings.h"

class MainMenu : public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();

	MainMenu();
	~MainMenu();

	// @ -- Detail: Initialise the scene.
	// @ -- Return: If the scene has not been initialise return true, otherwise 
	// return false. 
	virtual bool initLayer();

	void initMenu();
	void backgroundAndTitle();

	// @ -- Detail: The function applies the Play, Settings and Exit buttons to the screen.
	// When pressed the 'CallBack' function will perform a task selected. The function
	// concludes by initialising the Main Menu layer. 
	void menuButtons();

	// @ -- Detail: Go to the main game. This is where the player plays the game.
	void menuPlayGame(cocos2d::Ref* sender);

	// @ -- Detail: Go to the setting menu. This is where the player can change settings in
	// the upcoming game. 
	void menuSettingMenu(cocos2d::Ref* sender);

	// @ -- Detail: Exit the game. 
	void menuEndGame(cocos2d::Ref* pSender);

	
	CREATE_FUNC(MainMenu);


private:

};