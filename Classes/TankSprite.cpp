//
//  TankSprite.cpp
//  TankWar
//
//  Created by user on 13-9-3.
//
//

#include "TankSprite.h"
#include "MapLayer.h"
#include "EnemySprite.h"
#define FRAME(image) CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(image)

TankSprite::TankSprite()
{
}

TankSprite::~TankSprite()
{
}

bool TankSprite::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF( !CCSprite::init() );
        
        // 自添加代码
        
        
        bRet = true;
    } while (0);
    return bRet;
}

void TankSprite::initWithDelegate(int numLife, int tKind, cocos2d::CCSize mSize)
{
    CCSpriteFrame* frameKind;
//    TankSprite *tank;
    
    // 依据参数类型创建不同的玩家坦克
    switch (tKind) {
        case kBorn:
            frameKind = FRAME("p1.png");
//            tank = (TankSprite* )TankSprite::createWithSpriteFrame(frameKind);
//            tank->_speed = 1;
            this->initWithSpriteFrame(frameKind);
            this->_speed = 1;
            break;
            
        case kPlusStarOne:
            frameKind = FRAME("p1-a.png");
//            tank = (TankSprite* )TankSprite::createWithSpriteFrame(frameKind);
//            tank->_speed = 1.5;
            this->initWithSpriteFrame(frameKind);
            this->_speed = 1.5;
            break;
            
        case kPlusStarTwo:
            frameKind = FRAME("p1-b.png");
//            tank = (TankSprite* )TankSprite::createWithSpriteFrame(frameKind);
//            tank->_speed = 1.5;
            this->initWithSpriteFrame(frameKind);
            this->_speed = 1.5;
            break;
        case kPlusStarThree:
            frameKind = FRAME("p1-c.png");
//            tank = (TankSprite* )TankSprite::createWithSpriteFrame(frameKind);
//            tank->_speed = 1.5;
            this->initWithSpriteFrame(frameKind);
            this->_speed = 1.5;
            break;
            
        default:
            break;
    }
    
    this->_life = numLife;
    this->_mapSize = mSize;
    
    this->_kind = (TankKind)tKind;
    this->setScale(0.7f);
    
    // 方向默认向上
    this->_kAction = kUp;
    this->_isCanFire = true;
    
    // 布置出生场景
    this->bornInformation();
    
    //return tank;
}

void TankSprite::moveUp()
{
    
    // 设置旋转方向
    this->setRotation(0);
    // 设置tank的方向
    _kAction=kUp;
    
    // tank当前坐标
    CCPoint tp=this->getPosition();
    // tank移动后坐标
    CCPoint tnp = ccp(tp.x, tp.y+this->boundingBox().size.height/2+_speed);
    
    // 边界检测
    if ((tp.y + this->boundingBox().size.height/2 + _speed) > _mapSize.height ) return;
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2,tp.y + this->boundingBox().size.height / 2 + _speed);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/3,tp.y + this->boundingBox().size.height / 2 + _speed);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x + this->boundingBox().size.width/2,tp.y + this->boundingBox().size.height / 2 + _speed);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x + this->boundingBox().size.width/3,tp.y + this->boundingBox().size.height / 2 + _speed);
    if (this->checkPoint(tnp)) return;
    
    if (this-> checkTankPosition()){
        return;
    }
    
    // this->checkTool();
    this->setPosition(ccp(this->getPosition().x, this->getPosition().y+_speed));
}

void TankSprite::moveDown()
{
    
    
    this->setRotation(180);
    
    _kAction=kDown;
    
    CCPoint tp=this->getPosition();
    
    CCPoint tnp = ccp(tp.x, tp.y-this->boundingBox().size.height/2-_speed);
    
    //
    if ((tp.y - this->boundingBox().size.height/2 - _speed) < 0 ) return;
    
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x-this->boundingBox().size.width/2,tp.y - this->boundingBox().size.height/2 - _speed);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/3,tp.y - this->boundingBox().size.height / 2 - _speed);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x + this->boundingBox().size.width/2,tp.y - this->boundingBox().size.height / 2 - _speed);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x + this->boundingBox().size.width/3,tp.y - this->boundingBox().size.height / 2 - _speed);
    if (this->checkPoint(tnp)) return;
    
    if (this-> checkTankPosition()){
        return;
    }
    
    // this->checkTool();
    this->setPosition(ccp(this->getPosition().x, this->getPosition().y-_speed));
}

