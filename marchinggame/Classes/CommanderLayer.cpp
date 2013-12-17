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
            TroopSprite *troopSend = TroopSprite::create(kind);
            troopSend->initTroop();
            troopSend->setDirection(kDirectionUp);
            troopSend->retain();
            troop->setUserData(troopSend);
            troopMenuItems->addObject(troop);
            
            //控制上下运动
            menuItem = CCSprite::create("up_btn.png");
            CCMenuItemSprite *up = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::moveControl));
            up->setTag(kDirectionUp);
            up->setUserData(troopSend);
            menuItem = CCSprite::create("down_btn.png");
            CCMenuItemSprite *down = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::moveControl));
            down->setTag(kDirectionDown);
            down->setUserData(troopSend);
            
            CCMenu *moveControlMenu = CCMenu::create(up, down, NULL);
            moveControlMenu->alignItemsVerticallyWithPadding(25);
            moveControlMenu->setPosition(ccp(troop->boundingBox().size.width/2, troop->boundingBox().size.height/2));
            moveControlMenu->setTag(TAG_MOVE_CONTROL_MENU);  //方便拿到
            moveControlMenu->setVisible(false);
            troop->addChild(moveControlMenu);
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

void CommanderLayer::moveControl(CCMenuItemSprite *item) {
    int direction = item->getTag();
    TroopSprite *t = (TroopSprite *)item->getUserData();
    t->setDirection(direction);
}

void CommanderLayer::troopSelected(CCMenuItemSprite *troopMenu) {
    
    TroopSprite *troopSend = (TroopSprite *)troopMenu->getUserData();
    
    if(troopSend->getParent()!=NULL) {
        //已经送出去了, 这里控制
        troopSend->setDirection(kDirectionHold);
    }else {
        troopSend->setPosition(ccp(BOX_WIDTH/2 + _currentCommanderIdx*BOX_WIDTH , SCREEN_SPLIT_Y)); //y - BOX_WIDTH/2
        CCNotificationCenter::sharedNotificationCenter()->postNotification("TROOP_REQUEST", troopSend);
        
        //添加控制按钮
        CCMenu *control = (CCMenu *)troopMenu->getChildByTag(TAG_MOVE_CONTROL_MENU);
        control->setVisible(true);
    }

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

