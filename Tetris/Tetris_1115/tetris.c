#include "tetris.h"

unsigned char box_base[T_HIGH][T_WIDTH];
unsigned char box_display[T_HIGH][T_WIDTH];
unsigned char box_previous[T_HIGH][T_WIDTH];
BLOCK currentBLOCK;

int main() {

	int i;
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

	for (i = 0; i < 15; i++) {
		delay(1000);
		currentBLOCK.point.row++;
		//currentBLOCK.point.column++;
		addBlockToDisplay();
		display();
	}

	return 0;
}