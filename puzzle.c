/* 
** 1���� �迭�� �̿��� Puzzle ����� 
** (ch1~ch10, ��������, ���ǹ�, ��ȯ��, �Լ�, �迭, ������)
** Author: DY Kim
** Date: 2023. 05. 03
*/

#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
/*
72- up
80-down
75-left
77-right
*/
void getKey(int *key){
	*key=getch();
	if(*key == 224) *key = getch();
}

int main(){
	int key;
	int pz[9], index, targetIndex;
	int i, k, temp, score=0;

	//�ʱ�ȭ pz
	srand(time(NULL));
	for(i=0;i<9;i++){
		pz[i] = rand()%9 + 1;
		for(k=0;k<i;k++){
			if( pz[k] == pz[i] ){
				i--;
				break;
			}
		}
	}

	// ���� ��µ� �ε��� ����
	for(i=0;i<9;i++){
		if(pz[i] == 9){
			index = i;
			break;
		}
	}
	
	//���
	for(i=0;i<9;i++){
		if(i>0 && i%3 == 0) printf("\n");
		if(pz[i] == 9)  printf("%2c ", '*');
		else			printf("%2d ", pz[i]);
	}
	printf("\n\n================\n\nScore: %d\n", score++);

	while(1){
		if(kbhit()){
			getKey(&key);
			targetIndex = index;
			switch(key){
			case 72: //#define T_KEY_UP			72
				if(index > 2){
					targetIndex -= 3;
				}
				break;
			case 80: //#define T_KEY_DOWN		80
				if(index < 6){
					targetIndex += 3;
				}
				break;
			case 77: //#define T_KEY_RIGHT		77
				if(index %3 != 2){
					targetIndex += 1;
				}
				break;
			case 75: //#define T_KEY_LEFT		75
				if(index %3 != 0){
					targetIndex -= 1;
				}
				break;
			default:
				break;
			}

			if( index != targetIndex){
				//��ü
				temp			= pz[index];
				pz[index]		= pz[targetIndex];
				pz[targetIndex]	= temp;
				//���
				system("cls");
				for(i=0;i<9;i++){
					if(i>0 && i%3 == 0) printf("\n");
					if(pz[i] == 9)  printf("%2c ", '*');
					else			printf("%2d ", pz[i]);
				}
				printf("\n\n================\n\nScore: %d\n", score++);
				//index ����
				index = targetIndex;				
			}

			//�ϼ�?
			for(i=0;i<8;i++){
				if(pz[i] != i+1) break;
			}
			if( i == 8){
				printf("\n\n== Game Over!!! ==\n\n");
				break;
			}

		} //if(kbhit())

	} //while(1)

	return 0;
}


int game(){
	int key;
	int pz[9], index, targetIndex;
	int i, k, temp, score=0;

	//�ʱ�ȭ pz
	srand(time(NULL));
	for(i=0;i<9;i++){
		pz[i] = rand()%9 + 1;
		for(k=0;k<i;k++){
			if( pz[k] == pz[i] ){
				i--;
				break;
			}
		}
	}

	// ���� ��µ� �ε��� ����
	for(i=0;i<9;i++){
		if(pz[i] == 9){
			index = i;
			break;
		}
	}
	
	//���
	for(i=0;i<9;i++){
		if(i>0 && i%3 == 0) printf("\n");
		if(pz[i] == 9)  printf("%2c ", '*');
		else			printf("%2d ", pz[i]);
	}
	printf("\n\n================\n\nScore: %d\n", score++);

	while(1){
		if(kbhit()){
			getKey(&key);
			targetIndex = index;
			switch(key){
			case 72: //#define T_KEY_UP			72
				if(index > 2){
					targetIndex -= 3;
				}
				break;
			case 80: //#define T_KEY_DOWN		80
				if(index < 6){
					targetIndex += 3;
				}
				break;
			case 77: //#define T_KEY_RIGHT		77
				if(index %3 != 2){
					targetIndex += 1;
				}
				break;
			case 75: //#define T_KEY_LEFT		75
				if(index %3 != 0){
					targetIndex -= 1;
				}
				break;
			default:
				break;
			}

			if( index != targetIndex){
				//��ü
				temp			= pz[index];
				pz[index]		= pz[targetIndex];
				pz[targetIndex]	= temp;

				//���
				system("cls");
				for(i=0;i<9;i++){
					if(i>0 && i%3 == 0) printf("\n");
					if(pz[i] == 9)  printf("%2c ", '*');
					else			printf("%2d ", pz[i]);
				}
				printf("\n\n================\n\nScore: %d\n", score++);

				//index ����
				index = targetIndex;

				//�ϼ�?
				for(i=0;i<8;i++){
					if(pz[i] != i+1) break;
				}
				if( i == 8){
					printf("\n\n== Game Over!!! ==\n\n");
					break;
				}
			}

		}
	}

	return 0;
}