#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

void init(void *, int);
int getkey();
void puzzleDisplay(void *, int, int, int);
void play();

int main()
{
    void *pPz;
    int size;
    int key = 0, count = 0;

    srand(time(NULL));

    for(size=3; size <7; size++){
        // system("cls");
        if(size%2==1){
            // 1차원 배열 포인터
            printf("%s (size: %d), \n\n", "1차원 배열 할당", size);
            pPz = (int *)malloc(sizeof(int)*size*size);
        }
        else{
            // 2차원 배열 포인터
            printf("%s (size: %d), \n\n", "2차원 배열 할당", size);
            pPz = (int (*)[])malloc(sizeof(int)*size*size);
        }

        if(pPz == NULL) continue;
        
        init(pPz, size);
        puzzleDisplay(pPz, size, key, count);

        free(pPz);
        pPz = NULL;

        getch();
    }

    return 0;
}

void init(void *pPz, int size)
{
    int i, j;
    int *pz;
    pz = (int *)pPz;

	for(i=0;i<size*size;i++){
        pz[i] = rand() % (size*size);
        for(j=0;j<i;j++){
            if(pz[i] == pz[j]){
				i--;
				break;
			}
        }
    }
}

int getkey()
{
	int key;

    key = getch();
    if(key == 224) key = getch();

	return key;
}

void puzzleDisplay(void *pPz, int size, int key, int count)
{
    int i, j;
	
	printf("┌");
	for(i=0; i<size-1; i++){
		switch(size){
		case 3:
		default:
			// printf("┌───┬───┬───┐\n");
			printf("───┬");
			size=3;
			break;
		case 4:
			// printf("┌───┬───┬───┬───┐\n");
			printf("───┬");
			break;
		case 5:
			// printf("┌───┬───┬───┬───┬───┐\n");
			printf("───┬");
			break;
		}
	}
	printf("───┐\n");

    for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			switch(size){
			case 3:
			default:
				printf("│");
				if(((int (*)[3])pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[3])pPz)[i][j]);
				if(j==2){
					printf("│\n");
					if(i==2) printf("└───┴───┴───┘");
					else printf("├───┼───┼───┤");
				}
				size=3;
				break;
			case 4:
				printf("│");
				if(((int (*)[4])pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[4])pPz)[i][j]);
				if(j==3){
					printf("│\n");
					if(i==3) printf("└───┴───┴───┴───┘");
					else printf("├───┼───┼───┼───┤");
				}
				break;
			case 5:
				printf("│");
				if(((int (*)[5])pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[5])pPz)[i][j]);
				if(j==4){
					printf("│\n");
					if(i==4) printf("└───┴───┴───┴───┴───┘");
					else printf("├───┼───┼───┼───┼───┤");
				}
				break;
			}
		}
		printf("\n");
    }
	printf("\n");

}