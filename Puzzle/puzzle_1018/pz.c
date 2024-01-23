#include "pz.h"

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

	if(mode == _MODE_TEST){
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
		//Å° ÀÔ·Â
		key = getKey();
		
		//ÀÎµ¦½º °è»ê
		index = getCoordinate(pz, key);
		system("cls");
		//puzzleDisplay(pz, key, count);
		//printf("(%d,%d)->(%d,%d)\n", pz.pzIndex.row, pz.pzIndex.column, index.row, index.column);
		
		//ÆÛÁð ¹Ù²Û ÈÄ
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