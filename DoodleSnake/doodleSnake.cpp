#include"doodlesnake.h"

int main()
{
	initgraph(800, 720);
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeBKMusic.mp3 alias mybkmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString(_T("play mybkmusic repeat"), NULL, 0, NULL);  // ѭ������
	IMAGE imgMenu;
	loop : loadimage(&imgMenu, _T("C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeInit.jpg"));  // ��ȡͼƬ��img����
	putimage(0, 0, &imgMenu);  //��0,0λ����ʾ IMAGE ����
	showmenu();
	chose();
	cleardevice();//����																							 
	init();//��ʼ��
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
		tt2 = GetTickCount();  //���ϻ�ȡʱ�䣬�����ƶ��ٶ�
		if ((unsigned int)(tt2 - tt1) > (unsigned int)Moveinterval)  //��ÿ������ʱ���ƶ�һ��
		{
			move();
			tt1 = tt2;
		}
		if (again == 1)
		{
			again = 0;
			cleardevice();//����	
			goto loop;
		}
	}
	_getch();
	closegraph();
	return 0;
}

void showmenu()
{
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	settextcolor(RED);//����������ɫΪ��ɫ
	settextstyle(40, 0, _T("����"));
	outtextxy(330, 260, "��ͨģʽ");
	outtextxy(330, 340, "��ǽģʽ");
	outtextxy(330, 420, "�޵�ģʽ");
	settextstyle(25, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(160, 500, "��ĸ��W,S,A,D������ĸ��I,J,K,L���Ʒ���");
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
	memset(map, SPACE, sizeof(map));//����ͼȫ����ʼ��Ϊ�յ�  Ҳ����0
	//ÿһ�еĵ�һ�������һ����ǽ
	for (int i = 0; i < ROW; i++)
	{
		map[0][i] = map[COL - 1][i] = WALL;
	}
	//ÿһ�еĵ�һ���͵�����һ����ǽ
	for (int j = 0; j < COL; j++)
	{
		map[j][0] = map[j][ROW - 1] = WALL;
	}
	//��ʼ���ߵ�λ��
	map[8][8] = HEAD;//ͷ���ĳ�ʼλ��
	//��ʼ����ͷ������������
	map[7][8] = SNAKE;//����ĳ�ʼλ��
	map[6][8] = SNAKE;//����ĳ�ʼλ��
	//��ʼ����
	SnakeSize = 3;  //�߳�Ϊ3
	SnakeDir = 'D';  //�߳�ʼ����������
	snake[0].X = 8;
	snake[0].Y = 8;
	snake[1].X = 7;
	snake[1].Y = 8;
	snake[2].X = 6;
	snake[2].Y = 8;
	addfood();//�ڵ�ͼ������һ��ʳ��
}

void addfood()
{
	COORD food;
	int x, y;
	while (1)
	{
		//�������һ���ǿյصĵط�����ʳ��
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
	BeginBatchDraw();  //��ʼ��ͼ
	settextcolor(RGB(238, 0, 0));
	cleardevice();    //����
	IMAGE imgGameBK;
	loadimage(&imgGameBK, _T("C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeBK.jpg"));  // ��ȡͼƬ��img����
	putimage(0, 0, &imgGameBK);  //��0,0λ����ʾ IMAGE ����	
	setlinecolor(RED);
	//����
	for (int i = 70; i <= 670; i += 30)
	{
		line(70, i, 730, i);
	}
	//����
	for (int i = 70; i <= 730; i += 30)
	{
		line(i, 70, i, 670);
	}
	CHAR snakeLength[10];    //�����ߵĳ��ȵ��ַ���
	wsprintf(snakeLength, "%d", SnakeSize);  //�����ȸ�ʽ��������ַ���snakeLength��
	outtextxy(330, 11, snakeLength);        //��ʾ�ߵĳ���
	//����ͷ�������壬ʳ��
	//���μ���λ���ǻ���ʲô����
	for (int y = 0; y < ROW; y++)    //y�᷽������
	{
		for (int x = 0; x < COL; x++)  //x�᷽������
		{
			switch (map[x][y])
			{
			case SPACE:
				break;
			case SNAKE:
				setlinecolor(RGB(0, 245, 255));    //��ɫ
				setfillcolor(BLUE);
				fillrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			case WALL:
				setlinecolor(BLACK);
				setfillcolor(RGB(238, 233, 233));  //��ɫ
				fillrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			case HEAD:
				setlinecolor(RGB(0, 245, 255));    //��ɫ
				setfillcolor(RED);
				fillrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			case FOOD:
				setfillcolor(RGB(255, 0, 0));      //��ɫ
				setfillcolor(YELLOW);
				solidrectangle(70 + x * 30, 70 + y * 30, 100 + x * 30, 100 + y * 30);
				break;
			default:
				break;
			}
		}
		//������Ϸ��ʼ��ʱ��
		t2 = time(NULL);
		int time2 = (int)time(&t2);
		CHAR time[10];    //����ʱ��
		allTime = time2 - time3;
		wsprintf(time, "%d S", allTime);  //��ʱ���ʽ��������ַ���time��
		outtextxy(120, 11, time);        //��ʾʱ��
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
		if (SnakeDir != 'D') SnakeDir = 'A';  //�߲���һ�β�����ɵ�ͷ
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

void move()//�ƶ�
{
	//���ж���ͷ����һ��λ�õ�������ʲô
	COORD next;    //��ͷ����һ��λ�õ�����
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
	//������ͷ��һ��λ����ʲô������
	switch (map[next.X][next.Y])
	{
	case SPACE://ֱ���ƶ�
		stepmove(next);
		break;
	case WALL:
		wallmove(next);
		break;
	case SNAKE:
		snakemove();
		break;
	case FOOD://ʳ��
		foodmove(next);
		break;
	default:break;
	}
}

void stepmove(COORD next)//��յ��ƶ�
{
	//��ͼ��β���ڵ��ÿ�
	map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;
	//��β����ͷ�����ƶ�һλ
	for (int i = SnakeSize - 1; i > 0; i--)
	{
		snake[i] = snake[i - 1];
	}
	map[snake[0].X][snake[0].Y] = SNAKE;            //��ͷ��Ϊ����
	snake[0] = next;                      //����һ��λ�ø�ֵ����ͷ
	map[snake[0].X][snake[0].Y] = HEAD;              //����ͷ
}

void wallmove(COORD next)//��ǽ�ƶ�
{
	if (mode != 0)    //ģʽ1ģʽ2�ɴ�ǽ
	{
		mciSendString(_T("close thoughwallmusic"), NULL, 0, NULL);
		mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\thoughWall.mp3 alias thoughwallmusic"), NULL, 0, NULL);//�򿪴�ǽ����
		mciSendString(_T("play thoughwallmusic"), NULL, 0, NULL);  // ����
		map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;//��β�ÿ�
		for (int i = SnakeSize - 1; i > 0; i--)
			//��β����ͷ�����ƶ�һλ
		{
			snake[i] = snake[i - 1];
		}
		map[snake[0].X][snake[0].Y] = SNAKE;            //��ͷ��Ϊ����
		switch (SnakeDir)                      //��ǽ
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
		snake[0] = next;                      //��ͷ�ƶ�����λ��
		map[snake[0].X][snake[0].Y] = HEAD;   //�µ���ͷ���ڵ�λ��
	}
	else {
		end();
	}
}

void foodmove(COORD next)//��ʳ���ƶ�
{
	for (int i = SnakeSize; i > 0; i--)
		//��β����ͷ�����ƶ�һλ
	{
		snake[i] = snake[i - 1];
	}
	map[snake[0].X][snake[0].Y] = SNAKE;
	snake[0] = next;                      //����һ��λ�ø�ֵ����ͷ
	score++;      //������һ
	SnakeSize++;    //�߳߶ȼ�һ
	map[snake[0].X][snake[0].Y] = HEAD;       //��ͼ��������ͷ
	//�����߳Ե�ʳ�������
	mciSendString(_T("close eatmusic"), NULL, 0, NULL);
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\eatFood.mp3 alias eatmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString(_T("play eatmusic"), NULL, 0, NULL);  // ѭ������
	Moveinterval -= 3;//�ӿ��ƶ��ٶ�
	addfood();
}

void snakemove()//�������ƶ�
{
	if (mode == 2)    //ģʽ���޵�
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
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\end.mp3 alias endmusic"), NULL, 0, NULL);//����Ϸʧ�ܵ�����
	mciSendString(_T("play endmusic"), NULL, 0, NULL);  // ������Ϸʧ�ܵ�����

	cleardevice();    //����
	IMAGE imgEND;
	loadimage(&imgEND, _T("C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\DoodleSnakeEnd.jpg"));  // ��ȡͼƬ��img����
	putimage(0, 0, &imgEND);  //��0,0λ����ʾ IMAGE ����

	CHAR endTime[15] = {0};    //����ʱ��
	wsprintf(endTime, "��ʱ��%d S", allTime);
	CHAR endLength[10];    //����ʱ��
	wsprintf(endLength, "���ȣ�%d", SnakeSize);
	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
	settextcolor(RED);//����������ɫΪ��ɫ
	settextstyle(40, 0, _T("����"));
	outtextxy(330, 260, endTime);
	outtextxy(330, 340, endLength);
	outtextxy(330, 420, "����һ��");
	outtextxy(330, 500, "�˳���Ϸ");
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

	mciSendString(_T("close mybkmusic"), NULL, 0, NULL);//�رձ�������
	mciSendString(_T("open C:\\Users\\ztlzl\\Desktop\\DoodleSnake\\thank.mp3 alias thankmusic"), NULL, 0, NULL);//�򿪽�������
	mciSendString(_T("play thankmusic repeat"), NULL, 0, NULL);  // ѭ������
	MessageBox(GetHWnd(), "            ��Ϸ����", "SORRY", MB_OK);
	exit(0);
}