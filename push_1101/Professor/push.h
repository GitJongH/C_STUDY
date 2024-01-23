#ifndef _PUSH_H
#define _PUSH_H

#define TRUE			1
#define FALSE			0

#define PUSH_SIZE		20
#define LEVEL_NUM		5

#define KEY_UP			72
#define KEY_DOWN		80
#define KEY_LEFT		75
#define KEY_RIGHT		77


#define ICON_WALL		0
#define ICON_EMPTY		1
#define ICON_USER		2
#define ICON_BLOCK		3
#define ICON_TARGET		4
#define ICON_WALL_NEW	5
#define ICON_KILLER		6
#define ICON_INIT		9

void init();
void addWall();
int getKey();
int moveCheck(unsigned char key);
void moveUser(unsigned int step, unsigned char key);
int checkFinish();
//void displayBlock(unsigned char(*w)[PUSH_SIZE]);
//void delayTime(int st);
//int moveKiller();

#endif