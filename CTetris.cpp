#include "CTetris.h"
#include <conio.h>

void CinitGame(CTetris* cte)
{
	int i,j;
	initGame(&cte->tetris); //tetris�� tetris��� �ʱ�ȭ
	cte->Cboard = (int **)calloc(1, sizeof(int *)*(BOARD_HEIGHT + WALLSIZE));
	cte->CboPlusbl = (int **)calloc(1, sizeof(int *)*(BOARD_HEIGHT + WALLSIZE));
	for (i = 0; i < BOARD_HEIGHT + WALLSIZE; i++)
	{
		cte->Cboard[i] = (int *)calloc(1, sizeof(int)*(BOARD_WIDTH + (WALLSIZE * 2)));
		cte->CboPlusbl[i]= (int *)calloc(1, sizeof(int)*(BOARD_WIDTH + (WALLSIZE * 2)));
	}

	for (i = 0; i < BOARD_HEIGHT + WALLSIZE; i++)
	{
		for (j = 0; j < (BOARD_WIDTH + (WALLSIZE * 2)); j++)
		{
			if (j < WALLSIZE || j >= BOARD_WIDTH + WALLSIZE) { cte->Cboard[i][j] = cte->CboPlusbl[i][j] = 1; }
			if (i >= BOARD_HEIGHT)
				cte->Cboard[i][j] = cte->CboPlusbl[i][j] = 1;
		}
	}

}

