/*
 create namespace of images referenced by a code sent after the uses selects an image from the setings menu.



*/
#pragma once
#include "cocos2d.h"
USING_NS_CC;


namespace ImageLib
{
	cocos2d::Vector<Sprite*> imageList;

	void setTags();
	auto getImage(const unsigned int index);
};