void TankSprite::moveLeft()
{
    
    this->setRotation(-90);
    
    _kAction=kLeft;
    
    CCPoint tp=this->getPosition();
    
    CCPoint tnp = ccp(tp.x-this->boundingBox().size.width/2-_speed, tp.y);
    
    //
    if (tp.x-this->boundingBox().size.width/2-_speed < 0 ) return;
    
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 - _speed,tp.y + this->boundingBox().size.height/2 - 2);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 - _speed,tp.y + this->boundingBox().size.height/3);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 - _speed,tp.y - this->boundingBox().size.height/2 + 2);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 - _speed,tp.y - this->boundingBox().size.height/3);
    if (this->checkPoint(tnp)) return;
    
    if (this-> checkTankPosition()){
        return;
    }
    
    // this->checkTool();
    this->setPosition(ccp(this->getPosition().x-_speed, this->getPosition().y));
}

void TankSprite::moveRight()
{
    
    this->setRotation(90);
    
    _kAction=kRight;
    
    CCPoint tp=this->getPosition();
    
    CCPoint tnp = ccp(tp.x+this->boundingBox().size.width/2+_speed, tp.y);
    
    //
    if (tp.x+this->boundingBox().size.width/2+_speed > _mapSize.width ) return;
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 + _speed,tp.y + this->boundingBox().size.height/2 - 2);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 + _speed,tp.y + this->boundingBox().size.height/3);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 + _speed,tp.y - this->boundingBox().size.height/2 + 2);
    if (this->checkPoint(tnp)) return;
    
    tnp = ccp(tp.x - this->boundingBox().size.width/2 + _speed,tp.y - this->boundingBox().size.height/3);
    if (this->checkPoint(tnp)) return;
    
    if (this-> checkTankPosition()){
        return;
    }
    
    // this->checkTool();
    this->setPosition(ccp(this->getPosition().x+_speed, this->getPosition().y));
}

bool TankSprite::checkPoint(CCPoint pon)
{
    
    CCPoint tnp = pon;
    unsigned int tid;
    
    tid = _mapLayer->tileIDFromPosition(tnp);
    //CCLog("%d!!!", tid);
    if (tid != 0 && tid != 9 && tid != 10 && tid != 37 && tid != 38 ) return true;
    
    return false;
}

bool TankSprite::checkTankPosition()
{
    // 获取敌方坦克
    CCArray* array = _mapLayer->_enemyArray;
    
    CCPoint point;
    // 获取玩家坦克位置
    CCPoint tp = this->getPosition();
    
    // 计算玩家坦克移动后的位置
    if (_kAction == kUp){
        point = ccp(tp.x,tp.y + this->boundingBox().size.height / 2 + _speed);
    }else if (_kAction == kDown){
        point = ccp(tp.x,tp.y - this->boundingBox().size.height / 2 - _speed);
    }else if (_kAction == kLeft) {
        point =  ccp(tp.x - this->boundingBox().size.width/2 - _speed,tp.y);
    }else if (_kAction == kRight) {
        point = ccp(tp.x + this->boundingBox().size.width/2 + _speed,tp.y);
    }
    
    // 遍历敌方坦克是否发生碰撞
    CCRect tankEnemy;
    CCObject* pObj;
    
    CCARRAY_FOREACH(array, pObj){
        EnemySprite* tank = (EnemySprite*)pObj;
        tankEnemy = CCRectMake(tank->getPosition().x - tank->boundingBox().size.width/2,
                               tank->getPosition().y - tank->boundingBox().size.height/2,
                               tank->boundingBox().size.width,
                               tank->boundingBox().size.height);
        if (tankEnemy.containsPoint(point)){
            return true;
        }
    }
    return false;
}

