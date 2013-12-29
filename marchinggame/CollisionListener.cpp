//
//  CollisionListener.cpp
//  MiniPool
//
//  Created by Roger Engelbert on 1/14/13.
//
//

#include "CollisionListener.h"
#include "BattleFieldLayer.h"
#include "SimpleAudioEngine.h"
#include "TroopSprite.h"

using namespace CocosDenshion;

void CollisionListener::BeginContact(b2Contact* contact) {
//    b2Body * bodyA = contact->GetFixtureA()->GetBody();
//    b2Body * bodyB = contact->GetFixtureB()->GetBody();
//    
//    TroopSprite * spriteA = (TroopSprite *) bodyA->GetUserData();
//    TroopSprite * spriteB = (TroopSprite *) bodyB->GetUserData();
//    
    
}


void CollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)  {
    
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();
    
    TroopSprite * spriteA = (TroopSprite *) bodyA->GetUserData();
    TroopSprite * spriteB = (TroopSprite *) bodyB->GetUserData();
    
        
    if (spriteA && spriteB) {
        
        TroopSprite *blockedOne = (spriteA->getPosition().y < spriteB->getPosition().y)?spriteA:spriteB;
        blockedOne->setStatus(kStatusHold);
    
    }
    
}

