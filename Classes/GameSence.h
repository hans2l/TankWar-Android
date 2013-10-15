//
//  GameSence.h
//  TankWar
//
//  Created by user on 13-9-3.
//
//

#ifndef __TankWar__GameSence__
#define __TankWar__GameSence__

#include <iostream>
#include "cocos2d.h"

#include "MapLayer.h"
#include "ControlLayer.h"

class GameScene : public cocos2d::CCScene
{
public:
    CREATE_FUNC(GameScene);
    ~GameScene();
    
    bool init();
    
    void initWithMapInformation(int leve,int status ,int life);
    
    void showLife(int numLife);
    
    void showLeve(int inLeve);
    
private:
    MapLayer *_mapLayer;
    ControlLayer *_conLayer;
    
    CCLabelTTF* _1plifeString;
    CCLabelTTF* _leveString;
    CCLabelTTF* _robotLifeString;
};

#endif /* defined(__TankWar__GameSence__) */