void TankSprite::onFire()
{
    if (_life == 0) {
        return;
    }

    CCSpriteFrame* frameButtle = FRAME("bullet.png");
    if (_kind == kPlusStarTwo || _kind == kPlusStarThree) {
        
        if (_buttleCount <= 2){
            
            _buttleOrientation = _kAction;     //子弹运行的方向
            CCSprite *buttle = CCSprite::createWithSpriteFrame(frameButtle);
            buttle->setVisible(false);
            _map->addChild(buttle, -1);
            this->fire(buttle, (TankAction)_buttleOrientation);
            _buttleCount++;
            // 延时1s
            if (_buttleCount > 2){
                this->scheduleOnce(schedule_selector(TankSprite::canFire2), 1);
            }
            
        }else {
            return;
        }
        
    }else if (_kind == kBorn || _kind == kPlusStarOne) {
        if (_isCanFire == false) return;
        
        // 子弹方向即坦克方向
        _buttleOrientation = _kAction;
        
        CCSprite *buttle = CCSprite::createWithSpriteFrame(frameButtle);
        _map->addChild(buttle, -1);
    
        // 隐藏
        buttle->setVisible(false);
        _isCanFire = false;
        
        _buttle = buttle;
        this->fire(buttle, (TankAction)_buttleOrientation);
    }
}

void TankSprite::fire(CCSprite *buttle, TankAction buttleOrientation)
{
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/bullet.aif");
    
    CCPoint ptn;
    // 设置子弹的消失位置
    switch (buttleOrientation) {
        case kUp:
            buttle->setRotation(0);
            buttle->setPosition(ccp(this->getPosition().x, this->getPosition().y+this->boundingBox().size.height/2));
            //终点
            ptn=ccp(this->getPosition().x, this->getPosition().y+_mapSize.width);
            break;
        case kDown:
            buttle->setRotation(180);
            buttle->setPosition(ccp(this->getPosition().x, this->getPosition().y-this->boundingBox().size.height/2));
            ptn=ccp(this->getPosition().x, this->getPosition().y-_mapSize.width);
            break;
        case kRight:
            buttle->setRotation(90);
            buttle->setPosition(ccp(this->getPosition().x+this->boundingBox().size.width/2, this->getPosition().y));
            ptn=ccp(this->getPosition().x+_mapSize.width, this->getPosition().y);
            break;
        case kLeft:
            buttle->setRotation(-90);
            buttle->setPosition(ccp(this->getPosition().x-this->boundingBox().size.width/2, this->getPosition().y));
            ptn=ccp(this->getPosition().x-_mapSize.width, this->getPosition().y);
            break;
        default:
            break;
    }
    
    const CCPoint realyPosition = ptn;
    
    // 创建子弹移动动画
    // Show子弹
    CCShow *ac1=CCShow::create();
    // 子弹移动到边界
    CCMoveTo *ac2=CCMoveTo::create(2.0, realyPosition);
    // 组合子弹移出屏幕后的操作
    CCFiniteTimeAction *seq=CCSequence::create(ac1,ac2,CCCallFunc::create(this, callfunc_selector(TankSprite::makeCanFire)),NULL);
    buttle->runAction(seq);
    
    this->schedule(schedule_selector(TankSprite::checkBang), 1/60);
}

void TankSprite::makeCanFire()
{
    _isCanFire = true;
}

