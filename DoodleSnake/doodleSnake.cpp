#include"doodlesnake.h"

int main()
{
	initgraph(800, 720);
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeBKMusic.mp3 alias mybkmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play mybkmusic repeat"), NULL, 0, NULL);  // 循环播放
	IMAGE imgMenu;
	loop : loadimage(&imgMenu, _T("C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeInit.jpg"));  // 读取图片到img对象
	putimage(0, 0, &imgMenu);  //在0,0位置显示 IMAGE 对象
	showmenu();
	chose();
	cleardevice();//清屏																							 
	init();//初始化
	t1 = time(NULL);
	int time1 = (int)time(&t1);
	time3 = time1;
	while (1)
	{
		DrawMap();
		if (_kbhit())
		{
			ChangeDir();
			move();
		}
		tt2 = GetTickCount();  //不断获取时间，控制移动速度
		if ((unsigned int)(tt2 - tt1) > (unsigned int)Moveinterval)  //蛇每隔若干时间移动一次
		{
			move();
			tt1 = tt2;
		}
		if (again == 1)
		{
			again = 0;
			cleardevice();//清屏	
			goto loop;
		}
	}
	_getch();
	closegraph();
	return 0;
}

void showmenu()
{
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	settextcolor(RED);//设置字体颜色为黑色
	settextstyle(40, 0, _T("宋体"));
	outtextxy(330, 260, "普通模式");
	outtextxy(330, 340, "穿墙模式");
	outtextxy(330, 420, "无敌模式");
	settextstyle(25, 0, _T("宋体"));
	settextcolor(BLACK);
	outtextxy(160, 500, "字母键W,S,A,D或者字母键I,J,K,L控制方向");
}

void chose()
{
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			if (m.mkLButton == true)
			{
				if (m.x >= 328 && m.x <= 488)
				{
					if (m.y >= 253 && m.y <= 307)
					{
						mode = 0;
						break;
					}
					else if (m.y >= 338 && m.y <= 388)
					{
						mode = 1;
						break;
					}
					else if (m.y >= 416 && m.y <= 468)
					{
						mode = 2;
						break;
					}
				}
			}
		}
	}
}

void init()
{
	srand((unsigned)time(NULL));
	memset(map, SPACE, sizeof(map));//将地图全部初始化为空地  也就是0
	//每一行的第一个和最后一个是墙
	for (int i = 0; i < ROW; i++)
	{
		map[0][i] = map[COL - 1][i] = WALL;
	}
	//每一列的第一个和倒数第一个是墙
	for (int j = 0; j < COL; j++)
	{
		map[j][0] = map[j][ROW - 1] = WALL;
	}
	//初始化蛇的位置
	map[8][8] = HEAD;//头部的初始位置
	//初始让蛇头带动两个身体
	map[7][8] = SNAKE;//身体的初始位置
	map[6][8] = SNAKE;//身体的初始位置
	//初始化蛇
	SnakeSize = 3;  //蛇长为3
	SnakeDir = 'D';  //蛇初始化方向向右
	snake[0].X = 8;
	snake[0].Y = 8;
	snake[1].X = 7;
	snake[1].Y = 8;
	snake[2].X = 6;
	snake[2].Y = 8;
	addfood();//在地图上增加一个食物
}

void addfood()
{
	COORD food;
	int x, y;
	while (1)
	{
		//随机产生一个是空地的地方来放食物
		x = (int)rand() % 19 + 1;
		y = (int)rand() % 21 + 1;
		if (map[x][y] == SPACE)
		{
			food.X = x;
			food.Y = y;
			map[x][y] = FOOD;
			break;
		}
	}
}

