#pragma once
//这是俄罗斯方块的头文件
#define BBB -32//方向键
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#include<iostream>
#include<ctime>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include <chrono>
using namespace std;
void gotoxy(short x, short y)//光标移动
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Gamesetting//游戏设置类
{
public:
	static const int height = 20;
	static const int width = 10;
	static const int in_height = 0;
	static const int in_width = 6;
	static void setting()
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
		CursorInfo.bVisible = false; //隐藏控制台光标
		SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
		srand((unsigned int)time(0));//初始化随机种子
	}
};

//void spin(int block[][3])//3X3矩阵逆时针旋转
//{
//	//对角线互换
//	for (int n = 0; n < 3; n++)
//		for (int m = n + 1; m < 3; m++)
//		{
//			int sum = block[n][m];
//			block[n][m] = block[m][n];
//			block[m][n] = sum;
//		}
//	//左右互换
//	for (int n = 0; n < 3; n++)
//	{
//		int sum = block[n][0];
//		block[n][0] = block[n][2];
//		block[n][2] = sum;
//	}
//}
void _spin(int block[][4])//给4格长条用的//现在是给所有方块用的了
{
	for (int n = 0; n < 4; n++)
		for (int m = n + 1; m < 4; m++)
		{
			int sum = block[n][m];
			block[n][m] = block[m][n];
			block[m][n] = sum;
		}
	for (int n = 0; n < 4; n++)
		for (int m = 0; m < 2; m++)
		{
			int sum = block[n][m];
			block[n][m] = block[n][4 - 1 - m];
			block[n][4 - 1 - m] = sum;
		}
}
// 方块种类  坐标  颜色
struct block // 为对应方块添加颜色备注
{
	int x, y, colour;
	int matrix[4][4];
};

// O形状的方块，颜色为1（通常为黄色）
block block_o
{
	Gamesetting::in_width, Gamesetting::in_height, 1,{{1,1,0,0} ,{1,1,0,0},{0,0,0,0},{0,0,0,0}}
};

// I形状的方块，颜色为2（通常为青色或蓝色）
block block_i
{
	 Gamesetting::in_width, Gamesetting::in_height, 2, { {1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0} }
};

// S形状的方块，颜色为3（通常为绿色）
block block_s
{
	 Gamesetting::in_width, Gamesetting::in_height,3,{ {0,1,1},{1,1,0},{0,0,0},{0,0,0,0} }
};

// Z形状的方块，颜色为4（通常为红色）
block block_z
{
	 Gamesetting::in_width, Gamesetting::in_height, 4, { { 1,1,0 }, { 0,1,1 } ,{0, 0, 0} }
};

// L形状的方块，颜色为5（通常为橙色）
block block_l
{
	Gamesetting::in_width, Gamesetting::in_height, 5, { { 1,0,0 }, { 1,0,0 }, { 1,1,0 } }
};

// J形状的方块，颜色为6（通常为蓝色）
block block_j
{
	Gamesetting::in_width, Gamesetting::in_height, 6, { {0,1,0},{0,1,0},{1,1,0} }
};

// T形状的方块，颜色为7（通常为紫色）
block block_t
{
	Gamesetting::in_width, Gamesetting::in_height, 7, { {1,1,1},{0,1,0},{0,0,0} }
};