void TankSprite::checkBang(float dt)
{
    CCPoint btPoint = _buttle->getPosition();
    unsigned int gid = _mapLayer->tileIDFromPosition(btPoint);
    
    if(gid == -1
       || checkLayer2()
       || checkHome()
       || checkWall()
       || checkStrongWall()){
        // 停止tank的碰撞检测定时器
        this->unschedule(schedule_selector(TankSprite::checkBang));
        // 从移除地图层移出buttle
        _buttle->removeFromParentAndCleanup(true);
        _isCanFire = true;
        //_buttle = NULL;
        return;
    }
    
    // 检测子弹与敌方坦克的碰撞
    CCArray* enemys = new CCArray();
    enemys = _mapLayer->_enemyArray;
    CCRect buttleRect;
    CCRect tankEnemy;
    CCObject* pObj;

    //CCLOG("%d", _enemyArray->count());
    CCARRAY_FOREACH(enemys, pObj){
        EnemySprite* tank = (EnemySprite*)pObj;
        // 获取子弹的空间
        buttleRect = CCRectMake(_buttle->getPosition().x - _buttle->getContentSize().width/2,_buttle->getPosition().y - _buttle->getContentSize().height/2,_buttle->getContentSize().width,_buttle->getContentSize().height);
        // 获取敌方坦克的空间
        tankEnemy = CCRectMake(tank->getPosition().x - tank->boundingBox().size.width/2,tank->getPosition().y - tank->boundingBox().size.height/2,tank->boundingBox().size.width,tank->boundingBox().size.height);

        // 子弹已击中坦克的正中间
        if (NULL != tank->_buttle){
            if ( buttleRect.containsPoint(tank->getPosition())){
                // 停止tank的碰撞检测定时器
                this->unschedule(schedule_selector(TankSprite::checkBang));
                // 从移除地图层移出buttle
                _buttle->removeFromParentAndCleanup(true);
                _isCanFire =
                //_buttle = NULL;
                // 标记敌方坦克被子弹击中
                tank->_isButtleDone = true;
                return;
            }
        }

        // 子弹击中坦克的车身
        if ( tankEnemy.containsPoint(_buttle->getPosition())) {
            // 停止tank的碰撞检测定时器
            this->unschedule(schedule_selector(TankSprite::checkBang));
            // 从移除地图层移出buttle
            _buttle->removeFromParentAndCleanup(true);
            _isCanFire = true;
            //_buttle = NULL;
            _tmpTank = tank;

            // 判断敌方坦克的类型
            this->checkEnemyKind(tank);
        }
    }

    if (_isTankDone){
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/blast.aif");
        _tmpTank->animationBang();

        _mapLayer->removeSprite(_tmpTank);
        _isTankDone = false;
        return;
    }


    if (checkBound()){
        // 停止tank的碰撞检测定时器
        this->unschedule(schedule_selector(TankSprite::checkBang));
        // 从移除地图层移出buttle
        _buttle->removeFromParentAndCleanup(true);
        _isCanFire = true;
        return;
    }
}

bool TankSprite::checkLayer2()
{
    // 如果基地不被保护，则检测基地上的材质
    if(!_isHomeProtect) return false;
    // 如果基地被保护，则遇到保护层时直接移出buttle
    CCPoint btPoint = _buttle->getPosition();
    unsigned gid = _mapLayer->tileIDFromPosition(btPoint);
    if (0 != gid) {
        return true;
    }
    return false;
}

bool TankSprite::checkHome()
{
    CCRect rc = homeRect;
    if (rc.containsPoint(_buttle->getPosition())) {
        //CCLOG("isHomeProtect:%d", _isHomeProtect);
        // 如果基地被保护的话，则直接移除buttle
        if (_isHomeProtect) return true;
        // 如果基地不被保护的话
        if (!_isHomeDone){
            _isHomeDone = true;
            _mapLayer->gameOver();
        }
        return true;
    }
    return false;
}

