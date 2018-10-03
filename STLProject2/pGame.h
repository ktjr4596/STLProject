//-------------------------------------------------------------------
//2018.06.01
//
// 
//미로찾기
//pGame.h 
//메뉴 출력과 키입력 및 미로판 출력 헤더
//----------------------------------------------------------------
#ifndef PGAME_H
#define PGAME_H
#include "turbocc.h" // dll 헤더 인클루드 Turbocc 네임스페이스 사용
#pragma comment(lib,"turbocc.lib") 
#include<fstream>
#include <map>
#include <iostream>

#include <string>
#include <chrono>
#include <thread>
#include <iterator>



extern CRITICAL_SECTION cs;  // 임계영역 변수 화면출력점 보호

static const char *arTile[] = { " ","■","□","X"}; // 갈수있는길, 플레이어, 벽, 골
static short board[BW + 2][BH + 2]{ { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
{ 2,0,2,0,2,0,0,0,0,2,0,2,2,2,0,0,0,0,0,2,0,2 },
{ 2,0,2,0,2,2,2,2,0,2,0,2,0,0,0,2,2,2,0,2,0,2 },
{ 2,0,0,0,2,0,0,0,0,2,0,2,0,2,2,2,0,2,0,2,0,2 },
{ 2,0,2,2,2,0,2,0,2,2,0,2,0,2,0,2,0,0,0,0,0,2 },
{ 2,0,0,0,0,0,2,0,2,0,0,2,0,0,0,2,0,2,2,2,0,2 },
{ 2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,2,0,0,0,2 },
{ 2,0,0,0,0,0,0,0,2,2,2,0,0,0,2,0,0,2,0,2,2,2 },
{ 2,0,2,2,2,2,2,0,2,0,2,0,2,0,2,0,2,2,0,2,0,2 },
{ 2,0,2,0,0,0,2,0,2,0,0,0,2,0,0,0,2,0,0,2,0,2 },
{ 2,0,0,0,2,0,2,0,2,0,2,0,2,2,2,2,2,0,2,2,0,2 },
{ 2,0,2,2,2,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,0,2 },
{ 2,0,0,0,0,0,2,0,2,2,2,2,2,0,2,2,2,2,2,0,2,2 },
{ 2,2,2,2,2,2,2,0,2,0,0,0,2,0,2,0,0,0,2,2,0,2 },
{ 2,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,2,0,0,0,0,2 },
{ 2,0,2,2,2,2,2,2,2,0,2,0,2,0,2,0,2,2,2,2,0,2},
{ 2,0,2,0,0,0,0,0,0,0,2,0,2,0,0,0,2,0,2,0,0,2 },
{ 2,0,0,0,0,0,2,0,2,0,2,0,2,0,2,0,2,0,2,2,0,2 },
{ 2,0,2,2,2,0,2,0,2,0,2,0,2,0,2,0,2,0,0,2,0,2 },
{ 2,0,2,0,2,0,2,2,2,0,2,0,2,0,2,0,2,2,0,2,0,2 },
{ 2,0,0,0,2,0,0,0,0,0,2,0,2,0,2,0,0,0,0,2,0,2 },
{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2 } };

struct Point {
	int x, y;

	Point(int a, int b) {
		x = a;
		y = b;
	}
	Point(const Point&) = delete;
	Point(Point&&) = delete;
};


namespace game { // game 네임스페이스

	extern bool goal; // goal 여부 변수
	extern bool keyinterrupt; // 키 입력 확인 변수
	extern double ms; // 스레드에서 시간을 가져와 저장하는 변수
	void taketime(double a); // 스레드에서 시간가져와 ms에 저장하는 함수
	void DrawScreen(); // 미로를 그리는 함수
	void printBrick(BOOL show, const int x, const int  y); // 플레이어를 그리는 함수 show 변수 (false=지우기,true=그리기)
	void processKey(); // 키입력 함수
	int saveFile(std::map<double, Point>&& s); // 파일 저장함수
}
namespace menu { // menu 네임스페이스
	void printMenu(); // 메뉴 출력
	int selectMenu(); // 메뉴 선택
}
#endif // !PGAME_H