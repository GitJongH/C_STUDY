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
void exchangePz(myPz *,myIndex);	// 입력키에 따라 퍼즐 변화 함수
myIndex getCoordinate(myPz, int);	// Key 값에 따라 * 위치 계산
int checkPz(myPz *, int);			// 퍼즐 완성도 확인 함수
void user(char *, int);
void setConfig(int *, int *, char *);
void putScore(char *, char *, int);

int main()
{
    int size, mode, i, check;
    int key = 0, count = 0;
    char scorefile[100], name[100];
    myPz pz;
    myIndex Index;

    srand(time(NULL));

    setConfig(&size, &mode, scorefile);

    printf("\n\n\n\n\n\t\tID: ");
    scanf("%s", name);

    system("cls");

    pz.pPz = (int *)malloc(sizeof(int)*size*size);
    if(pz.pPz == NULL){
        printf("메모리가 부족합니다.\n");
        return 1;
    }

    pz.pzSize = size;

    if(mode == 0){
        for(i=0; i<(size*size)-2; i++){
            ((int *)pz.pPz)[i] = i+1;
        }
        ((int *)pz.pPz)[i] = 0;
        ((int *)pz.pPz)[i+1] = i+1;

        pz.pzIndex.row = i/size;
        pz.pzIndex.column = i%size;
    }
    else{
        init(&pz);
    }   

    puzzleDisplay(pz, key, count);

    while(1){
        key = getkey();
		count++;
		system("cls");
		
		Index = getCoordinate(pz, key);
		
		exchangePz(&pz, Index);

        puzzleDisplay(pz, key, count);

		printf("Coordinate: <%d,%d> -> <%d,%d>\n", pz.pzIndex.row, pz.pzIndex.column, Index.row, Index.column);

		pz.pzIndex.row = Index.row;
		pz.pzIndex.column = Index.column;
		/*
		check = checkPz(&pz, size);
		
		if(check == (size*size)){
			printf("You Win!!!\n\n");
			printf("Restart . . . put 'p'");
			key = getkey();
			if(key == 80 || key == 112){
				system("cls");
				printf("퍼즐 크기를 입력하세요(3, 4, 5): ");
				scanf("%d", &size);
				pz.pPz = (int *)malloc(sizeof(int)*size*size);
				pz.pzSize = size;
				init(&pz);
				puzzleDisplay(pz, key, count);
				check = 0;
				count = 0;
				key = 0;
				continue;
			}
			else break;
		}
		*/
		if((pz.pzIndex.column != Index.column) || (pz.pzIndex.row != Index.row)){
			exchangePz(&pz, Index);
			count++;
			puzzleDisplay(pz, key, count);

			if(!checkpz(pz)){
				printf("======= GAME OVER =======\n");
				putscore(scorefile, name, count);
				break;
			}

		}
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

	printf("Puzzle Game: by 김종현 <23018030>\n\n");

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
					if(i==2){
						printf("└───┴───┴───┘");
					}
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

	switch(key){
	case 72: //up
		printf("key: UP\n");
		break;
	case 80: //down
		printf("key: DOWN\n");
		break;
	case 75: //left
		printf("key: LEFT\n");
		break;
	case 77: //right
		printf("key: RIGHT\n");
		break;
	default:
		break;
	}

	printf("Count: %d\n", count);
}

void exchangePz(myPz *ppz,myIndex index) // 입력키에 따라 퍼즐 변화 함수
{
	int temp;
	int star, target;

	star = (ppz->pzSize)*(ppz->pzIndex.row)+(ppz->pzIndex.column);
	target = (ppz->pzSize)*(index.row)+(index.column);

	temp = ((int *)ppz->pPz)[star];
	((int *)ppz->pPz)[star] = ((int *)ppz->pPz)[target];
	((int *)ppz->pPz)[target] = temp;
}

myIndex getCoordinate(myPz pz, int key) // Key 값에 따라 * 위치 계산
{
	myIndex targetIndex;
	targetIndex = pz.pzIndex;

    switch(key){
	case 72: //up
		if(pz.pzIndex.row > 0) targetIndex.row--;
		break;
	case 80: //down
		if(pz.pzIndex.row < (pz.pzSize-1)) targetIndex.row++;
		break;
	case 75: //left
		if(pz.pzIndex.column > 0) targetIndex.column--;
		break;
	case 77: //right
		if(pz.pzIndex.column < (pz.pzSize-1)) targetIndex.column++;
		break;
	default:
		break;
	}

	return targetIndex;
}

int checkPz(myPz *ppz, int size) // 퍼즐 완성도 확인 함수
{
	int i, check = 0;
	int *pz;
	pz = (int *)(ppz->pPz);

	for(i=0; i<size*size; i++){
		switch(size){
			case 3:
			default:
				if(pz[i] != i+1){
					check = 0;
					break;
				}
				else check++;
				if(check == 8){
					printf("\n\n== Game Over!!! ==\n\n");
					check++;
				}
				break;
			case 4:
				if(pz[i] != i+1){
					check = 0;
					break;
				}
				else check++;
				if(check == 15){
					printf("\n\n== Game Over!!! ==\n\n");
					check++;
				}
				break;
			case 5:
				if(pz[i] != i+1){
					check = 0;
					break;
				}
				else check++;
				if(check == 24){
					printf("\n\n== Game Over!!! ==\n\n");
					check++;
				}
				break;
		}
		if(check == (size*size)) break;
	}

	return check;
}

void user(char *name, int len)
{
    int i;

    for(i=0; i<len; i++) name[i] = 0x00;
    gets(name);
    printf("%s", name);
}

void setConfig(int *size, int *mode, char * scoreFileName)
{
    FILE *fp;
    char buffer[100];
    int len;

    *size = 3;
    *mode = 1;  // game mode

    fp = fopen("./files/pzConfig.txt", "r");

    if(fp == NULL){
        printf("file open error\n");
        return;
    }
    else{
        while(1){
            if(fgets(buffer, sizeof(buffer), fp) == NULL, fp) break;

            if(strncmp("SIZE: ", buffer, 6) == 0){
                *size = atoi(&buffer[6]);
            }
            else if(strncmp("MODE: ", buffer, 6) == 0){
                if(strncmp("TEST", &buffer[6], 4) == 0) *mode = 0;
            }
            else if(strncmp("SCORE: ", buffer, 7) == 0){
                strcpy(scoreFileName, &buffer[7]);
                len = strlen(scoreFileName);
                if(scoreFileName[len - 1] == 10){       // 개항
                    scoreFileName[len - 1] = 0x00;
                }
            }

        }
    }

    fclose(fp);
}

void putScore(char *file, char *name, int count)
{
    FILE *fp;
    int i;
    char buffer[100] = {0x00}, Date[100], Time[100];
    
    if(file == NULL || name == NULL) return;

    strcat(buffer, "./files/");
    strcat(buffer, file);

    // 컬럼 타이틀 생성
    fp = fopen(buffer, "r");
    if(fp == NULL){
        fp = fopen(buffer, "w");
        fprintf(fp, "%20s %10s %10s\n", "data/tine", "name", "score");
        fclose(fp);
    }

    // 점수 기록
    fp = fopen(buffer, "a");
    _strdate(Date);
    _strtime(time);

    fprint(fp, "%10s : %7s %10s %10d\n", Date, Time, name, count);

    fclode(fp);
}