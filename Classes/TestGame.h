#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

class HelloWorld;

#include "cocos2d.h"

class TestGame
{
private:
	std::vector<cocos2d::Sprite*> sprites;


public:
	TestGame();
	virtual ~TestGame();

	bool Init(HelloWorld* hw);
};

#endif


