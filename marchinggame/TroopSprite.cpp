//
//  TroopSprite.cpp
//  marchinggame
//
//  Created by Jack on 13/12/2013.
//
//

#include "TroopSprite.h"

TroopSprite::TroopSprite(int akind) {
    _kind = akind;
}

TroopSprite::~TroopSprite() {
    
}

TroopSprite * TroopSprite::create(int akind) {
    
    TroopSprite *sprite = new TroopSprite(akind);
    if(sprite) {
        sprite->initTroop();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_RELEASE(sprite);
    return NULL;
}

void TroopSprite::initTroop() {
    CCString *name = CCString::createWithFormat("troop%d.png", _kind);
    //this->initWithSpriteFrameName(name->getCString());
    this->initWithFile(name->getCString());
}