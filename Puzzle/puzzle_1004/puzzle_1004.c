#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

typedef struct _myIndex{
	int row;						// 행
	int column;		 				// 열
} myIndex;

typedef struct _myPz{
	void *pPz;
	int pzSize;		 				// 퍼즐 크기 (if 3x3 -> 3)
	myIndex pzIndex; 				// star의 행/열
} myPz;

void init(myPz *);					// 퍼즐 할당 함수
int getkey();						// 키 입력 함수
void puzzleDisplay(myPz, int, int); // Puzzle 출력 함수
myIndex getCoordinate(myPz, int);	// Key 값에 따라 * 위치 계산

int main()
{
    int size = 3;
    int key = 0, count = 0;
    myPz pz;
    myIndex Index;

    srand(time(NULL));

    pz.pPz = (int *)malloc(sizeof(int)*size*size);
    if(pz.pPz == NULL){
        printf("메모리가 부족합니다.\n");
        return 1;
    }

    pz.pzSize = size;
    init(&pz);

    printf("Puzzle Game: by 김종현 <23018030>\n");
    puzzleDisplay(pz, key, count);

    while(1){
        key = getkey();
		system("cls");
		count++;
		
        printf("Puzzle Game: by 김종현 <23018030>\n");
		
        puzzleDisplay(pz, key, count);
		
		Index = getCoordinate(pz, key);
		printf("<%d,%d> -> <%d,%d>\n", pz.pzIndex.row, pz.pzIndex.column, Index.row, Index.column);

		puzzleDisplay(pz, key, count);

		pz.pzIndex.row = Index.row;
		pz.pzIndex.column = Index.column;
	}

    free(pz.pPz);
    pz.pPz = NULL;

    return 0;
}

void init(myPz *ppz) // 퍼즐 할당 함수
{ 
    int i, j;
    int *pz;
    pz = (int *)(ppz->pPz);

	for(i=0;i<ppz->pzSize*ppz->pzSize;i++){
        pz[i] = rand() % (ppz->pzSize*ppz->pzSize);
        for(j=0;j<i;j++){
            if(pz[i] == pz[j]){
				i--;
				break;
			}
        }

		if(pz[i] == 0){
			ppz->pzIndex.row = i/(ppz->pzSize);
			ppz->pzIndex.column = i%(ppz->pzSize);
		}
    }
}

int getkey() // 키 입력 함수
{
	int key;

    key = getch();
    if(key == 224) key = getch();

	return key;
}

void puzzleDisplay(myPz pz, int key, int count) // Puzzle 출력 함수
{
    int i, j;
    int size;

	size = pz.pzSize;

	printf("┌");
	for(i=0; i<size-1; i++){
		switch(size){
		case 3:
		default:
			printf("───┬");
			size=3;
			break;
		case 4:
			printf("───┬");
			break;
		case 5:
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
				if(((int (*)[3])pz.pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[3])pz.pPz)[i][j]);
				if(j==2){
					printf("│\n");
					if(i==2) printf("└───┴───┴───┘");
					else printf("├───┼───┼───┤");
				}
				break;
			case 4:
				printf("│");
				if(((int (*)[4])pz.pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[4])pz.pPz)[i][j]);
				if(j==3){
					printf("│\n");
					if(i==3) printf("└───┴───┴───┴───┘");
					else printf("├───┼───┼───┼───┤");
				}
				break;
			case 5:
				printf("│");
				if(((int (*)[5])pz.pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[5])pz.pPz)[i][j]);
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

	printf("Count: %d\n", count);
	count++;
}

myIndex getCoordinate(myPz pz, int key) // Key 값에 따라 * 위치 계산
{
	myIndex targetIndex;
	targetIndex = pz.pzIndex;

    switch(key){
	case 72: //up
		if(pz.pzIndex.row > 0) targetIndex.row--;
        printf("key: UP\n");
		break;
	case 80: //down
		if(pz.pzIndex.row < (pz.pzSize-1)) targetIndex.row++;
		printf("key: DOWN\n");
		break;
	case 75: //left
		if(pz.pzIndex.column > 0) targetIndex.column--;
		printf("key: LEFT\n");
		break;
	case 77: //right
		if(pz.pzIndex.column < (pz.pzSize-1)) targetIndex.column++;
		printf("key: RIGHT\n");
		break;
	default:
		break;
	}

	return targetIndex;
}