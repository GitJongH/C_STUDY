#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

int puzzle[3][3] = {0};

void init();
int getkey();
void puzzleDisplay(int, int*);
void play();

int main()
{
    void (*func)(); // 함수 포인터
    int key;
    int *count = 0;

    srand(time(NULL));
	/*
    CONSOLE_CURSOR_INFO Curinfo = {0, };

    Curinfo.dwSize = 1;
    Curinfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
	*/
    
    func = init;

    while(1){
        // system("cls");
        key = getkey();
        //if(key == 0) break;
        func();
        puzzleDisplay(key, &count);
    }

    return 0;
}

void init()
{
    int i, j;
    int *pz;
    pz = (int *)puzzle;

	for(i=0;i<9;i++){
        pz[i] = rand() % 9;
        for(j=0;j<i;j++){
            if(pz[i] == pz[j]){
				i--;
				break;
			}
        }
    }
}

int getkey()
{
	int key;

    key = getch();
    if(key == 224) key = getch();

	return key;
}

void puzzleDisplay(int key, int *count)
{
    int i, j;
    char key_char;

    for(i=0; i<3; i++){
		for(j=0; j<3; j++){
            if(puzzle[i][j] == 0) printf("%5c", '*');
			else printf("%5d", puzzle[i][j]);
		}
        printf("\n");
    }

    if(key == 72) printf("input : UP\n");
    if(key == 75) printf("input : LEFT\n");
    if(key == 77) printf("input : RIGHT\n");
    if(key == 80) printf("input : DOWN\n");

    printf("count : %d\n", *count);

    *count = *count + 1;
}