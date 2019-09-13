#include "ScoreBoard.h"

USING_NS_CC;


ScoreBoard::ScoreBoard( cocos2d::Layer *layer )
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	scoreText = Label::createWithTTF("0", "Roboto.ttf", 48);
	scoreText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	scoreText->setColor( Color3B(255,255,255));
	scoreText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	scoreText->setPosition( Vec2( visibleSize.width/2 + origin.x - 1.0f, visibleSize.height + origin.y - scoreText->getContentSize().height - 40.0f ) );

	layer->addChild( scoreText , 2 );

	timer = ProgressTimer::create(Sprite::create("radial.png"));
	timer->setType(ProgressTimerType::RADIAL);
	timer->setReverseProgress(true);
	timer->setPercentage(100.0f);
	timer->setAnchorPoint( Vec2(0.5f, 0.5f) );
	timer->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height + origin.y - scoreText->getContentSize().height - 40.0f ) );
	layer->addChild( timer , 0 );	
}

void ScoreBoard::setScore (int score)
{

	scoreText->setString(__String::createWithFormat( "%i", score )->getCString());
}

void ScoreBoard::setTimer(float percentage)
{
	timer->setPercentage(percentage);
}

