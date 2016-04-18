/*
// @ -- Detail:
// @ -- Param:
// @ -- Return:



*/
#pragma once
#include "PuzzleBoard.h"
#include "MainMenu.h"
#include <vector>

///////////////////////////////////////////////// NOTHING HAS BEEN UPDATED
class GameScene : public cocos2d::Layer
{
public:

	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene(
		int heightSegs, 
		int widthSegs, 
		int imageCode, 
		ImageLib* imgLib);

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	CREATE_FUNC(GameScene);

	GameScene();
	~GameScene();

	/////EXPLAIN
	void setGridSize(int heightSegments, int widthSegments);
	void setPuzzleImage(int imgCode, ImageLib* imgLib);

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Game Scene.
	// @ -- Return: If the layer has been initialised return TRUE.
	bool initLayer(
		int heightSegments, 
		int widthSegments, 
		int imageCode, 
		ImageLib* imgLib);

	// @ -- Detail: Passing information to the Puzzle Board and displaying the tiles.
	//			This also calls a function to shuffle the Puzzle Board.
	void addPuzzleBoard();

	// @ -- Detail: Create an event listener which looks out for the click of a mouse.
	//			If an event is detected call the onTouchBegan() function.
	void addEvent();

	// @ -- Param: Pass in the click coordinates and the event type. This will be made 
	//			readable by the function.
	// @ -- Return: If the click point coordinates match a tile position return TRUE.
	bool onTouchBegan(cocos2d::Touch* click, cocos2d::Event* event);

	// @ -- Detail: Call check functions to check surrounding positions for the empty 
	//			tile. If this tile is found call the swapTile() function.
	// @ -- Param: The tileID of the tile that was clicked.
	void checkForEmpty(int tileID);

	// @ -- Detail: These four functions check the position in each direction for a)
	//			the posID of the empty tile and b) if the empty tiles coordinates are 
	//			valid.
	// @ -- Param: Each functions takes the posID which is being checked and an integer
	//			used to determine if the current position being check is the empty tile.
	//			This integer will be set to the positionID in questions if its valid,
	//			otherwise it will stay as the unused value of -1.
	void checkLeft(int _posID, int* const n_posID);
	void checkRight(int _posID, int* const n_posID);
	void checkUp(int _posID, int* const n_posID);
	void checkDown(int _posID, int* const n_posID);

	// @ -- Detail: Function to check if the posID in question is the empty tile.
	// @ -- Param: The posID of the position being checked.
	// @ -- Return: If it is the empty tile return TRUE.
	bool getEmptyTilePos(int _posID);

	// @ -- Detail: If the game won boolean is FALSE create animation of the selected
	//			tile moving if the game is not worn. Swap selected posID and empty 
	//			posID. At then end of this function set game won boolean to TRUE.
	// @ -- Param: Pass in the tileID of the selected tile.
	void swapTiles(int tileID);

	// @ -- Detail: Call a function to iterate through each position checking the number
	//			of correctly placed tiles. 
	// @ -- Return: If the number of correctly placed tiles matches the number of tiles in
	//			the list return TRUE.
	bool boardComplete();

	// @ -- Detail: Displays options for the player to either reset the game or return to
	//			the main menu.
	void gameOverPopup();

	// @ -- Detail: The resetCallback() function replaces the the scene with a newly shuffled
	//			board. The returnCallback() function returns the player back to the main menu.
	void resetCallback(cocos2d::Ref* sender);
	void returnCallback(cocos2d::Ref* sender);

private:
	std::vector<SingleTile*> tileList;
	PuzzleBoard* puzzleBoard = new PuzzleBoard();
	ImageLib* imageLib = new ImageLib(); ///////////////NEW KEYWORD

	int hIndex = 0;
	int wIndex = 0;
	int heightSegments = 0;
	int widthSegments = 0;
	int numOfMoves = 0;
	int empTileID = 0;
	int imageCode = 0;
	bool gameWon = false;

};