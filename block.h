#pragma once
//���Ƕ���˹�����ͷ�ļ�
#define BBB -32//�����
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
void gotoxy(short x, short y)//����ƶ�
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Gamesetting//��Ϸ������
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
		GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
		CursorInfo.bVisible = false; //���ؿ���̨���
		SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
		srand((unsigned int)time(0));//��ʼ���������
	}
};

//void spin(int block[][3])//3X3������ʱ����ת
//{
//	//�Խ��߻���
//	for (int n = 0; n < 3; n++)
//		for (int m = n + 1; m < 3; m++)
//		{
//			int sum = block[n][m];
//			block[n][m] = block[m][n];
//			block[m][n] = sum;
//		}
//	//���һ���
//	for (int n = 0; n < 3; n++)
//	{
//		int sum = block[n][0];
//		block[n][0] = block[n][2];
//		block[n][2] = sum;
//	}
//}
void _spin(int block[][4])//��4�����õ�//�����Ǹ����з����õ���
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
// ��������  ����  ��ɫ
struct block // Ϊ��Ӧ���������ɫ��ע
{
	int x, y, colour;
	int matrix[4][4];
};

// O��״�ķ��飬��ɫΪ1��ͨ��Ϊ��ɫ��
block block_o
{
	Gamesetting::in_width, Gamesetting::in_height, 1,{{1,1,0,0} ,{1,1,0,0},{0,0,0,0},{0,0,0,0}}
};

// I��״�ķ��飬��ɫΪ2��ͨ��Ϊ��ɫ����ɫ��
block block_i
{
	 Gamesetting::in_width, Gamesetting::in_height, 2, { {1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0} }
};

// S��״�ķ��飬��ɫΪ3��ͨ��Ϊ��ɫ��
block block_s
{
	 Gamesetting::in_width, Gamesetting::in_height,3,{ {0,1,1},{1,1,0},{0,0,0},{0,0,0,0} }
};

// Z��״�ķ��飬��ɫΪ4��ͨ��Ϊ��ɫ��
block block_z
{
	 Gamesetting::in_width, Gamesetting::in_height, 4, { { 1,1,0 }, { 0,1,1 } ,{0, 0, 0} }
};

// L��״�ķ��飬��ɫΪ5��ͨ��Ϊ��ɫ��
block block_l
{
	Gamesetting::in_width, Gamesetting::in_height, 5, { { 1,0,0 }, { 1,0,0 }, { 1,1,0 } }
};

// J��״�ķ��飬��ɫΪ6��ͨ��Ϊ��ɫ��
block block_j
{
	Gamesetting::in_width, Gamesetting::in_height, 6, { {0,1,0},{0,1,0},{1,1,0} }
};

// T��״�ķ��飬��ɫΪ7��ͨ��Ϊ��ɫ��
block block_t
{
	Gamesetting::in_width, Gamesetting::in_height, 7, { {1,1,1},{0,1,0},{0,0,0} }
};

class Vessl//������
{
private:
	int vl[20 + 4][10];
	int point;
public:
	Vessl() :vl{}, point(0)
	{}
	void prt_point()//��ӡ���� ˳����ӡ��һ���������ʾ
	{
		gotoxy(22, 1);
		cout << "������" << point;
		gotoxy(22, 3);
		cout << "��һ�����飺";
	}
	void draw()//��������
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
					cout << "��";
			}
		}
	}
	void wipe()//��������
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
	bool is_down(block b)//�ж��Ƿ�����׶�
	{
		for (int n = 0; n < 4; n++)
			for (int m = 0; m < 4; m++)
				if (b.matrix[n][m] && (b.y + n >= 23 || vl[n + b.y + 1][m + b.x - 1]))
					return true;
		return false;
	}
	bool is_crash(block b)//�ж��Ƿ�����ײ
	{
		for (int n = 0; n < 4; n++)
			for (int m = 0; m < 4; m++)
				if (b.matrix[n][m])
				{
					if (vl[n + b.y][m + b.x - 1])//��ײ�����з���
						return true;
					if (m + b.x <1 || m + b.x>Gamesetting::width)//��ǽ
						return true;
				}
		return false;
	}
	bool is_lose()//ʧ���ж�
	{
		for (int n = 0; n < 3; n++)
			for (int m = 0; m < 10; m++)
				if (vl[n][m]) return true;
		return false;
	}
	void remove()//����
	{
		for (int n = 20 + 4 - 1; n >= 0; n--)
		{
			bool b = true;
			for (int m = 0; m < 10; m++)//��һ���ж���ʵ��
			{
				if (!vl[n][m])
					b = false;
			}
			if (b)
			{
				for (int i = n; i > 0; i--)//һ������¸���
					for (int m = 0; m < 10; m++)
						vl[i][m] = vl[i - 1][m];
				point += 10;//�ӷ�
				n++;
			}
		}
	}
	void mix(block b)//�����ڽ�����
	{
		for (int n = 0; n < 4; n++)
			for (int m = 0; m < 4; m++)
				if (b.matrix[n][m]) vl[n + b.y][m + b.x - 1] = 1;
	}
};
class Block//������
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
		case 1: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break; // ��ɫ
		case 2: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break; // ��ɫ����ɫ
		case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); break; // ��ɫ
		case 4: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break; // ��ɫ
		case 5: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;  // ��ɫ
		case 6: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); break;  // ��ɫ
		case 7: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); break; // ��ɫ
		}
	}

	void make()//��ʼ����
	{
		switch (now = rand() % 7 + 1)//������ɷ���
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
		switch (next = rand() % 7 + 1)//��һ������
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
	void update()//���·���״��
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
	void draw()//���Ʒ���
	{
		//���ö�Ӧ��ɫ
		color_set(b_now.colour);
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				gotoxy(b_now.x + m, b_now.y + n);
				if (b_now.matrix[n][m])
					cout << "��";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ָ�Ĭ����ɫ
	}
	void wipe()//����֮ǰ�ķ���
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
	void draw_next()//������һ������
	{
		//���ö�Ӧ��ɫ
		color_set(b_next.colour);
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				gotoxy(25 + m, 4 + n);
				if (b_next.matrix[n][m])
					cout << "��";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �ָ�Ĭ����ɫ
	}
	void wipe_next()//����֮ǰ����һ������
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
	void key_borad(Vessl v)//���̿���
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

class Ui//������
{
public:
	void drawmap()//���Ƶ�ͼ
	{
		for (int n = 4; n < 24; n++)
		{
			gotoxy(0, n);
			cout << "��";
			gotoxy(11, n);
			cout << "��";
		}
		for (int n = 0; n < 12; n++)
		{
			gotoxy(n, 24);
			cout << "��";
		}
	}
};
