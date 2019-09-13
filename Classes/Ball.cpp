#include "Ball.h"

USING_NS_CC;


Ball::Ball( cocos2d::Layer *layer )
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	ball = Sprite::create( "ball.png" );
	ball->setAnchorPoint(Vec2(0.5,0));
	ball->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 40.0f));

	layer->addChild( ball, 10 );
}

void Ball::Jump(){
	auto jumpUp = MoveBy::create(0.1f,Vec2(0,30));
	auto jumpDown = jumpUp->reverse();

	auto jump = Sequence::create(jumpUp,jumpDown,nullptr);

	ball->runAction(jump);
}