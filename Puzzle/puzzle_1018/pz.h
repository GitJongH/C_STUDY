#ifndef __PZ_H
#define __PZ_H

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

// 매크로 정의
#define _MODE_TEST		0
#define _MODE_GAME		1

#define _SIZE_DEFAULT	3
#define _SCORE_FILE		"./files/pzScore.txt"

#define _KEY_UP			72
#define _KEY_DOWN		80
#define _KEY_LEFT		75
#define _KEY_RIGHT		77

// 구조체 선언
struct _myIndex{
	int row;
	int column;
};

typedef struct _myIndex myIndex;

typedef struct _myPz{
	void *pPz;
	int  pzSize;
	myIndex	pzIndex;
}myPz;

// 함수선언
void init(myPz *pPz);
void puzzleDisplay(myPz pz, int key, int count);
myIndex getCoordinate(myPz pz, int key);
void exchangePz(myPz *pPz, myIndex index);
int checkPz(myPz pz);
void user(char *name, int len);
void setConfig(int *size, int *mode, char *scoreFileName);
void putScore(char *file, char *name, int count);

#endif