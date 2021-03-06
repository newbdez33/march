//
//  CommanderLayer.h
//  marchinggame
//
//  Created by Jack on 12/12/2013.
//
//

#ifndef __marchinggame__CommanderLayer__
#define __marchinggame__CommanderLayer__

#include "cocos2d.h"

using namespace cocos2d;

class BattleField;

class CommanderLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void buildCommandMenu();
    void troopSelected(CCMenuItemSprite *troopMenu);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(CommanderLayer);
    
    CCMenu * _supportMenu;
    CCMenu * _troopMenu;
    CC_SYNTHESIZE(BattleField *, _battleField, BattleField);
    
};

#endif /* defined(__marchinggame__CommanderLayer__) */
