#ifndef __END_SCENE_H__
#define __END_SCENE_H__

#include "BaseScene.h"

class EndScene : public BaseScene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene( int tempscore, int tempfailType );

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;

	// implement the "static create()" method manually
    CREATE_FUNC(EndScene);

private:
	void gotoScene( cocos2d::Ref *sender );

};

#endif // __END_SCENE_H__
