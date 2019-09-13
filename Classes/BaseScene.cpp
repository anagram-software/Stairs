#include "BaseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene*BaseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = BaseScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BaseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _txtStat = Label::createWithTTF("", "RobotoLight.ttf", 15);
    _txtStat->setAnchorPoint(Vec2(0.0f, 0.0f));
    _txtStat->setPosition(Vec2(200.0f, 30.0f));
    this->addChild(_txtStat);

    _txtConnection = Label::createWithTTF("", "RobotoLight.ttf", 15);
    _txtConnection->setAnchorPoint(Vec2(0.0f, 0.0f));
    _txtConnection->setPosition(Vec2(visibleSize.width - 200.0f, 65.0f));
    this->addChild(_txtConnection);

    return true;
}
