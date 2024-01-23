#ifndef _PUSH_H
#define _PUSH_H

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define PUSH_SIZE			20

#define _KEY_UP				72
#define _KEY_DOWN			80
#define _KEY_LEFT			75
#define _KEY_RIGHT			77

#define ICON_EMPTY			0
#define ICON_WALL			1
#define ICON_OBSTACLE		2
#define ICON_OBSTACLE_ADD	3
#define ICON_TARGET			4
#define ICON_BLOCK			7
#define ICON_USER			8
#define ICON_KILLER			9

// 구조체 선언
typedef struct _POSITION{
	int row;
	int col;
} POSITION;

// 함수 선언
void pushDisplay(unsigned char (*map)[PUSH_SIZE]);
POSITION pushinit(unsigned char (*OriginalMap)[PUSH_SIZE]);
int getkey();
int CheckMove(int key, POSITION player, unsigned char (*OriginalMap)[PUSH_SIZE]);
#endif