//
//  MapLayer.cpp
//  TankWar
//
//  Created by user on 13-9-3.
//
//

#include "MapLayer.h"

MapLayer::~MapLayer(){}

bool MapLayer::init()
{
    bool bRet = false;
    do {
        // 屏幕的大小
        CCSize wSize = CCDirector::sharedDirector()->getVisibleSize();
        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(0, 0, 0, 255), wSize.height, wSize.height));
        
        bRet = true;
    } while (0);
    return bRet;
}

void MapLayer::initWithMap(int leve, int tKind, int numLife)
{
    _leve = leve;
    
    // 解析tmx地图
    _map = cocos2d::CCTMXTiledMap::create(CCString::createWithFormat("maps/map%d.tmx",leve)->getCString());
    
    // 地图的大小
    CCSize cSize = _map->getContentSize();
    CCLOG("ContentSize: %f, %f", cSize.width,cSize.height);
    // 屏幕的大小
    CCSize wSize = CCDirector::sharedDirector()->getVisibleSize();
    CCLOG("WindowSize: %f, %f", wSize.width,wSize.height);
    
    // 缩放比例
    float scale = wSize.height / cSize.height;
    _map->setScale(scale);
    
    // 将地图向右平移屏幕宽度的1/6
    //map->setPosition(wSize.width / 6, 0);
    //CCLog("MapPosition: %f, %f", map->getPositionX(), map->getPositionY());
    
    this->addChild(_map, 1);
    
    // 从地图中获取地图层
    _bg1Layer = _map->layerNamed("bg1");
    _bg2Layer = _map->layerNamed("bg2");
    // 将层2隐藏起来
    _bg2Layer->setVisible(false);

    // 从地图中获取对象层
    _objects = _map->objectGroupNamed("objects");

    // 创建基地
    CCPoint homePoint = this->objectPosition(_objects, "home");
    _home = CCSprite::create("images/home.png");
    _home->setPosition(ccp(homePoint.x+_home->getTextureRect().size.width/2,homePoint.y + _home->getTextureRect().size.height/2));
    _homeRect = CCRectMake(_home->getPosition().x - _home->getTextureRect().size.width/2,_home->getPosition().y - _home->getTextureRect().size.height/2,_home->getTextureRect().size.width, _home->getTextureRect().size.height);
    _map->addChild(_home, -1);

    // 创建玩家坦克
    _tank1 = TankSprite::create();
    _tank1->initWithDelegate(numLife, tKind, _bg1Layer->getContentSize());
    _tank1->_mapLayer = this;
    _tank1->_map = _map;
    _tank1->homeRect = _homeRect;

    // 设置玩家坦克坐标
    CCPoint tankPoint = this->objectPosition(_objects, "pl1");
    _tank1->setPosition(ccp(tankPoint.x+_tank1->boundingBox().size.width/2, tankPoint.y+_tank1->boundingBox().size.width/2));

    _tank1->bornPosition = _tank1->getPosition();
    _map->addChild(_tank1, 1);


    // 创建敌人坦克
    _enemyNum = 1;
    _enemyArray = new CCArray();
    _enemyArray->retain();

    // 从Plist文件中读取敌方坦克数据
    this->initAIPlistFile();
    // 每相隔2s，判断是否生成一辆敌方坦克或者进入下一关
    this->schedule(schedule_selector(MapLayer::initEnemys), 2);

//    _rodamPoint = 10;
//    _pointArray = new CCArray();
//    _pointArray->retain();
//    _propArray = new CCArray();
//    _propArray->retain();
//
//    for (int i = 1; i <= _rodamPoint; i++) {
//        CCPoint *pot = new CCPoint();
//        CCPoint point = this->objectPosition(_objects, CCString::createWithFormat("t%d", i)->getCString());
//        pot->x = point.x;
//        pot->y = point.y;
//        _pointArray->addObject((CCObject*)pot);
//    }
}

CCPoint MapLayer::objectPosition(CCTMXObjectGroup *group,const char *object)
{
    CCPoint point;
    CCDictionary *dic=group->objectNamed(object);
    if (dic == NULL) {
        return ccp(0, 0);
    }
    point.x=dic->valueForKey("x")->intValue();
    point.y=dic->valueForKey("y")->intValue();
    return point;
}

CCPoint MapLayer::tileCoordinateFromPosition(CCPoint pos)
{
    CCSize szLayer = _bg1Layer->getLayerSize();
    CCSize szTile = _map->getTileSize();
    
    int cox = pos.x / szTile.width;
    int coy = szLayer.height - pos.y / szTile.height;
    
    if ( (cox >= 0) && (cox < szLayer.width) && (coy >= 0) && (coy <= szLayer.height)) {
        return ccp(cox, coy);
    }else{
        return ccp(-1,-1);
    }
}

int MapLayer::tileIDFromPosition(CCPoint pos)
{
    CCPoint cpt = this->tileCoordinateFromPosition(pos);
    if (cpt.x < 0) return  -1;
    if (cpt.y < 0) return -1;
    if (cpt.x >= _bg1Layer->getLayerSize().width) return -1;
    if (cpt.y >= _bg1Layer->getLayerSize().height) return -1;
    //CCLog("%f %f", cpt.x, cpt.y);
    return _bg1Layer->tileGIDAt(cpt);
}

