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

int getkey() {

	int key;

	key = _getch();
	if (key == 224) key = _getch();

	return key;
}

int checkTime(int ms) {

	static time_t start = 0;
	time_t		  finish;

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
					printf("  ");
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

// 입력 받은 키를 기반으로 블럭 이동좌표 또는 회전정보를 추출
BLOCK getTempBlock(int key) {

	BLOCK block;
	block = currentBLOCK;

	switch (key) {
	case T_KEY_UP:		// 90도 회전
		block.rotation++;
		block.rotation %= 4;
		break;
	case T_KEY_DOWN:	// 한칸 아래 이동
		block.point.row++;
		break;
	case T_KEY_LEFT:	// 왼쪽 이동
		block.point.column--;
		break;
	case T_KEY_RIGHT:	// 오른쪽 이동
		block.point.column++;
		break;
	default:
		break;
	}

	return block;
}

// getBlockPosition
int	checkBlockMove(BLOCK newBlock) {

	int num;
	int row, column;
	// b의 4개 좌표값에 따라서
	for (num = 0; num < 4; num++) {

		row = newBlock.point.row + block[newBlock.type][newBlock.rotation][num].row;
		
		column = newBlock.point.column + block[newBlock.type][newBlock.rotation][num].column;

		if (box_base[row][column] != T_VALUE_SPACE) {
			return T_CANNOT_MOVE;	// retuen: 0
		}
	}

	return T_CAN_MOVE;				// return: 1
}

// 현재 블럭을 갱신한다
void changeBlock(BLOCK b) {

	currentBLOCK = b;
}

// 블럭이 더 이상 아래로 움직일 수 없는지 체크
int	checkEndOfLine() {

	BLOCK newBlock;

	newBlock = currentBLOCK;
	newBlock.point.row++;

	return checkBlockMove(newBlock);
}

// 블럭이 더 이상 아래로 이동 못하면, box_base에 블럭 추가
void copyDisplayToBase() {

	int i, row, column;

	for (i = 0; i < 4; i++) {
		row = currentBLOCK.point.row;
		column = currentBLOCK.point.column;

		row += block[currentBLOCK.type][currentBLOCK.rotation][i].row;
		column += block[currentBLOCK.type][currentBLOCK.rotation][i].column;

		box_base[row][column] = T_VALUE_BLOCK;
	}
}

void copyBaseToDisplay() {

	int i, k;

	for (i = 0; i < T_HIGH - 1; i++) {
		for (k = 0; k < T_WIDTH - 1; k++) {
			box_display[i][k] = box_display[i][k];
		}
	}
}

int	checkDeleteLine(int line) {

	int i;

	for (i = 1; i < T_WIDTH - 1; i++) {
		if (box_base[line][i] == T_VALUE_SPACE) {
			return T_NOT_FULL;
		}
	}

	return T_FULL;
}

int	deleteLine() {

	int line, i, k;

	for (line = T_HIGH - 2; line > 0; line--) {
		if (checkDeleteLine(line) == T_FULL) {
			for (i = line; i > 1; i--) {				// 라인 삭제 << 윗 라인 아래 라인으로 복사
				for (k = 1; k < T_WIDTH - 1; k++) {
					box_base[i][k] = box_base[i - 1][k];
				}
			}

			copyBaseToDisplay();
			display();
			delay(1000);
			line++;
		}
	}
}

int	checkGameFinish() {

	int result;

	result = checkBlockMove(currentBLOCK);

	if (result == T_CANNOT_MOVE) {
		gotoxy(T_HIGH / 2 - 2, 7);
		printf("==================");
		gotoxy(T_HIGH / 2 - 1,7);
		printf("=                =");
		gotoxy(T_HIGH / 2, 7);
		printf("=   GAME  OVER   =");
		gotoxy(T_HIGH / 2 + 1, 7);
		printf("=                =");
		gotoxy(T_HIGH / 2 + 2, 7);
		printf("==================");

		return T_GAME_FINISH;
	}

	return T_GAME_NOt_FINISH;
}