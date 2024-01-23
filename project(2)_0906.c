#include <stdio.h>
#include <string.h>

// 23018030 ±èÁ¾Çö
void compareWord(char *, char *, int);

int main()
{
	char A[1000] = "The international community in the 21st century needs people who exert their capacity fully at a world level beyond the narrow boundary of nation and race. In other words, the global leader of the 21st century is not the type of person who merely specializes in a specific field but the one who commands synthetic knowledge of many fields of learning. ";
	char B[1000];
 // B : So USW offers students educational environments where they can learn not merely their major fields but also a variety of fields such as English and other foreign languages, etiology, humanities, economics, science and technology. USW VISION 2020 aims to foster leaders pioneering the future of the whole world and human race.
	int lenA, lenB;
	int i = 4;

    printf("A : %s\n\n", A);

	gets(B);

	printf("\n");
    printf("B : %s\n", B);
	
	compareWord(A, B, i);

	return  0;
}

void compareWord(char *ap, char *bp, int num)
{
	int i = 0, j = 0, k = 0;
	int res;
	char *app;
	char *bpp;
	char *blank = " ";

	while(1){
		if(*(ap + k) == *blank){
			i++;
			if(i == num){
				strcpy(app, ap);
			}
		}
		if(*(bp + k) == *blank){
			j++;
			if(j == num){
				strcpy(bpp, bp);
			}
		}

		k++;
		if(i == num && j == num) break;
	}

	res = strcmp(app, bpp);

	if(res == 1) printf("%s\n", app);
	if(res == -1) printf("%s\n", bpp);
}
