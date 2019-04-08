#include "game_logic.h"
#include "game_map.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>

/*************************************************************************
*
*  函数名称：void game::game_init(unsigned int map[][], catcher catcher1, runner runner1)
*  功能说明：初始化游戏所有变量 （1）初始化冷却时间 （2）初始化生命和能量 （3）读取地图并自动找到逃跑者和抓捕者的位置
*  参数说明：**map:地图的二维数组名 catcher 抓捕者对象 runner 逃跑者对象
*  函数返回：无
*  修改时间：2018-07-09          未测试
*  备    注：无
*************************************************************************/

void game::game_init(unsigned int map[][map_size], catcher &catcher1, runner &runner1,QGraphicsScene *scene) {
    int i,j;
    for(i=0;i<map_size;i++){
        for(j=0;j<map_size;j++){
            map_cache[i][j]=map[i][j];
        }
    }

    catcher1.energy=energy_initial_value;
    runner1.lives=lives_initial_value;

    catcher1.skill_1_cooling=catcher_skill_1_initial_value;
    catcher1.skill_2_cooling=catcher_skill_2_initial_value;
    catcher1.skill_3_cooling=catcher_skill_3_initial_value;

    runner1.skill_1_cooling=runner_skill_1_initial_value/2;
    runner1.skill_2_cooling=runner_skill_2_initial_value/2;
    runner1.skill_3_cooling=runner_skill_3_initial_value/2;

    catcher1.direction=direction_null;
    catcher1.last_direction=direction_up;
    catcher1.skill_in=skill_null;

    catcher1.cather_skill_1_last=0;
    catcher1.cather_skill_1_state= 0;
    catcher1.cather_skill_2_last=0;
    catcher1.cather_skill_2_state= 0;
    catcher1.catcher_skill_3_graph_number=0;
    catcher1.catcher_skill_3_graph_cache_number=0;
    catcher1.catcher_skill_3_graph_start=0;

	runner1.runner_skill_3_last = 0;
	runner1.runner_skill_3_state = 0;

    runner1.direction=direction_null;
    runner1.last_direction=direction_up;
    runner1.skill_in=skill_null;

    runner1.speed_count=0;
    catcher1.speed_count=0;

    for(i=0;i<map_size;i++){
        for(j=0;j<map_size;j++){
            if(map[i][j]==map_runner){
                runner1.pos_x=j;
                runner1.pos_y=i;
                break;
            }
        }
    }

    for(i=0;i<map_size;i++){
        for(j=0;j<map_size;j++){
            if(map[i][j]==map_catcher){
                catcher1.pos_x=j;
                catcher1.pos_y=i;
                break;
            }
        }
    }

    for(i=0;i<40;i++)
    {
        for(j=0;j<40;j++){
        map_Graphdata[i][j]=new QGraphicsPixmapItem;
        }

    }
    runner1.graph=new QGraphicsPixmapItem;
    catcher1.graph=new QGraphicsPixmapItem;
    catcher1.graph_for_skill_1=new QGraphicsPixmapItem;
    QPixmap image;
         for(int i=0;i<40;i++)
         {
             for(int j=0;j<40;j++)

             {

                 switch(map_data[i][j])
                 {
                 case 0:
                      image.load(":/sourse/floor.jpg");
                      map_Graphdata[i][j]->setPixmap(image.scaled(20,20));
                      scene->addItem(map_Graphdata[i][j]);
                      map_Graphdata[i][j]->setPos(QPointF(-400+j*20,-400+i*20));
                     break;
                    case 1:
                     image.load(":/sourse/wall.jpg");
                     map_Graphdata[i][j]->setPixmap(image.scaled(20,20));
                     scene->addItem(map_Graphdata[i][j]);
                     map_Graphdata[i][j]->setPos(QPointF(-400+j*20,-400+i*20));
                     break;
                 case 2:
                     image.load(":/sourse/floor.jpg");
                     map_Graphdata[i][j]->setPixmap(image.scaled(20,20));
                     scene->addItem(map_Graphdata[i][j]);
                     map_Graphdata[i][j]->setPos(QPointF(-400+j*20,-400+i*20));
                     break;
                  case 3:
                     image.load(":/sourse/floor.jpg");
                     map_Graphdata[i][j]->setPixmap(image.scaled(20,20));
                     scene->addItem(map_Graphdata[i][j]);
                     map_Graphdata[i][j]->setPos(QPointF(-400+j*20,-400+i*20));
                     break;
                 case 4:
                     image.load(":/sourse/wall--.jpg");
                     map_Graphdata[i][j]->setPixmap(image.scaled(20,20));
                     scene->addItem(map_Graphdata[i][j]);
                     map_Graphdata[i][j]->setPos(QPointF(-400+j*20,-400+i*20));
                     break;
                 case 5:
                     image.load(":/sourse/runner.gif");
                     map_Graphdata[i][j]->setPixmap(image.scaled(20,20));
                     scene->addItem(map_Graphdata[i][j]);
                     map_Graphdata[i][j]->setPos(QPointF(-400+j*20,-400+i*20));
                     break;
                 default:
                     break;
                 }
}
         }
         image.load(":/sourse/light.jpg");
         catcher1.graph_for_skill_1->setPixmap(image.scaled(20,20));


         image.load(":/sourse/runner.gif");
         runner1.graph->setPixmap(image.scaled(20,20));
         scene->addItem(runner1.graph);
         runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));

         image.load(":/sourse/monster.jpg");
         catcher1.graph->setPixmap(image.scaled(20,20));
         scene->addItem(catcher1.graph);
         catcher1.graph->setPos(QPointF(-400+catcher1.pos_x*20,-400+catcher1.pos_y*20));


         for(i=0;i<map_size-2;i++){
         image.load(":/sourse/skill_3.jpg");
             catcher1.graph_for_skill_3[i]=new QGraphicsPixmapItem;
             catcher1.graph_for_skill_3[i]->setPixmap(image.scaled(20,20));
         }
}

