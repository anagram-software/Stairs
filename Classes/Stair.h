#ifndef __STAIR_H__
#define __STAIR_H__

#include "cocos2d.h"

class Stair
{
public:
	Stair( cocos2d::Layer *layer );	
	Stair( cocos2d::Layer *layer, Stair *s);	

	void setPrevStair( Stair *s );
	int getNextDir();

	void jumpLeft();
	void jumpRight();	

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	int nextDir;

	Stair *prevStair;  	
	cocos2d::Sprite *stair;   

	void checkRespawn();
 
};

#endif // __STAIR_H__
