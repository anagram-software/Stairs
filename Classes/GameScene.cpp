#include "GameScene.h"
#include "EndScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	score = 0;
	fullTime = 4.0f;
	currentTime = fullTime;
	isGameStart = false;
	isGameOver = false;

	//add ball
	ball = new Ball( this );

	//set stairs
	stair[0] = new Stair( this );

	for(int e = 1; e <= 12; e++){
		stair[e] = new Stair( this, stair[e-1] );
	}

	stair[0]->setPrevStair(stair[12]);

	//set currnt floor to 0
	floorNum = 0;

	//set score board
	scoreboard = new ScoreBoard(this);

	// set instruction banner
	instBanner = Sprite::create("instruction.png");
	instBanner->setAnchorPoint( Vec2(0.5f, 0.5f) );
	instBanner->setPosition( Vec2( visibleSize.width/2 + origin.x, origin.y + 150.0f ) );

	auto fadeOut = FadeTo::create(0.4f,50);
	auto fadeIn = FadeTo::create(0.4f,255);
	auto impluse = Sequence::create(fadeIn,fadeOut,nullptr);
	instBanner->runAction(RepeatForever::create(impluse));

	this->addChild( instBanner , 0 );

	//add touch lisetner
	touchListener = EventListenerTouchOneByOne::create();

	touchListener->setSwallowTouches(true);

	// trigger when you push down
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);

	// Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->schedule(schedule_selector(GameScene::tickTock));
    return true;
}

bool GameScene::onTouchBegan (cocos2d::Touch * touch, cocos2d::Event * event)
{
	if ( !isGameStart )
	{
		isGameStart = true;
		instBanner->stopAllActions();
		instBanner->runAction(FadeOut::create(0.1f));
	}

	ball->Jump();

	//init audio
	auto audio = SimpleAudioEngine::getInstance();

	// play jump music
	audio->playEffect("jump.ogg");

	UserDefault *def = UserDefault::getInstance();

	auto sounds = def->getBoolForKey( "SOUNDS",  true );

	if ( sounds )
	{
		audio->setBackgroundMusicVolume(1.0f);
	  	audio->setEffectsVolume(1.0f);
	}else{
	  	audio->setBackgroundMusicVolume(0.0f);
	   	audio->setEffectsVolume(0.0f);
	}

	def->flush();

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if ( touch->getLocationInView().x < visibleSize.width/2 + origin.x ) {
		checkFail(0);
		for(int e = 0; e <= 12; e++) {
			stair[e]->jumpLeft();
		}
	}else if ( touch->getLocationInView().x >= visibleSize.width/2 + origin.x ) {
		checkFail(1);
		for(int e = 0; e <= 12; e++) {
			stair[e]->jumpRight();
		}
	}

	if (floorNum == 12){
		floorNum = 0;
	}else{
		floorNum++;
	}

    return true;
}

void GameScene::checkFail (int dir)
{
	if(stair[floorNum]->getNextDir() == dir)
	{
		score++;
		currentTime += 0.2f;
		if (currentTime > fullTime)
		{
			currentTime = fullTime;
		}
		scoreboard->setScore(score);
	}else{
		endGame(0);
	}
}

void GameScene::tickTock ( float dt )
{
	currentTime -= dt;
	scoreboard->setTimer(100 * currentTime / fullTime);
    if (currentTime <= 0 && !isGameOver)
    {
       isGameOver = true;
       endGame(1);
    }
}

void GameScene::endGame ( int failType )
{
	_eventDispatcher->removeEventListener(touchListener);
	gotoScene( this , failType);
}

void GameScene::gotoScene( cocos2d::Ref *sender, int failType)
{
	auto scene = EndScene::createScene(score, failType);

	Director::getInstance()->replaceScene( TransitionFade::create( 0.3f, scene ));
}
