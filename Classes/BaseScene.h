#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class BaseScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

    // implement the "static create()" method manually
    CREATE_FUNC(BaseScene);

    void updateConnectionStatus();

protected:
    cocos2d::Label * _txtConnection;
    cocos2d::Label * _txtStat;

    void onConnect(cocos2d::Ref *sender);
};

#endif // __HELLOWORLD_SCENE_H__

