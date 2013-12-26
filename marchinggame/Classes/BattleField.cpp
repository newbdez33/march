#include "BattleField.h"
#include "SimpleAudioEngine.h"
#include "TroopSprite.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define TANK_PACE   10  //临时定义，每秒单位距离

CCScene* BattleField::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BattleField *layer = BattleField::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    CommanderLayer *cl = CommanderLayer::create();
    scene->addChild(cl);
    layer->commanderLayer = cl;

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BattleField::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("screen hegith: %f", _screenSize.height);
    _battleFieldY = SCREEN_SPLIT_Y;
    
    _troops = CCArray::createWithCapacity(5);
    _troops->retain();
    
    _tileMap = CCTMXTiledMap::create("tilemap.tmx");
    _background = _tileMap->layerNamed("background");
    _tileMap->setPosition(ccp(0, _battleFieldY));
    this->addChild(_tileMap, kBackground);
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleField::troopSend), "TROOP_REQUEST", NULL);
    
    this->scheduleUpdate();
    
    return true;
}

void BattleField::troopSend(cocos2d::CCSprite *troop) {
    //CCLog("%p", troop);
    //TODO action应该根据troop类型，集成在troop类里面，在这里直接调就行
    //比如 troop->go(), troop->stop(), troop->glow();
    _troops->addObject(troop);
//    CCFiniteTimeAction* move = CCSequence::create(CCMoveTo::create(120, ccp(troop->getPosition().x, _tileMap->boundingBox().size.height+BOX_WIDTH)), CCCallFuncN::create(this, callfuncN_selector(BattleField::troopDismiss)), NULL);
//    troop->runAction(move);
    this->addChild(troop, kMiddleground);
}

void BattleField::troopDismiss(cocos2d::CCNode *sender) {
    CCSprite *troop = (CCSprite *)sender;
    troop->removeFromParent();
    _troops->removeObject(troop);
}

void BattleField::adjustViewBoundingPosition(cocos2d::CCPoint newPos) {
    
    newPos.x = 0;
    newPos.y = MIN(0, newPos.y);
    newPos.y = MAX(newPos.y, _screenSize.height - _tileMap->boundingBox().size.height - _battleFieldY);
    this->setPosition(newPos);
}

BattleField::~BattleField() {
    CC_SAFE_RELEASE(_troops);
}

#pragma mark - Touch Events
void BattleField::xtTouchesBegan(cocos2d::CCSet *_touches, cocos2d::CCEvent *event) {
    
//    CCTouch *pTouch = (CCTouch *)_touches->anyObject();
//    CCPoint location = pTouch->getLocationInView();
//    location = CCDirector::sharedDirector()->convertToGL( location );
//    for (int i=0; i<_troops->count(); i++) {
//        TroopSprite *troop = (TroopSprite *)_troops->objectAtIndex(i);
//        if (troop->boundingBox().containsPoint(location)) {
//            troop->setDirection(kDirectionHold);
//            _touchedTroop = troop;
//            return;
//        }
//    }
    
//    _touchedTroop = NULL;
    return;

}

void BattleField::xtTouchesMoved(cocos2d::CCSet *_touches, cocos2d::CCEvent *event) {

    if (_touchedTroop!=NULL) {
        return;
    }
    CCTouch *pTouch = (CCTouch *)_touches->anyObject();
    CCPoint loc = this->convertTouchToNodeSpace(pTouch);
    
    CCPoint prevoiusLoc = pTouch->getPreviousLocationInView();
    
    //屏幕坐标变成GL坐标
    prevoiusLoc = CCDirector::sharedDirector()->convertToGL(prevoiusLoc);
    //然后转成layer相对坐标
    prevoiusLoc = this->convertToNodeSpace(prevoiusLoc);
    
    CCPoint translation = ccpSub(loc, prevoiusLoc);
    CCPoint next = ccpAdd(this->getPosition(), translation);
    
    this->adjustViewBoundingPosition(next);
}

void BattleField::xtSwipeGesture(XTLayer::XTTouchDirection direction, float distance, float speed) {

//    if (_touchedTroop==NULL) {
//        return;
//    }
//    
//    CCLog("SWIP");
//    if (direction==DOWN) {
//        CCLog("DOWN");
//        _touchedTroop->setDirection(kDirectionUp);
//    }else if (direction==UP) {
//        CCLog("UP");
//
//        _touchedTroop->setDirection(kDirectionDown);
//    }else {
//        CCLog("L or R");
//    }
}

#pragma mark - Cocos2d Events
void BattleField::update(float dt) {
    
    for(int i=0; i<_troops->count(); i++) {
        TroopSprite *troop = (TroopSprite *)_troops->objectAtIndex(i);
        if(troop->getStatus()==kStatusForward) {
            troop->setPositionY(troop->getPositionY()+dt*TANK_PACE);
        }else if(troop->getStatus()==kStatusAttack) {
            //
        }
    }
    
}

