#include "EndScene.h"
#include "GameScene.h"

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
    if ( !BaseScene::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto failText = Label::createWithTTF("", "RobotoLight.ttf", 56);
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

	auto scoreBack = Sprite::create("scoreBack.png");
	scoreBack->setAnchorPoint( Vec2(0.5f, 0.5f) );
	scoreBack->setPosition( Vec2( visibleSize.width/2 + origin.x, failText->getPositionY() - 230.0f ) );

	this->addChild( scoreBack , 1 );

	auto scoreText = Label::createWithTTF(__String::createWithFormat( "%i", score )->getCString(), "RobotoLight.ttf", 140);
	scoreText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	scoreText->setColor( Color3B(0,0,0));
	scoreText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	scoreText->setPosition( Vec2(scoreBack->getPositionX() - 5.0f , scoreBack->getPositionY()));

	this->addChild( scoreText , 2 );

	auto highScoreText = Label::createWithTTF( "", "RobotoLight.ttf", 48);
	highScoreText->setAlignment( TextHAlignment::CENTER, TextVAlignment::CENTER);
	highScoreText->setColor( Color3B(255,255,255));
	highScoreText->setAnchorPoint( Vec2(0.5f, 0.5f) );
	highScoreText->setPosition( Vec2(scoreBack->getPositionX() , scoreBack->getPositionY() - 250.0f ));

	this->addChild( highScoreText , 2 );

	UserDefault *def = UserDefault::getInstance();

	auto highscore = def->getIntegerForKey( "HIGHSCORE", 0 );

	if (highscore < score)
	{
		highscore = score;

		def->setIntegerForKey( "HIGHSCORE", highscore);
		highScoreText->setString("NEW BEST");
	}else{
		highScoreText->setString(__String::createWithFormat( "%i", highscore )->getCString());
	}

	def->flush();

	auto restartButton = MenuItemImage::create( "retry.png", "retryOver.png", CC_CALLBACK_1( EndScene::gotoScene, this ));
	restartButton->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 300.0f ) );

	auto menu = Menu::create( restartButton, nullptr );
	menu->setPosition( Vec2( 0, 0 ) );

	this->addChild(menu, 0);

    return true;
}

void EndScene::gotoScene( cocos2d::Ref *sender )
{
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene( TransitionFade::create( 0.3f, scene ));
}