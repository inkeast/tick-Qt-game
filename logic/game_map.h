/***********************************************************************************************************************
 地图说明：
 数组中 0 表示 空地
        1 表示 障碍物
        2 表示 追捕者初始位置
        3 表示 逃跑者初始位置
        4 表示 临时障碍物？？？
 **********************************************************************************************************************/
#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <QGraphicsItem>

#define map_null 0
#define map_Obstacle 1
#define map_catcher 2
#define map_runner 3
#define map_temporary_obstacle 4
#define map_runner_part 5
#define map_runner_skill_3_part 6

extern unsigned int map_data[40][40];
extern QGraphicsPixmapItem *map_Graphdata[40][40];
#endif //_GAME_MAP_H
