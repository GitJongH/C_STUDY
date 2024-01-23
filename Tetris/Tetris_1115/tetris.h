#ifndef _TETRIS
#define _TETRIS

// 라이브러리
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// 상수정의
#define T_PATTERN_NUM			4
#define T_HIGH					25
#define T_WIDTH					15
#define T_DELAT_TIME			1000

// 블럭 값
#define T_VALUE_SPACE			0x0F
#define T_VALUE_WALL			0xF0
#define T_VALUE_BLOCK_1			0
#define T_VALUE_BLOCK_2			1
#define T_VALUE_BLOCK_3			2
#define T_VALUE_BLOCK_4			3
#define T_VALUE_BLOCK_5			4
#define T_VALUE_BLOCK			9
#define T_VALUE_BLOCK_FINISH	10

// 키 값
#define T_KEY_UP				72
#define T_KEY_DOWN				80
#define T_KEY_LEFT				75
#define T_KEY_RIGHT				77
#define T_SPACE					32
#define PAUSE				    'P'

#define T_TIMEOUT				1
#define T_NOT_TIMEOUT			0

// 구조체
typedef struct _T_POINT {
	int row;						// 행
	int column;						// 열
} T_POINT;

typedef struct _BLOCK {
	int type;						// 블럭 형태 (0, 1, 2, 3, 4)
	int rotation;					// 블럭 방향 (0, 1, 2, 3)
	T_POINT point;
} BLOCK;

// 함수
void	gotoxy(int row, int column); // 커서 이동 함수
void	delay(int sec);				 // 딜레이 함수
int		checkTime(int ms);			 // 시간 함수
void	init();						 // 초기화 & 벽 설정
void	display();					 // 벽 & 블럭 출력
void	selectBlock();				 // 새로운 블럭 선택(내려오는 블럭)
void	addBlockToDisplay();		 // 선택된 블럭을 display에 추가
#endif