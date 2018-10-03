#define TURBOCC_EXPORTS
#include"turbocc.h"


TURBOCC void Turbocc::clrscr()
{
	system("cls");
}

TURBOCC void Turbocc::gotoxy(const short & x, const short & y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

TURBOCC short Turbocc::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO Bufinfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Bufinfo);
	return Bufinfo.dwCursorPosition.X;

}

TURBOCC short Turbocc::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO Bufinfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Bufinfo);
	return Bufinfo.dwCursorPosition.Y;
}

TURBOCC void Turbocc::setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO Curinfo;
	switch (c)
	{
	case NOCURSOR:
		Curinfo.dwSize = 1;
		Curinfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		Curinfo.dwSize = 100;
		Curinfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		Curinfo.dwSize = 20;
		Curinfo.bVisible = TRUE;
		break;

	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
}

