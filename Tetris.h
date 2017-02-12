#pragma once
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4
#define WALLSIZE 4
#define GAME_OVER 0
#define PLAYING 1
#define PAUSE 2
#define READY 3

typedef struct _tetris{
	char** board; //�������
	char** boPlusbl; //�浹üũ, ��¿� ����
	int x; //�����
	int y; //������
	int gameState; // ���� ���� ���� 0 GAMEOVER, 1 PLAYING, 2 PAUSE, 3 READY
	int blockState; //�� ȸ�� ī��Ʈ
	int whichBlock; //�� ���
	int NextBlock; //������////////////////////////////////////////////////////////////////
	int score; //���� ���� ����
}Tetris;

//�Լ��� :initGame
//precondition : None
//�Լ����� : ���ӿ� ���� ������ �ʱ���·� �����Ѵ�.
//te->board, te->boPlusbl 2�����迭 �����Ҵ�
//te->socre = 0 , te->blockState = 0, whichBlock = ���� ����
void initGame(Tetris* te);

//�Լ��� : printBoard
//Precondition : bo�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : ����ȭ���� ���
//Postcondition : None
//return : None
void printBoard(int** bo);

//�Լ��� : pasteBoard
//Precondition : bPb�� bo�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : ���� �ٿ��� ���带 ���� ������� �ǵ��� ���´�.
//Postcondition : None
//return : None
void pasteBoard(int**bPb, int** bo,int x,int y);

//�Լ��� : pasteBlock
//Precondition : bo�� bl�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : ���� ���Ǵ� ���� ��濡 �ٿ��ִ´�.����+��
//Postcondition : bo(��) �� bl(��)�� �ٿ�����.
//return : None
void pasteBlock(int** bo, int(*bl)[4], int x, int y);

//�Լ��� : crushCheck
//Precondition : bpb , x, y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : bpb�� ���� �ٿ��� �κ��� üũ�Ͽ� �浹�� �Ͼ������ üũ�Ѵ�.(���� 2������ Ȯ��)
//Postcondition : None
//return : 1 (crash) , 0 (not crash)
int crashCheck(int** bpb, int x, int y);

//�Լ��� : lineCheck
//Precondition : bpb , y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : y�� ����Ű�� �� ������ üũ�� �Ѵ�.
//Postcondition : None
//return : 1 (full line) , 0 (not full)
int lineCheck(int** bpb, int y);

//�Լ��� : lineErase
//Precondition : bpb , y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : y�� ����Ű�� ���� �� �Ʒ��ٺ��� ������ üũ�Ͽ� �����Ѵ�.
//Postcondition : bpb�� ������ ������ �����̴�.(������ ������ �����ÿ� bpb�� �״��)
//return : 0 ���ٵ� ����������, 1 �������� 2�������� 3�������� 4��������
int lineErase(int** bpb, int y);

//�Լ��� : gameOver
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�.
//���� : ������ �ʱ�ȭ��Ű�� �����Ҵ��� �޸𸮸� ��� ������Ų��. Score�� �����Ѵ�.
//Postcondition : board �� boPlusbl�� �޸� ����
//return : None
void gameOver(Tetris* Te);

//�Լ��� : createBlock 
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�. 
//���� : �������� ���� �����Ѵ�. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 ���� �ʱ�ȭ�ȴ�. 
//return : None 
void createBlock(Tetris* Te);


