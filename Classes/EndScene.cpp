#include "EndScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

int score;
int failType;

cocos2d::Scene *EndScene::createScene( int tempscore, int tempfailType )
{
	score = tempscore;
	failType = tempfailType;

    // 'scene' is an autorelease object
	auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = EndScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    //init audio
    auto audio = SimpleAudioEngine::getInstance();

    // set the background music and continuously play it.
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("background.ogg", true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto failText = Label::createWithTTF("", "FredokaOne.ttf", 56);
	failText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	failText->setColor( Color3B(255,255,255));
	failText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	failText->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height + origin.y - 110.0f ) );
	if (failType == 1)
	{
		failText->setString("Time's Up");
	}else if (failType == 0) {
		failText->setString("Oops...");
	}

	this->addChild( failText , 2 );

	auto scoreText = Label::createWithTTF(__String::createWithFormat( "%i", score )->getCString(), "FredokaOne.ttf", 196);
	scoreText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	scoreText->setColor( Color3B(255, 255, 255));
	scoreText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	scoreText->setPosition( Vec2(visibleSize.width/2 + origin.x, failText->getPositionY() - 230.0f));

	this->addChild( scoreText , 2 );

	auto highScoreText = Label::createWithTTF( "", "FredokaOne.ttf", 48);
	highScoreText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	highScoreText->setColor( Color3B(255,255,255));
	highScoreText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	highScoreText->setPosition( Vec2(scoreText->getPositionX() , scoreText->getPositionY() - 250.0f ));

	this->addChild( highScoreText , 2 );

	auto restartButton = MenuItemImage::create( "retry.png", "retryOver.png", CC_CALLBACK_1( EndScene::gotoScene, this ));
	restartButton->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 270.0f ) );

	auto soundButton = MenuItemSprite::create( Sprite::create("soundOn.png"), Sprite::create("soundOff.png"), CC_CALLBACK_1( EndScene::toggleSounds, this ));
	soundButton->setPosition( Vec2( visibleSize.width/2 + origin.x, restartButton->getPositionY() - 120.0f ) );

	auto menu = Menu::create( restartButton, soundButton, nullptr );
	menu->setPosition( Vec2( 0, 0 ) );

	this->addChild(menu, 0);

	UserDefault *def = UserDefault::getInstance();

	auto highscore = def->getIntegerForKey( "HIGHSCORE", 0 );

	if (highscore < score)
	{
		highscore = score;
		def->setIntegerForKey( "HIGHSCORE", highscore);
		highScoreText->setString("NEW BEST");
	}else{
		highScoreText->setString( __String::createWithFormat( "%s %i", "BEST\n", highscore )->getCString());
	}

	auto sounds = def->getBoolForKey( "SOUNDS",  true );

	if ( sounds )
	{
		audio->setBackgroundMusicVolume(1.0f);
		audio->setEffectsVolume(1.0f);
		soundButton->setNormalImage(Sprite::create("soundOn.png"));
		soundButton->setSelectedImage(Sprite::create("soundOff.png"));
	}else{
		audio->setBackgroundMusicVolume(0.0f);
		audio->setEffectsVolume(0.0f);
		soundButton->setNormalImage(Sprite::create("soundOff.png"));
		soundButton->setSelectedImage(Sprite::create("soundOn.png"));
	}

	def->flush();

    return true;
}

void EndScene::gotoScene( cocos2d::Ref *sender )
{
	//init audio
	auto audio = SimpleAudioEngine::getInstance();

	// play jump music
	audio->playEffect("click.ogg");

	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene( TransitionFade::create( 0.3f, scene ));
}

void EndScene::toggleSounds( cocos2d::Ref *sender )
{
	UserDefault *def = UserDefault::getInstance();

	//init audio
	auto audio = SimpleAudioEngine::getInstance();

	// play jump music
	audio->playEffect("click.ogg");

	auto sounds = def->getBoolForKey( "SOUNDS",  true );

	auto const soundButton = dynamic_cast <MenuItemSprite*>(sender);
	if(!soundButton) {return;}

	if ( sounds )
	{
		audio->setBackgroundMusicVolume(0.0f);
		audio->setEffectsVolume(0.0f);
		soundButton->setNormalImage(Sprite::create("soundOff.png"));
		soundButton->setSelectedImage(Sprite::create("soundOn.png"));
		def->setBoolForKey( "SOUNDS", false );
	}else{
		audio->setBackgroundMusicVolume(1.0f);
		audio->setEffectsVolume(1.0f);
		soundButton->setNormalImage(Sprite::create("soundOn.png"));
		soundButton->setSelectedImage(Sprite::create("soundOff.png"));
		def->setBoolForKey( "SOUNDS", true );
	}

	def->flush();
}
