#pragma once
#define BOARD_HEIGHT 20 //���� ����
#define BOARD_WIDTH 10 //���� �ʺ�
#define BLOCK_HEIGHT 4 //�� ����
#define BLOCK_WIDTH 4  //�� �ʺ�
#define WALLSIZE 4 //�� ũ��
#define BLOCK_NUM 7 //BLOCK NUMBER
#define GAME_OVER 0 //gameState
#define PLAYING 1 //gameState
#define PAUSE 2 //gameState
#define READY 3 //gameState
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

extern int block[][4][4][4];

typedef struct _tetris{
	int** board; //�������
	int** boPlusbl; //�浹üũ, ��¿� ����
	int x; //�����
	int y; //������
	int gameState; // ���� ���� ���� 0 GAMEOVER, 1 PLAYING, 2 PAUSE, 3 READY
	int blockState; //�� ȸ�� ī��Ʈ
	int whichBlock; //�� ���
	int nextBlock; //������////////////////////////////////////////////////////////////////
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
void pasteBoard(int**bPb, int** bo);

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
int lineCheck(int** bPb, int y);

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
void gameOver(Tetris* te);

//�Լ��� : createBlock 
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�. 
//���� : �������� ���� �����Ѵ�. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 ���� �ʱ�ȭ�ȴ�. 
//return : None 
void createBlock(Tetris* te);


//�Լ��� : moveLeft
//return : 1(����), 0 ����
int moveLeft(Tetris* te);
//�Լ��� : move Right
//return : 1(����) 0 ����
int moveRight(Tetris* te);
//�Լ��� : move Down
//return : 1(����) 0 ����
int moveDown(Tetris* te);
//�Լ��� : rotate
//return : 1(����) 0 ����
int rotate(Tetris* te);
//�Լ��� : spaceMove
//return :1(����) 0 ����
int spaceMove(Tetris* te);

//Precondition : bPb�� y�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : y-1��~0�� �ٿ� �ִ� ���� y��~1���� �ٷ� ���� �ٿ��ֱ� ���ش�.
//Postcondition : None
//return : None
void moveBoardDown(int**bPb, int y);