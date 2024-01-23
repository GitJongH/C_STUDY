#include <stdio.h>

int main(){

	int lines;
	int k=1, i, j, l;
	char a;

	
	while(1){
		
		printf("[%d] - 학번: 24018030, 이름: 김종현\n", k++); 
		
		printf("Line : ");
		scanf("%d", &lines);

		for(i=0; i<lines; i++){
			for(j=0; j<lines-i; j++){
					printf(" ");
			}			
			for(l=0; l<i+1; l++){
					printf("*");
			}
			printf("\n");
		}
	
		printf("게속 하시겠습니까? (y/n) : ");
		scanf(" %c", &a);

		if(a=='n')
			break;
	}
		
	return 0;
}
