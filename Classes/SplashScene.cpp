#include "SplashScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

cocos2d::Scene *SplashScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// pre load audio
	auto audio = SimpleAudioEngine::getInstance();

	// pre-loading background music and effects. You could pre-load
	// effects, perhaps on app startup so they are already loaded
	// when you want to use them.
	audio->preloadBackgroundMusic("background.ogg");
	audio->preloadEffect("jump.ogg");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto logo = Sprite::create("anagram.png");
	logo->setAnchorPoint( Vec2(0.5f, 0.5f) );
	logo->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y  ) );

	this->addChild( logo , 1 );

	this->scheduleOnce( schedule_selector( SplashScene::gotoScene ), 4.0f );

    return true;
}

void SplashScene::gotoScene( float dt )
{
	auto scene = StartScene::createScene();

	Director::getInstance()->replaceScene( TransitionFade::create( 0.3f, scene ));
}
