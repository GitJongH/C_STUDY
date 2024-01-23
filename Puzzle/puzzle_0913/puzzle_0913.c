#include <stdio.h>
#include <Windows.h>

char puzzle[9] = {'*', '1', '2', '3', '4', '5', '6', '7', '8'};
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
    char temp;

    temp = puzzle[8];
	puzzle[8] = puzzle[7];
	puzzle[7] = puzzle[6];
	puzzle[6] = puzzle[5];
	puzzle[5] = puzzle[4];
	puzzle[4] = puzzle[3];
	puzzle[3] = puzzle[2];
	puzzle[2] = puzzle[1];
	puzzle[1] = puzzle[0];
	puzzle[0] = temp;
    
    for(i=0; i<9; i++){
        printf("%5c", puzzle[i]);
        if(i == 2 || i ==5) printf("\n");
    }
	printf("\n");
    
    if(puzzle[8] == '1') printf("%s\n", pP[1]);
    if(puzzle[8] == '2') printf("%s\n", pP[2]);
    if(puzzle[8] == '3') printf("%s\n", pP[3]);
    if(puzzle[8] == '4') printf("%s\n", pP[4]);
    if(puzzle[8] == '5') printf("%s\n", pP[5]);
    if(puzzle[8] == '6') printf("%s\n", pP[6]);
    if(puzzle[8] == '7') printf("%s\n", pP[7]);       
    if(puzzle[8] == '8') printf("%s\n", pP[8]);          
    if(puzzle[8] == '*') printf("%s\n", pP[0]);

    count++;

    return count;
}
