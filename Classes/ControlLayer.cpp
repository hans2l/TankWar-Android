//
//  ControlLayer.cpp
//  TankWar
//
//  Created by user on 13-9-4.
//
//

#include "ControlLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool ControlLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF( ! CCLayer::init() );
        
        // 自添加代码

        this->addJoystick();
        this->addFireButton();
        // 调用系统的刷新函数
        this->scheduleUpdate();
        
        bRet = true;
    } while (0);
    return bRet;
}

void ControlLayer::addJoystick()
{
    float joystickRadius = 70;
    
    // 创建SneakyJoystick实例并初始化
    _joystick = new SneakyJoystick();
    _joystick->autorelease();
    _joystick->initWithRect(CCRectMake(0, 0, joystickRadius, joystickRadius));
    // 是否自动回到中心
    _joystick->setAutoCenter(true);
    // 是否支持死亡区域，该区域不会触发
    _joystick->setHasDeadzone(true);
    // 死亡区域半径
    _joystick->setDeadRadius(5);
    
    SneakyJoystickSkinnedBase *joystickSkin = new SneakyJoystickSkinnedBase();
    joystickSkin->autorelease();
    joystickSkin->init();
    // 设置虚拟摇杆的位置
    joystickSkin->setPosition(CCPointMake(100, 100));
    joystickSkin->setScale(1.0f);
    
    // 背景
    CCSprite *bgSprite = CCSprite::create("images/control_bg.png");
    bgSprite->setOpacity(100);
    joystickSkin->setBackgroundSprite(bgSprite);
    
    // 中心
    CCSprite *thumbSprite=CCSprite::create("images/cen.png");
    thumbSprite->setOpacity(100);
    joystickSkin->setThumbSprite(thumbSprite);
    joystickSkin->getThumbSprite()->setScale(1.5f);
    
    joystickSkin->setJoystick(_joystick);
    
    this->addChild(joystickSkin);
}

void ControlLayer::update(float t)
{
    if (_mapLayer == NULL) {
        return;
    }

    // 获取地图层的玩家坦克实例
    TankSprite *tank = _mapLayer->_tank1;

    if (tank == NULL) {
        return;
    }

    // getVelocity()到的值很小，需要放大
    CCPoint poi = ccpMult(_joystick->getVelocity(), 50);
    
    // 判断开火按钮是否被按下
    if (_fireButton->getIsActive()) {
        //CCLog("Fire!");
        tank->onFire();
    }
    
    //right
    if ((poi.x  >  0)  && (poi.x - poi.y) >0 && (poi.x + poi.y) > 0){
        tank->moveRight();
    }
    //left
    else if ( (poi.x < 0)  && (poi.x + poi.y) < 0 &&(poi.x - poi.y) < 0) {
        tank->moveLeft();
    }
    //up
    else if ((poi.y > 0) &&(poi.y - poi.x) > 0 &&(poi.y + poi.x) >0 ){
        tank->moveUp();
    }
    //down
    else if ((poi.y < 0) &&(poi.y - poi.x) < 0 && (poi.y + poi.x) < 0) {
        tank->moveDown();
    }
}

void ControlLayer::addFireButton()
{
    //float buttonRadius = 80;
    CCSize wSize = CCDirector::sharedDirector()->getWinSize();
    
    _fireButton = new SneakyButton();
    _fireButton->initWithRect(CCRectZero);
    _fireButton->autorelease();
    _fireButton->setIsHoldable(true);
    _fireButton->setIsToggleable(true);
    
    SneakyButtonSkinnedBase *skinFireButton = new SneakyButtonSkinnedBase();
    skinFireButton->autorelease();
    skinFireButton->init();
    
    CCSprite *normalSprite = CCSprite::create("images/fire_button_default.png");
    normalSprite->setOpacity(100);
    
    CCSprite *pressedSprite = CCSprite::create("images/fire_button_press.png");
    pressedSprite->setOpacity(100);
    
    skinFireButton->setPosition(ccp(wSize.width-75, 75));
    skinFireButton->setDefaultSprite(normalSprite);
    skinFireButton->setPressSprite(pressedSprite);
    skinFireButton->setActivatedSprite(CCSprite::create("images/fire_button_press.png"));
    skinFireButton->setScale(1.0f);
    skinFireButton->setButton(_fireButton);
    
    this->addChild(skinFireButton);
}