/*************************************************************************
*
*  函数名称：unsigned int game::victor_judge(catcher catcher1, runner runner1)
*  功能说明：（1）判断抓捕者是否抓到逃跑者 （2）判断游戏结果
*  参数说明：catcher 抓捕者对象 runner 逃跑者对象
*  函数返回：0 没有结果 1 逃跑者胜利 2 抓捕者胜利
*  修改时间：2018-07-09      未测试
*  备    注：无
*************************************************************************/
unsigned int game::victor_judge(catcher &catcher1, runner &runner1) {
    unsigned int result=result_null;
		int x, y;
    if(abs(catcher1.pos_x-runner1.pos_x)<catch_distance&&abs(catcher1.pos_y-runner1.pos_y)<catch_distance){
        catcher1.energy+=energy_add;
        if(catcher1.energy>2000)catcher1.energy=2000;
        runner1.lives--;
        QSound::play(":/sourse/eat.wav");
		srand((unsigned)time(NULL));
		do {
			x = rand() % map_size;
			y = rand() % map_size;
		} while (map_cache[y][x] == map_Obstacle || map_cache[y][x] == map_catcher || map_cache[y][x] == map_temporary_obstacle || map_cache[y][x] == map_runner_part);
		//map_cache[runner1.pos_y][runner1.pos_x] = map_null;
		runner1.pos_x = x;
		runner1.pos_y = y;
        runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
		map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
    }
    if(runner1.lives==0)result=result_catcher_win;
    if(catcher1.energy==0)result=result_runner_win;
    return result;
}

/*************************************************************************
*
*  函数名称：void runner::keyboard_in()
*  功能说明：读取键值数据存入对象中
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-09
*  备    注：
*************************************************************************/
void runner::keyboard_in() {
    if(GetAsyncKeyState(0X57)){			//VK_W
        this->direction=direction_up;
    }else if(GetAsyncKeyState(0X53)){	//VK_S
        this->direction=direction_down;
    }else if(GetAsyncKeyState(0X41)){	//VK_A
        this->direction=direction_left;
    }else if(GetAsyncKeyState(0X44)){	//VK_D
        this->direction=direction_right;
    } else{
        this->direction=direction_null;
    }

    if(GetAsyncKeyState(0X46)){			//VK_F
        this->skill_in=skill_1_in;
    } else if(GetAsyncKeyState(0X47)){	//VK_G
        this->skill_in=skill_2_in;
    } else if(GetAsyncKeyState(0X48)){	//VK_H
        this->skill_in=skill_3_in;
    } else{
        this->skill_in=skill_null;
    }
}

/*************************************************************************
*
*  函数名称：void catcher::keyboard_in()
*  功能说明：读取键值数据存入对象中
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-09
*  备    注：
*************************************************************************/

