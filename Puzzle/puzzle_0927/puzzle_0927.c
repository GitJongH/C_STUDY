#include <stdio.h>
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

    for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			switch(size){
			case 3:
			default:
				printf("%3d", ((int (*)[3])pPz)[i][j]);
				size=3;
				break;
			case 4:
				printf("%3d", ((int (*)[4])pPz)[i][j]);
				break;
			case 5:
				printf("%3d", ((int (*)[5])pPz)[i][j]);
				break;
			}
		}
		printf("\n");
    }
	printf("\n");

}