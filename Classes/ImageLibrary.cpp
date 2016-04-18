/*
	Solution: ImageLibrary.cpp
	Author: Dudley Dawes
	Date: 19/04/16
*/
#include "ImageLibrary.h"

ImageLib::ImageLib()
{
	// Empty  
}

ImageLib::~ImageLib()
{
	// Empty
}

void ImageLib::initLibrary()
{
	imgList = new cocos2d::Sprite[NUMBER_OF_IMAGES];

	imgList[0].initWithFile("p_hamsterRunning.jpg");
	imgList[1].initWithFile("p_mountains.JPG");

	for (int index = 0; index < NUMBER_OF_IMAGES; index++)
	{
		imgList[index].setTag(index);
	}
}

cocos2d::Sprite* ImageLib::getPuzzleImg(int code)
{
	for (int index = 0; index < NUMBER_OF_IMAGES; index++)
	{
		if (imgList[index].getTag() == code)
		{
			return &imgList[index];
		}
	}
	return nullptr;
}