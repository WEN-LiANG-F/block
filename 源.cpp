#define _CRT_SECURE_NO_WARNINGS 1
#include"block.h"
int main()
{
	Ui ui;
	Gamesetting::setting();
	cout << "���������ʼ��Ϸ" << endl
		<< "����Ϸ�ɷ�������Ʒ����ƶ�" << endl
		<< "���������������ͣ" << endl;
	_getch();
	while (true)
	{
		system("cls");
		ui.drawmap();
		Vessl vessl;
		Block block;
		block.make();
		while (!vessl.is_lose())
		{
			vessl.prt_point();
			block.draw();
			block.draw_next();
			vessl.draw();
			block.key_borad(vessl);
			auto start = chrono::steady_clock::now();
			chrono::milliseconds duration(500);
			while (chrono::high_resolution_clock::now() - start < duration)
				block.key_borad(vessl);
			if (vessl.is_down(block.b_now))
			{
				vessl.mix(block.b_now);
				block.wipe_next();
				block.update();
			}
			else
			{
				block.wipe();
				block.b_now.y++;
			}
			vessl.wipe();
			vessl.remove();
		}
		system("cls");
		cout << "��Ϸ����" << endl
			<< "�Ƿ������Ϸ" << endl
			<< "���ո���˳�" << endl
			<< "���������������(���벻Ҫ����������Ῠ��)" << endl
			<< "Ϊʲô�Ҳ��Ż�һ���������Ϊ�����������鷳��";
		char ch = _getch();
		if (ch == ' ')
			break;
	}
}
