#include "push.h"
#include <stdio.h>

// �ܺ� �������� ���� 
extern unsigned char	map_1[PUSH_SIZE][PUSH_SIZE];

// �������� ����
unsigned char			map[PUSH_SIZE][PUSH_SIZE] = {0};
POSITION				player;

int main(){
	int key, step;

	// �ܼ��� ũ�� ����
	system("mode con: cols=50 lines=25");

	player = pushinit(map_1);
	pushDisplay(map);

	while(1){
		key = getkey();
		step = CheckMove(key, player, map);

	}

	return 0;
}