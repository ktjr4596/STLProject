//-------------------------------------------------------------------
//2018.06.01
//
// 
//�̷�ã��
//��������
//
//----------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include"pGame.h"

using std::cout;
using std::endl;
using namespace std::chrono;

CRITICAL_SECTION cs;
bool game::goal = false;
double game::ms = 0;
bool game::keyinterrupt = false;

void hThread1(); // �ð� ��� �Լ�
char * dtoa(char *cbuf, double f); // double �� char�� ��ȯ�ϴ� �Լ� 


void hThread1() {
	auto start = std::chrono::high_resolution_clock::now();
	
	char  buf[20] = "0";
	while (game::goal != true) {
		std::this_thread::sleep_for(20ms);
		auto Elapsed = high_resolution_clock::now() - start;
		if (game::keyinterrupt == true) { // Ű�Է��� ������ �ð��� �����ְ� �ٽ� Ű�Էº����� false�� ��ȯ
			EnterCriticalSection(&cs);
			game::taketime(std::chrono::duration<double>(Elapsed).count());
			game::keyinterrupt = false;
			LeaveCriticalSection(&cs);
		}
		if (game::goal == false) {
			dtoa(buf, std::chrono::duration<double>(Elapsed).count());
			EnterCriticalSection(&cs);
			Turbocc::gotoxy(5, BH + 3);
			puts(buf);
			LeaveCriticalSection(&cs);
		}

	}

}

char * dtoa(char *cbuf, double f) {
	sprintf(cbuf, "%.3f", f);
	return cbuf;
}

int main()
{
	std::ifstream in;
	InitializeCriticalSection(&cs);
	Turbocc::setcursortype(NOCURSOR);
	std::ofstream out;
	std::map<double, Point> save; // ���Ͽ��� �ð��� ��ǥ�� �ҷ��� ������ �� ����
	while (true) {
		std::thread t;
		int nMenu;
		int ch = 0;
		int x = 1, y = 1;
		menu::printMenu();
		nMenu = menu::selectMenu();
		switch (nMenu)
		{
		case 1:
			Turbocc::clrscr();
			x = 2;
			y = 1;
			game::DrawScreen();
			Turbocc::gotoxy(BX + x * 2, BY + y);
			puts(arTile[1 ? BRICK : EMPTY]);
			game::goal = false;
			t = std::move(std::thread{ hThread1 });  // �ð� ��� ������ ����
			game::processKey();
			t.detach(); // �����庯������ �Լ��� �����
		
			break;
		case 2:
				in.open("replay.txt");
				if (in) {
					save.clear();
					std::string a;
					std::string xtemp;
					std::string ytemp;
					while (in) { // ���Ͽ��� save�ʿ� �ð��� ��ǥ ����
						std::getline(in, a, ',');
						std::getline(in, xtemp, ',');
						std::getline(in, ytemp, ',');
						save.emplace(std::piecewise_construct, std::forward_as_tuple(atof(a.c_str())),
							std::forward_as_tuple(atoi(xtemp.c_str()), atoi(ytemp.c_str())));
					}
					Turbocc::clrscr();
					game::DrawScreen();
					
					Point pTemp{ 1, 1 };
					game::printBrick(TRUE, pTemp.x, pTemp.y);
					char buf[20];
					auto start = std::chrono::high_resolution_clock::now();
					for (auto p = save.cbegin(); p != save.cend(); ++p) // save�ǹݺ����� Ű�� �ð�������� ��ǥ�� �÷��̾� ���
					{
						
						while (p->first > std::chrono::duration<double>(high_resolution_clock::now() - start).count())
						{
							Turbocc::gotoxy(5, BH + 3);
							dtoa(buf, std::move((std::chrono::duration<double>(high_resolution_clock::now() - start).count())));
							puts(buf);
						}
						
						game::printBrick(FALSE, pTemp.x, pTemp.y);
						game::printBrick(TRUE, p->second.x, p->second.y);
						
						pTemp.x = p->second.x;
						pTemp.y = p->second.y;
					}
					double temp = (--save.end())->first;
					Turbocc::gotoxy(5, BH + 3);
					puts(dtoa(buf,std::move(temp)));
					Turbocc::gotoxy(5, BH + 4);
					puts("���÷��̰� �������ϴ�. �ƹ�Ű�� �Է��ϼ���");
					system("pause");
				}
				else {
					Turbocc::clrscr();
					puts("���÷��̰� �����ϴ�. ������ �Ϸ����ּ���");
					system("pause");
				}
				in.close();
			break;
		case 3:
			DeleteCriticalSection(&cs);
			return 1;
		}
	}
}