void catcher::keyboard_in() {
    if(GetAsyncKeyState(VK_UP)){
        this->direction=direction_up;
    }else if(GetAsyncKeyState(VK_DOWN)){
        this->direction=direction_down;
    }else if(GetAsyncKeyState(VK_LEFT)){
        this->direction=direction_left;
    }else if(GetAsyncKeyState(VK_RIGHT)){
        this->direction=direction_right;
    } else{
        this->direction=direction_null;
    }

    if(GetAsyncKeyState(188)){               //触发 ，
        this->skill_in=skill_1_in;
    } else if(GetAsyncKeyState(190)){       //触发 。
        this->skill_in=skill_2_in;
    } else if(GetAsyncKeyState(191)){      //触发 /
        this->skill_in=skill_3_in;
    } else{
        this->skill_in=skill_null;
    }
}
/*************************************************************************
*
*  函数名称：void game::catcher_skill_1(catcher catcher1)
*  功能说明：抓捕者技能1（定身实现）
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-10          未测试
*  备    注：
*************************************************************************/
void game::catcher_skill_1(catcher &catcher1,runner runner1,QGraphicsScene *scene) {
    scene->addItem(catcher1.graph_for_skill_1);
    catcher1.graph_for_skill_1->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
    catcher1.cather_skill_1_state= 1;
    catcher1.cather_skill_1_last=catcher_skill_1_last_time;
    catcher1.skill_1_cooling+=catcher_skill_1_initial_value;
    catcher1.energy-=catcher_skill_1_cost;
    QSound::play(":/sourse/freze.wav");
}
/*************************************************************************
*
*  函数名称：void catcher_skill_2::write_map(map[][map_size])
*  功能说明：抓捕者技能2 地图写入实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-10      未测试
*  备    注：
*************************************************************************/
void catcher_skill_2::write_map(unsigned int map[][map_size],QGraphicsScene *scene) {
    QPixmap image;
    if(pos_x>map_size||pos_y>map_size||pos_x<0||pos_y<0){
        this->on_wall= true;
        return;
    }
    if(map[pos_y][pos_x]==map_Obstacle||map[pos_y][pos_x]==map_runner||map[pos_y][pos_x]==map_runner_part){
        this->on_wall= true;
    } else{
        this->on_wall= false;
        map[pos_y][pos_x]=map_temporary_obstacle;
        this->graph=new QGraphicsPixmapItem;
        image.load("C:/Users/yu/Desktop/UItry/sourse/wall--.jpg");
        this->graph->setPixmap(image.scaled(20,20));
        scene->addItem(this->graph);
        this->graph->setPos(QPointF(-400+pos_x*20,-400+pos_y*20));
    }
}
/*************************************************************************
*
*  函数名称：void catcher_skill_2::clear_map(map[][map_size])
*  功能说明：抓捕者技能2 地图清除实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-11      未测试
*  备    注：
*************************************************************************/
void catcher_skill_2::clear_map(unsigned int map[][map_size],QGraphicsScene *scene) {
    if(this->on_wall== 0){
        map[pos_y][pos_x]=map_null;
        scene->removeItem(this->graph);
        delete(this->graph);
    }
}
/*************************************************************************
*
*  函数名称：void game::catcher_skill_2(catcher catcher1)
*  功能说明：抓捕者技能二总实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-11          未测试
*  备    注：
*************************************************************************/

