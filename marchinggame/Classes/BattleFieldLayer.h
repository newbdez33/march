#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CommanderLayer.h"
#include "XTLayer.h"
#include "TroopSprite.h"
#include "GLES-Render.h"

using namespace cocos2d;

class BattleField : public XTLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    ~BattleField();
    
    void initPhysics();
    
    void adjustViewBoundingPosition(CCPoint newPos);
    void troopSend(CCSprite*);
    void troopDismiss(cocos2d::CCNode *sender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(BattleField);
    
    CC_SYNTHESIZE(b2World *, _world, World);
    CC_SYNTHESIZE(CCSprite *, _enemyBase, EnemyBase);
    
    //XTLayer
    virtual void xtTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    virtual void xtTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    virtual void xtSwipeGesture(XTTouchDirection direction, float distance, float speed);
    
    virtual void draw();
    void update (float dt);
    
private:
    
    GLESDebugDraw * m_debugDraw;
    CCArray *_troops;
    TroopSprite *_touchedTroop;
    CCSize _screenSize;
    float _battleFieldY;
    CommanderLayer *_commanderLayer;
    cocos2d::CCTMXTiledMap* _tileMap;
    cocos2d::CCTMXLayer* _background;

};

#endif // __HELLOWORLD_SCENE_H__
