#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

class Ball
{
public:
	Ball( cocos2d::Layer *layer);
	void Jump();
	
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *ball;
	    
};

#endif // __BALL_H__
