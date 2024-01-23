#include "push.h"
#include <stdio.h>

// 외부 전역변수 선언 
extern unsigned char	map_1[PUSH_SIZE][PUSH_SIZE];

// 전역변수 선언
unsigned char			map[PUSH_SIZE][PUSH_SIZE] = {0};
POSITION				player;

int main(){
	int key, step;

	// 콘솔의 크기 설정
	system("mode con: cols=50 lines=25");

	player = pushinit(map_1);
	pushDisplay(map);

	while(1){
		key = getkey();
		step = CheckMove(key, player, map);

	}

	return 0;
}