#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CommanderLayer.h"

using namespace cocos2d;

class BattleField : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void adjustViewBoundingPosition(CCPoint newPos);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BattleField);
    
    CCSize _screenSize;
    
    CommanderLayer *commanderLayer;
    
    cocos2d::CCTMXTiledMap* _tileMap;
    cocos2d::CCTMXLayer* _background;
    
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

};

#endif // __HELLOWORLD_SCENE_H__
