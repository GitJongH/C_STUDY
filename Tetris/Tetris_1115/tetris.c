#include "tetris.h"

unsigned char box_base[T_HIGH][T_WIDTH];
unsigned char box_display[T_HIGH][T_WIDTH];
unsigned char box_previous[T_HIGH][T_WIDTH];
BLOCK currentBLOCK;

int main() {

	int i;
	// Ŀ�� ���߱�
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;											// Ŀ�� �����
	cursorInfo.dwSize = 1;												// �β� : 1
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Ŀ��  ����

	srand(time(NULL));
	
	// cmdâ ũ�� ����
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