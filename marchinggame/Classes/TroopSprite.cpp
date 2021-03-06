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
    _speed = 50;
    _fireTimer = 0;
    _holdTimer = 0;
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
    
    CCString *name = CCString::createWithFormat("troop%d.png", _type);
    //this->initWithSpriteFrameName(name->getCString());
    this->initWithFile(name->getCString());

    //box2d
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    
    _body = _battleField->getWorld()->CreateBody(&bodyDef);
    _body->SetSleepingAllowed(true);
    _body->SetLinearDamping(1.2);
    _body->SetAngularDamping(0.8);
    
    b2CircleShape circle;
    circle.m_radius = (this->boundingBox().size.width/2)/PTM_RATIO; //TODO 这个值要调整
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 5;
    fixtureDef.restitution = 0;
    fixtureDef.friction = 10;
    fixtureDef.filter.categoryBits = 0x0010;
    
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
    
    _dt = dt;
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
    }
    
    if(this->getStatus()==kStatusHold) {
        _holdTimer += dt;
        if(_holdTimer>0.1) {
            _holdTimer = 0;
            this->setStatus(kStatusForward);
        }
        //wiat
        return;
    }
    
    if(this->getStatus()==kStatusForward) {
        
        //先检查视野范围内有没有敌军
        if (this->radarRangeCheck(_battleField->getEnemyBase()->getPosition())) {
            
            this->setStatus(kStatusTarget);    //转为目标状态
            
        }else {
            
            //没有敌军，直线前进
            this->setPositionY(this->getPositionY()+dt*_speed);
            this->setSpritePosition(this->getPosition());
            
        }
        
        return;
    }
        
    this->rotateToTarget(this->getBattleField()->getEnemyBase()->getPosition());
    
    if(this->getStatus()==kStatusTarget) {
    
        if (this->attachRangeCheck(_battleField->getEnemyBase()->getPosition())) {
            this->setStatus(kStatusAttack);
        }else {
            //这里锁定目标后走斜线
            CCPoint position = this->getPosition();
            position.x += _vector.x * dt;
            position.y += _vector.y * dt;
            this->setSpritePosition(position);
        }
        
    } else {
        //Attack
        _fireTimer += _dt;
        if(_fireTimer>1) {
            _fireTimer = 0;
            this->fireTarget(this->getBattleField()->getEnemyBase()->getPosition());
        }
    }
    
}

bool TroopSprite::radarRangeCheck(cocos2d::CCPoint p) {
    if (this->getPosition().y + _radarRange > p.y) {
        return true;
    }
    return false;
}

bool TroopSprite::attachRangeCheck(CCPoint p) {
    if (this->getPosition().y + _attachRange > p.y) {
        return true;
    }
    return false;
}

float TroopSprite::rotateToTarget(CCPoint p) {
    
    // 转向敌军, rotate动画
    CCPoint point = ccpSub(_battleField->getEnemyBase()->getPosition(), this->getPosition());
    float angleRadians = atanf((float)point.y / (float)point.x);
    float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
    float cocosAngle = angleDegrees;
    if (cocosAngle>0) {
        cocosAngle = 90 - cocosAngle;
    } else {
        cocosAngle = - (90 + cocosAngle);
    }
    
    if (this->getRotation() != cocosAngle) {
        CCLog("x:%f, y:%f, ang:%f", point.x, point.y, cocosAngle);
        CCLog("angle:%f", cocosAngle);
        //TODO 动画调头
        this->setRotation(cocosAngle);
    }
    
    //得到向量
    _vector = ccp ( _speed * cos( cocosAngle ),
                   -_speed * sin( cocosAngle ));
    
    return cocosAngle;
    
}

void TroopSprite::fireTarget(CCPoint p) {
    CCSprite *bullet = CCSprite::create("bullet.png");
    bullet->setPosition(this->getPosition());
    this->getBattleField()->addChild(bullet);
    bullet->cocos2d::CCNode::setRotation(90);
    bullet->runAction(CCMoveTo::create(0.5, p));
}

