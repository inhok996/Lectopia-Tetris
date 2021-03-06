#include "CTetris.h"
#include <conio.h>

void CinitGame(CTetris* cte)
{
	int i,j;
	initGame(&cte->tetris); //tetris는 tetris대로 초기화
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

//함수명 : CmoveLeft
//return : 1(성공), 0 실패
int CmoveLeft(CTetris* cte)
{
	int res = 0;
	pasteBoard(cte->CboPlusbl,cte->Cboard);//배경보드로 돌려놓음
	res = moveLeft(&cte->tetris); //tetris를 먼저 초기화
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //CboPlusbl에 Paste
	return res;
}
//함수명 : CmoveRight
//return : 1(성공) 0 실패
int CmoveRight(CTetris* cte)
{
	int res = 0;
	pasteBoard(cte->CboPlusbl,cte->Cboard);//배경보드로 돌려놓음
	res = moveRight(&cte->tetris); //tetris를 먼저 초기화
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2); //cte->blcok을 coloring
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //CboPlusbl에 Paste
	return res;
}
//함수명 : CmoveDown
//return : 지운 line 수 리턴
int CmoveDown(CTetris* cte)
{
	int lines = 1; //지운 라인수
	pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //일단 움직이기 전에 bpb를 board로 초기화
	pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard 초기화
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte 의 Cblock을 Coloring
	cte->tetris.y++; //좌표이동
	pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block 붙이기
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //block 붙이기
	if(crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //만약 충돌하면
		pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //bpb 원위치
		pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard 초기화
		cte->tetris.y--;//좌표를 돌려놓음
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block 붙이기
		pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
		//lineErase
		switch(lines = ClineErase(cte->tetris.boPlusbl,cte->CboPlusbl,cte->tetris.y)){
		case 1: cte->tetris.score += 10; break; //single score
		case 2: cte->tetris.score += 30; break; //double
		case 3: cte->tetris.score += 50; break; //triple
		case 4: cte->tetris.score += 100; break; //tetris
		}

		//바닥에 도달 -> board(배경)을 bpb으로 초기화
		pasteBoard(cte->tetris.board,cte->tetris.boPlusbl);
		pasteBoard(cte->Cboard,cte->CboPlusbl); //ColorBoard도 같이 초기화
		createBlock(&cte->tetris); //다음 블럭 생성
		CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte 의 Cblock을 Coloring
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y);
		pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
		//game over 확인
		if(crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //새로생긴 블럭과 만약 충돌이면?
			cte->tetris.gameState = GAME_OVER; //gamestate == GameOver
		}
	}
	return lines; //무조건 성공으로 간주

}
//함수명 : Crotate
//return : 1(성공) 0 실패
int Crotate(CTetris* cte)
{
	int res = 0;
	pasteBoard(cte->CboPlusbl,cte->Cboard);//배경보드로 돌려놓음
	res = rotate(&cte->tetris); //tetris를 먼저 초기화
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2); //cte->blcok을 coloring
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //CboPlusbl에 Paste
	return res;
}
//함수명 : CspaceMove
//return :1(성공) 0 실패
int CspaceMove(CTetris* cte)
{
	int lines = 1; //지운 라인수
	while(!crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //충돌 안할 때
		pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //일단 움직이기 전에 bpb를 board로 초기화
		pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard 초기화
		CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte 의 Cblock을 Coloring
		cte->tetris.y++; //좌표이동
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block 붙이기
		pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y); //block 붙이기
	}
	//충돌 이후
	pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //bpb 원위치
	pasteBoard(cte->CboPlusbl,cte->Cboard);//Cboard 초기화
	cte->tetris.y--;//좌표를 돌려놓음
	pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y); //block 붙이기
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
	//lineErase
	switch(lines = ClineErase(cte->tetris.boPlusbl,cte->CboPlusbl,cte->tetris.y)){
	case 1: cte->tetris.score += 10; break; //single score
	case 2: cte->tetris.score += 30; break; //double
	case 3: cte->tetris.score += 50; break; //triple
	case 4: cte->tetris.score += 100; break; //tetris
	}

	//바닥에 도달 -> board(배경)을 bpb으로 초기화
	pasteBoard(cte->tetris.board,cte->tetris.boPlusbl);
	pasteBoard(cte->Cboard,cte->CboPlusbl); //ColorBoard도 같이 초기화
	createBlock(&cte->tetris); //다음 블럭 생성
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cte 의 Cblock을 Coloring
	pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,cte->tetris.y);
	pasteBlock(cte->CboPlusbl,cte->cBlock,cte->tetris.x,cte->tetris.y);
	//game over 확인
	if(crashCheck(cte->tetris.boPlusbl,cte->tetris.x,cte->tetris.y)){ //새로생긴 블럭과 만약 충돌이면?
		cte->tetris.gameState = GAME_OVER; //gamestate == GameOver
	}

	return lines; //지운 라인 수 리턴

}
//함수명 : CmakeGhost
//return :1(성공) 0 실패
void CmakeGhost(CTetris* cte)
{
	int tempy = cte->tetris.y;
	int ghostBlk[BLOCK_HEIGHT][BLOCK_WIDTH];
	while(!crashCheck(cte->tetris.boPlusbl,cte->tetris.x,tempy)){ //충돌 할때까지 내려감
		pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //일단 움직이기 전에 bpb를 board로 초기화
		tempy++; //좌표이동
		pasteBlock(cte->tetris.boPlusbl,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.x,tempy); //block 붙이기
	}
	//충돌 이후
	pasteBoard(cte->tetris.boPlusbl,cte->tetris.board); //bpb 원위치
	tempy--;//좌표를 돌려놓음

	CblockColoring(ghostBlk,block[cte->tetris.whichBlock][cte->tetris.blockState],1);//ghost block setting
	CblockColoring(cte->cBlock,block[cte->tetris.whichBlock][cte->tetris.blockState],cte->tetris.whichBlock+2);//cblock setting
	pasteBlock(cte->CboPlusbl,ghostBlk,cte->tetris.x,tempy);//ghostBlock을 먼저 paste
	if(tempy <= cte->tetris.y + 4){ //Ghost와 블럭이 겹치는 구간
		for(int i = 0 ; i < BLOCK_HEIGHT; i++){ //block Coloring
			for(int j = 0 ; j < BLOCK_WIDTH ; j++){
				if(ghostBlk[i][j]) //블럭구간만 체크
					cte->CboPlusbl[i + cte->tetris.y][j + cte->tetris.x] = cte->tetris.whichBlock + 2;//겹치는 구간을 다시 coloring
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


//Block의 Color를 입힘
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
