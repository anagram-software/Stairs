#include "StartScene.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene *StartScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    // 1. super init first
    if ( !BaseScene::init() )
    {
        return false;
    }
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto logo = Sprite::create("logo.png");
	logo->setAnchorPoint( Vec2(0.5f, 0.5f) );
	logo->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 250.0f ) );

	this->addChild( logo , 1 );

	auto playButton = MenuItemImage::create( "play.png", "playOver.png", CC_CALLBACK_1( StartScene::gotoScene, this ));
	playButton->setAnchorPoint( Vec2(0.5f, 0.5f) );
	playButton->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 250.0f) );

	auto menu = Menu::create( playButton, nullptr );
	menu->setPosition( Vec2( 0, 0 ) );

	this->addChild(menu, 0);

    return true;
}

void StartScene::gotoScene( cocos2d::Ref *sender )
{
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene( TransitionFade::create( 0.3f, scene ));
}

