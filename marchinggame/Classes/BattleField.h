#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CommanderLayer.h"
#include "XTLayer.h"

using namespace cocos2d;

class BattleField : public XTLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    ~BattleField();
    
    CCArray *_troops;
    CCSprite *_touchedTroop;
    
    void adjustViewBoundingPosition(CCPoint newPos);
    void troopSend(CCSprite*);
    void troopDismiss(cocos2d::CCNode *sender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BattleField);
    
    CCSize _screenSize;
    float _battleFieldY;
    
    CommanderLayer *commanderLayer;
    
    cocos2d::CCTMXTiledMap* _tileMap;
    cocos2d::CCTMXLayer* _background;
    
//    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    //XTLayer
    virtual void xtTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    virtual void xtTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    virtual void xtSwipeGesture(XTTouchDirection direction, float distance, float speed);

};

#endif // __HELLOWORLD_SCENE_H__
