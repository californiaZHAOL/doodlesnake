#pragma once
#include <graphics.h> 
#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#pragma comment(lib,"Winmm.lib")
# define ROW 20
# define COL 22
int mode = 0;      //游戏模式
void showmenu();//显示游戏模式选择的菜单
void chose();//判断用户的输入来选择对应模式
void DrawMap();//绘制地图
void init();//初始化游戏界面和数据
void addfood();//地图中添加食物
void ChangeDir();//用户改变蛇移动方向
void snakemove();//向蛇身移动
void foodmove(COORD next);//向食物移动
void wallmove(COORD next);//向墙移动
void stepmove(COORD next);//向空地移动
void move();//移动
void end();//当局游戏结束页面
enum game
{
	SPACE, WALL, SNAKE, FOOD, HEAD//空地0  墙1 蛇2  食物3  蛇头4
};
time_t  t1, t2;
DWORD tt1, tt2;
int time3;
int score = 3;     //分数
int map[COL][ROW];    //地图大小
COORD snake[1024];    //蛇
//COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。其定义为：
//typedef struct _COORD {
//	SHORT X; // horizontal coordinate
//	SHORT Y; // vertical coordinate
//} COORD;
size_t SnakeSize;    //蛇的尺度    typedef unsigned int  size_t;
char SnakeDir;      //蛇移动方向
int Moveinterval = 100;//蛇的自动移动时间间隔
int allTime = 0;
int again = 0;

