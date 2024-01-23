#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

typedef struct _myIndex{
	int row;						// ��
	int column;		 				// ��
} myIndex;

typedef struct _myPz{
	void *pPz;
	int pzSize;		 				// ���� ũ�� (if 3x3 -> 3)
	myIndex pzIndex; 				// star�� ��/��
} myPz;

void init(myPz *);					// ���� �Ҵ� �Լ�
int getkey();						// Ű �Է� �Լ�
void puzzleDisplay(myPz, int, int); // Puzzle ��� �Լ�
void exchangePz(myPz *,myIndex);	// �Է�Ű�� ���� ���� ��ȭ �Լ�
myIndex getCoordinate(myPz, int);	// Key ���� ���� * ��ġ ���
int checkPz(myPz *, int);			// ���� �ϼ��� Ȯ�� �Լ�

int main()
{
    int size;
    int key = 0, count = 0;
	int check;
    myPz pz;
    myIndex Index;

    srand(time(NULL));

	printf("���� ũ�⸦ �Է��ϼ���(3, 4, 5): ");
	scanf("%d", &size);

    pz.pPz = (int *)malloc(sizeof(int)*size*size);
    if(pz.pPz == NULL){
        printf("�޸𸮰� �����մϴ�.\n");
        return 1;
    }

    pz.pzSize = size;

    init(&pz);
    puzzleDisplay(pz, key, count);

    while(1){
        key = getkey();
		count++;
		system("cls");
		
		Index = getCoordinate(pz, key);
		
		exchangePz(&pz, Index);

        puzzleDisplay(pz, key, count);

		printf("Coordinate: <%d,%d> -> <%d,%d>\n", pz.pzIndex.row, pz.pzIndex.column, Index.row, Index.column);

		pz.pzIndex.row = Index.row;
		pz.pzIndex.column = Index.column;

		check = checkPz(&pz, size);
		
		if(check == (size*size)){
			printf("You Win!!!\n\n");
			printf("Restart . . . put 'p'");
			key = getkey();
			if(key == 80 || key == 112){
				system("cls");
				printf("���� ũ�⸦ �Է��ϼ���(3, 4, 5): ");
				scanf("%d", &size);
				pz.pPz = (int *)malloc(sizeof(int)*size*size);
				pz.pzSize = size;
				init(&pz);
				puzzleDisplay(pz, key, count);
				check = 0;
				count = 0;
				key = 0;
				continue;
			}
			else break;
		}
	}

    free(pz.pPz);
    pz.pPz = NULL;

    return 0;
}

void init(myPz *ppz) // ���� �Ҵ� �Լ�
{ 
    int i, j;
    int *pz;
    pz = (int *)(ppz->pPz);

	for(i=0;i<ppz->pzSize*ppz->pzSize;i++){
        pz[i] = rand() % (ppz->pzSize*ppz->pzSize);
        for(j=0;j<i;j++){
            if(pz[i] == pz[j]){
				i--;
				break;
			}
        }

		if(pz[i] == 0){
			ppz->pzIndex.row = i/(ppz->pzSize);
			ppz->pzIndex.column = i%(ppz->pzSize);
		}
    }
}

int getkey() // Ű �Է� �Լ�
{
	int key;

    key = getch();
    if(key == 224) key = getch();

	return key;
}

void puzzleDisplay(myPz pz, int key, int count) // Puzzle ��� �Լ�
{
    int i, j;
    int size;

	size = pz.pzSize;

	printf("Puzzle Game: by ������ <23018030>\n\n");

	printf("��");
	for(i=0; i<size-1; i++){
		switch(size){
		case 3:
		default:
			printf("��������");
			size=3;
			break;
		case 4:
			printf("��������");
			break;
		case 5:
			printf("��������");
			break;
		}
	}
	printf("��������\n");

    for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			switch(size){
			case 3:
			default:
				printf("��");
				if(((int (*)[3])pz.pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[3])pz.pPz)[i][j]);
				if(j==2){
					printf("��\n");
					if(i==2){
						printf("��������������������������");
					}
					else printf("��������������������������");
				}
				break;
			case 4:
				printf("��");
				if(((int (*)[4])pz.pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[4])pz.pPz)[i][j]);
				if(j==3){
					printf("��\n");
					if(i==3) printf("����������������������������������");
					else printf("����������������������������������");
				}
				break;
			case 5:
				printf("��");
				if(((int (*)[5])pz.pPz)[i][j] == 0) printf("%3c", '*');
				else printf("%3d", ((int (*)[5])pz.pPz)[i][j]);
				if(j==4){
					printf("��\n");
					if(i==4) printf("������������������������������������������");
					else printf("������������������������������������������");
				}
				break;
			}
		}
		printf("\n");
    }
	printf("\n");

	switch(key){
	case 72: //up
		printf("key: UP\n");
		break;
	case 80: //down
		printf("key: DOWN\n");
		break;
	case 75: //left
		printf("key: LEFT\n");
		break;
	case 77: //right
		printf("key: RIGHT\n");
		break;
	default:
		break;
	}

	printf("Count: %d\n", count);
}

void exchangePz(myPz *ppz,myIndex index) // �Է�Ű�� ���� ���� ��ȭ �Լ�
{
	int temp;
	int star, target;

	star = (ppz->pzSize)*(ppz->pzIndex.row)+(ppz->pzIndex.column);
	target = (ppz->pzSize)*(index.row)+(index.column);

	temp = ((int *)ppz->pPz)[star];
	((int *)ppz->pPz)[star] = ((int *)ppz->pPz)[target];
	((int *)ppz->pPz)[target] = temp;
}

myIndex getCoordinate(myPz pz, int key) // Key ���� ���� * ��ġ ���
{
	myIndex targetIndex;
	targetIndex = pz.pzIndex;

    switch(key){
	case 72: //up
		if(pz.pzIndex.row > 0) targetIndex.row--;
		break;
	case 80: //down
		if(pz.pzIndex.row < (pz.pzSize-1)) targetIndex.row++;
		break;
	case 75: //left
		if(pz.pzIndex.column > 0) targetIndex.column--;
		break;
	case 77: //right
		if(pz.pzIndex.column < (pz.pzSize-1)) targetIndex.column++;
		break;
	default:
		break;
	}

	return targetIndex;
}

int checkPz(myPz *ppz, int size) // ���� �ϼ��� Ȯ�� �Լ�
{
	int i, check = 0;
	int *pz;
	pz = (int *)(ppz->pPz);

	for(i=0; i<size*size; i++){
		switch(size){
			case 3:
			default:
				if(pz[i] != i+1){
					check = 0;
					break;
				}
				else check++;
				if(check == 8){
					printf("\n\n== Game Over!!! ==\n\n");
					check++;
				}
				break;
			case 4:
				if(pz[i] != i+1){
					check = 0;
					break;
				}
				else check++;
				if(check == 15){
					printf("\n\n== Game Over!!! ==\n\n");
					check++;
				}
				break;
			case 5:
				if(pz[i] != i+1){
					check = 0;
					break;
				}
				else check++;
				if(check == 24){
					printf("\n\n== Game Over!!! ==\n\n");
					check++;
				}
				break;
		}
		if(check == (size*size)) break;
	}

	return check;
}