#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>


/*
** ch 18, 파일 연습
**
**
*/

struct _myIndex{
	int row;
	int column;
};

typedef struct _myIndex myIndex;

typedef struct _myPz{
	void *pPz;
	int  pzSize;
	myIndex	pzIndex;
}myPz;

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
void puzzleDisplay(myPz pz, int key, int count){
	int i,k;	
	int size, value;

	size = pz.pzSize;


	if(size!=4 && size !=5) size=3;


	//system("cls");
	printf("┌");
	for(i=0;i<size-1;i++){
		printf("──┬");
	}
	printf("──┐\n");
	
	for( i=0;i<size;i++){	
		for(k=0;k<size;k++){
			printf("│");
			switch(size){
			case 3:
			default:
				value = ((int(*)[3])(pz.pPz))[i][k];
				size=3;
				break;
			case 4:
				value = ((int(*)[4])(pz.pPz))[i][k];
				break;
			case 5:
				value = ((int(*)[5])(pz.pPz))[i][k];
				break;
			}
			if(value != 0) printf("%2d", value);
			else printf("%2c", '*');
		}
		printf("│\n");
		if(i<size-1){
			printf("├");
			for(k=0;k<size-1;k++){
				printf("──┼");
			}
			printf("──┤\n");
		}
		else{
			printf("└");
			for(k=0;k<size-1;k++){
				printf("──┴");
			}
			printf("──┘\n");
		}
	}
	switch(key){
	case 72:
		printf("UP\n");
		break;
	case 80:
		printf("DOWN\n");
		break;
	case 75:
		printf("LEFT\n");
		break;
	case 77:
		printf("RIGHT\n");
		break;
	default:
		printf("%d\n",key);
		break;
	}

	printf("count: %d\n", count);
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
	case 72:
		if(pz.pzIndex.row > 0) targetIndex.row--;
		//printf("UP\n");
		break;
	case 80:
		if(pz.pzIndex.row < (pz.pzSize-1)) targetIndex.row++;
		//printf("DOWN\n");
		break;
	case 75:
		if(pz.pzIndex.column > 0) targetIndex.column--;
		//printf("LEFT\n");
		break;
	case 77:
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

void setConfig(int *size, int *mode, char * scoreFileName){
	FILE *fp;
	char buffer[100];
	int len;

	*size = 3;
	*mode = 1; //game mode

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

	strcat(buffer, "./files/");
	strcat(buffer, file);
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

int main(){
	myPz	pz;
	int		size, mode, i;
	int		key=0, count=0;
	char	scorefile[100], name[100];
	myIndex index;
	
	setConfig(&size, &mode, scorefile);
/*
	for(i=0;i<5;i++){
		count = rand()%100;
		putScore(scorefile, "DY", count);
	}
*/

	printf("\n\n\n\n\n\t\tID: ");
	scanf("%s", name);
	//getch();
	system("cls");

	srand(time(NULL));
	pz.pPz = (int *)malloc(sizeof(int)*size*size);
	pz.pzSize=size;
	if(pz.pPz == NULL) return 1;

	if(mode == 0){
		for(i=0;i< (size*size)-2; i++){
			((int*)pz.pPz)[i]=i+1;
		}
		((int*)pz.pPz)[i]=0;
		((int*)pz.pPz)[i+1]=size*size-1;
		pz.pzIndex.row = i/size;
		pz.pzIndex.column = i%size;
	}
	else{
		init(&pz);		
	}

	puzzleDisplay(pz, key, count);

	while(1){
		//키 입력
		key = getKey();
		
		//인덱스 계산
		index = getCoordinate(pz, key);
		system("cls");
		//puzzleDisplay(pz, key, count);
		//printf("(%d,%d)->(%d,%d)\n", pz.pzIndex.row, pz.pzIndex.column, index.row, index.column);
		
		//퍼즌 바꾼 후
		if( (pz.pzIndex.column != index.column) || 
			(pz.pzIndex.row != index.row)){
			exchangePz(&pz, index);
			count++;
			puzzleDisplay(pz, key, count);

			if(!checkPz(pz)) {
				printf("======= GAME OVER ========\n");
				putScore(scorefile, name, count);
				break;
			}
		}
	}

	free(pz.pPz);
	pz.pPz = NULL;	

	getch();
	
	return 0;	
}