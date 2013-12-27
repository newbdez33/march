//
//  TroopSprite.cpp
//  marchinggame
//
//  Created by Jack on 13/12/2013.
//
//

#include "TroopSprite.h"
#include "BattleFieldLayer.h"

TroopSprite::TroopSprite(BattleField * bf, int akind, CCPoint position) {
    _type = akind;
    _battleField = bf;
    _status = kStatusForward;   //默认
    _startPosition = position;
    _radarRange = 200;
    _attachRange = 100;
}

TroopSprite::~TroopSprite() {
    
}

TroopSprite * TroopSprite::create(BattleField * bf, int akind, CCPoint position) {
    
    TroopSprite *sprite = new TroopSprite(bf, akind, position);
    if(sprite) {
        sprite->initTroop();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_RELEASE(sprite);
    return NULL;
}

void TroopSprite::initTroop() {

    //box2d
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    
    _body = _battleField->getWorld()->CreateBody(&bodyDef);
    _body->SetSleepingAllowed(true);
    _body->SetLinearDamping(1.2);
    _body->SetAngularDamping(0.8);
    
    b2CircleShape circle;
    circle.m_radius = 32.0f/PTM_RATIO; //TODO 这个值要调整
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 5;
    fixtureDef.restitution = 0.7;
    fixtureDef.filter.categoryBits = 0x0010;
    
    CCString *name = CCString::createWithFormat("troop%d.png", _type);
    //this->initWithSpriteFrameName(name->getCString());
    this->initWithFile(name->getCString());
    
    _body->CreateFixture(&fixtureDef);
    _body->SetUserData(this);
    
    setSpritePosition(_startPosition);
}

void TroopSprite::setSpritePosition (CCPoint position) {
    
    setPosition(position);
    
    //update box2d body if any
    if (_body) {
        _body->SetTransform(b2Vec2(
                                   position.x / PTM_RATIO,
                                   position.y/ PTM_RATIO),
                            _body->GetAngle());
    }
    
}

void TroopSprite::update(float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
        setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
    }
}

bool TroopSprite::radarRangeCheck(cocos2d::CCPoint p) {
    if (this->getPosition().y + _radarRange > p.y) {
        return true;
    }
    return false;
}

bool TroopSprite::attachRangeCheck(CCPoint p) {
    //TODO
    return false;
}
