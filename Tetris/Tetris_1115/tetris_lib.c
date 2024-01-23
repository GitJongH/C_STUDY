#include "tetris.h"

extern T_POINT block[T_PATTERN_NUM][4][4];
extern unsigned char box_base[T_HIGH][T_WIDTH];
extern unsigned char box_display[T_HIGH][T_WIDTH];
extern unsigned char box_previous[T_HIGH][T_WIDTH];
extern BLOCK currentBLOCK;

void gotoxy(int row, int column) {		// 커서 이동 함수

	static HANDLE h = NULL;
	COORD c = { column, row };

	if (!h) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(h, c);
}

void delay(int sec) {

	time_t	start;						// time_t : time 헤더에서 시간을 잘 다루기 위한 데이터 타입
	time_t	finish;

	start = clock();					// clock() 함수 : 시간 측정 함수

	while (1) {
		finish = clock();
		if (finish - start > sec) break; // finish가 sec만큼 지나면 break
	}
}

int checkTime(int ms) {

	static time_t start = 0;
	time_t finish;

	finish = clock();
	if (finish - start > ms) {
		start = finish;
		return T_TIMEOUT;				// return 1;
	}

	return T_NOT_TIMEOUT;				// return 0;
}

// box_base와 box_previous 초기화
void init() {

	int i, k;

	// 초기화
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_base[i][k] = T_VALUE_SPACE;
			box_previous[i][k] = 0xFF;	// 255
			box_display[i][k] = 0x00;	// 0
		}
	}

	// 위 & 아래 벽 설정
	for (k = 0; k < T_WIDTH; k++) {
		box_base[0][k] = T_VALUE_WALL;			// 위
		box_base[T_HIGH - 1][k] = T_VALUE_WALL;	// 아래
	}

	// 좌 & 우 벽 설정
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_base[i][0] = T_VALUE_WALL;
			box_base[i][T_WIDTH - 1] = T_VALUE_WALL;
		}
	}

	// base를 display에 복사
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_display[i][k] = box_base[i][k];
		}
	}
}

// box_display와 box_previous의	     
// 차이점을 찾아서 출력			     
// 출력을 마친후,				     
// box_display를 box_previous에 복사 
void display() {

	int i, k;

	// display/previous를 좌상단에서 시작해서 우하단까지
	// 값을 하나하나 비교해서 다른 값을 발견하면,
	// 그 부분만 수정(출력)한다.
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			if (box_display[i][k] != box_previous[i][k]) {
				gotoxy(i, 2 * k);
				switch (box_display[i][k]) {
				case T_VALUE_SPACE:
					printf(" ");
					break;
				case T_VALUE_WALL:
					printf("□"); // ▤
					break;
				case T_VALUE_BLOCK_1:
				case T_VALUE_BLOCK_2:
				case T_VALUE_BLOCK_3:
				case T_VALUE_BLOCK_4:
				case T_VALUE_BLOCK_5:
				case T_VALUE_BLOCK_FINISH:
					printf("■");
					break;
				case T_VALUE_BLOCK:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					break;
				default:
					break;
				}
			}
		}
	}

	// display -> previous 복사
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_previous[i][k] = box_display[i][k];
		}
	}
}

// 새로운 블럭 선택 (내려오는 블럭)
void selectBlock() {

	currentBLOCK.type = rand() % T_PATTERN_NUM; // 블럭 타입
	currentBLOCK.rotation = rand() % 4;			// 블럭 방향
	currentBLOCK.point.row = 1;
	currentBLOCK.point.column = T_WIDTH / 2;
}

// 선택된 블럭을 display에 추가
void addBlockToDisplay() {

	int i, k;
	int row, column;

	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_display[i][k] = box_base[i][k];
		}
	}

	for (i = 0; i < 4; i++) {
		row = currentBLOCK.point.row;
		column = currentBLOCK.point.column;

		row += block[currentBLOCK.type][currentBLOCK.rotation][i].row;
		column += block[currentBLOCK.type][currentBLOCK.rotation][i].column;

		box_display[row][column] = currentBLOCK.type;
	}
}