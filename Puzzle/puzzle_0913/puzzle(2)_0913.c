#include <stdio.h>
#include <Windows.h>

char puzzle[3][3] = {{'*', '1', '2'}, {'3', '4', '5'}, {'6', '7', '8'}};
int count = 0;

int play(char **);

int main()
{
    int count;
	char *puzzlePoint[9] = {"STAR", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT"};
    char input;

    while(1)
    {
        // system("cls");

        count = play(puzzlePoint);

        printf("count : %d\n", count);

        printf("계속 하시겠습니까? (y/n) : ");
        scanf(" %c", &input);

        if(input == 'n' || input == 'N') break;
        else continue;
    }
	return 0;
}

int play(char **pP)
// 23018030 김종현
{
    int i, j;
	int num;
    char temp;

    temp = puzzle[2][2];
    for(i=2; i>0; i--){
        puzzle[2][i] = puzzle[2][i-1];
    }
    puzzle[2][0] = puzzle[1][2];

    for(i=2; i>0; i--){
        puzzle[1][i] = puzzle[1][i-1];
    }
    puzzle[1][0] = puzzle[0][2];

    for(i=2; i>0; i--){
        puzzle[0][i] = puzzle[0][i-1];
    }
    puzzle[0][0] = temp;

    for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			printf("%5c", puzzle[i][j]);
			if(j==2) printf("\n");
		}
    }
	printf("\n");

	if(puzzle[2][2] == '*') num = 0;
	else num = puzzle[2][2] - '0';
	

	printf("%s\n", pP[num]);

    count++;
    
    return count;
}
