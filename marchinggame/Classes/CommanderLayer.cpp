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

using namespace cocos2d;
using namespace CocosDenshion;

bool CommanderLayer::init() {
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _currentTroopsMenu = NULL;
    _currentCommanderIdx = -1;
    _channelSelected = CCSprite::create("channel_selected.png");
    _channelSelected->setVisible(false);
    this->addChild(_channelSelected);
    this->buildCommanderMenu();
    
    return true;
}

void CommanderLayer::buildCommanderMenu() {
    
    CCSprite * menuItem;
    CCArray * commanderMenuItems = CCArray::createWithCapacity(5);
    for(int i=0; i<5; i++) {
        menuItem = CCSprite::create(CCString::createWithFormat("commander%d.png", i)->getCString());
        CCMenuItemSprite *commander = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected));
        commander->setTag(i);
        CCArray *troopMenuItems = CCArray::create();
        for(int i=0; i<4; i++) {
            int kind = (arc4random()%4);
            CCString *name = CCString::createWithFormat("troop_menu_%d.png", kind);
            menuItem = CCSprite::create(name->getCString());
            CCMenuItemSprite *troop = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::troopSelected));
            troop->setTag(kind);
            troopMenuItems->addObject(troop);
        }
        CCMenu *troopsMenu = CCMenu::createWithArray(troopMenuItems);
        troopsMenu->alignItemsHorizontallyWithPadding(0);
        commander->setUserData(troopsMenu);
        troopsMenu->retain();
        
        commanderMenuItems->addObject(commander);
    }
    
    _commandersMenu = CCMenu::createWithArray(commanderMenuItems);
    _commandersMenu->alignItemsHorizontallyWithPadding(0);
    _commandersMenu->setPosition(_commandersMenu->boundingBox().size.width/2, SCREEN_SPLIT_Y - 64);
    this->addChild(_commandersMenu,kForeground);

}

void CommanderLayer::troopSelected(CCMenuItemSprite *troopMenu) {
    
    int kind = troopMenu->getTag();
    CCSprite *troop = CCSprite::create(CCString::createWithFormat("troop%d.png", kind)->getCString());
    troop->setPosition(ccp(BOX_WIDTH/2 + _currentCommanderIdx*BOX_WIDTH , SCREEN_SPLIT_Y));
    CCNotificationCenter::sharedNotificationCenter()->postNotification("TROOP_REQUEST", troop);

}

void CommanderLayer::commanderSelected(CCMenuItemSprite *m) {
    
    if(_currentTroopsMenu!=NULL) {
        _currentTroopsMenu->removeFromParent();
    }
    
    _currentCommanderIdx = m->getTag();
    _channelSelected->setPosition(ccp(BOX_WIDTH*(_currentCommanderIdx+1)-_channelSelected->boundingBox().size.width/2, SCREEN_SPLIT_Y));
    _channelSelected->setVisible(true);

    CCMenu *troopsMenu = (CCMenu *)m->getUserData();
    _currentTroopsMenu = troopsMenu;
    troopsMenu->setPosition(troopsMenu->boundingBox().size.width/2, 32);
    this->addChild(troopsMenu, kMiddleground);
}