void DrawMap()
{
	BeginBatchDraw();  //开始绘图
	settextcolor(RGB(238, 0, 0));
	cleardevice();    //清屏
	IMAGE imgGameBK;
	loadimage(&imgGameBK, _T("C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeBK.jpg"));  // 读取图片到img对象
	putimage(0, 0, &imgGameBK);  //在0,0位置显示 IMAGE 对象	
	setlinecolor(RED);
	//画行
	for (int i = 70; i <= 670; i += 30)
	{
		line(70, i, 730, i);
	}
	//画列
	for (int i = 70; i <= 730; i += 30)
	{
		line(i, 70, i, 670);
	}
	CHAR snakeLength[10];    //保存蛇的长度的字符串
	wsprintf(snakeLength, "%d", SnakeSize);  //将长度格式化输出到字符串snakeLength中
	outtextxy(330, 11, snakeLength);        //显示蛇的长度
	//画蛇头，蛇身体，食物
	//依次检测该位置是画的什么东西
	for (int y = 0; y < ROW; y++)    //y轴方向向下
	{
		for (int x = 0; x < COL; x++)  //x轴方向向右
		{
			switch (map[x][y])
			{
			case SPACE:
				break;
			case SNAKE:
				setlinecolor(RGB(0, 245, 255));    //绿色
				setfillcolor(BLUE);
				fillrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			case WALL:
				setlinecolor(BLACK);
				setfillcolor(RGB(238, 233, 233));  //灰色
				fillrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			case HEAD:
				setlinecolor(RGB(0, 245, 255));    //绿色
				setfillcolor(RED);
				fillrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			case FOOD:
				setfillcolor(RGB(255, 0, 0));      //红色
				setfillcolor(YELLOW);
				solidrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			default:
				break;
			}
		}
		//更新游戏开始的时间
		t2 = time(NULL);
		int time2 = (int)time(&t2);
		CHAR time[10];    //保存时间
		allTime = time2 - time3;
		wsprintf(time, "%d S", allTime);  //将时间格式化输出到字符串time中
		outtextxy(120, 11, time);        //显示时间
	}
	EndBatchDraw();
}

void ChangeDir()
{
	switch (_getch())
	{
	case 'A':
	case 'a':
	case 'J':
	case 'j':
		if (SnakeDir != 'D') SnakeDir = 'A';  //蛇不能一次操作完成掉头
		break;
	case 'D':
	case 'd':
	case 'L':
	case 'l':
		if (SnakeDir != 'A') SnakeDir = 'D';
		break;
	case 'W':
	case 'w':
	case 'I':
	case 'i':
		if (SnakeDir != 'S') SnakeDir = 'W';
		break;
	case 'S':
	case 's':
	case 'K':
	case 'k':
		if (SnakeDir != 'W') SnakeDir = 'S';
		break;
	default:
		break;
	}
}

void move()//移动
{
	//先判断蛇头的下一个位置的坐标是什么
	COORD next;    //蛇头的下一个位置的坐标
	switch (SnakeDir)
	{
	case'A':
		next.X = snake[0].X - 1;
		next.Y = snake[0].Y;
		break;
	case'W':
		next.X = snake[0].X;
		next.Y = snake[0].Y - 1;
		break;
	case'D':
		next.X = snake[0].X + 1;
		next.Y = snake[0].Y;
		break;
	case'S':
		next.X = snake[0].X;
		next.Y = snake[0].Y + 1;
		break;
	default:
		break;
	}
	//根据蛇头下一个位置是什么来画蛇
	switch (map[next.X][next.Y])
	{
	case SPACE://直接移动
		stepmove(next);
		break;
	case WALL:
		wallmove(next);
		break;
	case SNAKE:
		snakemove();
		break;
	case FOOD://食物
		foodmove(next);
		break;
	default:break;
	}
}

void stepmove(COORD next)//向空地移动
{
	//地图蛇尾所在地置空
	map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;
	//蛇尾到蛇头整体移动一位
	for (int i = SnakeSize - 1; i > 0; i--)
	{
		snake[i] = snake[i - 1];
	}
	map[snake[0].X][snake[0].Y] = SNAKE;            //蛇头置为蛇身
	snake[0] = next;                      //将下一个位置赋值给蛇头
	map[snake[0].X][snake[0].Y] = HEAD;              //设置头
}

