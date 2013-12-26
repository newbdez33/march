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

using namespace cocos2d;

class TroopSprite : public CCSprite {
private:
    int _kind;
public:
    
    CC_SYNTHESIZE(int, status, Status);
    
    ~TroopSprite(void);
    TroopSprite(int akind);

	static TroopSprite* create(int akind);
    void initTroop();

};

#endif /* defined(__marchinggame__TroopSprite__) */
