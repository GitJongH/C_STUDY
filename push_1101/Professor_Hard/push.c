#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<wincon.h>
#include<conio.h>
#include<time.h>

#include "push.h"

extern unsigned char map_1[PUSH_SIZE][PUSH_SIZE];
extern unsigned char map_2[PUSH_SIZE][PUSH_SIZE];
extern unsigned char map_3[PUSH_SIZE][PUSH_SIZE];
extern unsigned char map_4[PUSH_SIZE][PUSH_SIZE];
extern unsigned char map_5[PUSH_SIZE][PUSH_SIZE];

unsigned char world[PUSH_SIZE][PUSH_SIZE] = { 0 };
unsigned char(*map[LEVEL_NUM])[PUSH_SIZE] = { map_1, map_2, map_3, map_4, map_5};

unsigned char gameMap[PUSH_SIZE][PUSH_SIZE];
int userColumn, userRow;

int killerColumn, killerRow;

int level = 2;		// LEVEL : 0, 1, 2
int count = 0;
int limit = 100000000;
int delay = 0;

#ifdef _MY_DEBUG
unsigned char debugMsg[100] = { 0 };
unsigned int  debugCount = 0;
#endif


int main(int argc, char **argv){

	unsigned char	key;
	unsigned int	moveStep;


	// ƒøº≠ º˚±‚±‚
	CONSOLE_CURSOR_INFO CurInfo;

	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);

	// ƒ‹º÷¿« ≈©±‚ º≥¡§
	system("mode con: cols=50 lines=25");

	
	srand(time(NULL));

	init();

	system("cls");
	displayBlock(gameMap);
	
	while (1) {

		key = getKey();
		
		if (key == KEY_UP 
			|| key == KEY_DOWN
			|| key == KEY_LEFT 
			|| key == KEY_RIGHT) {
				moveStep = moveCheck(key);
				if ( moveStep > 0) {
					moveUser(moveStep, key);
					//system("cls");
					displayBlock(gameMap);
				}			

				if (checkFinish()) {
					printf("\n\nYou WIN!!\n\n");
					break;
				}
		}
		else if (key == 'r') {
			init();			
		}
		else if (key == 'q'){
			break;
		}
		

	}
	return 0;
}

unsigned char init() {

	int i, k;	

	count = 0;
	limit = 10;

	for (i = 0;i < PUSH_SIZE;i++) {
		for (k = 0;k < PUSH_SIZE;k++) {
			gameMap[i][k] = (map[level])[i][k];
			if (gameMap[i][k] == ICON_USER) {
				userColumn = i;
				userRow = k;
			}
			else if(gameMap[i][k] == ICON_KILLER) {
				//killerColumn = i;
				//killerRow = k;
			}
		}
	}
	return 1;
}

void addWall() {
	int column, row;

	while (1) {
		column = rand() % PUSH_SIZE;
		row = rand() % PUSH_SIZE;
		if (gameMap[column][row] == ICON_EMPTY &&
			(column!= killerColumn && 
			row != killerRow)) break;
	}

	gameMap[column][row] = ICON_WALL_NEW;
}

unsigned int getKey() {
	
	unsigned char key=NULL;

	if (kbhit()) {   //kbhit() --> ≈∞∫∏µÂ∏¶ ≈Î«— ¿‘∑¬¿Ã ¿÷æ˙¥¬¡ˆ∏∏ »Æ¿Œ
		key = getch();
		if (key == 224) key = getch();		
		fflush(stdin);
	}
	
	return key;
}

