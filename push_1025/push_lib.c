#include "push.h"
#include <stdio.h>
#include <Windows.h>

extern unsigned char	map[PUSH_SIZE][PUSH_SIZE];

POSITION pushinit(unsigned char (*OriginalMap)[PUSH_SIZE])
{
	int			i, j;
	POSITION	player;

	for(i=0; i<PUSH_SIZE; i++){
		for(j=0; j<PUSH_SIZE; j++){
			map[i][j] = OriginalMap[i][j];
			if(map[i][j] == ICON_USER){
				player.row = i;
				player.col = j;
			}
		}
	}

	return player;
}
void pushDisplay(unsigned char (*map)[PUSH_SIZE])
{
	int i, j;

	for(i=0; i<PUSH_SIZE; i++){
		for(j=0; j<PUSH_SIZE; j++){
			switch(map[i][j]){
			case ICON_EMPTY:
				printf("  ");
				break;
			case ICON_WALL:
				printf("¢Ç");
				break;
			case ICON_OBSTACLE:
				printf("¡à");
				break;
			case ICON_OBSTACLE_ADD:
			case ICON_TARGET:
				printf("¡Ù");
				break;
			case ICON_BLOCK:
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("¡Ú");
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 15);
				break;
			case ICON_USER:
				printf("¡Ý");
				break;
			}
		}
		printf("\n");
	}
}