void wallmove(COORD next)//向墙移动
{
	if (mode != 0)    //模式1模式2可穿墙
	{
		mciSendString(_T("close thoughwallmusic"), NULL, 0, NULL);
		mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\thoughWall.mp3 alias thoughwallmusic"), NULL, 0, NULL);//打开穿墙音乐
		mciSendString(_T("play thoughwallmusic"), NULL, 0, NULL);  // 播放
		map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;//蛇尾置空
		for (int i = SnakeSize - 1; i > 0; i--)
			//蛇尾到蛇头整体移动一位
		{
			snake[i] = snake[i - 1];
		}
		map[snake[0].X][snake[0].Y] = SNAKE;            //蛇头置为蛇身
		switch (SnakeDir)                      //穿墙
		{
		case 'A':
		case 'a': next.X = COL - 2; break;
		case 'D':
		case 'd': next.X = 1; break;
		case 'W':
		case 'w': next.Y = ROW - 2; break;
		case 'S':
		case 's': next.Y = 1; break;
		default:
			break;
		}
		snake[0] = next;                      //蛇头移动到新位置
		map[snake[0].X][snake[0].Y] = HEAD;   //新的蛇头所在的位置
	}
	else {
		end();
	}
}

void foodmove(COORD next)//向食物移动
{
	for (int i = SnakeSize; i > 0; i--)
		//蛇尾到蛇头整体移动一位
	{
		snake[i] = snake[i - 1];
	}
	map[snake[0].X][snake[0].Y] = SNAKE;
	snake[0] = next;                      //将下一个位置赋值给蛇头
	score++;      //分数加一
	SnakeSize++;    //蛇尺度加一
	map[snake[0].X][snake[0].Y] = HEAD;       //地图上重置蛇头
	//播放蛇吃到食物的声音
	mciSendString(_T("close eatmusic"), NULL, 0, NULL);
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\eatFood.mp3 alias eatmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play eatmusic"), NULL, 0, NULL);  // 循环播放
	Moveinterval -= 3;//加快移动速度
	addfood();
}

void snakemove()//向蛇身移动
{
	if (mode == 2)    //模式二无敌
	{
		return;
	}
	else {
		end();
	}
}

void end()
{
	mciSendString(_T("close endmusic"), NULL, 0, NULL);
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\end.mp3 alias endmusic"), NULL, 0, NULL);//打开游戏失败的音乐
	mciSendString(_T("play endmusic"), NULL, 0, NULL);  // 播放游戏失败的音乐

	cleardevice();    //清屏
	IMAGE imgEND;
	loadimage(&imgEND, _T("C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeEnd.jpg"));  // 读取图片到img对象
	putimage(0, 0, &imgEND);  //在0,0位置显示 IMAGE 对象

	CHAR endTime[15] = {0};    //保存时间
	wsprintf(endTime, "用时：%d S", allTime);
	CHAR endLength[10];    //保存时间
	wsprintf(endLength, "长度：%d", SnakeSize);
	setbkmode(TRANSPARENT);	//设置字体背景色为透明
	settextcolor(RED);//设置字体颜色为黑色
	settextstyle(40, 0, _T("宋体"));
	outtextxy(330, 260, endTime);
	outtextxy(330, 340, endLength);
	outtextxy(330, 420, "再来一局");
	outtextxy(330, 500, "退出游戏");
	MOUSEMSG m;
	while (1)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			if (m.mkLButton == true)
			{
				if (m.x >= 328 && m.x <= 488)
				{
					if (m.y >= 416 && m.y <= 468)
					{
						again = 1;
						return;
					}
					else if (m.y >= 490 && m.y <= 550)
						break;
				}
			}
		}
	}

	mciSendString(_T("close mybkmusic"), NULL, 0, NULL);//关闭背景音乐
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\thank.mp3 alias thankmusic"), NULL, 0, NULL);//打开结束音乐
	mciSendString(_T("play thankmusic repeat"), NULL, 0, NULL);  // 循环播放
	MessageBox(GetHWnd(), "            游戏结束", "SORRY", MB_OK);
	exit(0);
}