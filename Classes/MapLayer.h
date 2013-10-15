//
//  MapLayer.h
//  TankWar
//
//  Created by user on 13-9-3.
//
//

#ifndef __TankWar__MapLayer__
#define __TankWar__MapLayer__

#include <iostream>
#include "cocos2d.h"

#include "TankSprite.h"
#include "EnemySprite.h"

USING_NS_CC;

class MapLayer : public cocos2d::CCLayerColor
{
public:
    CREATE_FUNC(MapLayer);
    virtual ~MapLayer(void);
    
    bool init();
    
    /**
     *	@brief	使用传入的参数初始化地图层
     *
     *	@param 	leve 	游戏关数，依据该参数选择tmx地图
     *	@param 	tKind 	坦克类型
     *	@param 	numLife 	坦克生命值
     */
    void initWithMap(int leve, int tKind, int numLife);
    
    
    /**
     *	@brief	根据对象名从对象层获取对象的坐标
     *
     *	@param 	group 	对象层的所有对象
     *	@param 	object 	要获取的对象名字
     *
     *	@return	要获取的对象坐标
     */
    CCPoint objectPosition(CCTMXObjectGroup *group, const char *object);

    /**
     *	@brief	将触摸点的坐标转为Tmx地图上的坐标
     *
     *	@param 	pos 	触摸点的坐标
     *
     *	@return	Tmx地图上的坐标
     */
    CCPoint tileCoordinateFromPosition(CCPoint pos);

    /**
     *	@brief	将Tmx地图坐标转为瓦片值tileID，当tileID为0的时候表示该坐标上没有瓦片
     *
     *	@param 	pos 	Tmx地图上的坐标点
     *
     *	@return	0   该地图坐标上没有瓦片
     *  @return -1  该地图坐标不在地图上
     *  @return others  该地图坐标在地图上
     */
    int tileIDFromPosition(CCPoint pos);
    
    void destpryTile(CCPoint pos);
    
    void initAIPlistFile();

    void initEnemys();
    
    void gotoScoreScene();
    
    void gameOver();
    
    void removeSprite(TankSprite* aTank);
    
    void removeSelfFromMap();
    
    TankSprite *_tank1;
public:
    cocos2d::CCTMXLayer* _bg1Layer;
    cocos2d::CCTMXLayer* _bg2Layer;
    CCTMXTiledMap *_map;
    
    CCSprite* _home;
    CCRect _homeRect;
    
    CCDictionary* _remoteSpheres;
    
    int _enemyNum;
    
    CCArray* _enemyArray;
    CCArray* _toolArray;
    CCTMXObjectGroup* _objects;
    CCDictionary* _aiDic;
    
    
    int _slowTankCount;
    int _quikeTankCount;
    int _strongTankCount;
    
    int _rodamPoint;
    CCArray* _pointArray;
    CCPoint _tmpPoint;
    CCArray* _propArray;
    
    int _slow;
    int _quike;
    int _strong;
    int _strongYe;
    int _strongG;
    int _leve;
    int _bornNum;
    bool _isGameOver;
    
    EnemySprite* _tTank;
};
#endif /* defined(__TankWar__MapLayer__) */
