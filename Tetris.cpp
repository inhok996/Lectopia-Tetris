#include "Tetris.h"
#include <stdio.h>

int block[][4][4][4]=
{ //�� 4���� �迭 ù�����迭�ε���: ���� ���� �ι�°�迭�ε��� :���� ȸ��
	{
		{
			{0,0,0,0}, 
			{1,0,0,0}, 
			{1,1,1,0}, 
			{0,0,0,0}, 
		},
		{
			{0,0,1,0}, 
			{0,0,1,0}, 
			{0,1,1,0}, 
			{0,0,0,0}, 
			},
			{
				{1,1,1,0}, 
				{0,0,1,0}, 
				{0,0,0,0}, 
				{0,0,0,0}, 
			},
			{
				{1,1,0,0}, 
				{1,0,0,0}, 
				{1,0,0,0}, 
				{0,0,0,0}, 
				}
	}
};



//�Լ��� : printBoard
//Precondition : bo�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : ����ȭ���� ���
//Postcondition : None
//return : None
void printBoard(int** bo)
{
	for(int i = 0 ; i < BOARD_HEIGHT + 1; i++){
		for(int j = WALLSIZE - 1 ; j < BOARD_WIDTH + WALLSIZE + 1; j++){
			if(bo[i][j] == 1) printf("�� ");
			else if(bo[i][j] ==2) printf("�� ");
			else printf("�� ");
		}
		printf("\n");
	}
}

//Precondition : bo�� bl�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : ���� ���Ǵ� ���� ��濡 �ٿ��ִ´�.����+��
//Postcondition : bo(��) �� bl(��)�� �ٿ�����.
//return : None
void pasteBlock(int** bo, int(*bl)[4], int x, int y)
{
	for(int i = 0 ; i < BLOCK_HEIGHT; i++){
		for(int j = 0 ; j < BLOCK_WIDTH ; j++){

	bo[i+y][j+x] += bl[i][j];
		}
	}
}

//Precondition : bPb�� bo�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : ���� �ٿ��� ���带 ���� ������� �ǵ��� ���´�.
//Postcondition : None
//return : None
void pasteBoard(int**bPb, int** bo,int x,int y)
{
	for(int i = 0 ; i < BLOCK_HEIGHT; i++){
		for(int j = 0 ; j < BLOCK_WIDTH ; j++){
			bPb[i+y][j+x] = bo[i+y][j+x];
		}
	}
}


//�Լ��� :initGame
//precondition : None
//�Լ����� : ���ӿ� ���� ������ �ʱ���·� �����Ѵ�.
//te->board, te->boPlusbl 2�����迭 �����Ҵ�
//te->socre = 0 , te->blockState = 0, whichBlock = ���� ����
void initGame(Tetris* te){}


//�Լ��� : crushCheck
//Precondition : bpb , x, y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : bpb�� ���� �ٿ��� �κ��� üũ�Ͽ� �浹�� �Ͼ������ üũ�Ѵ�.(���� 2������ Ȯ��)
//Postcondition : None
//return : 1 (crash) , 0 (not crash)
int crashCheck(int** bpb, int x, int y){return 1;}

//�Լ��� : lineCheck
//Precondition : bpb , y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : y�� ����Ű�� �� ������ üũ�� �Ѵ�.
//Postcondition : None
//return : 1 (full line) , 0 (not full)
int lineCheck(int** bpb, int y){return 1;}

//�Լ��� : lineErase
//Precondition : bpb , y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : y�� ����Ű�� ���� �� �Ʒ��ٺ��� ������ üũ�Ͽ� �����Ѵ�.
//Postcondition : bpb�� ������ ������ �����̴�.(������ ������ �����ÿ� bpb�� �״��)
//return : 0 ���ٵ� ����������, 1 �������� 2�������� 3�������� 4��������
int lineErase(int** bpb, int y){return 1;}

//�Լ��� : gameOver
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�.
//���� : ������ �ʱ�ȭ��Ű�� �����Ҵ��� �޸𸮸� ��� ������Ų��. Score�� �����Ѵ�.
//Postcondition : board �� boPlusbl�� �޸� ����
//return : None
void gameOver(Tetris* Te){}

//�Լ��� : createBlock 
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�. 
//���� : �������� ���� �����Ѵ�. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 ���� �ʱ�ȭ�ȴ�. 
//return : None 
void createBlock(Tetris* Te){}

