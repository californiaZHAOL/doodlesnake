#pragma once
#include <graphics.h> 
#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#pragma comment(lib,"Winmm.lib")
# define ROW 20
# define COL 22
int mode = 0;      //��Ϸģʽ
void showmenu();//��ʾ��Ϸģʽѡ��Ĳ˵�
void chose();//�ж��û���������ѡ���Ӧģʽ
void DrawMap();//���Ƶ�ͼ
void init();//��ʼ����Ϸ���������
void addfood();//��ͼ�����ʳ��
void ChangeDir();//�û��ı����ƶ�����
void snakemove();//�������ƶ�
void foodmove(COORD next);//��ʳ���ƶ�
void wallmove(COORD next);//��ǽ�ƶ�
void stepmove(COORD next);//��յ��ƶ�
void move();//�ƶ�
void end();//������Ϸ����ҳ��
enum game
{
	SPACE, WALL, SNAKE, FOOD, HEAD//�յ�0  ǽ1 ��2  ʳ��3  ��ͷ4
};
time_t  t1, t2;
DWORD tt1, tt2;
int time3;
int score = 3;     //����
int map[COL][ROW];    //��ͼ��С
COORD snake[1024];    //��
//COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ�䶨��Ϊ��
//typedef struct _COORD {
//	SHORT X; // horizontal coordinate
//	SHORT Y; // vertical coordinate
//} COORD;
size_t SnakeSize;    //�ߵĳ߶�    typedef unsigned int  size_t;
char SnakeDir;      //���ƶ�����
int Moveinterval = 100;//�ߵ��Զ��ƶ�ʱ����
int allTime = 0;
int again = 0;