bool TankSprite::checkWall()
{
    CCPoint btPoint = _buttle->getPosition();
    unsigned gid,gid1,gid2,gid3,gid4;
    gid = _mapLayer->tileIDFromPosition(btPoint);
    
    
    if ( (_buttleOrientation == kUp) || ( _buttleOrientation == kDown))
    {
        
        gid1 = _mapLayer->tileIDFromPosition(ccp(btPoint.x - 8, btPoint.y));
        gid2 = _mapLayer->tileIDFromPosition(ccp(btPoint.x + 8, btPoint.y));
        gid3 = _mapLayer->tileIDFromPosition(ccp(btPoint.x - 16, btPoint.y));
        gid4 = _mapLayer->tileIDFromPosition(ccp(btPoint.x + 16, btPoint.y));
        
        
        if (gid == 29 || gid == 30 || gid == 2 || gid == 1)
        {
            
            _mapLayer->destpryTile(btPoint);
            
            
            if ((gid1 == 29 || gid1 == 30 || gid1 == 2 || gid1 == 1) && (gid2 == 29 || gid2 == 30 || gid2== 2 || gid2 == 1))
            {
                
                
                if (gid4 == 29 || gid4 == 30 || gid4 == 2 || gid4 == 1 )
                {
                    _mapLayer->destpryTile(ccp(btPoint.x - 8, btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x + 8, btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x + 16, btPoint.y));
                    return true;
                }
                else
                {
                    if (gid3 == 0)
                    {
                        _mapLayer->destpryTile(ccp(btPoint.x - 8, btPoint.y));
                        _mapLayer->destpryTile(ccp(btPoint.x + 8, btPoint.y));
                        return true;
                    } else if (gid3 == 29 || gid3 == 30 || gid3 == 2 || gid3 == 1)
                    {
                        _mapLayer->destpryTile(ccp(btPoint.x - 8, btPoint.y));
                        _mapLayer->destpryTile(ccp(btPoint.x - 16, btPoint.y));
                        _mapLayer->destpryTile(ccp(btPoint.x + 8, btPoint.y));
                        return true;
                    }else
                    {
                        _mapLayer->destpryTile(ccp(btPoint.x - 8, btPoint.y));
                        _mapLayer->destpryTile(ccp(btPoint.x + 8, btPoint.y));
                        return true;
                    }
                }
                
            }
            
            
            if ((gid1 == 29 || gid1 == 30 || gid1 == 2 || gid1 == 1) && gid2 == 0)
            {
                _mapLayer->destpryTile(ccp(btPoint.x - 8, btPoint.y));
                return true;
            }
            
            
            if (gid1 == 0 && (gid2 == 29 || gid2 == 30 || gid2== 2 || gid2 == 1))
            {
                _mapLayer->destpryTile(ccp(btPoint.x + 8, btPoint.y));
                return true;
            }
            
            
            if ((gid1 != 1 && gid1 != 2 && gid1 != 29 && gid1 != 30 && gid1 != 0) && (gid2 == 29 || gid2 == 30 || gid2== 2 || gid2 == 1))
            {
                _mapLayer->destpryTile(ccp(btPoint.x + 8, btPoint.y));
                return true;
            }
            
            
            if ((gid1 != 1 && gid1 != 2 && gid1 != 29 && gid1 != 30 && gid1 != 0) && gid2 == 0)
            {
                return true;
            }
            
            
            if ((gid2 != 1 && gid2 != 2 && gid2 != 29 && gid2 != 30 && gid2 != 0) && (gid1 == 29 || gid1 == 30 || gid1 == 2 || gid1 == 1))
            {
                _mapLayer->destpryTile(ccp(btPoint.x - 8, btPoint.y));
                return true;
            }
            
            
            if ((gid2 != 1 && gid2 != 2 && gid2 != 29 && gid2 != 30 && gid2 != 0) && gid1 == 0)
            {
                return true;
            }
            
            
            if (gid1 == 0 && gid2 == 0) {
                return true;
            }
        }
    }
    
    if (_buttleOrientation == kLeft || _buttleOrientation == kRight)
    {
        
        gid1 = _mapLayer->tileIDFromPosition(ccp(btPoint.x, btPoint.y - 8));
        gid2 = _mapLayer->tileIDFromPosition(ccp(btPoint.x, btPoint.y + 8));
        gid3 = _mapLayer->tileIDFromPosition(ccp(btPoint.x, btPoint.y - 16));
        gid4 = _mapLayer->tileIDFromPosition(ccp(btPoint.x, btPoint.y + 16));
        
        
        if (gid == 29 || gid == 30 || gid == 2 || gid == 1)
        {
            
            _mapLayer->destpryTile(btPoint);
            
            
            if ((gid1 == 29 || gid1 == 30 || gid1 == 2 || gid1 == 1) && (gid2 == 29 || gid2 == 30 || gid2== 2 || gid2 == 1))
            {
                
                
                if (gid4 == 29 || gid4 == 30 || gid4 == 2 || gid4 == 1 )
                {
                    _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 8));
                    _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 8));
                    _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 16));
                    return true;
                }
                else
                {
                    if (gid3 == 0)
                    {
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 8));
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 8));
                        return true;
                    } else if (gid3 == 29 || gid3 == 30 || gid3 == 2 || gid3 == 1)
                    {
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 8));
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 16));
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 8));
                        return true;
                    }else
                    {
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 8));
                        _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 8));
                        return true;
                    }
                }
                
            }
            
            
            if ((gid1 == 29 || gid1 == 30 || gid1 == 2 || gid1 == 1) && gid2 == 0)
            {
                _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 8));
                return true;
            }
            
            
            if (gid1 == 0 && (gid2 == 29 || gid2 == 30 || gid2== 2 || gid2 == 1))
            {
                _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 8));
                return true;
            }
            
            
            if ((gid1 != 1 && gid1 != 2 && gid1 != 29 && gid1 != 30 && gid1 != 0) && (gid2 == 29 || gid2 == 30 || gid2== 2 || gid2 == 1))
            {
                _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y + 8));
                return true;
            }
            
            
            if ((gid1 != 1 && gid1 != 2 && gid1 != 29 && gid1 != 30 && gid1 != 0) && gid2 == 0)
            {
                return true;
            }
            
            
            if ((gid2 != 1 && gid2 != 2 && gid2 != 29 && gid2 != 30 && gid2 != 0) && (gid1 == 29 || gid1 == 30 || gid1 == 2 || gid1 == 1))
            {
                _mapLayer->destpryTile(ccp(btPoint.x, btPoint.y - 8));
                return true;
            }
            
            
            if ((gid2 != 1 && gid2 != 2 && gid2 != 29 && gid2 != 30 && gid2 != 0) && gid1 == 0)
            {
                return true;
            }
            
            
            if (gid1 == 0 && gid2 == 0) {
                return true;
            }
            
        }
        
    }

    return false;
}

