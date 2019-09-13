#include "Stair.h"

USING_NS_CC;


Stair::Stair( cocos2d::Layer *layer )
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	int rand = (CCRANDOM_0_1() * 10 );
	nextDir = rand % 2;

	stair = Sprite::create( "floor.png" );
	stair->setAnchorPoint(Vec2(0.5,1));
	stair->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y -40.0f));

	layer->addChild( stair , 5 );
}

Stair::Stair( cocos2d::Layer *layer, Stair *s)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	int rand = (CCRANDOM_0_1() * 10 );
	nextDir = rand % 2;

	prevStair = s;   
	
	stair = Sprite::create( "floor.png" );
	stair->setAnchorPoint(Vec2(0.5,1));
	if(prevStair->nextDir == 1){
		stair->setPosition( Vec2( prevStair->stair->getPositionX() + prevStair->stair->getContentSize().width,  prevStair->stair->getPositionY() + prevStair->stair->getContentSize().height));
	}else{
		stair->setPosition( Vec2( prevStair->stair->getPositionX() - prevStair->stair->getContentSize().width,  prevStair->stair->getPositionY() + prevStair->stair->getContentSize().height));
	}	
	if (stair->getPositionY() > visibleSize.height){
		stair->setOpacity(0);		
	}else if (stair->getPositionY() > visibleSize.height/2){
		stair->setOpacity(255*(visibleSize.height - stair->getPositionY())/(visibleSize.height/2 + stair->getContentSize().height/2));		
	}else{
		stair->setOpacity(255);
	}

	layer->addChild( stair );
}

void Stair::setPrevStair( Stair *s )
{
	prevStair = s;
}

int Stair::getNextDir()
{
	return nextDir;
}

void Stair::jumpLeft(  )
{
	checkRespawn();	
	auto move = MoveBy::create(0.1f,Vec2( stair->getContentSize().width, -stair->getContentSize().height));
	stair->runAction(move);
}

void Stair::jumpRight(  )
{
	checkRespawn();
	auto move = MoveBy::create(0.1f,Vec2( -stair->getContentSize().width, -stair->getContentSize().height));
	stair->runAction(move);
}

void Stair::checkRespawn(  )
{
	//set color not a part of respawn
	if (stair->getPositionY() - stair->getContentSize().height > visibleSize.height){
		stair->setOpacity(0);		
	}else if (stair->getPositionY() > visibleSize.height/2)	{
		stair->setOpacity(255*(visibleSize.height - prevStair->stair->getPositionY())/(visibleSize.height/2 + stair->getContentSize().height/2));
	}else{
		stair->setOpacity(255);
	}
	//real resawn
	if (stair->getPositionY() <= -stair->getContentSize().height) {
		stair->setPositionY(prevStair->stair->getPositionY() + stair->getContentSize().height);
		if(prevStair->nextDir == 1){
			stair->setPosition( Vec2( prevStair->stair->getPositionX() + prevStair->stair->getContentSize().width,  prevStair->stair->getPositionY() + prevStair->stair->getContentSize().height));
		}else{
			stair->setPosition( Vec2( prevStair->stair->getPositionX() - prevStair->stair->getContentSize().width,  prevStair->stair->getPositionY() + prevStair->stair->getContentSize().height));
		}	
		stair->setOpacity(0);
		int rand = (CCRANDOM_0_1() * 10 );
		nextDir = rand % 2;
	}
}


