// push.txt -> level 버전, 파일이름을 push.c로 변경해서 검파일

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<wincon.h>
#include<time.h>

#include"push.h"

//외부 전역변수 선언
extern unsigned char map_1[PUSH_SIZE][PUSH_SIZE];

//전역변수 선언
unsigned int game[PUSH_SIZE][PUSH_SIZE];
int row, column;

int getKey(){
	int key;
	key = getch();
	if(key == 224){
		key = getch();
	}
	return key;
}

void init(){
	int i,k;
	for(i=0;i<PUSH_SIZE;i++){
		for(k=0;k<PUSH_SIZE;k++){
			game[i][k] = map_1[i][k];
			if(game[i][k]==ICON_USER){
				row = i;
				column = k;
			}
		}
	}
}

void display(){
	int i,k;

	system("cls");
	for(i=0;i<PUSH_SIZE;i++){
		for(k=0;k<PUSH_SIZE;k++){
			switch(game[i][k]){
			case ICON_WALL:
				printf("□");
				break;
			case ICON_WALL_NEW:
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("■");
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 15);
				break;
			case ICON_EMPTY:
				printf("  ");
				break;
			case ICON_USER:	
				printf("ⓦ");
				break;
			case ICON_BLOCK:	
				printf("☆");				
				break;
			case ICON_TARGET:
				printf("★");
				break;
			default:
				break;
			}
		}

		printf("\n");
	}
}

// return:
// 0 : 이동 못함
// 1 : 한칸이동 (no block)
// 2 ; 두칸이동 (with block)
int checkMove(int key){
	int tempRow, tempColumn, temp, move;

	tempRow = row;		 // user의 행값
	tempColumn = column; // user의 열값

	if(key == KEY_DOWN || key == KEY_RIGHT) temp = 1;
	else if	(key == KEY_UP || key == KEY_LEFT) temp = -1;
	else temp = 0;

	move=1;
	if(key == KEY_UP || key == KEY_DOWN){
		tempRow +=temp;
	}
	else{
		tempColumn +=temp;
	}

	if(game[tempRow][tempColumn] == ICON_BLOCK){
		move = 2;
		if(key == KEY_UP || key == KEY_DOWN){
			tempRow +=temp;
		}
		else{
			tempColumn +=temp;
		}
	}

	if( game[tempRow][tempColumn] == ICON_EMPTY ||
		game[tempRow][tempColumn] == ICON_TARGET ){
		//이동 
		return move;
	}
	else{
		//이동 x
		return 0;
	}
}

//step: checkMove의 return 값
void moveUser(unsigned int step, unsigned char key){

	int tempRow, tempColumn, temp;

	if(key == KEY_DOWN || key == KEY_RIGHT) temp = 1;
	else if	(key == KEY_UP || key == KEY_LEFT) temp = -1;
	else temp = 0;

	tempRow = row;
	tempColumn = column;

	//1 블럭이동 (step 2)
	if( step == 2 ){
		if(key == KEY_UP || key == KEY_DOWN){
			tempRow +=(temp*2);
		}
		else{
			tempColumn +=(temp*2);
		}
		game[tempRow][tempColumn] = ICON_BLOCK;
	}

	//2 사용자 이동
	tempRow = row;
	tempColumn = column;
	
	if(key == KEY_UP || key == KEY_DOWN){
		tempRow +=temp;
	}
	else{
		tempColumn +=temp;
	}
	game[tempRow][tempColumn] = ICON_USER;

	//3 이전 사용자 위치값 정리
	game[row][column] = ICON_EMPTY;
	
	if(map_1[row][column] == ICON_TARGET){
		game[row][column] = ICON_TARGET;
	}

	//4 사용자 현재 위치값 변
	row = tempRow;
	column = tempColumn;
}


int checkFinish(){
	int i,k;

	for(i=0;i<PUSH_SIZE;i++){
		for(k=0;k<PUSH_SIZE;k++){
			if(map_1[i][k] ==ICON_TARGET &&
				game[i][k] !=ICON_BLOCK ) return 0;
		}
	}
	return 1;
}


void addWall(){
	int count=0, r,c;

	while(1){
		r = rand()%PUSH_SIZE;
		c = rand()%PUSH_SIZE;
		if(game[r][c] == ICON_EMPTY){
			game[r][c]=ICON_WALL_NEW;
			break;
		}
		else{
			count++;
			if(count >20) break;
		}
	}
}

#if 1
int main(){
	int key, step;
	// 커서 숨기기
	CONSOLE_CURSOR_INFO CurInfo;

	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);

	// 콘솔의 크기 설정
	system("mode con: cols=50 lines=25");

	init();
	display();

	while(1){
		key = getKey();
		step = checkMove(key);
		if(step) {
			moveUser(step, key);
			display();
			if(checkFinish()) break;
		}
	}
	printf("\n\n ==== GAME OVER!! ==== \n");

	return 0;
}

#else

int main(){
	int key, step;
	time_t	start, finish;
	// 커서 숨기기
	CONSOLE_CURSOR_INFO CurInfo;

	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);

	// 콘솔의 크기 설정
	system("mode con: cols=50 lines=25");

	init();
	display();

	start = GetTickCount64();
	while(1){
		if(!kbhit()){
			finish = GetTickCount64();
			if((finish-start) > 2000){
				addWall();
				start = finish;
			}
		}
		key = getKey();
		step = checkMove(key);
		if(step) {
			moveUser(step, key);
			display();
			if(checkFinish()) break;
		}
	}
	printf("\n\n ==== GAME OVER!! ==== \n");

	return 0;
}
#endif

