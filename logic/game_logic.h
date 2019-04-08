#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QDebug>

#define energy_initial_value 1000
#define lives_initial_value 3

#define map_size 40

#define catcher_skill_1_cost 20
#define catcher_skill_2_cost 30
#define catcher_skill_3_cost 50

#define catcher_skill_1_initial_value 2//20
#define catcher_skill_2_initial_value 2//15
#define catcher_skill_3_initial_value 2//60

#define runner_skill_1_initial_value 2//15
#define runner_skill_2_initial_value 2//25
#define runner_skill_3_initial_value 2//35

#define direction_null 0
#define direction_up 1
#define direction_down 2
#define direction_left 3
#define direction_right 4

#define skill_null 0
#define skill_1_in 1
#define skill_2_in 2
#define skill_3_in 3

#define result_null 0
#define result_runner_win 1
#define result_catcher_win 2

#define catch_distance 1
#define energy_add 1000

#define catcher_skill_1_last_time 1
#define catcher_skill_2_last_time 20
#define runner_skill_3_last_time 20

#define catcher_skill_2_length 9
#define catcher_skill_2_range 5

#define runner_skill_1_range 4

#define runner_speed 5
#define catcher_speed 4

#define runner_skill_3_delay 0
class runner;
class catcher_skill_2{
private:
     int pos_x;
     int pos_y;
     int on_wall;
     QGraphicsPixmapItem * graph;
public:
	catcher_skill_2(){pos_x=-1;pos_y=-1;on_wall=true;}
    void write_pos(int x, int y){pos_y=y;pos_x=x;}
    void write_map(unsigned int map[][map_size],QGraphicsScene *scene);
    void clear_map(unsigned int map[][map_size],QGraphicsScene *scene);
};

class runner_skill_3{
private:
    int pos_x;
    int pos_y;
    unsigned int direction;
    QGraphicsPixmapItem * graph;
public:
	runner_skill_3() { direction = direction_up; pos_x = 0; pos_y = 0; }
    void create(unsigned int map[][map_size], int pos_y, int pos_x,QGraphicsScene *scene);
    void move(unsigned int map[][map_size],runner runner1);
    void clear(unsigned int map[][map_size],QGraphicsScene *scene);
};

class player{
protected:
     int pos_x;
     int pos_y;
    unsigned int direction;
    unsigned int last_direction;
    unsigned int skill_in;
    unsigned int skill_1_cooling;
    unsigned int skill_2_cooling;
    unsigned int skill_3_cooling;
    unsigned int speed_count;
    QGraphicsPixmapItem * graph;
public:
    unsigned int get_skill_1_cooling(){return skill_1_cooling;}
    unsigned int get_skill_2_cooling(){return skill_2_cooling;}
    unsigned int get_skill_3_cooling(){return skill_3_cooling;}
};

class catcher : public player{
protected:
    unsigned int energy;
    unsigned int cather_skill_1_last;
    unsigned int cather_skill_1_state;
    QGraphicsPixmapItem *graph_for_skill_1 ;
    unsigned int cather_skill_2_last;
    unsigned int cather_skill_2_state;
    catcher_skill_2 catcher_skill_2_array[catcher_skill_2_length];
public:
    unsigned int get_cather_skill_1_last(){return cather_skill_1_last;}
    unsigned int get_cather_skill_2_last(){return cather_skill_2_last;}
    unsigned int catcher_skill_3_graph_start;
    QGraphicsPixmapItem *graph_for_skill_3[map_size-2];
    unsigned int catcher_skill_3_graph_number;
    unsigned int catcher_skill_3_graph_cache_number;
    void keyboard_in();
    unsigned int get_energy(){return this->energy;}
    friend class game;
};

class runner : public player{
protected:
    unsigned int lives;
    unsigned int runner_skill_3_last;
    unsigned int runner_skill_3_state;
    runner_skill_3 runner_skill_3_array[4];
public:
    void keyboard_in();
    unsigned int get_runner_skill_3_last(){return runner_skill_3_last;}
    unsigned int get_lives(){return lives;}
    friend class game;
    friend class runner_skill_3;
};

class game {
protected:
public:
    unsigned int map_cache[map_size][map_size];
    void game_init(unsigned int map[][map_size],catcher &catcher1,runner &runner1,QGraphicsScene *scene);
    unsigned int victor_judge(catcher &catcher1,runner &runner1);
    void all_move(catcher &catcher1,runner &runner1);
    void all_skill(catcher &catcher1,runner &runner1,QGraphicsScene *scene);
    void all_skill_clear(catcher &catcher1,runner &runner1,QGraphicsScene *scene);
    void catcher_skill_1(catcher &catcher1,runner runner1,QGraphicsScene *scene);
    void catcher_skill_2(catcher &catcher1,QGraphicsScene *scene);
    void catcher_skill_2_clear(catcher &catcher1,QGraphicsScene *scene);
    void catcher_skill_3(catcher &catcher1,runner &runner1,QGraphicsScene *scene);
    void runner_skill_1(runner &runner1);
    void runner_skill_2(runner &runner1);
    void runner_skill_3(runner &runner1,QGraphicsScene *scene);
	void timer(catcher &catcher1, runner &runner1);
    void debug(catcher &catcher1, runner &runner1){
        qDebug() << runner1.runner_skill_3_last;
        qDebug() << catcher1.cather_skill_2_last;
    }
    friend class catcher_skill_2;
};


#endif //_GAME_LOGIC_H
