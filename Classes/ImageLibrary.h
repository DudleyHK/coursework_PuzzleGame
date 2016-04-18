/*
 create namespace of images referenced by a code sent after the uses selects an image from the setings menu.



*/
#pragma once
#include "cocos2d.h"

class ImageLib
{
public:

	ImageLib();
	~ImageLib();

	void initLibrary();
	cocos2d::Sprite* getPuzzleImg(int code);

private:
	int const NUMBER_OF_IMAGES = 2;
	cocos2d::Sprite* imgList = nullptr;
};