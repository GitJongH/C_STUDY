#include "tetris.h"

extern T_POINT block[T_PATTERN_NUM][4][4];
extern unsigned char box_base[T_HIGH][T_WIDTH];
extern unsigned char box_display[T_HIGH][T_WIDTH];
extern unsigned char box_previous[T_HIGH][T_WIDTH];
extern BLOCK currentBLOCK;

void gotoxy(int row, int column) {		// Ŀ�� �̵� �Լ�

	static HANDLE h = NULL;
	COORD c = { column, row };

	if (!h) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(h, c);
}

void delay(int sec) {

	time_t	start;						// time_t : time ������� �ð��� �� �ٷ�� ���� ������ Ÿ��
	time_t	finish;

	start = clock();					// clock() �Լ� : �ð� ���� �Լ�

	while (1) {
		finish = clock();
		if (finish - start > sec) break; // finish�� sec��ŭ ������ break
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

// box_base�� box_previous �ʱ�ȭ
void init() {

	int i, k;

	// �ʱ�ȭ
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_base[i][k] = T_VALUE_SPACE;
			box_previous[i][k] = 0xFF;	// 255
			box_display[i][k] = 0x00;	// 0
		}
	}

	// �� & �Ʒ� �� ����
	for (k = 0; k < T_WIDTH; k++) {
		box_base[0][k] = T_VALUE_WALL;			// ��
		box_base[T_HIGH - 1][k] = T_VALUE_WALL;	// �Ʒ�
	}

	// �� & �� �� ����
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_base[i][0] = T_VALUE_WALL;
			box_base[i][T_WIDTH - 1] = T_VALUE_WALL;
		}
	}

	// base�� display�� ����
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_display[i][k] = box_base[i][k];
		}
	}
}

// box_display�� box_previous��	     
// �������� ã�Ƽ� ���			     
// ����� ��ģ��,				     
// box_display�� box_previous�� ���� 
void display() {

	int i, k;

	// display/previous�� �»�ܿ��� �����ؼ� ���ϴܱ���
	// ���� �ϳ��ϳ� ���ؼ� �ٸ� ���� �߰��ϸ�,
	// �� �κи� ����(���)�Ѵ�.
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			if (box_display[i][k] != box_previous[i][k]) {
				gotoxy(i, 2 * k);
				switch (box_display[i][k]) {
				case T_VALUE_SPACE:
					printf("  ");
					break;
				case T_VALUE_WALL:
					printf("��"); // ��
					break;
				case T_VALUE_BLOCK_1:
				case T_VALUE_BLOCK_2:
				case T_VALUE_BLOCK_3:
				case T_VALUE_BLOCK_4:
				case T_VALUE_BLOCK_5:
				case T_VALUE_BLOCK_FINISH:
					printf("��");
					break;
				case T_VALUE_BLOCK:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					printf("��");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					break;
				default:
					break;
				}
			}
		}
	}

	// display -> previous ����
	for (i = 0; i < T_HIGH; i++) {
		for (k = 0; k < T_WIDTH; k++) {
			box_previous[i][k] = box_display[i][k];
		}
	}
}

// ���ο� �� ���� (�������� ��)
void selectBlock() {

	currentBLOCK.type = rand() % T_PATTERN_NUM; // �� Ÿ��
	currentBLOCK.rotation = rand() % 4;			// �� ����
	currentBLOCK.point.row = 1;
	currentBLOCK.point.column = T_WIDTH / 2;
}

// ���õ� ���� display�� �߰�
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

// �Է� ���� Ű�� ������� �� �̵���ǥ �Ǵ� ȸ�������� ����
BLOCK getTempBlock(int key) {

	BLOCK block;
	block = currentBLOCK;

	switch (key) {
	case T_KEY_UP:		// 90�� ȸ��
		block.rotation++;
		block.rotation %= 4;
		break;
	case T_KEY_DOWN:	// ��ĭ �Ʒ� �̵�
		block.point.row++;
		break;
	case T_KEY_LEFT:	// ���� �̵�
		block.point.column--;
		break;
	case T_KEY_RIGHT:	// ������ �̵�
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
	// b�� 4�� ��ǥ���� ����
	for (num = 0; num < 4; num++) {

		row = newBlock.point.row + block[newBlock.type][newBlock.rotation][num].row;
		
		column = newBlock.point.column + block[newBlock.type][newBlock.rotation][num].column;

		if (box_base[row][column] != T_VALUE_SPACE) {
			return T_CANNOT_MOVE;	// retuen: 0
		}
	}

	return T_CAN_MOVE;				// return: 1
}

// ���� ���� �����Ѵ�
void changeBlock(BLOCK b) {

	currentBLOCK = b;
}

// ���� �� �̻� �Ʒ��� ������ �� ������ üũ
int	checkEndOfLine() {

	BLOCK newBlock;

	newBlock = currentBLOCK;
	newBlock.point.row++;

	return checkBlockMove(newBlock);
}

// ���� �� �̻� �Ʒ��� �̵� ���ϸ�, box_base�� �� �߰�
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
			for (i = line; i > 1; i--) {				// ���� ���� << �� ���� �Ʒ� �������� ����
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