void game::catcher_skill_2(catcher &catcher1,QGraphicsScene *scene) {
    int x,y,i;
    switch (catcher1.last_direction){
        case direction_up:
            x=catcher1.pos_x-catcher_skill_2_length/2;
            y=catcher1.pos_y-catcher_skill_2_range;
            for (i = 0;  i<catcher_skill_2_length ; i++) {
				catcher1.catcher_skill_2_array[i].write_pos(x+i,y);
                catcher1.catcher_skill_2_array[i].write_map(map_cache,scene);
            }
            break;
        case direction_down:
            x=catcher1.pos_x-catcher_skill_2_length/2;
            y=catcher1.pos_y+catcher_skill_2_range;
            for (i = 0;  i<catcher_skill_2_length ; i++) {
				catcher1.catcher_skill_2_array[i].write_pos(x+i,y);
                catcher1.catcher_skill_2_array[i].write_map(map_cache,scene);
            }
            break;
        case direction_left:
            x=catcher1.pos_x-catcher_skill_2_range;
            y=catcher1.pos_y-catcher_skill_2_length/2;
            for (i = 0;  i<catcher_skill_2_length ; i++) {
				catcher1.catcher_skill_2_array[i].write_pos(x,y+i);
                catcher1.catcher_skill_2_array[i].write_map(map_cache,scene);
            }
            break;
        case direction_right:
            x=catcher1.pos_x+catcher_skill_2_range;
            y=catcher1.pos_y-catcher_skill_2_length/2;
            for (i = 0;  i<catcher_skill_2_length ; i++) {
				catcher1.catcher_skill_2_array[i].write_pos(x,y+i);
                catcher1.catcher_skill_2_array[i].write_map(map_cache,scene);
            }
            break;
    }
    catcher1.cather_skill_2_state= 1;
    catcher1.cather_skill_2_last+=catcher_skill_2_last_time;
    catcher1.skill_2_cooling+=catcher_skill_2_initial_value;
    catcher1.energy-=catcher_skill_2_cost;
    QSound::play(":/sourse/create.wav");
}
/*************************************************************************
*
*  函数名称：void game::catcher_skill_3(catcher catcher1,runner runner1)
*  功能说明：抓捕者第三个技能实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-11      未测试
*  备    注：              未设置显示对接接口
*************************************************************************/
void game::catcher_skill_3(catcher &catcher1,runner &runner1,QGraphicsScene *scene) {
    int i,x,y,count=0;
    QSound::play(":/sourse/boom.wav");
    catcher1.catcher_skill_3_graph_start=1;
    catcher1.catcher_skill_3_graph_cache_number=0;
	srand((unsigned)time(NULL));
    switch (catcher1.last_direction){
        case direction_up:
			for (i = 1; i < map_size; i++) {
				if (catcher1.pos_y - i < 0)break;
				if (map_cache[catcher1.pos_y - i][catcher1.pos_x] == map_runner) {
					catcher1.energy += energy_add;
					runner1.lives--;
                    scene->addItem(catcher1.graph_for_skill_3[i-1]);
                    catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+(catcher1.pos_y-i)*20));
                    count++;
                    QSound::play(":/sourse/dead.wav");
					do {
						x = rand() % map_size;
						y = rand() % map_size;
					} while (map_cache[y][x] == map_Obstacle || map_cache[y][x] == map_catcher || map_cache[y][x] == map_temporary_obstacle || map_cache[y][x] == map_runner_part);
                    map_cache[runner1.pos_y][runner1.pos_x] = map_null;
					runner1.pos_x = x;
					runner1.pos_y = y;
					map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                    runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                    Sleep(runner_skill_3_delay);
					break;
				}
				if (map_cache[catcher1.pos_y - i][catcher1.pos_x] == map_Obstacle || map_cache[catcher1.pos_y - i][catcher1.pos_x] == map_temporary_obstacle) {
                    //!!!!!!!!!!!!!!!!!!!!!
					Sleep(runner_skill_3_delay);
					break;
				}
                scene->addItem(catcher1.graph_for_skill_3[i-1]);
                catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+(catcher1.pos_y-i)*20));
                count++;
            }
            break;
        case direction_down:
			for (i = 1; i < map_size; i++) {
				if (catcher1.pos_y + i > map_size)break;
				if (map_cache[catcher1.pos_y + i][catcher1.pos_x] == map_runner) {
					catcher1.energy += energy_add;
					runner1.lives--;
                    scene->addItem(catcher1.graph_for_skill_3[i-1]);
                    catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+(catcher1.pos_y+i)*20));
                    count++;
                    QSound::play(":/sourse/dead.wav");
					do {
						x = rand() % map_size;
						y = rand() % map_size;
					} while (map_cache[y][x] == map_Obstacle || map_cache[y][x] == map_catcher || map_cache[y][x] == map_temporary_obstacle || map_cache[y][x] == map_runner_part);
					map_cache[runner1.pos_y][runner1.pos_x] = map_null;
					runner1.pos_x = x;
					runner1.pos_y = y;
					map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                    runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                    Sleep(runner_skill_3_delay);
                    break;
				}
				if (map_cache[catcher1.pos_y + i][catcher1.pos_x] == map_Obstacle || map_cache[catcher1.pos_y + i][catcher1.pos_x] == map_temporary_obstacle) {
                    //!!!!!!!!!!!!!!!!!!!!!
					Sleep(runner_skill_3_delay);
					break;
                }
                scene->addItem(catcher1.graph_for_skill_3[i-1]);
                catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+(catcher1.pos_y+i)*20));
                count++;
            }

            
            break;
        case direction_left:
			for (i = 1; i < map_size; i++) {
				if (catcher1.pos_x - i < 0)break;
				if (map_cache[catcher1.pos_y][catcher1.pos_x - i] == map_runner) {
					catcher1.energy += energy_add;
					runner1.lives--;
                    scene->addItem(catcher1.graph_for_skill_3[i-1]);
                    catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x-i)*20,-400+(catcher1.pos_y)*20));
                    count++;
                    QSound::play(":/sourse/dead.wav");
					do {
						x = rand() % map_size;
						y = rand() % map_size;
					} while (map_cache[y][x] == map_Obstacle || map_cache[y][x] == map_catcher || map_cache[y][x] == map_temporary_obstacle || map_cache[y][x] == map_runner_part);
					map_cache[runner1.pos_y][runner1.pos_x] = map_null;
					runner1.pos_x = x;
					runner1.pos_y = y;
					map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                        runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                    Sleep(runner_skill_3_delay);
                    break;
				}
				if (map_cache[catcher1.pos_y][catcher1.pos_x - i] == map_Obstacle || map_cache[catcher1.pos_y][catcher1.pos_x - i] == map_temporary_obstacle) {
                    //!!!!!!!!!!!!!!!!!!!!!
					Sleep(runner_skill_3_delay);
					break;
                }
                scene->addItem(catcher1.graph_for_skill_3[i-1]);
                catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x-i)*20,-400+(catcher1.pos_y)*20));
                count++;
            }
            
            break;
        case direction_right:
			for (i = 1; i < map_size; i++) {
				if (catcher1.pos_x + i > map_size)break;
				if (map_cache[catcher1.pos_y][catcher1.pos_x + i] == map_runner) {
					catcher1.energy += energy_add;
					runner1.lives--;
                    scene->addItem(catcher1.graph_for_skill_3[i-1]);
                    catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x+i)*20,-400+(catcher1.pos_y)*20));
                    count++;
                    QSound::play(":/sourse/dead.wav");
					do {
						x = rand() % map_size;
						y = rand() % map_size;
					} while (map_cache[y][x] == map_Obstacle || map_cache[y][x] == map_catcher || map_cache[y][x] == map_temporary_obstacle || map_cache[y][x] == map_runner_part);
					map_cache[runner1.pos_y][runner1.pos_x] = map_null;
					runner1.pos_x = x;
					runner1.pos_y = y;
					map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                        runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                    Sleep(runner_skill_3_delay);
                    break;
				}
				if (map_cache[catcher1.pos_y][catcher1.pos_x + i] == map_Obstacle || map_cache[catcher1.pos_y][catcher1.pos_x + i] == map_temporary_obstacle) {
                    //!!!!!!!!!!!!!!!!!!!!!
					Sleep(runner_skill_3_delay);
					break;
                }
                scene->addItem(catcher1.graph_for_skill_3[i-1]);
                catcher1.graph_for_skill_3[i-1]->setPos(QPointF(-400+(catcher1.pos_x+i)*20,-400+(catcher1.pos_y)*20));
                count++;
            }

            
            break;
    }
    catcher1.catcher_skill_3_graph_number=count;
    catcher1.skill_3_cooling+=catcher_skill_3_initial_value;
    catcher1.energy-=catcher_skill_3_cost;
}
/*************************************************************************
*
*  函数名称：void game::runner_skill_1(runner runner1)
*  功能说明：逃跑者技能一实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-11          未测试
*  备    注：
*************************************************************************/
void game::runner_skill_1(runner &runner1) {
    switch (runner1.last_direction) {
        case direction_up:
            if(runner1.pos_y-runner_skill_1_range<0)return;
            if(map_cache[runner1.pos_y-runner_skill_1_range][runner1.pos_x]!=map_Obstacle&&
               map_cache[runner1.pos_y-runner_skill_1_range][runner1.pos_x]!=map_catcher&&
               map_cache[runner1.pos_y-runner_skill_1_range][runner1.pos_x]!=map_temporary_obstacle){
                map_cache[runner1.pos_y][runner1.pos_x]=map_null;
                runner1.pos_y-=runner_skill_1_range;
                runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                map_cache[runner1.pos_y][runner1.pos_x]=map_runner;
            } else return;
            break;
        case direction_down:
            if(runner1.pos_y+runner_skill_1_range>map_size)return;
            if(map_cache[runner1.pos_y+runner_skill_1_range][runner1.pos_x]!=map_Obstacle&&
               map_cache[runner1.pos_y+runner_skill_1_range][runner1.pos_x]!=map_catcher&&
               map_cache[runner1.pos_y+runner_skill_1_range][runner1.pos_x]!=map_temporary_obstacle){
                map_cache[runner1.pos_y][runner1.pos_x]=map_null;
                runner1.pos_y+=runner_skill_1_range;
                runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                map_cache[runner1.pos_y][runner1.pos_x]=map_runner;
            } else return;
            break;
        case direction_left:
            if(runner1.pos_x-runner_skill_1_range<0)return;
            if(map_cache[runner1.pos_y][runner1.pos_x-runner_skill_1_range]!=map_Obstacle&&
               map_cache[runner1.pos_y][runner1.pos_x-runner_skill_1_range]!=map_catcher&&
               map_cache[runner1.pos_y][runner1.pos_x-runner_skill_1_range]!=map_temporary_obstacle){
                map_cache[runner1.pos_y][runner1.pos_x]=map_null;
                runner1.pos_x-=runner_skill_1_range;
                runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                map_cache[runner1.pos_y][runner1.pos_x]=map_runner;
            } else return;
            break;
        case direction_right:
            if(runner1.pos_x+runner_skill_1_range>map_size)return;
            if(map_cache[runner1.pos_y][runner1.pos_x+runner_skill_1_range]!=map_Obstacle&&
               map_cache[runner1.pos_y][runner1.pos_x+runner_skill_1_range]!=map_catcher&&
               map_cache[runner1.pos_y][runner1.pos_x+runner_skill_1_range]!=map_temporary_obstacle){
                map_cache[runner1.pos_y][runner1.pos_x]=map_null;
                runner1.pos_x+=runner_skill_1_range;
                runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
                map_cache[runner1.pos_y][runner1.pos_x]=map_runner;
            } else return;
            break;
    }
    runner1.skill_1_cooling+=runner_skill_1_initial_value;
    QSound::play(":/sourse/go.wav");
}
/*************************************************************************
*
*  函数名称：void game::runner_skill_2(runner runner1)
*  功能说明：逃亡者技能二实现函数
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12          未测试
*  备    注：
*************************************************************************/
void game::runner_skill_2(runner &runner1) {
    int x,y;
    srand((unsigned)time(NULL));
    do{
        x=rand()%map_size;
        y=rand()%map_size;
    }while (map_cache[y][x]==map_Obstacle||map_cache[y][x]==map_catcher||map_cache[y][x]==map_temporary_obstacle||map_cache[y][x]==map_runner_part);
    map_cache[runner1.pos_y][runner1.pos_x]=map_null;
    runner1.pos_x=x;
    runner1.pos_y=y;
    map_cache[runner1.pos_y][runner1.pos_x]=map_runner;
    runner1.graph->setPos(QPointF(-400+runner1.pos_x*20,-400+runner1.pos_y*20));
    runner1.skill_2_cooling+=runner_skill_2_initial_value;
    QSound::play(":/sourse/fly.wav");
}

