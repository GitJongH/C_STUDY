#include "pz.h"

//pPz - 1차원 배열
void init(myPz *pPz){
	int i,k;
	int size = 9;
	int *p = (int *)(pPz->pPz);

	if( 3 <= pPz->pzSize  && pPz->pzSize <6) size = (pPz->pzSize)*(pPz->pzSize);

	for( i=0 ;i<size;i++){
		p[i] = rand()%size;
		for(k=0;k<i;k++){
			if(p[i] == p[k]){
				i--;
				break;
			}
		}
		if(p[i] == 0){
			pPz->pzIndex.row = i/(pPz->pzSize);
			pPz->pzIndex.column = i%(pPz->pzSize);
		}
	}
}

//pPz - 2차원 배열
#if 0
void puzzleDisplay(myPz pz, int key, int count){
	int i,k;	
	
	for( i=0;i<pz.pzSize;i++){	
		for(k=0;k<pz.pzSize;k++){
			switch(pz.pzSize){
			case 3:
			default:
				printf("%3d",((int(*)[3])(pz.pPz))[i][k]);
				size=3;
				break;
			case 4:
				printf("%3d",((int(*)[4])(pz.pPz))[i][k]);
				break;
			case 5:
				printf("%3d",((int(*)[5])(pz.pPz))[i][k]);
				break;
			}
		}
		printf("\n");
	}
}
#else
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
	case _KEY_UP: //up
		printf("key: UP\n");
		break;
	case _KEY_DOWN: //down
		printf("key: DOWN\n");
		break;
	case _KEY_LEFT: //left
		printf("key: LEFT\n");
		break;
	case _KEY_RIGHT: //right
		printf("key: RIGHT\n");
		break;
	default:
		break;
	}

	printf("Count: %d\n", count);
}
#endif

int getKey(){
	int key;
	key = getch();
	if(key == 224) key = getch();
	return key;
}

myIndex getCoordinate(myPz pz, int key){

	myIndex targetIndex;

	targetIndex = pz.pzIndex;

	switch(key){
	case _KEY_UP:
		if(pz.pzIndex.row > 0) targetIndex.row--;
		//printf("UP\n");
		break;
	case _KEY_DOWN:
		if(pz.pzIndex.row < (pz.pzSize-1)) targetIndex.row++;
		//printf("DOWN\n");
		break;
	case _KEY_LEFT:
		if(pz.pzIndex.column > 0) targetIndex.column--;
		//printf("LEFT\n");
		break;
	case _KEY_RIGHT:
		if(pz.pzIndex.column < (pz.pzSize-1)) targetIndex.column++;
		//printf("RIGHT\n");
		break;
	default:
		//printf("%d\n",key);
		break;
	}

	return targetIndex;
}

void exchangePz(myPz *pPz, myIndex index){
	int temp;
	int star, target;

	star = (pPz->pzSize)*(pPz->pzIndex.row)+(pPz->pzIndex.column);
	target = (pPz->pzSize)*(index.row)+(index.column);

	temp = ((int *)pPz->pPz)[star];
	((int *)pPz->pPz)[star] = ((int *)pPz->pPz)[target];
	((int *)pPz->pPz)[target] = temp;

	pPz->pzIndex = index;
}

// if it returns '1', it means that this game is not over.
int checkPz(myPz pz){

	int i, size;

	size = pz.pzSize*pz.pzSize;

	for(i=0;i<size-1;i++){
		if(((int *)(pz.pPz))[i] != i+1) return 1;
	}

	return 0;
}

void user(char *name, int len){
	int i;
	for(i=0;i<len;i++) name[i]=0x00;
	gets(name);
	printf("%s", name);
}

void setConfig(int *size, int *mode, char *scoreFileName){
	FILE *fp;
	char buffer[100];
	int len;

	*size = _SIZE_DEFAULT;
	*mode = _MODE_GAME;

	fp = fopen("./files/pzConfig.txt","r");
	if(fp == NULL){
		printf("file open error\n");
		return;
	}
	else{
		while(1){
			if(NULL == fgets(buffer, sizeof(buffer), fp) ) break;
			
			if(strncmp("SIZE: ", buffer, 6) == 0){
				*size = atoi(&buffer[6]);
			}
			else if(strncmp("MODE: ", buffer, 6) == 0){
				if(strncmp("TEST", &buffer[6], 4) == 0) *mode = 0;
			}
			else if(strncmp("SCORE: ", buffer, 7) == 0){
				strcpy(scoreFileName, &buffer[7]);
				len = strlen(scoreFileName);
				if(scoreFileName[len-1] == 10) {        // 개항
					scoreFileName[len-1] = 0x00;
				}
			}
		}
	}

	fclose(fp);
}

void putScore(char *file, char *name, int count){
	
	FILE *fp;
	char buffer[100]={0x00}, Date[100], Time[100];
	int i;

	if(file == NULL || name == NULL) return;	

	strcat(buffer, _SCORE_FILE);
	//strcat(buffer, "./files/");
	//strcat(buffer, file);
	//buffer[19]=0x00;

	//컬럼 타이틀 생성
	fp = fopen(buffer, "r");
	if(fp == NULL){
		fp = fopen(buffer, "w");
		fprintf(fp,"%20s %10s %10s\n","data/time", "name", "score");
		fclose(fp);
	}

	
	//점수 기록
	fp = fopen(buffer, "a");
	_strdate(Date);
	_strtime(Time);
	fprintf(fp,"%10s : %7s %10s %10d\n",Date,Time, name, count);
	fclose(fp);
}