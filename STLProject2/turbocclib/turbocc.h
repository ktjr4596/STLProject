//-------------------------------------------------------------------
//2018.06.01
//2012150025 서광석 STL 과제 2 
// 
//미로찾기
//turbocc.h - tubocc.dll 헤더파일
//키 정의 및 화면 클리어 , 화면 출력점 지정 함수
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

const int LEFT{ 75 }; // 키 정의
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

	
		TURBOCC void clrscr(); // 화면 클리어 함수
		TURBOCC void gotoxy(const short &x, const short& y); // 지정 좌표로 출력점 이동 함수
		TURBOCC short wherex(); // x좌표 반환 함수
		TURBOCC short wherey(); // y 좌표 반환 함수
		TURBOCC void setcursortype(CURSOR_TYPE   c); // 출력점 커서 변환 함수
	

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !TURBOC_PROTOTYPE_ONLY
#endif // !TURBOC_HEADE