unsigned int moveCheck(unsigned char key) {

	int column_1, row_1;
	int column_2, row_2;

	column_1 = userColumn; 
	row_1 = userRow;

	column_2 = userColumn;
	row_2 = userRow;
	
	switch (key) {
	case KEY_UP:
		column_1 -= 1;
		column_2 -= 2;		
		break;
	case KEY_DOWN:
		column_1 += 1;
		column_2 += 2;
		break;
	case KEY_LEFT:
		row_1 -= 1;
		row_2 -= 2;
		break;
	case KEY_RIGHT:
		row_1 += 1;
		row_2 += 2;		
		break;
	default:
		break;

	}

	if (gameMap[column_1][row_1] == ICON_EMPTY) return 1;
	else if (gameMap[column_1][row_1] == ICON_TARGET) return 1;
	else if (gameMap[column_1][row_1] == ICON_BLOCK) {
		if (gameMap[column_2][row_2] == ICON_EMPTY) return 2;
		else if (gameMap[column_2][row_2] == ICON_TARGET) return 2;
		else return 0;
	}
	else return 0; //killerµµ

	//return 0;

}
/*
unsigned int moveCheck(unsigned char key) {

	switch (key) {
	case KEY_UP:
		if (gameMap[userColumn-1][userRow] == ICON_EMPTY) return 1;
		else if (gameMap[userColumn - 1][userRow] == ICON_TARGET) return 1;
		else if (gameMap[userColumn-1][userRow] == ICON_BLOCK) {
			if (gameMap[userColumn-2][userRow] == ICON_EMPTY) return 2;
			else if (gameMap[userColumn - 2][userRow] == ICON_TARGET) return 2;
			else return 0;
		}
		else return 0;

		break;
	case KEY_DOWN:
		if (gameMap[userColumn + 1][userRow] == ICON_EMPTY) return 1;
		else if (gameMap[userColumn + 1][userRow] == ICON_TARGET) return 1;
		else if (gameMap[userColumn + 1][userRow] == ICON_BLOCK) {
			if (gameMap[userColumn + 2][userRow] == ICON_EMPTY) return 2;
			else if (gameMap[userColumn + 2][userRow] == ICON_TARGET) return 2;
			else return 0;
		}
		else return 0;
		break;
	case KEY_LEFT:
		if (gameMap[userColumn][userRow - 1] == ICON_EMPTY) return 1;
		else if (gameMap[userColumn][userRow-1] == ICON_TARGET) return 1;
		else if (gameMap[userColumn][userRow - 1] == ICON_BLOCK) {
			if (gameMap[userColumn][userRow - 2] == ICON_EMPTY) return 2;
			else if (gameMap[userColumn][userRow - 2] == ICON_TARGET) return 2;
			else return 0;
		}
		else return 0;
		
		break;
	case KEY_RIGHT:	
		if (gameMap[userColumn][userRow + 1] == ICON_EMPTY) return 1;
		else if (gameMap[userColumn][userRow+1] == ICON_TARGET) return 1;
		else if (gameMap[userColumn][userRow + 1] == ICON_BLOCK) {
			if (gameMap[userColumn][userRow + 2] == ICON_EMPTY) return 2;
			else if (gameMap[userColumn][userRow + 2] == ICON_TARGET) return 2;
			else return 0;
		}
		else return 0;		
		break;
	default:
		break;

	}

	return 0;

}
*/

unsigned int moveUser(unsigned int step, unsigned char key) {

	if (step != 1 && step != 2) return 1;

	count++;

#ifdef _MY_DEBUG
	debugCount++;
	sprintf_s(debugMsg, 100, "in] moveUser step=%d key=%d count=%d\n", step, key, debugCount);
#endif	

	switch (key) {
	case KEY_UP:
		gameMap[userColumn + 0][userRow] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		gameMap[userColumn - 1][userRow] = ICON_USER;
		if (step == 2) gameMap[userColumn - 2][userRow] = ICON_BLOCK;
		userColumn -= 1;
		break;
	case KEY_DOWN:
		gameMap[userColumn + 0][userRow] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		gameMap[userColumn + 1][userRow] = ICON_USER;
		if (step == 2) gameMap[userColumn + 2][userRow] = ICON_BLOCK;
		userColumn += 1;
		break;
	case KEY_LEFT:
		gameMap[userColumn][userRow + 0] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn + 0][userRow] = ICON_TARGET;
		gameMap[userColumn][userRow - 1] = ICON_USER;
		if (step == 2) gameMap[userColumn][userRow - 2] = ICON_BLOCK;
		userRow -= 1;
		break;
	case KEY_RIGHT:
		gameMap[userColumn][userRow + 0] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		gameMap[userColumn][userRow + 1] = ICON_USER;
		if (step == 2) gameMap[userColumn][userRow + 2] = ICON_BLOCK;
		userRow += 1;
		break;
	default:
		break;

	}

	return 0;
}



/*
unsigned int moveUser(unsigned int step, unsigned char key) {

	if (step != 1 && step != 2) return 1;

	count++;

	switch (key) {
	case KEY_UP:
		gameMap[userColumn+0][userRow] = ICON_EMPTY;
		if((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		gameMap[userColumn-1][userRow ] = ICON_USER;
		if (step == 2) gameMap[userColumn-2][userRow] = ICON_BLOCK;
		userColumn -= 1;
		break;
	case KEY_DOWN:
		gameMap[userColumn + 0][userRow] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		gameMap[userColumn + 1][userRow] = ICON_USER;
		if (step == 2) gameMap[userColumn + 2][userRow] = ICON_BLOCK;
		userColumn += 1;
		break;		
	case KEY_LEFT:
		gameMap[userColumn][userRow + 0] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn + 0][userRow] = ICON_TARGET;
		gameMap[userColumn][userRow - 1] = ICON_USER;
		if (step == 2) gameMap[userColumn][userRow - 2] = ICON_BLOCK;
		userRow -= 1;
		break;
	case KEY_RIGHT:
		gameMap[userColumn][userRow + 0] = ICON_EMPTY;
		if ((map[level])[userColumn][userRow] == ICON_TARGET)
			gameMap[userColumn][userRow] = ICON_TARGET;
		gameMap[userColumn][userRow + 1] = ICON_USER;
		if (step == 2) gameMap[userColumn][userRow + 2] = ICON_BLOCK;
		userRow += 1;		
		break;
	default:
		break;

	}

	return 0;
}
*/
unsigned int checkFinish() {
	int i, k;
	for (i = 0; i < PUSH_SIZE; i++) {
		for (k = 0;k < PUSH_SIZE;k++) {
			if ((map[level])[i][k] == ICON_TARGET) {
				if(gameMap[i][k] != ICON_BLOCK) return 0; //not yet
			}
		}
	}

	return 1;//finish
}

