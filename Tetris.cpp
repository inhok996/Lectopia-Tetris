#include "Tetris.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

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
void pasteBoard(int**bPb, int** bo)
{
	for(int i = 0 ; i < BOARD_HEIGHT + WALLSIZE ; i++){
		for(int j = 0 ; j < BOARD_WIDTH + (WALLSIZE * 2) ; j++){
			bPb[i][j] = bo[i][j];
		}
	}
}


//�Լ��� :initGame
//precondition : None
//�Լ����� : ���ӿ� ���� ������ �ʱ���·� �����Ѵ�.
//te->board, te->boPlusbl 2�����迭 �����Ҵ�
//te->socre = 0 , te->blockState = 0, whichBlock = ���� ����
void initGame(Tetris* te)
{
	int i, j;
	te->x = (BOARD_WIDTH + WALLSIZE * 2) / 2 - 2;
	te->y = 0;
	te->board = (int **)calloc(1, sizeof(int *)*(BOARD_HEIGHT + WALLSIZE));
	assert(te->board != NULL);
	te->boPlusbl = (int **)calloc(1, sizeof(int *)*(BOARD_HEIGHT + WALLSIZE));
	assert(te->boPlusbl != NULL);
	te->gameState = GAME_OVER;
	te->blockState = 0; //ȸ�� 4������� 
	te->whichBlock = 0;// �迭�� ù��° index 7����
	te->score = 0;

	for (i = 0; i < BOARD_HEIGHT + WALLSIZE; i++)
	{
		te->board[i] = (int *)calloc(1, sizeof(int)*(BOARD_WIDTH + (WALLSIZE * 2)));
		te->boPlusbl[i]= (int *)calloc(1, sizeof(int)*(BOARD_WIDTH + (WALLSIZE * 2)));
	}

	for (i = 0; i < BOARD_HEIGHT + WALLSIZE; i++)
	{
		for (j = 0; j < (BOARD_WIDTH + (WALLSIZE * 2)); j++)
		{
			if (j < WALLSIZE || j >= BOARD_WIDTH + WALLSIZE) { te->board[i][j] = te->boPlusbl[i][j] = 1; }
			if (i >= BOARD_HEIGHT)
				te->board[i][j] = te->boPlusbl[i][j] = 1;
		}
	}
}


//�Լ��� : crushCheck
//Precondition : bpb , x, y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : bpb�� ���� �ٿ��� �κ��� üũ�Ͽ� �浹�� �Ͼ������ üũ�Ѵ�.(���� 2������ Ȯ��)
//Postcondition : None
//return : 1 (crash) , 0 (not crash)
int crashCheck(int** bpb, int x, int y)
{
	int i, j;
	for (i = 0; i < BLOCK_HEIGHT; i++)
	{
		for (j = 0; j < BLOCK_HEIGHT; j++)
		{
			if (bpb[y + i][x+ j] == 2)
				return true;
		}
	}
	return false;
}

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
void gameOver(Tetris* te){}

//�Լ��� : createBlock 
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�., srand�� 1ȸ �̻� ȣ��Ǿ�� �Ѵ�.
//���� : �������� ���� �����Ѵ�. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 ���� �ʱ�ȭ�ȴ�. 
//return : None 
void createBlock(Tetris* te)
{
	te->x = (BOARD_WIDTH + WALLSIZE * 2) / 2 - 2; //x,y �ʱ�ȭ
	te->y = 0; 

	//te->whichBlock = rand() % 7; //whichBlock�� 0~6������ ��
	te->whichBlock = 0;
	te->blockState = 0; //ȸ�����¸� �ʱⰪ����
}


//�Լ��� : moveLeft
//return : 1(����), 0 ����
int moveLeft(Tetris* te)
{
	pasteBoard(te->boPlusbl,te->board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
	te->x--; //��ǥ�̵�
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //���� �浹�ϸ�
		pasteBoard(te->boPlusbl,te->board); //bpb ����ġ
		te->x++;//��ǥ�� ��������
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
		return 0;//����
	}
	return 1; //����
}
//�Լ��� : move Right
//return : 1(����) 0 ����
int moveRight(Tetris* te)
{
	pasteBoard(te->boPlusbl,te->board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
	te->x++; //��ǥ�̵�
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //���� �浹�ϸ�
		pasteBoard(te->boPlusbl,te->board); //bpb ����ġ
		te->x--;//��ǥ�� ��������
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
		return 0;//����
	}
	return 1; //����
}
//�Լ��� : move Down
//return : 1(����) 0 ����
int moveDown(Tetris* te)
{
	pasteBoard(te->boPlusbl,te->board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
	te->y++; //��ǥ�̵�
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //���� �浹�ϸ�
		pasteBoard(te->boPlusbl,te->board); //bpb ����ġ
		te->y--;//��ǥ�� ��������
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�

		//�ٴڿ� ���� -> board(���)�� bpb���� �ʱ�ȭ
		pasteBoard(te->board,te->boPlusbl);
		createBlock(te);
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);
		//full line Ȯ��
		//game over Ȯ��

		return 0;//����
	}
	return 1; //����

}
int rotate(Tetris* te)
{
	int pre_blockstate = te->blockState;//�� ���� ȸ������ ����
	pasteBoard(te->boPlusbl,te->board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
	te->blockState = (te->blockState + 1) % 4;
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //���� �浹�ϸ�
		pasteBoard(te->boPlusbl,te->board); //bpb ����ġ
		te->blockState = pre_blockstate;
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�
		return 0;//����
	}
	return 1; //����

}

int spaceMove(Tetris* te)
{
	while(!crashCheck(te->boPlusbl,te->x,te->y)){ //�浹�Ҷ����� üũ
		pasteBoard(te->boPlusbl,te->board); //�����̱� �� bPb�� �������/
		te->y++;//��ǥ �̵�
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);//�ٿ�����
	}
	//�浹 �Ŀ�
	pasteBoard(te->boPlusbl,te->board); //bpb ����ġ
	te->y--;//��ǥ�� ��������
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block ���̱�

	//�ٴڿ� ���� -> board(���)�� bpb���� �ʱ�ȭ
	pasteBoard(te->board,te->boPlusbl);
	createBlock(te);
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);
	return 1; //����
}