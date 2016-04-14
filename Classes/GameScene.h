/*



*/
#pragma once
#include "cocos2d.h"
#include "PuzzleBoard.h"
#include "Tags.h"
#include <vector>


class GameScene : public cocos2d::Layer
{
public:

	// @ -- Detail: Create a new scene.
	// @ -- Return: Created scene
	static cocos2d::Scene* createScene();
	
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
	void checkLeft(int _posID, int* n_posID);
	void checkRight(int _posID, int* n_posID);
	void checkUp(int _posID, int* n_posID);
	void checkDown(int _posID, int* n_posID);

	// @ -- Detail: Function to check if the posID in question is the empty tile.
	// @ -- Param: The posID of the position being checked.
	// @ -- Return: If it is the empty tile return TRUE.
	bool getEmptyTilePos(int _posID);

	// @ -- Detail: Create animation of the selected tile moving. Swap selected posID and 
	//			empty posID.
	// @ -- Param: Pass in the tileID of the selected tile.
	void swapTiles(int tileID);

	// USE WHEN CREATING A BACKGROUND FOR THE SCENE
	//void initBackground();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	std::vector<SingleTile*> tileList;
	PuzzleBoard* puzzleBoard = new PuzzleBoard();									///////////////NEW KEYWORD

	int hIndex = 0;
	int wIndex = 0;

	const int empTileID = 3;

};
