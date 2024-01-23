#include<stdio.h>

int tree(int,int);

int main()
{
	int lines, space;
	int k = 1;
	int star = 0;
	char a;

	while(1){
		
		printf("라인수와 스페이스 수 : ");
		scanf("%d%d", &lines, &space);

		printf("[%d] - 학번: 23018030, 이름: 김종현\n", k++);

		star = tree(lines, space);

		printf("별의 개수는 %d개 입니다.\n", star);

		printf("계속 하시겠습니까? (y/n) : ");
		scanf(" %c", &a);

		if(a=='n') break;
	}

	return 0;
}

int tree(int lines, int space)
{
	int i, j, l;
	int star = 0;

	for(i=0; i<lines; i++){
		for(j=0; j<lines+space-i; j++){
			printf(" ");
		}			
		for(l=0; l<2*i+1; l++){
			printf("*");
			star++;
		}
		printf("\n");
	}

	return star;
}