class Vessl//容器类
{
private:
	int vl[20 + 4][10];
	int point;
public:
	Vessl() :vl{}, point(0)
	{}
	void prt_point()//打印分数 顺带打印下一个方块的提示
	{
		gotoxy(22, 1);
		cout << "分数：" << point;
		gotoxy(22, 3);
		cout << "下一个方块：";
	}
	void draw()//绘制容器
	{
		for (int n = 0; n < 24; n++)
		{
			for (int m = 0; m < 10; m++)
			{
				gotoxy(m + 1, n);
				if (vl[n][m])
					cout << " ";
			}
		}

		for (int n = 0; n < 24; n++)
		{
			for (int m = 0; m < 10; m++)
			{
				gotoxy(m + 1, n);
				if (vl[n][m])
					cout << "■";
			}
		}
	}
	void wipe()//擦除容器
	{
		for (int n = 0; n < 24; n++)
		{
			for (int m = 0; m < 10; m++)
			{
				if (vl[n][m])
				{
					gotoxy(m + 1, n);
					cout << " ";
				}
			}
		}
	}
	bool is_down(block b)//判断是否掉到底端
	{
		for (int n = 0; n < 4; n++)
			for (int m = 0; m < 4; m++)
				if (b.matrix[n][m] && (b.y + n >= 23 || vl[n + b.y + 1][m + b.x - 1]))
					return true;
		return false;
	}
	bool is_crash(block b)//判断是否有碰撞
	{
		for (int n = 0; n < 4; n++)
			for (int m = 0; m < 4; m++)
				if (b.matrix[n][m])
				{
					if (vl[n + b.y][m + b.x - 1])//碰撞到已有方块
						return true;
					if (m + b.x <1 || m + b.x>Gamesetting::width)//出墙
						return true;
				}
		return false;
	}
	bool is_lose()//失败判定
	{
		for (int n = 0; n < 3; n++)
			for (int m = 0; m < 10; m++)
				if (vl[n][m]) return true;
		return false;
	}
	void remove()//消行
	{
		for (int n = 20 + 4 - 1; n >= 0; n--)
		{
			bool b = true;
			for (int m = 0; m < 10; m++)//若一整行都是实块
			{
				if (!vl[n][m])
					b = false;
			}
			if (b)
			{
				for (int i = n; i > 0; i--)//一层层往下复制
					for (int m = 0; m < 10; m++)
						vl[i][m] = vl[i - 1][m];
				point += 10;//加分
				n++;
			}
		}
	}
	void mix(block b)//方块融进容器
	{
		for (int n = 0; n < 4; n++)
			for (int m = 0; m < 4; m++)
				if (b.matrix[n][m]) vl[n + b.y][m + b.x - 1] = 1;
	}
};
class Block//方块类
{
private:
public:
	int now;
	block b_now;
	int next;
	block b_next;
	Block()
	{
		now = 0;
		next = 0;
	}
	void color_set(int colour)
	{
		switch (colour)
		{
		case 1: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break; // 黄色
		case 2: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break; // 青色或蓝色
		case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); break; // 绿色
		case 4: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break; // 红色
		case 5: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;  // 橙色
		case 6: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); break;  // 蓝色
		case 7: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); break; // 紫色
		}
	}

	void make()//初始创建
	{
		switch (now = rand() % 7 + 1)//随机生成方块
		{
		case 1: b_now = block_o;
			break;
		case 2: b_now = block_i;
			break;
		case 3: b_now = block_s;
			break;
		case 4: b_now = block_z;
			break;
		case 5: b_now = block_l;
			break;
		case 6: b_now = block_j;
			break;
		case 7: b_now = block_t;
			break;
		}
		switch (next = rand() % 7 + 1)//下一个方块
		{
		case 1: b_next = block_o;
			break;
		case 2: b_next = block_i;
			break;
		case 3: b_next = block_s;
			break;
		case 4: b_next = block_z;
			break;
		case 5: b_next = block_l;
			break;
		case 6: b_next = block_j;
			break;
		case 7: b_next = block_t;
			break;
		}
	}
	void update()//更新方块状况
	{
		now = next;
		b_now = b_next;
		switch (next = rand() % 7 + 1)
		{
		case 1: b_next = block_o;
			break;
		case 2: b_next = block_i;
			break;
		case 3: b_next = block_s;
			break;
		case 4: b_next = block_z;
			break;
		case 5: b_next = block_l;
			break;
		case 6: b_next = block_j;
			break;
		case 7: b_next = block_t;
			break;
		}
	}
	void draw()//绘制方块
	{
		//设置对应颜色
		color_set(b_now.colour);
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				gotoxy(b_now.x + m, b_now.y + n);
				if (b_now.matrix[n][m])
					cout << "■";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 恢复默认颜色
	}
	void wipe()//擦除之前的方块
	{
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				if (b_now.matrix[n][m])
				{
					gotoxy(b_now.x + m, b_now.y + n);
					cout << " ";
				}
			}
		}
	}
	void draw_next()//绘制下一个方块
	{
		//设置对应颜色
		color_set(b_next.colour);
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				gotoxy(25 + m, 4 + n);
				if (b_next.matrix[n][m])
					cout << "■";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 恢复默认颜色
	}
	void wipe_next()//擦除之前的下一个方块
	{
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				if (b_next.matrix[n][m])
				{
					gotoxy(25 + m, 4 + n);
					cout << " ";
				}
			}
		}
	}
	void key_borad(Vessl v)//键盘控制
	{
		char key;
		char ch;
		if (_kbhit())
		{
			key = _getch();
			ch = _getch();
			block b = b_now;
			if (key == BBB)
				switch (ch)
				{
				case UP:
					wipe();
					_spin(b.matrix);
					if (!v.is_crash(b))
						b_now = b;
					draw();
					break;
				case DOWN:
					while (!v.is_down(b_now))
					{
						wipe();
						b_now.y++;
						draw();
					}
					break;
				case LEFT:
					wipe();
					b_now.x--;
					if (v.is_crash(b_now))
						b_now.x++;
					draw();
					break;
				case RIGHT:
					wipe();
					b_now.x++;
					if (v.is_crash(b_now))
						b_now.x--;
					draw();
					break;
				}
		}
	}
};

class Ui//界面类
{
public:
	void drawmap()//绘制地图
	{
		for (int n = 4; n < 24; n++)
		{
			gotoxy(0, n);
			cout << "■";
			gotoxy(11, n);
			cout << "■";
		}
		for (int n = 0; n < 12; n++)
		{
			gotoxy(n, 24);
			cout << "■";
		}
	}
};
