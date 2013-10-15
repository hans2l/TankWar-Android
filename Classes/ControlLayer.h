//
//  ControlLayer.h
//  TankWar
//
//  Created by user on 13-9-4.
//
//

#ifndef __TankWar__ControlLayer__
#define __TankWar__ControlLayer__

#include <iostream>
#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "MapLayer.h"
#include "TankSprite.h"

class ControlLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(ControlLayer);
    virtual bool init();

    MapLayer *_mapLayer;
protected:
    SneakyJoystick* _joystick;
    SneakyButton* _fireButton;
    
    void addJoystick(void);
    void update(float t);
    void addFireButton(void);
};

#endif /* defined(__TankWar__ControlLayer__) */
