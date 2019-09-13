#ifndef __SCORE_BOARD_H__
#define __SCORE_BOARD_H__

#include "cocos2d.h"

class ScoreBoard
{
public:
	ScoreBoard( cocos2d::Layer *layer );
	void setScore(int score);
	void setTimer(float percentage);
	
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	
	cocos2d::Label *scoreText;
	cocos2d::ProgressTimer *timer; 
 
};

#endif // __SCORE_BOARD_H__
