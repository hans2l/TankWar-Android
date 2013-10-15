//
//  GameSence.cpp
//  TankWar
//
//  Created by user on 13-9-3.
//
//

#include "GameSence.h"
#include "SimpleAudioEngine.h"

GameScene::~GameScene()
{}

bool GameScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(! CCScene::init());
        
        // 自添加代码
        
        this->initWithMapInformation(3, 1, 1);

        _conLayer = ControlLayer::create();
        _conLayer->_mapLayer = _mapLayer;
        this->addChild(_conLayer, 1);
        
        bRet = true;
    } while (0);
    return bRet;
}

void GameScene::initWithMapInformation(int leve, int status, int life)
{
    // 开始音乐
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/02 start.aif");
    
    // 创建一个颜色层
    CCLayerColor *backColor = CCLayerColor::create(ccc4(192, 192, 192, 255));
    this->addChild(backColor, 1);
                                                
    // 精灵帧类，提高效率
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile("images/images.plist");
    
    // 场景内一些精灵的创建
    CCSize wSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *ipLife = CCSprite::createWithSpriteFrameName("IP.png");
    ipLife->setPosition(ccp(30, wSize.height - 50));
    ipLife->setScale(1.0f);
    this->addChild(ipLife, 1);
    CCSprite *ipLifeIock = CCSprite::createWithSpriteFrameName("p1.png");
    ipLifeIock->setPosition(ccp(20, wSize.height - 70));
    ipLifeIock->setScale(0.5f);
    this->addChild(ipLifeIock, 1);
    
    this->showLife(life);
    
    CCSprite *flag = CCSprite::createWithSpriteFrameName("flag.png");
    flag->setPosition(ccp(wSize.width - 50, wSize.height - 200));
    flag->setScale(1.0f);
    this->addChild(flag, 1);
    
    this->showLeve(leve);
    
    _mapLayer = MapLayer::create();
    _mapLayer->initWithMap(leve, status, life);
    _mapLayer->setPosition(ccp(wSize.width/6, 0));
    this->addChild(_mapLayer, 1);
}

void GameScene::showLife(int numLife)
{
    if (_1plifeString != NULL) {
        _1plifeString->removeFromParentAndCleanup(true);
    }
    
    CCSize wSize = CCDirector::sharedDirector()->getWinSize();
    _1plifeString = CCLabelTTF::create(CCString::createWithFormat("%d",numLife)->getCString(), "Courier-Bold", 20);
    _1plifeString->setColor(ccc3(0, 0, 0));
    _1plifeString->setPosition(ccp(45, wSize.height - 70)   );
    this->addChild(_1plifeString,1);
}

void GameScene::showLeve(int inLeve)
{
    if (_leveString != NULL) {
        _leveString->removeFromParentAndCleanup(true);
    }
    
    CCSize wSize = CCDirector::sharedDirector()->getWinSize();
    _leveString=CCLabelTTF::create(CCString::createWithFormat("%d",inLeve)->getCString(), "Courier-Bold", 20);
    _leveString->setColor(ccc3(0, 0, 0));
    _leveString->setPosition(ccp(wSize.width - 50, wSize.height - 230));
    this->addChild(_leveString,1);
}
