//
//  CommanderLayer.cpp
//  marchinggame
//
//  Created by Jack on 12/12/2013.
//
//

#include "CommanderLayer.h"
#include "SimpleAudioEngine.h"
#include <stdio.h>
#include "TroopSprite.h"

#define TAG_MOVE_CONTROL_MENU   1001

using namespace cocos2d;
using namespace CocosDenshion;

bool CommanderLayer::init() {
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    //背景
    CCSprite * bg = CCSprite::create("commander_bg.png");
    bg->setPosition(ccp(bg->boundingBox().size.width * 0.5f, bg->boundingBox().size.height * 0.5f));
    this->addChild(bg);
    
    //菜单
    this->buildCommandMenu();
    
    return true;
}

void CommanderLayer::buildCommandMenu() {
    
    CCSprite * menuItem;
    CCArray * troopMenuItems = CCArray::createWithCapacity(4);
    for(int i=0; i<4; i++) {
        CCString *name = CCString::createWithFormat("troop%d.png", i);
        menuItem = CCSprite::create(name->getCString());
        CCMenuItemSprite *troop = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::troopSelected));
        TroopSprite *troopSend = TroopSprite::create(i);
        troopSend->initTroop();
        troopSend->setStatus(kStatusForward);
        troopSend->retain();
        troop->setUserData(troopSend);
        troopMenuItems->addObject(troop);
    }
    
    _troopMenu = CCMenu::createWithArray(troopMenuItems);
    _troopMenu->setPosition(_troopMenu->boundingBox().size.width/2, 32);
    _troopMenu->alignItemsHorizontallyWithPadding(5);
    this->addChild(_troopMenu,kForeground);
    
}

void CommanderLayer::troopSelected(CCMenuItemSprite *troopMenu) {
    
    TroopSprite *troopSend = (TroopSprite *)troopMenu->getUserData();
    
    if(troopSend->getParent()!=NULL) {
        //已经送出去了, 这里控制
        troopSend->setStatus(kStatusForward);
    }else {
        int p = (arc4random()%5);   //随机位置出现
        troopSend->setPosition(ccp(BOX_WIDTH/2 + p*BOX_WIDTH , SCREEN_SPLIT_Y)); //y - BOX_WIDTH/2
        CCNotificationCenter::sharedNotificationCenter()->postNotification("TROOP_REQUEST", troopSend);
    }

}

