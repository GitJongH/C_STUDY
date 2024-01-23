#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>

void drawingTree(int, int, int ); 

int main()
{
	int high, width, space;
	int i;
	
	printf("트리의 높이, 시작 행의 별 수, 시작 행의 공백 수 : ");
	scanf("%d%d%d", &high, &width, &space);

	drawingTree(high, width, space);

	drawingTree(1,5,18);

	return 0;
}

void drawingTree(int high, int width, int space)// high : 트리높이, width : 트리의 시작 행의 별 수
{												// space : 트리의 시작 행의 공백의 수
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

		for(h=0; h<4; h++){					// 트리 전체 높이
			tree = width;
			for(i=0; i<high; i++){			// 트리 한 개 높이
				for(j=0; j<space-i; j++){	// 빈칸
					printf(" ");
				}
				for(k=0; k<tree; k++){		// 트리
					printf("?");
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0xF0+(color));
					color = rand()%16;
				}
				tree+=2;
				printf("\n");
			}
			width+=6;						// 다음 트리 시작 별 수 +6
			space-=3;						// 다음 트리 시작 빈칸 -3
		}
	}
}