void gotoxy(int x, int y){

	static HANDLE h = NULL;
	COORD c;
	if (!h){
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(h, c);
}


void displayBlock(unsigned char(*w)[PUSH_SIZE]) {
	
	int i, k;

#if 0
	static unsigned char previous[PUSH_SIZE][PUSH_SIZE] = {
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	
};

	for (i = 0; i < PUSH_SIZE; i++) {
		for (k = 0; k < PUSH_SIZE; k++) {
			if(w[i][k] != previous[i][k]){
				gotoxy(2*k,i);
				previous[i][k]=w[i][k];
				if (w[i][k] == ICON_WALL) printf("°‡");
				else if (w[i][k] == ICON_WALL_NEW) {
					// 0=∞À¡§, 1=∆ƒ∂˚, 4=ª°∞≠, 6=≥Î∂˚, 7,»Òªˆ, F=π‡¿∫ »Úªˆ
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  
					printf("°·");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else if (w[i][k] == ICON_EMPTY)	printf("  ");
				else if (w[i][k] == ICON_USER)	printf("®„");
				else if (w[i][k] == ICON_BLOCK)	printf("°Ÿ");				
				else if (w[i][k] == ICON_TARGET)	printf("°⁄");
				else if (w[i][k] == ICON_KILLER){	
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);  
					printf("¢ﬁ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  
				}
			}
		}
		//printf("\n");
	}

	gotoxy(0, PUSH_SIZE+3);
	printf("count: %d (delay: %d, limit: %d)", count, delay, limit);
#else
	for (i = 0; i < PUSH_SIZE; i++) {
		for (k = 0; k < PUSH_SIZE; k++) {
			if (w[i][k] == ICON_WALL) printf("°‡");
			else if (w[i][k] == ICON_WALL_NEW) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);  // 0=∞À¡§, 1=∆ƒ∂˚, 4=§≤ª°∞≠, 6=≥Î∂˚, 7,»Òªˆ, F=π‡¿∫ »Úªˆ
				printf("°·");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else if (w[i][k] == ICON_EMPTY)		printf("  ");
			else if (w[i][k] == ICON_USER)		printf("®„");
			else if (w[i][k] == ICON_BLOCK)		printf("°Ÿ");				
			else if (w[i][k] == ICON_TARGET)	printf("°⁄");
		}
		printf("\n");
	}
	printf("\n\ncount: %d (delay: %d, limit: %d)\n\n", count, delay, limit);
#endif

	

#ifdef _MY_DEBUG
	printf("\n\nDebug: %s\n\n", debugMsg);
#endif
}

void delayTime(int st) {
	
	int i, k=0;
	st = st * 1000;
	for (i = 0; i < st; i++){ 
		k++;
	}
	
}

int moveKiller(){
	int column, row;
	int column2, row2;

	column=killerColumn;
	row=killerRow;

	if(userColumn > killerColumn ) column++;			
	else if(userColumn < killerColumn )column--;
	if(userRow > killerRow ) row++;
	else if(userRow < killerRow )row--;

	column2=column;
	row2=row;

	while(gameMap[column2][row2] != ICON_EMPTY &&
		gameMap[column2][row2] != ICON_USER ){
		column2=killerColumn;
		row2=killerRow;
		switch(rand()%4){
		case 0:
			column2++;
			break;
		case 1:
			column2--;
			break;
		case 2:
			row2++;
			break;
		case 3:
			row2--;
			break;
		default:
			break;
		}
	}

	gameMap[column2][row2] = ICON_KILLER;
	gameMap[killerColumn][killerRow] = ICON_EMPTY;
	killerColumn = column2;
	killerRow = row2;
	displayBlock(gameMap);

	if(userColumn==killerColumn && 
		userRow == killerRow) return 1;
	else return 0;


}