//�Լ��� : CmoveLeft
//return : 1(����), 0 ����
int CmoveLeft(CTetris* cte)
{
	int res = 0;
	pasteBoard(cte->CboPlusbl,cte->Cboard);//��溸��� ��������
	res = moveLeft(&cte->tetris); //tetris�� ���� �ʱ�ȭ
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //CboPlusbl�� Paste
	return res;
}
//�Լ��� : CmoveRight
//return : 1(����) 0 ����
int CmoveRight(CTetris* cte)
{
	int res = 0;
	pasteBoard(cte->CboPlusbl,cte->Cboard);//��溸��� ��������
	res = moveRight(&cte->tetris); //tetris�� ���� �ʱ�ȭ
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2); //cte->blcok�� coloring
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //CboPlusbl�� Paste
	return res;
}
//�Լ��� : CmoveDown
//return : ���� line �� ����
int CmoveDown(CTetris* cte)
{
	int lines = 1; //���� ���μ�
	pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
	pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard �ʱ�ȭ
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte �� Cblock�� Coloring
	cte->tetris.y++; //��ǥ�̵�
	pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block ���̱�
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //block ���̱�
	if(crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //���� �浹�ϸ�
		pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //bpb ����ġ
		pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard �ʱ�ȭ
		cte->tetris.y--;//��ǥ�� ��������
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block ���̱�
		pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
		//lineErase
		switch(lines = ClineErase(cte->tetris.boPlusbl,cte->CboPlusbl,cte->tetris.y)){
		case 1: cte->tetris.score += 10; break; //single score
		case 2: cte->tetris.score += 30; break; //double
		case 3: cte->tetris.score += 50; break; //triple
		case 4: cte->tetris.score += 100; break; //tetris
		}

		//�ٴڿ� ���� -> board(���)�� bpb���� �ʱ�ȭ
		pasteBoard(cte->tetris.board,cte->tetris.boPlusbl);
		pasteBoard(cte->Cboard,cte->CboPlusbl); //ColorBoard�� ���� �ʱ�ȭ
		createBlock(&cte->tetris); //���� �� ����
		CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte �� Cblock�� Coloring
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y);
		pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
		//game over Ȯ��
		if(crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //���λ��� ���� ���� �浹�̸�?
			cte->tetris.gameState = GAME_OVER; //gamestate == GameOver
		}
	}
	return lines; //������ �������� ����

}
//�Լ��� : Crotate
//return : 1(����) 0 ����
int Crotate(CTetris* cte)
{
	int res = 0;
	pasteBoard(cte->CboPlusbl,cte->Cboard);//��溸��� ��������
	res = rotate(&cte->tetris); //tetris�� ���� �ʱ�ȭ
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2); //cte->blcok�� coloring
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //CboPlusbl�� Paste
	return res;
}
//�Լ��� : CspaceMove
//return :1(����) 0 ����
int CspaceMove(CTetris* cte)
{
	int lines = 1; //���� ���μ�
	while(!crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //�浹 ���� ��
		pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
		pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard �ʱ�ȭ
		CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte �� Cblock�� Coloring
		cte->tetris.y++; //��ǥ�̵�
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block ���̱�
		pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //block ���̱�
	}
	//�浹 ����
	pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //bpb ����ġ
	pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard �ʱ�ȭ
	cte->tetris.y--;//��ǥ�� ��������
	pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block ���̱�
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
	//lineErase
	switch(lines = ClineErase(cte->tetris.boPlusbl,cte->CboPlusbl,cte->tetris.y)){
	case 1: cte->tetris.score += 10; break; //single score
	case 2: cte->tetris.score += 30; break; //double
	case 3: cte->tetris.score += 50; break; //triple
	case 4: cte->tetris.score += 100; break; //tetris
	}

	//�ٴڿ� ���� -> board(���)�� bpb���� �ʱ�ȭ
	pasteBoard(cte->tetris.board,cte->tetris.boPlusbl);
	pasteBoard(cte->Cboard,cte->CboPlusbl); //ColorBoard�� ���� �ʱ�ȭ
	createBlock(&cte->tetris); //���� �� ����
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte �� Cblock�� Coloring
	pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y);
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
	//game over Ȯ��
	if(crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //���λ��� ���� ���� �浹�̸�?
		cte->tetris.gameState = GAME_OVER; //gamestate == GameOver
	}

	return lines; //���� ���� �� ����

}
//�Լ��� : CmakeGhost
//return :1(����) 0 ����
void CmakeGhost(CTetris* cte)
{
	int tempy = cte->tetris.y;
	int ghostBlk[BLOCK_HEIGHT][BLOCK_WIDTH];
	while(!crashCheck(cte->tetris.boPlusbl,cte->tetris.x,tempy)){ //�浹 �Ҷ����� ������
		pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //�ϴ� �����̱� ���� bpb�� board�� �ʱ�ȭ
		tempy++; //��ǥ�̵�
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,tempy); //block ���̱�
	}
	//�浹 ����
	pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //bpb ����ġ
	tempy--;//��ǥ�� ��������

	CblockColoring(ghostBlk,block[cte->tetris.whichBlock][cte->tetris.blockState],1);//ghost block setting
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cblock setting
	pasteBlock(cte->CboPlusbl,ghostBlk,cte->tetris.x,tempy);//ghostBlock�� ���� paste
	if(tempy <= cte->tetris.y + 4){ //Ghost�� ���� ��ġ�� ����
		for(int i = 0 ; i < BLOCK_HEIGHT; i++){ //block Coloring
			for(int j = 0 ; j < BLOCK_WIDTH ; j++){
				if(ghostBlk[i][j]) //�������� üũ
					cte->CboPlusbl[i + cte->tetris.y][j + cte->tetris.x] = cte->tetris.whichBlock + 2;//��ġ�� ������ �ٽ� coloring
			}
		}
	}
}

void CgameOver(CTetris* cte)
{
	int i;
	gameOver(&cte->tetris);//tetris Terminate
	for (i = 0; i < BOARD_HEIGHT + WALLSIZE; i++)
	{
		free(cte->Cboard[i]);
		free(cte->CboPlusbl[i]);
	}
	free(cte->Cboard);
	free(cte->CboPlusbl);
}


//Block�� Color�� ����
void CblockColoring(int(*to)[4],int(*from)[4],int color)
{
	for(int i = 0 ; i < BLOCK_HEIGHT; i++){
		for(int j = 0 ; j < BLOCK_WIDTH ; j++){
			to[i][j] = from[i][j];
			if(to[i][j] != 0) to[i][j] = color;
			//printf("%d",cte->cBlock[i][j]);
		}
		//printf("\n");
		//getch();
	}
}

int ClineErase(int** bPb,int** CbPb, int y)
{
	int i, j, k, cnt = 0;
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		if( lineCheck(bPb,y+i) )
		{
			if( y+i >= BOARD_HEIGHT || (y+i) <1) break;
			else{
				cnt++;
				moveBoardDown(CbPb,y+i);
				moveBoardDown(bPb, y+i);
			}
		}
	}
	return cnt;
}
