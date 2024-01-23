#include "push.h"
#include <stdio.h>

extern unsigned char	map_1[PUSH_SIZE][PUSH_SIZE];

unsigned char			map[PUSH_SIZE][PUSH_SIZE] = {0};
POSITION				player;

int main(){
	player = pushinit(map_1);
	pushDisplay(map);
	printf("Player: (%d %d)\n", player.row, player.col);
	return 0;
}