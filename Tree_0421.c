#include<stdio.h>

int tree(int,int);

int main()
{
	int lines, space;
	int k = 1;
	int star = 0;
	char a;

	while(1){
		
		printf("���μ��� �����̽� �� : ");
		scanf("%d%d", &lines, &space);

		printf("[%d] - �й�: 23018030, �̸�: ������\n", k++);

		star = tree(lines, space);

		printf("���� ������ %d�� �Դϴ�.\n", star);

		printf("��� �Ͻðڽ��ϱ�? (y/n) : ");
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