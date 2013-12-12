#include "BattleField.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
    
    _tileMap = CCTMXTiledMap::create("tilemap.tmx");
    _background = _tileMap->layerNamed("background");
    _tileMap->setPosition(ccp(0, BOX_WIDTH));
    this->addChild(_tileMap, kBackground);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    return true;
}

#pragma mark - Touch Events
bool BattleField::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void BattleField::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
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

void BattleField::adjustViewBoundingPosition(cocos2d::CCPoint newPos) {
    
    newPos.x = 0;
    newPos.y = MIN(0, newPos.y);
    newPos.y = MAX(newPos.y, _screenSize.height - _tileMap->boundingBox().size.height - BOX_WIDTH);
    this->setPosition(newPos);
}
