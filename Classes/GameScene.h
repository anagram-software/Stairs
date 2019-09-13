#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Ball.h"
#include "Stair.h"
#include "ScoreBoard.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	bool onTouchBegan (cocos2d::Touch * touch, cocos2d::Event * event);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	Ball *ball;
	Stair *stair[13];
	ScoreBoard *scoreboard;
	cocos2d::Sprite *instBanner;
	cocos2d::EventListenerTouchOneByOne *touchListener;
	int score;
	int floorNum;
	float fullTime;
	float currentTime;
	bool isGameStart;
	bool isGameOver;

	void gotoScene( cocos2d::Ref *sender, int failType );
	void endGame(int failType);
	void checkFail(int dir);
	void tickTock(float dt);

};

#endif // __GAME_SCENE_H__
