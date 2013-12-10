#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GamePlay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GamePlay *layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
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
    _tileMap->setPosition(ccp(0, 0));
    this->addChild(_tileMap, kBackground);
    
    return true;
}
