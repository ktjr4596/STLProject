#include "pGame.h"


void game::taketime(double a) {
	ms = a;
}
void game::DrawScreen() {


	for (int x = 0; x < BW + 2; ++x) {
		for (int y = 0; y < BH + 2; ++y) {
			Turbocc::gotoxy(BX + x * 2, BY + y);
			puts(arTile[board[x][y]]);
		}
	}
	Turbocc::gotoxy(50, 3);
	puts("�̷�ã��");
	Turbocc::gotoxy(50, 5);
	puts("����Ű�� �̵�");

}

void game::printBrick(BOOL show, const int x, const int  y) {

	Turbocc::gotoxy(BX + x * 2, BY + y);
	puts(arTile[show ? BRICK : EMPTY]);


}

void game::processKey() {
	std::map<double, Point> m; // <Ű�Է½ð�,��ǥ> �ʺ��� ����
	int x = 1, y = 1;
	int ch;

	while (true) {
		if (_kbhit()) { 
			ch = _getch();
			if (ch == 0xE0 || ch == 0)
			{
				ch = _getch();
				switch (ch)
				{
				case LEFT: 
					if (board[x - 1][y] == WALL) {
						break;
					}
					else {
						EnterCriticalSection(&cs); // �̵��� ���� �ƴϸ� �Ӱ迵�� ������ Ű�Է�Ȯ�� ���� ����,�����忡�� �ð��޾ƿ��� �÷��̾� �̵� �ʿ� ����
						keyinterrupt = true;
						game::printBrick(FALSE, x, y);
						LeaveCriticalSection(&cs);
						--x;
						EnterCriticalSection(&cs);
						m.emplace(std::piecewise_construct, std::forward_as_tuple(ms), std::forward_as_tuple(x, y));
						LeaveCriticalSection(&cs);
						if ((x == BW + 1) && (y == BH))
						{
							goal = true;
							int checkMsg;
							EnterCriticalSection(&cs);
							Turbocc::gotoxy(5, BH + 3);
							printf("%.3f\n", (--m.end())->first);
							LeaveCriticalSection(&cs);
							checkMsg = MessageBox(nullptr, L"���÷��̿� �����մϴ�.", L"��������", IDOK);
							if (checkMsg == IDOK)
								game::saveFile(std::move(m));
							return;
						}
						EnterCriticalSection(&cs);
						game::printBrick(TRUE, x, y);
						LeaveCriticalSection(&cs);
					}
					break;
				case RIGHT:

					if (board[x + 1][y] == WALL) {
						break;
					}
					else {
						EnterCriticalSection(&cs);
						keyinterrupt = true;
						game::printBrick(FALSE, x, y);
						LeaveCriticalSection(&cs);
						++x;
						EnterCriticalSection(&cs);
						m.emplace(std::piecewise_construct, std::forward_as_tuple(ms), std::forward_as_tuple(x, y));
						LeaveCriticalSection(&cs);
						if ((x == BW + 1) && (y == BH))
						{
							EnterCriticalSection(&cs);
							goal = true;
							LeaveCriticalSection(&cs);
							
							int checkMsg;
						;
							EnterCriticalSection(&cs);
							Turbocc::gotoxy(5, BH + 3);
							printf("%.3f\n", (--m.end())->first);
							LeaveCriticalSection(&cs);
							checkMsg = MessageBox(nullptr, L"���÷��̿� �����մϴ�.", L"��������", IDOK);
							if (checkMsg == IDOK)
							
								game::saveFile(std::move(m));
							return;
						}
						EnterCriticalSection(&cs);
						game::printBrick(TRUE, x, y);
						LeaveCriticalSection(&cs);
					}
					break;
				case UP:
					if (board[x][y - 1] == WALL) {
						break;
					}
					else {
						EnterCriticalSection(&cs);
						keyinterrupt = true;
						LeaveCriticalSection(&cs);
						game::printBrick(FALSE, x, y);
						--y;
						EnterCriticalSection(&cs);
						m.emplace(std::piecewise_construct, std::forward_as_tuple(ms), std::forward_as_tuple(x, y));
						LeaveCriticalSection(&cs);
						if ((x == BW + 1) && (y == BH))
						{
							goal = true;
							int checkMsg;
							EnterCriticalSection(&cs);
							Turbocc::gotoxy(5, BH + 3);
							printf("%.3f\n", (--m.end())->first);
							LeaveCriticalSection(&cs);
				
							checkMsg = MessageBox(nullptr, L"���÷��̿� �����մϴ�.", L"��������", IDOK);
							if (checkMsg == IDOK)
								game::saveFile(std::move(m));
							return;
						}
						EnterCriticalSection(&cs);
						game::printBrick(TRUE, x, y);
						LeaveCriticalSection(&cs);
					}
					break;
				case DOWN:
					if (board[x][y + 1] == WALL) {
						break;
					}
					else {
						EnterCriticalSection(&cs);
						keyinterrupt = true;
						LeaveCriticalSection(&cs);
						game::printBrick(FALSE, x, y);
						++y;

						
						EnterCriticalSection(&cs);
						m.emplace(std::piecewise_construct, std::forward_as_tuple(ms), std::forward_as_tuple(x, y));
						LeaveCriticalSection(&cs);
						if ((x == BW + 1) && (y == BH))
						{
							goal = true;
							int checkMsg;
							EnterCriticalSection(&cs);
							Turbocc::gotoxy(5, BH + 3);
							printf("%.3f\n", (--m.end())->first);
							LeaveCriticalSection(&cs);
							checkMsg = MessageBox(nullptr, L"���÷��̿� �����մϴ�.", L"��������", IDOK);
							if (checkMsg == IDOK)
								game::saveFile(std::move(m));
							return;
						}
						EnterCriticalSection(&cs);
						game::printBrick(TRUE, x, y);
						LeaveCriticalSection(&cs);
					}
					break;
				}
			}
		}
	}
}


