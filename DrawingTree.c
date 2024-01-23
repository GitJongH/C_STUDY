#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>

void drawingTree(int, int, int ); 

int main()
{
	int high, width, space;
	int i;
	
	printf("Ʈ���� ����, ���� ���� �� ��, ���� ���� ���� �� : ");
	scanf("%d%d%d", &high, &width, &space);

	drawingTree(high, width, space);

	drawingTree(1,5,18);

	return 0;
}

void drawingTree(int high, int width, int space)// high : Ʈ������, width : Ʈ���� ���� ���� �� ��
{												// space : Ʈ���� ���� ���� ������ ��
	int h, i, j, k;
	int color;
	int tree = 0;
	srand(time(NULL));

	if(high == 1){
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0xF0+(0));
		while(1){
			for(i=0; i<4; i++){					// high == 1 & width == 5 & space == 18
				for(j=0; j<space; j++){
					printf(" ");
				}
				for(h=0; h<width; h++){
					printf("?");
				}
				printf("\n");
			}
			if(i==4) break;
		}

		high+=3;							// high == 4
		width+=6;							// width == 11
		space-=3;							// space == 15

		for(i=0; i<high; i++){
			for(h=0; h<2; h++){
				for(j=0; j<space; j++){
					printf(" ");
				}
				for(k=0; k<width; k++){
					printf("?");
				}
				printf("\n");
			}
			width-=2;
			space++;		
		}
	}

	else{
		system("color f0");
		color = rand()%16;

		for(h=0; h<4; h++){					// Ʈ�� ��ü ����
			tree = width;
			for(i=0; i<high; i++){			// Ʈ�� �� �� ����
				for(j=0; j<space-i; j++){	// ��ĭ
					printf(" ");
				}
				for(k=0; k<tree; k++){		// Ʈ��
					printf("?");
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0xF0+(color));
					color = rand()%16;
				}
				tree+=2;
				printf("\n");
			}
			width+=6;						// ���� Ʈ�� ���� �� �� +6
			space-=3;						// ���� Ʈ�� ���� ��ĭ -3
		}
	}
}