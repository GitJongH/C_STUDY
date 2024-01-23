#include <stdio.h>
#include <string.h>

// 23018030 ¡¾??¨ú??
void capitalString(char *, char *, int);
void compareWord(char *, char *, int);

int main()
{
	char A[1000] = "The international community in the 21st century needs people who exert their capacity fully at a world level beyond the narrow boundary of nation and race. In other words, the global leader of the 21st century is not the type of person who merely specializes in a specific field but the one who commands synthetic knowledge of many fields of learning. ";
	char B[1000];
 // B : So USW offers students educational environments where they can learn not merely their major fields but also a variety of fields such as English and other foreign languages, etiology, humanities, economics, science and technology. USW VISION 2020 aims to foster leaders pioneering the future of the whole world and human race.
	char C[2000] = {0};
	char D[2000];
	int lenA, lenB;

    printf("A : %s\n\n", A);

	gets(B);

	printf("\n");
    printf("B : %s\n", B);
	
	lenA = strlen(A);
	lenB = strlen(B);

	strcat(C, A);
	strcat(C, " ");
	strcat(C, B);

	printf("\n");
	printf("C : %s\n", C);

	capitalString(C, D, lenA+lenB);

	printf("\n");
	printf("D : %s\n", D);
	

	return  0;
}

void capitalString(char *cp, char *dp, int len)
{
	int i;

    for(i = 0; i < len; i++){
	    if(*(cp + i) >= 96 && *(cp + i) <= 122){
            *(cp + i) = *(cp + i) - 32;
        }
    }

	strcpy(dp, cp);
}
