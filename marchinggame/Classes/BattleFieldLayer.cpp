#include "BattleFieldLayer.h"
#include "SimpleAudioEngine.h"
#include "TroopSprite.h"
#include "Box2D.h"
#include "CollisionListener.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define DEBUG_DRAW  0

CCScene* BattleField::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    BattleField *layer = BattleField::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->_commanderLayer = CommanderLayer::create();
    layer->_commanderLayer->setBattleField(layer);
    scene->addChild(layer->_commanderLayer);
    
    layer->release();
    
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
    if (DEBUG_DRAW) {
        _tileMap->setVisible(false);
    }
    
    _enemyBase = CCSprite::create("down_btn.png");
    _enemyBase->setPosition(ccp(_screenSize.width/2, _tileMap->boundingBox().size.height + _battleFieldY - _enemyBase->boundingBox().size.height));
    this->addChild(_enemyBase, kMiddleground);
    
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    this->setTouchEnabled(true);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleField::troopSend), "TROOP_REQUEST", NULL);
    
    this->scheduleUpdate();
    
    this->initPhysics();
    
    return true;
}

void BattleField::initPhysics() {
    
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);    //真空呀，哥们
    _world = new b2World(gravity);
    _world->SetAllowSleeping(false); //if not moving then not generationg derived data(skip checking for derived data from objects)
    _world->SetContinuousPhysics(true); //连续检查碰撞
    _collisionListener = new CollisionListener();
    _world->SetContactListener(_collisionListener);
    
    //create table sides
    b2BodyDef tableBodyDef;
    tableBodyDef.position.Set(0, 0);
    b2Body* tableBody = _world->CreateBody(&tableBodyDef);
    
    // Define the table edges
    b2EdgeShape tableBox;
    
    // top
    tableBox.Set(b2Vec2(0, (_tileMap->boundingBox().size.height + _battleFieldY) * 0.99f/PTM_RATIO),
                 b2Vec2(_tileMap->boundingBox().size.width/PTM_RATIO, (_tileMap->boundingBox().size.height + _battleFieldY) * 0.99f/PTM_RATIO));
    tableBody->CreateFixture(&tableBox,0);

    
    m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    _world->SetDebugDraw(m_debugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    m_debugDraw->SetFlags(flags);
    
}

void BattleField::troopSend(cocos2d::CCSprite *troop) {
    //CCLog("%p", troop);
    //TODO action应该根据troop类型，集成在troop类里面，在这里直接调就行
    //比如 troop->go(), troop->stop(), troop->glow();
    _troops->addObject(troop);
//    CCFiniteTimeAction* move = CCSequence::create(CCMoveTo::create(120, ccp(troop->getPosition().x, _tileMap->boundingBox().size.height+BOX_WIDTH)), CCCallFuncN::create(this, callfuncN_selector(BattleField::troopDismiss)), NULL);
//    troop->runAction(move);
    this->addChild(troop, kMiddleground);
    if (DEBUG_DRAW) {
        troop->setVisible(false);
    }

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
    delete _world;
    _world = NULL;
    delete m_debugDraw;
    m_debugDraw = NULL;
}

#pragma mark - Touch Events
void BattleField::xtTouchesBegan(cocos2d::CCSet *_touches, cocos2d::CCEvent *event) {
    
//    CCTouch *pTouch = (CCTouch *)_touches->anyObject();
//    CCPoint location = pTouch->getLocationInView();
//    location = CCDirector::sharedDirector()->convertToGL( location );
//    for (int i=0; i<_troops->count(); i++) {
//        TroopSprite *troop = (TroopSprite *)_troops->objectAtIndex(i);
//        if (troop->boundingBox().containsPoint(location)) {
//            if (troop->getStatus()==kStatusAttack) {
//                troop->setStatus(kStatusForward);
//            }else {
//                troop->setStatus(kStatusAttack);
//            }
//            
//            _touchedTroop = troop;
//            return;
//        }
//    }
    
    _touchedTroop = NULL;
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
void BattleField::draw() {
    
    CCLayer::draw();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    _world->DrawDebugData();
    
    kmGLPopMatrix();
    
}

void BattleField::update(float dt) {
    
    _world->Step(dt, 1, 1);
    
    for(int i=0; i<_troops->count(); i++) {
        TroopSprite *troop = (TroopSprite *)_troops->objectAtIndex(i);
        troop->update(dt);
    }
    
}