void MapLayer::destpryTile(CCPoint pos)
{
    CCPoint cpt = this->tileCoordinateFromPosition(pos);
    _bg1Layer->setTileGID(0, cpt);
}

void MapLayer::initAIPlistFile()
{
    CCString* plistPath = CCStringMake("AI/AI.plist");
    CCDictionary* data = CCDictionary::createWithContentsOfFile(plistPath->getCString());
    _aiDic = (CCDictionary*) (data->objectForKey(CCString::createWithFormat("leve%d", _leve)->getCString()));
    // retain一次确保不会被自动回收
    _aiDic->retain();
}

void MapLayer::initEnemys()
{
    // 如果已产生并都被消灭了20辆敌方坦克，则进入下一关
    if (_enemyNum > 20 && _enemyArray->count() == 0) {
        this->unschedule(schedule_selector(MapLayer::initEnemys));
        this->scheduleOnce(schedule_selector(MapLayer::gotoScoreScene), 3);
    }
    // 已产生了20辆敌方坦克，并还未被团灭，也不会再产生坦克
    if(_enemyNum > 20) return;
    // 屏幕上已有4辆敌方坦克，延迟敌方坦克的生成
    if(_enemyArray->count() >= 4) return;
    
    // 获取坦克类型
    int enemyKind =(_aiDic->valueForKey(CCString::createWithFormat("%d", _enemyNum++)->getCString()))->intValue();
    
    // 依据坦克类型初始化坦克
//    EnemySprite* enemy = EnemySprite::initWithKind(enemyKind);
    EnemySprite* enemy = EnemySprite::create();
    enemy->initWithKind(enemyKind);
    enemy->_mapSize = _bg1Layer->getContentSize();
    enemy->_map = _map;
    enemy->_mapLayer = this;
    enemy->_tank = _tank1;
    enemy->homeRect = _homeRect;
    
    // 每辆敌方坦克循环地出现在屏幕上方的3个位置
    if (_bornNum == 3) {
        _bornNum = 0;
    }
    int random = _bornNum;
    _bornNum++;
    
    CCPoint poin;
    
    if (random == 0) {
        poin = this->objectPosition(_objects, "en1");
    }else if (random == 1){
        poin = this->objectPosition(_objects, "en2");
    }else if (random == 2){
        poin = this->objectPosition(_objects, "en3");
    }else{
        poin = this->objectPosition(_objects, "en3");
    }
    
    enemy->setPosition(ccp(poin.x + enemy->boundingBox().size.width/2,poin.y + enemy->boundingBox().size.height/2));
    _map->addChild(enemy);
    
    _enemyArray->addObject(enemy);
}

void MapLayer::gotoScoreScene()
{
    
}

void MapLayer::gameOver()
{
    // 停止坦克的生成
    this->unschedule(schedule_selector(MapLayer::initEnemys));
    
    // 游戏已经结束
    if(_isGameOver) return;
    
    // 布置游戏结束场景并跳转到开始场景
    CCImage *image = new CCImage();
    image->autorelease();
    image->initWithImageFile("images/home2.png");
    
    CCTexture2D *newTexture = CCTextureCache::sharedTextureCache()->addUIImage(image, NULL);
    _home->setTexture(newTexture);
    
    CCSprite* gameSprite = CCSprite::create("images/gamedone.png");
    gameSprite->setScale(8.0f);
    gameSprite->setPosition(ccp(_bg1Layer->getContentSize().width/2,-10));
    CCPoint overPoint = ccp(_bg1Layer->getContentSize().width/2,_bg1Layer->getContentSize().height/2);
    _map->addChild(gameSprite, 2);
    
    CCAction* ac1 = CCMoveTo::create(4.0, overPoint);
    gameSprite->runAction(ac1);
    
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/gameover.aif");
    
    //[self schedule:@selector(retunMainScene) interval:5];
    _isGameOver = true;
}

void MapLayer::removeSprite(TankSprite* aTank)
{
    EnemySprite* tank = (EnemySprite *)aTank;
    
    if (tank->_enemyKindForScore == kSlow || tank->_enemyKindForScore == kSlowR) {
        _slow++;
    }else if (tank->_enemyKindForScore == kQuike || tank->_enemyKindForScore == kQuikeR){
        _quike++;
    }else if (tank->_enemyKindForScore == kStrong || tank->_enemyKindForScore == kStrongRed){
        _strong++;
    }else if (tank->_enemyKindForScore == kStrongYellow){
        _strongYe++;
    }else if (tank->_enemyKindForScore == kStrongRedLife3 || tank->_enemyKindForScore == kStrongGreen) {
        _strongG++;
    }
    
    _enemyArray->removeObject(tank);
    tank->stopTankAction();
    _tTank = tank;
    tank->scheduleOnce(schedule_selector(MapLayer::removeSelfFromMap), 0.3);
}

void MapLayer::removeSelfFromMap()
{
    _tTank->removeFromParentAndCleanup(true);
}
