//
//  TroopSprite.h
//  marchinggame
//
//  Created by Jack on 13/12/2013.
//
//

#ifndef __marchinggame__TroopSprite__
#define __marchinggame__TroopSprite__

#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;
class BattleField;

class TroopSprite : public CCSprite {
private:
    CCPoint _startPosition;
    float _radarRange;
    float _attachRange;
    float _speed;
    float _dt;
    float _holdTimer;
    float _fireTimer;
    
public:
    
    CC_SYNTHESIZE(int, _status, Status);
    CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(int, _type, Type);
    CC_SYNTHESIZE(BattleField *, _battleField, BattleField);
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    
    ~TroopSprite(void);
    TroopSprite(BattleField * bf, int akind, CCPoint position);

	static TroopSprite* create(BattleField * bf, int akind, CCPoint position);
    void initTroop();
    virtual void update(float dt);
    virtual void setSpritePosition (CCPoint position);
    bool radarRangeCheck(CCPoint p);
    bool attachRangeCheck(CCPoint p);
    float rotateToTarget(CCPoint p);
    void fireTarget(CCPoint p);

};

#endif /* defined(__marchinggame__TroopSprite__) */