int game::saveFile(std::map<double, Point>&& s) {
	std::ofstream out{ "replay.txt" };
	for (auto &n : s) {
		out << n.first << ',' << n.second.x << ',' << n.second.y << ',';
	}
	system("pause");
	Turbocc::clrscr();
	out.close();
	return 1;
}

void menu::printMenu()
{
	Turbocc::clrscr();
	Turbocc::gotoxy(50, 10);
	puts("�̷�ã��");
	Turbocc::gotoxy(50, 15);
	puts("���ӽ���");
	Turbocc::gotoxy(50, 20);
	puts("���÷���");
	Turbocc::gotoxy(50, 25);
	puts("��������");
}

int menu::selectMenu() {
	int cnt = 1;
	int ch;
	Turbocc::gotoxy(45, 15);
	puts(">");
	while (true) {
		if (_kbhit()) {
			ch = _getch();

			if (ch == 0xE0 || ch == 0)
			{
				ch = _getch();

				switch (ch)
				{
				case UP:
					cnt--;
					if (cnt < 1)
						cnt = 3;
					switch (cnt)
					{
					case 1:
						Turbocc::gotoxy(45, 20);
						puts(" ");
						Turbocc::gotoxy(45, 15);
						puts(">");
						break;
					case 2:
						Turbocc::gotoxy(45, 25);
						puts(" ");
						Turbocc::gotoxy(45, 20);
						puts(">");
						break;
					case 3:
						Turbocc::gotoxy(45, 15);
						puts(" ");
						Turbocc::gotoxy(45, 25);
						puts(">");
						break;
					}
					break;
				case DOWN:
					cnt++;
					if (cnt>3)
						cnt = 1;
					switch (cnt)
					{
					case 1:
						Turbocc::gotoxy(45, 25);
						puts(" ");
						Turbocc::gotoxy(45, 15);
						puts(">");

						break;
					case 2:
						Turbocc::gotoxy(45, 15);
						puts(" ");
						Turbocc::gotoxy(45, 20);
						puts(">");

						break;
					case 3:
						Turbocc::gotoxy(45, 20);
						puts(" ");
						Turbocc::gotoxy(45, 25);
						puts(">");
						break;
					}
					break;
				}
			}
			else if (ch == 0x20) {
				return cnt;
			}
		}
	}
}