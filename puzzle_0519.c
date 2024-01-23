#include<stdio.h>
#include<conio.h> 	// getch & kbhit 함수
#include<time.h>	// srand 함수
#include<Windows.h>	// rand 함수?

void getkey(int *key){
    *key = getch();
    if(*key == 224) *key = getch();
}

int main(){

	int key;
	int pz[9], index, targetIndex;
	int i, k , temp, score = 0;
	srand(time(NULL));

	// pz 초기화
	for(i=0; i<9; i++){
		pz[i] = rand() % 9 + 1;
		for(k=0; k<i; k++){
			if(pz[i] == pz[k]){
				i--;
				break;
			}
		}
	}

	// pz 출력
	for(i=0; i<9; i++){
		if(i>0 && i%3 ==0)	printf("\n");
		if(pz[i] == 9)		printf("%2c", '*');
		else				printf("%2d", pz[i]);
	}

	// 별 위치 확인
	for(i=0; i<9; i++){
		if(pz[i] == 9){
			index = i;
			break;
		}
	}

	//game 징행
	while(1){
		//키입력 확인
		if(kbhit()){
			//키 입력
			getkey(&key);
			//키 값에 따라 targetIndex 결정
			targetIndex = index;
			switch(key){
			case 72: //up
				if(index>2) targetIndex -= 3;
				break;
			case 80: //down
				if(index<6) targetIndex += 3;
				break;
			case 75: //left
				if(index%3 != 0) targetIndex -= 1;
				break;
			case 77: //right
				if(index%3 != 2) targetIndex += 1;
				break;
			default:
				break;
			}

			if(index != targetIndex){
				//pz 값 교환
				temp = pz[index];
				pz[index] = pz[targetIndex];
				pz[targetIndex] = temp;

				//index 값 수정
				index = targetIndex;

				//pz 출력
				system("cls");
				for(i=0; i<9; i++){
					if(i>0 && i%3 ==0)	printf("\n");
					if(pz[i] == 9)		printf("%2c", '*');
					else				printf("%2d", pz[i]);
				}
				// 완성?
				for(i=0; i<9; i++){
					if(pz[i] != (i+1)){
						break;
					}
				}
				if(i==9){
					printf("\n\n=== Game Over ===\n\n");
					break;
				}
			}
		}
	}
    
	return 0;
}