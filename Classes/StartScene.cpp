#include "StartScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

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
    if ( !Layer::init() )
    {
        return false;
    }

    //init audio
    auto audio = SimpleAudioEngine::getInstance();

    // set the background music and continuously play it.
    audio->playBackgroundMusic("background.ogg", true);

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

    auto logoText = Label::createWithTTF(__String::createWithFormat( "STAIRS" )->getCString(), "FredokaOne.ttf", 120);
	logoText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	logoText->setColor( Color3B(255, 255, 255));
	logoText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	logoText->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 250.0f ) );

	this->addChild( logoText , 1 );

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

	//init audio
	auto audio = SimpleAudioEngine::getInstance();

	// play jump music
	audio->playEffect("click.ogg");

	Director::getInstance()->replaceScene( TransitionFade::create( 0.3f, scene ));
}