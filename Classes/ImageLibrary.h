/*
	Solution: ImageLibrary.h
	Author: Dudley Dawes
	Date: 19/04/16
*/
#pragma once
#include "cocos2d.h"

class ImageLib
{
public:
	ImageLib();
	~ImageLib();

	// @ -- Detail: Add each puzzle image to the image array and run a for loop to 
	//			set their tags equal to their position in the list. 
	void initLibrary();

	// @ -- Detail: Run a loop to check each images tag. When the tag is equal to the 
	//			code value return sprite at position.
	// @ -- Param: Position in the list
	// @ -- Return: Sprite at positoin in array.
	cocos2d::Sprite* getPuzzleImg(int code);

private:
	int const NUMBER_OF_IMAGES = 2;
	cocos2d::Sprite* imgList = nullptr;
};