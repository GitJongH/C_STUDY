#include<stdio.h>

int tree(int,int,char);

int main(){
	
	int star[5] = {0};
	int lines, space;
	int i = 0, k = 1;
	int total = 0;
	char a;
    char symbol[5] = {'@','#','$','%','*'};

	while(1){
		
		printf("라인수와 스페이스 수 : ");
		scanf("%d%d", &lines, &space);

		printf("[%d] - 학번: 23018030, 이름: 김종현\n", k++);
		
		star[i] = tree(lines, space, symbol[i]);

		printf("심볼의 개수는 %d개 입니다.\n", star[i]);
			
		total += star[i];
		
        i++;

		if(i==5){
			printf("심볼의 총 수는 %d개입니다.\n", total);
			break;
		}
	}

	return 0;
}

int tree(int lines, int space, char symbol)
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
    
	return star;
}