#include "tetris.h"

unsigned char box_base[T_HIGH][T_WIDTH];
unsigned char box_display[T_HIGH][T_WIDTH];
unsigned char box_previous[T_HIGH][T_WIDTH];
BLOCK currentBLOCK;


void check_getTempBlock() {

	int key;
	BLOCK tb;
	BLOCK cb = currentBLOCK;

	tb = getTempBlock(T_KEY_UP);
	printf("[c]key = %d, t = %d, r = %d, row = %d, col = %d\n", T_KEY_UP, cb.type, cb.rotation, cb.point.row, cb.point.column);
	tb = getTempBlock(T_KEY_DOWN);
	printf("[c]key = %d, t = %d, r = %d, row = %d, col = %d\n", T_KEY_DOWN, cb.type, cb.rotation, cb.point.row, cb.point.column);
	tb = getTempBlock(T_KEY_LEFT);
	printf("[c]key = %d, t = %d, r = %d, row = %d, col = %d\n", T_KEY_LEFT, cb.type, cb.rotation, cb.point.row, cb.point.column);
	tb = getTempBlock(T_KEY_RIGHT);
	printf("[c]key = %d, t = %d, r = %d, row = %d, col = %d\n", T_KEY_RIGHT, cb.type, cb.rotation, cb.point.row, cb.point.column);

}

int main() {

	int i, key;
	BLOCK tempBlock;
	int tempFlag;

	// 커서 감추기
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;											// 커서 숨기기
	cursorInfo.dwSize = 1;												// 두께 : 1
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 커서  설정

	srand(time(NULL));
	
	// cmd창 크기 변경
	system("mode con: cols=50 lines=25");

	init();
	selectBlock();
	addBlockToDisplay();
	display();

	while (1) {

		delay(100);
		tempFlag = 0;

		if (_kbhit()) {
			key = getkey();
			tempBlock = getTempBlock(key);
			tempFlag = 1;
		}
		else if (checkTime(1000)) {
			tempBlock = currentBLOCK;
			tempBlock.point.row++;
			tempFlag = 1;
		}
		if (tempFlag) {
			if (checkBlockMove(tempBlock)) {
				changeBlock(tempBlock);
				addBlockToDisplay();
				display();
				if (checkEndOfLine() == T_END_LINE) {
					copyDisplayToBase();
					selectBlock();
					addBlockToDisplay();
					display();
				}
			}
		}
	}

	return 0;
}
