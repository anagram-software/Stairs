#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

	// implement the "static create()" method manually
    CREATE_FUNC(StartScene);

private:
	void gotoScene( cocos2d::Ref *sender );
	void fbShare( cocos2d::Ref *sender );

};

#endif // __START_SCENE_H__
