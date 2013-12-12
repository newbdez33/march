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
    menuItem = CCSprite::create("empty_commander.png");
    CCMenuItemSprite *commander2 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected2));
    menuItem = CCSprite::create("empty_commander.png");
    CCMenuItemSprite *commander3 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected3));
    menuItem = CCSprite::create("empty_commander.png");
    CCMenuItemSprite *commander4 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected4));
    menuItem = CCSprite::create("empty_commander.png");
    CCMenuItemSprite *commander5 = CCMenuItemSprite::create(menuItem, menuItem, this, menu_selector(CommanderLayer::commanderSelected5));
    
    _commandersMenu = CCMenu::create(commander1, commander2, commander3, commander4, commander5, NULL);
    _commandersMenu->alignItemsHorizontallyWithPadding(0);
    //CCSize ss = CCDirector::sharedDirector()->getWinSize();
    _commandersMenu->setPosition(_commandersMenu->boundingBox().size.width/2, BOX_WIDTH/2);
    this->addChild(_commandersMenu,kForeground);
}

void CommanderLayer::toggleTroopsMenu() {
    
    if(_commandersMenu->getPosition().y==BOX_WIDTH/2) {
        _commandersMenu->setPosition(ccp(_commandersMenu->getPosition().x, BOX_WIDTH/2 + BOX_WIDTH));
    }else {
        _commandersMenu->setPosition(ccp(_commandersMenu->getPosition().x, BOX_WIDTH/2));
    }
    
    //TODO show troops
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