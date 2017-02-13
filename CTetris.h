#pragma once
#include "Tetris.h"

typedef struct _Ctetris{
	int** Cboard; //백업보드
	int** CboPlusbl; //충돌체크, 출력용 보드
	Tetris tetris; //기존 테트리스
	int cBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
}CTetris;


//컬러, Ghost를 포함한 테트리스의 init
void CinitGame(CTetris* cte);

//함수명 : moveLeft
//return : 1(성공), 0 실패
int CmoveLeft(CTetris* cte);
//함수명 : move Right
//return : 1(성공) 0 실패
int CmoveRight(CTetris* cte);
//함수명 : move Down
//return : 1(성공) 0 실패
int CmoveDown(CTetris* cte);
//함수명 : rotate
//return : 1(성공) 0 실패
int Crotate(CTetris* cte);
//함수명 : spaceMove
//return :1(성공) 0 실패
int CspaceMove(CTetris* cte);
void CmakeGhost(CTetris* cte);
void CgameOver(CTetris* cte);
void CblockColoring(CTetris* cte);

//함수명 : ClineErase
//설명 : bpb를 체크하여 CbPb를 같이 초기화
int ClineErase(int** bPb,int** CbPb ,int y);