bool TankSprite::checkStrongWall()
{
    
    CCPoint btPoint = _buttle->getPosition();
    unsigned gid = _mapLayer->tileIDFromPosition(btPoint);
    
    
    if (gid == 5 || gid ==6 ||gid ==33 ||gid == 34 ) {
        
        if (_kind == kPlusStarThree) {
            
            _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y));
            
            _isCanFire = true;
            if ( _buttleOrientation == kUp){
                if (gid == 33) {
                    
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y + 8));
                    _mapLayer->destpryTile(ccp(btPoint.x + 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x+8,btPoint.y+8));
                }else if (gid == 34){
                    
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y+8));
                    _mapLayer->destpryTile(ccp(btPoint.x - 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x-8,btPoint.y+8));
                }
                return true;
                
            }else if (_buttleOrientation == kDown){
                if (gid == 5) {
                    
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y - 8));
                    _mapLayer->destpryTile(ccp(btPoint.x + 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x + 8,btPoint.y-8));
                }else if (gid == 6){
                    
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y-8));
                    _mapLayer->destpryTile(ccp(btPoint.x - 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x-8,btPoint.y-8));
                }
                return true;
                
            }else if (_buttleOrientation == kLeft){
                if (gid == 34){
                    
                    _mapLayer->destpryTile(ccp(btPoint.x - 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y +8));
                    _mapLayer->destpryTile(ccp(btPoint.x-8,btPoint.y+8));
                }else if(gid == 6){
                    
                    _mapLayer->destpryTile(ccp(btPoint.x- 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y - 8));
                    _mapLayer->destpryTile(ccp(btPoint.x - 8,btPoint.y -8));
                }
                return true;
            }else if (_buttleOrientation == kRight){
                
                if (gid == 5){
                    
                    _mapLayer->destpryTile(ccp(btPoint.x + 8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y -8));
                    _mapLayer->destpryTile(ccp(btPoint.x+8,btPoint.y-8));
                }else if(gid == 33){
                    
                    _mapLayer->destpryTile(ccp(btPoint.x,btPoint.y + 8));
                    _mapLayer->destpryTile(ccp(btPoint.x +8,btPoint.y));
                    _mapLayer->destpryTile(ccp(btPoint.x +8,btPoint.y +8));
                }
                return true;
            }
            
        }else {
            return true;
        }
        
    }
    return false;
    
}

void TankSprite::bornInformation()
{
    // 出生动画
    this->animationBorn();
    // 保护层动画
    this->scheduleOnce(schedule_selector(TankSprite::animationShield), 1/2);
    this->scheduleOnce(schedule_selector(TankSprite::removeShield), 5);
}

void TankSprite::animationBorn()
{
    // 创建帧动画
    CCArray* array = new CCArray();
    array->retain();
    
    CCSpriteFrame* f1;
    for (int i =1 ; i < 5; i++) {
        CCString* name = CCString::createWithFormat("xing%1d.png",i);
        f1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        array->addObject(f1);
    }
    
    CCAnimation* anim = CCAnimation::createWithSpriteFrames(array);
    anim->setDelayPerUnit(0.2f);
    anim->setRestoreOriginalFrame(true);
    
    CCAnimate *animate = CCAnimate::create(anim);
    this->runAction(animate);
    
    array->removeAllObjects();
}

