#pragma once
#include "Tetris.h"

typedef struct _Ctetris{
	int** Cboard; //�������
	int** CboPlusbl; //�浹üũ, ��¿� ����
	Tetris tetris; //���� ��Ʈ����
	int cBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
}CTetris;


//�÷�, Ghost�� ������ ��Ʈ������ init
void CinitGame(CTetris* cte);

//�Լ��� : moveLeft
//return : 1(����), 0 ����
int CmoveLeft(CTetris* cte);
//�Լ��� : move Right
//return : 1(����) 0 ����
int CmoveRight(CTetris* cte);
//�Լ��� : move Down
//return : 1(����) 0 ����
int CmoveDown(CTetris* cte);
//�Լ��� : rotate
//return : 1(����) 0 ����
int Crotate(CTetris* cte);
//�Լ��� : spaceMove
//return :1(����) 0 ����
int CspaceMove(CTetris* cte);
void CmakeGhost(CTetris* cte);
void CgameOver(CTetris* cte);
void CblockColoring(CTetris* cte);

//�Լ��� : ClineErase
//���� : bpb�� üũ�Ͽ� CbPb�� ���� �ʱ�ȭ
int ClineErase(int** bPb,int** CbPb ,int y);