/*************************************************************************
*
*  函数名称：void game::catcher_skill_2_clear(catcher catcher1)
*  功能说明：抓捕者清除障碍物总命令
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12
*  备    注：
*************************************************************************/
void game::catcher_skill_2_clear(catcher &catcher1,QGraphicsScene *scene) {
    int i;
    catcher1.cather_skill_2_state= false;
    catcher1.skill_2_cooling+=catcher_skill_2_initial_value;
    for (i = 0;  i<catcher_skill_2_length ;i ++) {
        catcher1.catcher_skill_2_array[i].clear_map(map_cache,scene);
    }
}
/*************************************************************************
*
*  函数名称：void runner_skill_3::move(unsigned int map[][map_size])
*  功能说明：逃跑者单个分身移动实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12
*  备    注：
*************************************************************************/
void runner_skill_3::move(unsigned int map[][map_size],runner runner1) {
    unsigned int judge= 0;
    do{ if(rand()%4) direction = runner1.direction;
        else direction=rand()%4+1;
        switch (direction){
            case direction_up:
                if(map[pos_y-1][pos_x]==map_null){
                    judge= 0X0F;
                    map[pos_y][pos_x]=map_null;
                    pos_y--;
                    this->graph->setPos(QPointF(-400+pos_x*20,-400+pos_y*20));
                    map[pos_y][pos_x]=map_runner_part;
                }
                else judge|=0X01;
                break;
            case direction_down:
                if(map[pos_y+1][pos_x]==map_null){
                    judge= 0X0F;
                    map[pos_y][pos_x]=map_null;
                    pos_y++;
                    this->graph->setPos(QPointF(-400+pos_x*20,-400+pos_y*20));
                    map[pos_y][pos_x]=map_runner_part;
                }
                else judge|=0X02;
                break;
            case direction_left:
                if(map[pos_y][pos_x-1]==map_null){
                    judge= 0X0F;
                    map[pos_y][pos_x]=map_null;
                    pos_x--;
                    this->graph->setPos(QPointF(-400+pos_x*20,-400+pos_y*20));
                    map[pos_y][pos_x]=map_runner_part;
                }
                else judge|=0X04;
                break;
            case direction_right:
                if(map[pos_y][pos_x+1]==map_null){
                    judge= 0X0F;
                    map[pos_y][pos_x]=map_null;
                    pos_x++;
                    this->graph->setPos(QPointF(-400+pos_x*20,-400+pos_y*20));
                    map[pos_y][pos_x]=map_runner_part;
                }
                else judge|=0X08;
                break;
        }
    }while(judge !=0X0F);
}
/*************************************************************************
*
*  函数名称：runner_skill_3::create(unsigned int map[][map_size], int pos_y, int pos_x)
*  功能说明：逃跑者单个分身创造
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12
*  备    注：
*************************************************************************/
void runner_skill_3::create(unsigned int map[][map_size], int pos_y, int pos_x,QGraphicsScene *scene){
    QPixmap image;
    this->pos_y=pos_y;
    this->pos_x=pos_x;
    if(map[pos_y][pos_x]!=map_Obstacle)
    map[pos_y][pos_x]=map_runner_part;
    this->graph=new QGraphicsPixmapItem;
    image.load(":/sourse/runner.gif");
    this->graph->setPixmap(image.scaled(20,20));
    scene->addItem(this->graph);
    this->graph->setPos(QPointF(-400+pos_x*20,-400+pos_y*20));
}
/*************************************************************************
*
*  函数名称：void runner_skill_3::clear(unsigned intmap[][map_size])
*  功能说明：逃亡者单个分身清除
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12
*  备    注：
*************************************************************************/
void runner_skill_3::clear(unsigned int map[][map_size],QGraphicsScene *scene){
    map[pos_y][pos_x]=map_null;
    scene->removeItem(this->graph);
    delete(this->graph);
    pos_y=-1;
    pos_x=-1;
}
/*************************************************************************
*
*  函数名称：game::runner_skill_3(runner runner1)
*  功能说明：逃亡者技能3总实现
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12
*  备    注：
*************************************************************************/
void game::runner_skill_3(runner &runner1,QGraphicsScene *scene) {
    runner1.runner_skill_3_array[0].create(map_cache,runner1.pos_y-1,runner1.pos_x,scene);
    runner1.runner_skill_3_array[1].create(map_cache,runner1.pos_y+1,runner1.pos_x,scene);
    runner1.runner_skill_3_array[2].create(map_cache,runner1.pos_y,runner1.pos_x-1,scene);
    runner1.runner_skill_3_array[3].create(map_cache,runner1.pos_y,runner1.pos_x+1,scene);
	runner1.runner_skill_3_state = 1;
	runner1.runner_skill_3_last += runner_skill_3_last_time;
    runner1.skill_3_cooling+=runner_skill_3_initial_value;
    QSound::play(":/sourse/to4.wav");
}

