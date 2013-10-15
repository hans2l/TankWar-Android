//
//  EnemySprite.h
//  TankWar
//
//  Created by user on 13-9-7.
//
//

#ifndef __TankWar__EnemySprite__
#define __TankWar__EnemySprite__

#include <iostream>
#include "cocos2d.h"
#include "TankSprite.h"

USING_NS_CC;

class EnemySprite : public TankSprite{
public:
	EnemySprite(){}
    CREATE_FUNC(EnemySprite);
    virtual ~EnemySprite(void){}
    
    virtual bool init();
    void initWithKind(int Kind);
    
    void stopTankAction();
    void removeSelfFromMap();
    bool checkTank();
    
    void initAction();
    void doRandomAction();
    void KeepMove();
    void rodmoFire();
    
    void onFire();
    void fire(CCSprite* buttle, TankAction buttleOrientation);
    
    void makeCanFire();
    
    void checkBang();
    TankSprite* _tank;
protected:
    int _score;
};
#endif /* defined(__TankWar__EnemySprite__) */
