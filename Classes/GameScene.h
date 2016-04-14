/*

// @ -- Detail:
// @ -- Param:
// @ -- Return:



*/
#pragma once
#include "PuzzleBoard.h"
#include "MainMenu.h"
#include <vector>


class GameScene : public cocos2d::Layer
{
public:

	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameScene);
	
	GameScene();
	~GameScene();

	// @ -- Detail: Check if the layer has been initialised and call functions
	//			to setup the Game Scene.
	// @ -- Return: If the layer has been initialised return TRUE.
	virtual bool initLayer();

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

	// @ -- Detail: Create animation of the selected tile moving if the game is not worn. 
	//			Swap selected posID and empty posID.
	// @ -- Param: Pass in the tileID of the selected tile.
	void swapTiles(int tileID);


	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	bool boardComplete();

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	bool gameOverPopup();

	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void resetCallback(cocos2d::Ref* sender);

	
	// @ -- Detail:
	// @ -- Param:
	// @ -- Return:
	void returnCallback(cocos2d::Ref* sender);

private:
	std::vector<SingleTile*> tileList;
	PuzzleBoard* puzzleBoard = new PuzzleBoard();									///////////////NEW KEYWORD

	int hIndex = 0;
	int wIndex = 0;
	int numOfMoves = 0;
	const int empTileID = 3;
	bool gameWon = false;

};
