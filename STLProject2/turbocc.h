//-------------------------------------------------------------------
//2018.06.01
//2012150025 ������ STL ���� 2 
// 
//�̷�ã��
//turbocc.h - tubocc.dll �������
//Ű ���� �� ȭ�� Ŭ���� , ȭ�� ����� ���� �Լ�
//----------------------------------------------------------------
#ifndef TURBOCC_HEADER
#define TURBOCC_HEADER

#ifdef TURBOCC_EXPORTS

#define TURBOCC __declspec(dllexport)

#else 

#define TURBOCC _declspec(dllimport)
#endif // !1

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<Windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
enum { EMPTY, BRICK, WALL };

const int LEFT{ 75 }; // Ű ����
const int RIGHT{ 77 };
const int UP{ 72 };
const int DOWN{ 80 };
const  int ESC{ 27 };
const int BX{ 5 };
const int BY{ 1 };
const int BW{ 20 };
const int BH{ 20 };
//#define delay(n) Sleep(n)
//#define randomize() srand((unsigned)time(NULL))
//#define random(n) (rand()%n)
#ifndef TURBOCC_PROTOTYPE_ONLY

#ifdef __cplusplus
extern "C" namespace Turbocc{
#endif // __cplusplus

	
		TURBOCC void clrscr(); // ȭ�� Ŭ���� �Լ�
		TURBOCC void gotoxy(const short &x, const short& y); // ���� ��ǥ�� ����� �̵� �Լ�
		TURBOCC short wherex(); // x��ǥ ��ȯ �Լ�
		TURBOCC short wherey(); // y ��ǥ ��ȯ �Լ�
		TURBOCC void setcursortype(CURSOR_TYPE   c); // ����� Ŀ�� ��ȯ �Լ�
	

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !TURBOC_PROTOTYPE_ONLY
#endif // !TURBOC_HEADE