void TankSprite::animationShield()
{
    //
    //this->unschedule(schedule_selector(TankSprite::shieldAnimation));
    _isProtect = true;
    
    CCArray* array = CCArray::createWithCapacity(0);
    CCSpriteFrame* f1;
    for (int i = 1; i < 3; i++) {
        CCString* name = CCString::createWithFormat("shield%1d.png", i);
        f1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        array->addObject(f1);
    }
    
    CCAnimation* anim = CCAnimation::createWithSpriteFrames(array, 0.2);
    CCAnimate* animate = CCAnimate::create(anim);
    CCAction* action = CCRepeatForever::create(animate);
    
    CCSprite* backAn = CCSprite::create();
    // 精灵出生时，坐标为0，0
    backAn->setPosition(ccp(backAn->getPosition().x + this->getContentSize().width/2, backAn->getPosition().y + this->getContentSize().height/2));
    backAn->runAction(action);
    //将此执行动画的精灵加到坦克精灵上
    this->addChild(backAn, 1, 1001);
    
    array->removeAllObjects();
};

void TankSprite::removeShield()
{
    CCSprite* backAnim = (CCSprite*) (this->getChildByTag(1001));
    backAnim->removeFromParentAndCleanup(true);
    _isProtect = false;
}

void TankSprite::canFire2()
{
    _buttleCount = 0;
}

void TankSprite::checkEnemyKind(EnemySprite* aTank)
{
    
    CCSpriteFrame* frame;
    switch (aTank->_kind) {
            
        case kSlow:
            _isTankDone = true;
            break;

        case kQuike:
            _isTankDone = true;
            break;
        
        case kStrong:
            _isTankDone = true;
            break;
        
        case kStrongYellow:
            if (aTank->_life == 2){
                aTank->_life--;
                frame = FRAME("en6.png");
                aTank->_eKind = kStrong;
                aTank->setDisplayFrame(frame);
            }else {
                _isTankDone = true;
            }
            break;
        
        case kStrongRedLife3:
            
            if (aTank->_isRead) {
                //[_delegate createTool];
                aTank->_isRead = false;
            }
            if (aTank->_life == 3){
                aTank->_life--;
                frame = FRAME("en5.png");
                aTank->_eKind = kStrongYellow;
                aTank->setDisplayFrame(frame);
            }else if (aTank->_life == 2){
                aTank->_life--;
                aTank->_eKind = kStrong;
                frame = FRAME("en6.png");
                aTank->setDisplayFrame(frame);
            }
            else {
                _isTankDone = true;
            }
            break;
        
        case kStrongRed:
            
            //[_delegate createTool];
            _isTankDone = true;
            break;
    
        case kStrongGreen:
            if (aTank->_life == 3){
                aTank->_life--;
                aTank->_eKind = kStrongYellow;
                frame = FRAME("en5.png");
                aTank->setDisplayFrame(frame);
            }else if (aTank->_life == 2){
                aTank->_eKind = kStrong;
                aTank->_life--;
                frame = FRAME("en6.png");
                aTank->setDisplayFrame(frame);
            }
            else {
                _isTankDone = true;
            }
            break;
            
        
        case kQuikeR:
            
            //[_delegate createTool];
            _isTankDone = true;
            break;
        
        case kSlowR:
            
            //[_delegate createTool];
            _isTankDone = true;
            break;
        
        default:
            break;
    }
}

void TankSprite::animationBang()
{
    CCArray* array = new CCArray();
    CCSpriteFrame* f1;
    for (int i = 1; i < 3; i++) {
        CCString* name = CCString::createWithFormat("explode%1d.png", i);
        f1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());
        array->addObject(f1);
    }
    
    CCAnimation* anim = CCAnimation::createWithSpriteFrames(array, 0.1);
    anim->setRestoreOriginalFrame(true);
    
    CCAnimate *animate = CCAnimate::create(anim);
    this->runAction(animate);
    array->removeAllObjects();
}

bool TankSprite::checkBound()
{
    if ((_buttle->getPosition().y + _buttle->getContentSize().height/2) > _mapSize.height){
        return true;
    }
    else if((_buttle->getPosition().y - _buttle->getContentSize().height/2) < 0){
        return true;
    }
    else if((_buttle->getPosition().x - _buttle->getContentSize().width/2) < 0){
        return true;
    }
    else if((_buttle->getPosition().x + _buttle->getContentSize().width/2) > _mapSize.width){
        return true;
    }
    return true;
}
