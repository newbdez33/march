//
//  CommanderLayer.cpp
//  marchinggame
//
//  Created by Jack on 12/12/2013.
//
//

#include "CommanderLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool CommanderLayer::init() {
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->buildCommanderMenu();
    
    return true;
}

void CommanderLayer::buildCommanderMenu() {
    
    CCSprite * menuItem;
    menuItem = CCSprite::create("commander1.png");
    CCMenuItemSprite *commander1 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected1));
    menuItem = CCSprite::create("commander2.png");
    CCMenuItemSprite *commander2 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected2));
    menuItem = CCSprite::create("commander3.png");
    CCMenuItemSprite *commander3 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected3));
    menuItem = CCSprite::create("commander4.png");
    CCMenuItemSprite *commander4 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected4));
    menuItem = CCSprite::create("commander5.png");
    CCMenuItemSprite *commander5 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected5));
    
    _commandersMenu = CCMenu::create(commander1, commander2, commander3, commander4, commander5, NULL);
    _commandersMenu->alignItemsHorizontallyWithPadding(0);
    //CCSize ss = CCDirector::sharedDirector()->getWinSize();
    _commandersMenu->setPosition(_commandersMenu->boundingBox().size.width/2, SCREEN_SPLIT_Y - menuItem->boundingBox().size.height/2);
    this->addChild(_commandersMenu,kForeground);
    
    //Troops menu
    menuItem = CCSprite::create("troop_menu_1.png");
    CCMenuItemSprite *troop1 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::troopSelected));
    menuItem = CCSprite::create("troop_menu_2.png");
    CCMenuItemSprite *troop2 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::troopSelected));
    menuItem = CCSprite::create("troop_menu_3.png");
    CCMenuItemSprite *troop3 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::troopSelected));
    menuItem = CCSprite::create("troop_menu_4.png");
    CCMenuItemSprite *troop4 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::troopSelected));
    _troopsMenu = CCMenu::create(troop1, troop2, troop3, troop4, NULL);
    _troopsMenu->alignItemsHorizontallyWithPadding(0);
    _troopsMenu->setPosition(_troopsMenu->boundingBox().size.width/2, troop1->boundingBox().size.height/2);
    _troopsMenu->setVisible(true);
    this->addChild(_troopsMenu, kMiddleground);
}

void CommanderLayer::troopSelected() {
    
    CCSprite *tank = CCSprite::create("troop1_sent.png");
    tank->setPosition(ccp(BOX_WIDTH/2, BOX_WIDTH/2 + BOX_WIDTH));
    CCNotificationCenter::sharedNotificationCenter()->postNotification("TROOP_REQUEST", tank);

}

void CommanderLayer::toggleTroopsMenu() {
    
    //_troopsMenu->setVisible(true);
    
}

void CommanderLayer::commanderSelected1() {
    this->toggleTroopsMenu();
    CCLog("commanderSelected1");
}
void CommanderLayer::commanderSelected2() {
    CCLog("commanderSelected1");
}
void CommanderLayer::commanderSelected3() {
    CCLog("commanderSelected1");
}
void CommanderLayer::commanderSelected4() {
    CCLog("commanderSelected1");
}
void CommanderLayer::commanderSelected5() {
    CCLog("commanderSelected1");
}