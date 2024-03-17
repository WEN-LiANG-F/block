#define _CRT_SECURE_NO_WARNINGS 1
#include"block.h"
int main()
{
	Ui ui;
	Gamesetting::setting();
	cout << "按任意键开始游戏" << endl
		<< "本游戏由方向键控制方块移动" << endl
		<< "按其他任意键可暂停" << endl;
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
		cout << "游戏结束" << endl
			<< "是否继续游戏" << endl
			<< "按空格键退出" << endl
			<< "按其他任意键继续(但请不要按方向键，会卡的)" << endl
			<< "为什么我不优化一下这个？因为清理缓冲区老麻烦了";
		char ch = _getch();
		if (ch == ' ')
			break;
	}
}
