/*



// @ -- Detail:
// @ -- Param:
// @ -- Return:

*/
#pragma once
#include "cocos2d.h"
#include "SingleTile.h"
#include <cstdlib>
#include <ctime>
#include <vector>


class PuzzleBoard
{
public:
	PuzzleBoard();
	~PuzzleBoard();


	/* =====GETTERS AND SETTERS===== */
	void getSpriteList(std::vector<SingleTile*> *list);
	void getCoordinates(int posID, int* const w, int* const h);
	/* ============================== */


	// @ -- Detail: This function creates the image for the game, sets its anchor
	//			point and position on the screen. It then calls the sliceImage() 
	//			function.
	void createImage();

	// @ -- Detail: Run through a loop of each coordinate to be. Creates a new 
	//			instance a Single Tile and calls functions to set each tiles 
	//			new information. It then pushs the new instance onto a vector.
	// @ -- Param: Takes the sprite created in the createImage() function.
	void sliceImage(cocos2d::Sprite* puzzleImage);

	// @ -- Detail: Run through each tile in the vector list and make the tile
	//			equal to the width of the grid transparent (empty).
	void setTransparentTile();

	// @ -- Detail: Produce a random value 1 - 4.
	// @ -- Return: The product of the random value.
	int produceRandValue() const;

	// @ -- Detail: Runs through x amount of iterations, each time getting
	//			a new direction to move the empty tile.
	void getDirection();

	// @ -- Detail: Checks if the coordinates past in are valid.
	// @ -- Param: Width/ height coordinates.
	// @ -- Return: If they are valid return TRUE.
	bool checkInBounds(int w, int h) const;

	// @ -- Detail: Find the tile ID of the adjacent tile and use it to find its own 
	//			tile ID. Change and use the adjacent position ID.
	// @ -- Param: The adjacent position ID
	// @ -- Return: The tileID of the adjacent tile.
	int getAdjacentTileID(int* const adjacentPosID);

	// @ -- Detail: Swaps the empty tile with the randomly selected place. Then swaps
	//			the two tiles position IDs. If at the end of the shuffle the board is in
	//			its original state give it one extra shuffle.
	// @ -- Param: The tileID and position ID of the adjacent tiles.
	void swap(int adjacentTileID, int adjacentPosID); 

	// @ -- Detail: for every tile ID and position ID that match add one to the counter. 
	// @ -- Param: right place counter.
	void getCorrectTiles(int* const rightPlace);


private:
	std::vector<SingleTile*> tileList;

	float scaleWidth = 0.0f;
	float scaleHeight = 0.0f;
	int imageWidth = 0;
	int imageHeight = 0;
	int newIndexW = 0;
	int newIndexH = 0;
	

	const int empTileID = 3;
}; 