/*************************************************************************
*
*  函数名称：void game::all_move(catcher catcher1, runner runner1)
*  功能说明：所有可移动实体的移动函数
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-12
*  备    注：
*************************************************************************/
void game::all_move(catcher &catcher1, runner &runner1) {
    int i;
    catcher1.speed_count++;
    runner1.speed_count++;
    if(catcher1.speed_count>=catcher_speed){
        catcher1.speed_count = 0;
        switch (catcher1.direction){
            case direction_up:
                if(map_cache[catcher1.pos_y-1][catcher1.pos_x]==map_null||
                   map_cache[catcher1.pos_y-1][catcher1.pos_x]==map_runner||
                   map_cache[catcher1.pos_y-1][catcher1.pos_x]==map_runner_part){
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_null;
                    catcher1.pos_y--;
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_catcher;
                    catcher1.graph->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+catcher1.pos_y*20));
                    catcher1.last_direction=catcher1.direction;
                    catcher1.energy--;

                }
                break;
            case direction_down:
                if(map_cache[catcher1.pos_y+1][catcher1.pos_x]==map_null||
                   map_cache[catcher1.pos_y+1][catcher1.pos_x]==map_runner||
                   map_cache[catcher1.pos_y+1][catcher1.pos_x]==map_runner_part){
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_null;
                    catcher1.pos_y++;
                    catcher1.graph->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+catcher1.pos_y*20));
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_catcher;
                    catcher1.last_direction=catcher1.direction;
                    catcher1.energy--;
                }
                break;
            case direction_left:
                if(map_cache[catcher1.pos_y][catcher1.pos_x-1]==map_null||
                   map_cache[catcher1.pos_y][catcher1.pos_x-1]==map_runner||
                   map_cache[catcher1.pos_y][catcher1.pos_x-1]==map_runner_part){
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_null;
                    catcher1.pos_x--;
                    catcher1.graph->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+catcher1.pos_y*20));
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_catcher;
                    catcher1.last_direction=catcher1.direction;
                    catcher1.energy--;
                }
                break;
            case direction_right:
                if(map_cache[catcher1.pos_y][catcher1.pos_x+1]==map_null||
                   map_cache[catcher1.pos_y][catcher1.pos_x+1]==map_runner||
                   map_cache[catcher1.pos_y][catcher1.pos_x+1]==map_runner_part){
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_null;
                    catcher1.pos_x++;
                    catcher1.graph->setPos(QPointF(-400+(catcher1.pos_x)*20,-400+catcher1.pos_y*20));
                    map_cache[catcher1.pos_y][catcher1.pos_x]=map_catcher;
                    catcher1.last_direction=catcher1.direction;
                    catcher1.energy--;
                }
                break;
        }
        catcher1.direction=direction_null;
    }
    if(runner1.speed_count>=runner_speed){
        runner1.speed_count = 0;
        if(catcher1.cather_skill_1_last);
        else {
            switch (runner1.direction) {
                case direction_up:
                    if (map_cache[runner1.pos_y - 1][runner1.pos_x] == map_null ||
                        map_cache[runner1.pos_y - 1][runner1.pos_x] == map_catcher ||
                        map_cache[runner1.pos_y - 1][runner1.pos_x] == map_runner_part) {
                        map_cache[runner1.pos_y][runner1.pos_x] = map_null;
                        runner1.pos_y--;
                        runner1.graph->setPos(QPointF(-400+(runner1.pos_x)*20,-400+runner1.pos_y*20));
                        map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                        runner1.last_direction=runner1.direction;
                    }
                    break;
                case direction_down:
                    if (map_cache[runner1.pos_y + 1][runner1.pos_x] == map_null ||
                        map_cache[runner1.pos_y + 1][runner1.pos_x] == map_catcher ||
                        map_cache[runner1.pos_y + 1][runner1.pos_x] == map_runner_part) {
                        map_cache[runner1.pos_y][runner1.pos_x] = map_null;
                        runner1.pos_y++;
                        runner1.graph->setPos(QPointF(-400+(runner1.pos_x)*20,-400+runner1.pos_y*20));
                        map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                        runner1.last_direction=runner1.direction;
                    }
                    break;
                case direction_left:
                    if (map_cache[runner1.pos_y][runner1.pos_x - 1] == map_null ||
                        map_cache[runner1.pos_y][runner1.pos_x - 1] == map_catcher ||
                        map_cache[runner1.pos_y][runner1.pos_x - 1] == map_runner_part) {
                        map_cache[runner1.pos_y][runner1.pos_x] = map_null;
                        runner1.pos_x--;
                        runner1.graph->setPos(QPointF(-400+(runner1.pos_x)*20,-400+runner1.pos_y*20));
                        map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                        runner1.last_direction=runner1.direction;
                    }
                    break;
                case direction_right:
                    if (map_cache[runner1.pos_y][runner1.pos_x + 1] == map_null ||
                        map_cache[runner1.pos_y][runner1.pos_x + 1] == map_catcher ||
                        map_cache[runner1.pos_y][runner1.pos_x + 1] == map_runner_part) {
                        map_cache[runner1.pos_y][runner1.pos_x] = map_null;
                        runner1.pos_x++;
                        runner1.graph->setPos(QPointF(-400+(runner1.pos_x)*20,-400+runner1.pos_y*20));
                        map_cache[runner1.pos_y][runner1.pos_x] = map_runner;
                        runner1.last_direction=runner1.direction;
                    }
                    break;
            }
            if(runner1.runner_skill_3_last){
                for(i=0;i<4;i++){
                    runner1.runner_skill_3_array[i].move(map_cache,runner1);
                }
            }else if(runner1.runner_skill_3_state){
                runner1.runner_skill_3_state= false;
                for (i=0;i<4;i++){
                    runner1.runner_skill_3_array[i].clear(map_cache,scene);
                }
            }
            runner1.direction=direction_null;
        }
    }
}
/*************************************************************************
*
*  函数名称：void game::all_skill(catcher catcher1, runner runner1)
*  功能说明：检测输入的技能并执行释放技能函数
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-16
*  备    注：
*************************************************************************/

