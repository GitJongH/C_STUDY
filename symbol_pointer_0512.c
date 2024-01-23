#include<stdio.h>

void tree(int,int,char,int *);

int main(){
	
	int star[5] = {0};
	int lines, space;
	int i = 0, k = 1;
	int total = 0;
	int starNum = 0;
	char a;
    char symbol[5] = {'@','#','$','%','*'};

	while(1){
		
		printf("���μ��� �����̽� �� : ");
		scanf("%d%d", &lines, &space);

		printf("[%d] - �й�: 23018030, �̸�: ������\n", k++);
		
		tree(lines, space, symbol[i], &starNum);

		printf("�ɺ��� ������ %d�� �Դϴ�.\n", starNum);
			
		total += starNum;
		
        i++;

		if(i==5){
			printf("�ɺ��� �� ���� %d���Դϴ�.\n", total);
		}
		
		if(i==5) break;
	}

	return 0;
}

void tree(int lines, int space, char symbol, int *np)
{
	int i, j, k;
	int star = 0;
	
	for(i=0; i<lines; i++){
		for(j=0; j<lines+space-i; j++){
				printf(" ");
		}			
		for(k=0; k<2*i+1; k++){
			printf("%c",symbol);	
			star++;
		}
		printf("\n");
	}	
	*np = star;
}