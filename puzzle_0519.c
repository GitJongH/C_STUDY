#include<stdio.h>
#include<conio.h> 	// getch & kbhit �Լ�
#include<time.h>	// srand �Լ�
#include<Windows.h>	// rand �Լ�?

void getkey(int *key){
    *key = getch();
    if(*key == 224) *key = getch();
}

int main(){

	int key;
	int pz[9], index, targetIndex;
	int i, k , temp, score = 0;
	srand(time(NULL));

	// pz �ʱ�ȭ
	for(i=0; i<9; i++){
		pz[i] = rand() % 9 + 1;
		for(k=0; k<i; k++){
			if(pz[i] == pz[k]){
				i--;
				break;
			}
		}
	}

	// pz ���
	for(i=0; i<9; i++){
		if(i>0 && i%3 ==0)	printf("\n");
		if(pz[i] == 9)		printf("%2c", '*');
		else				printf("%2d", pz[i]);
	}

	// �� ��ġ Ȯ��
	for(i=0; i<9; i++){
		if(pz[i] == 9){
			index = i;
			break;
		}
	}

	//game ¡��
	while(1){
		//Ű�Է� Ȯ��
		if(kbhit()){
			//Ű �Է�
			getkey(&key);
			//Ű ���� ���� targetIndex ����
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
				//pz �� ��ȯ
				temp = pz[index];
				pz[index] = pz[targetIndex];
				pz[targetIndex] = temp;

				//index �� ����
				index = targetIndex;

				//pz ���
				system("cls");
				for(i=0; i<9; i++){
					if(i>0 && i%3 ==0)	printf("\n");
					if(pz[i] == 9)		printf("%2c", '*');
					else				printf("%2d", pz[i]);
				}
				// �ϼ�?
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