void game::all_skill(catcher &catcher1, runner &runner1,QGraphicsScene *scene) {
    switch (catcher1.skill_in){
        case skill_1_in:
			if(!catcher1.skill_1_cooling)
            this->catcher_skill_1(catcher1,runner1,scene);
            break;
        case skill_2_in:
			if (!catcher1.skill_2_cooling)
            this->catcher_skill_2(catcher1,scene);
            break;
        case skill_3_in:
			if (!catcher1.skill_3_cooling)
            this->catcher_skill_3(catcher1,runner1,scene);
            break;
    }
    switch (runner1.skill_in){
        case skill_1_in:
			if(!runner1.skill_1_cooling)
            this->runner_skill_1(runner1);
            break;
        case skill_2_in:
			if (!runner1.skill_2_cooling)
            this->runner_skill_2(runner1);
            break;
        case skill_3_in:
			if (!runner1.skill_3_cooling)
            this->runner_skill_3(runner1,scene);
            break;
    }
}

/*************************************************************************
*
*  函数名称：void game::all_skill_clear(catcher catcher1, runner runner1)
*  功能说明：清空延时性技能
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-16
*  备    注：
*************************************************************************/
void game::all_skill_clear(catcher &catcher1, runner &runner1,QGraphicsScene *scene) {
    int i;
    if(catcher1.cather_skill_2_state == 1){
        if(catcher1.cather_skill_2_last==0){
            for (i = 0;  i<catcher_skill_2_length ; i++) {
                catcher1.catcher_skill_2_array[i].clear_map(this->map_cache,scene);
                catcher1.cather_skill_2_state= 0;
            }
        }
    }
    if(catcher1.cather_skill_1_state == 1){
        if(catcher1.cather_skill_1_last==0){
           catcher1.cather_skill_1_state =0;
           scene->removeItem(catcher1.graph_for_skill_1);
        }
    }
    if(runner1.runner_skill_3_state == 1){
        if(runner1.runner_skill_3_last==0){
            for (i = 0;  i<4 ; i++) {
                runner1.runner_skill_3_array[i].clear(this->map_cache,scene);
                runner1.runner_skill_3_state= 0;
            }
        }
    }


}
/*************************************************************************
*
*  函数名称：void game::all_skill_clear(catcher catcher1, runner runner1)
*  功能说明：清空延时性技能
*  参数说明：无
*  函数返回：无
*  修改时间：2018-07-16
*  备    注：
*************************************************************************/
void game::timer(catcher &catcher1, runner &runner1) {
	if (catcher1.cather_skill_1_last) {
		catcher1.cather_skill_1_last--;
    }else if (catcher1.skill_1_cooling) {
        catcher1.skill_1_cooling--;
    }

	if (catcher1.cather_skill_2_last) {
		catcher1.cather_skill_2_last--;
    } else	if (catcher1.skill_2_cooling) {
        catcher1.skill_2_cooling--;
    }

	if (runner1.runner_skill_3_last) {
		runner1.runner_skill_3_last--;
    } else 	if (runner1.skill_3_cooling) {
        runner1.skill_3_cooling--;
    }


	if (catcher1.skill_3_cooling) {
		catcher1.skill_3_cooling--;
	}

	if (runner1.skill_1_cooling) {
		runner1.skill_1_cooling--;
	}

	if (runner1.skill_2_cooling) {
		runner1.skill_2_cooling--;
	}


}
