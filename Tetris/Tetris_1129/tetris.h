#ifndef _TETRIS
#define _TETRIS

// ���̺귯��
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// �������
#define T_PATTERN_NUM			4
#define T_HIGH					25
#define T_WIDTH					15
#define T_DELAT_TIME			1000

// �� ��
#define T_VALUE_SPACE			0x0F
#define T_VALUE_WALL			0xF0
#define T_VALUE_BLOCK_1			0
#define T_VALUE_BLOCK_2			1
#define T_VALUE_BLOCK_3			2
#define T_VALUE_BLOCK_4			3
#define T_VALUE_BLOCK_5			4
#define T_VALUE_BLOCK			9
#define T_VALUE_BLOCK_FINISH	10

// Ű ��
#define T_KEY_UP				72
#define T_KEY_DOWN				80
#define T_KEY_LEFT				75
#define T_KEY_RIGHT				77
#define T_SPACE					32
#define PAUSE				    'P'

#define T_TIMEOUT				1
#define T_NOT_TIMEOUT			0

#define T_CAN_MOVE				1
#define T_CANNOT_MOVE			0

#define T_END_LINE				0
#define T_NOTEND_LINE			1

#define T_FULL					1
#define T_NOT_FULL				0

#define T_GAME_FINISH			1
#define T_GAME_NOt_FINISH		0

// ����ü
typedef struct _T_POINT {
	int row;						// ��
	int column;						// ��
} T_POINT;

typedef struct _BLOCK {
	int type;						// �� ���� (0, 1, 2, 3, 4)
	int rotation;					// �� ���� (0, 1, 2, 3)
	T_POINT point;
} BLOCK;

// �Լ�
void	gotoxy(int row, int column); // Ŀ�� �̵� �Լ�
void	delay(int sec);				 // ������ �Լ�
int		getkey();					 // Ű �Է�
int		checkTime(int ms);			 // �ð� �Լ�
void	init();						 // �ʱ�ȭ & �� ����
void	display();					 // �� & �� ���
void	selectBlock();				 // ���ο� �� ����(�������� ��)
void	addBlockToDisplay();		 // ���õ� ���� display�� �߰�

BLOCK	getTempBlock(int key);		 // �Է� ���� Ű�� ������� �� �̵���ǥ �Ǵ� ȸ�������� ����
int		checkBlockMove(BLOCK b);	 // getBlockPosition
void	changeBlock(BLOCK b);		 // ���� ���� �����Ѵ�

int		checkEndOfLine();			 // ���� �� �̻� �Ʒ��� ������ �� ������ üũ
void	copyDisplayToBase();		 // ���� �� �̻� �Ʒ��� �̵� ���ϸ�, box_base�� �� �߰�

void	copyBaseToDisplay();
int		checkDeleteLine(int line);
int		deleteLine();
int		checkGameFinish();

#endif