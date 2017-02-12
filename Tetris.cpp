#include "Tetris.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>

int block[][4][4][4]=
{ //블럭 4차원 배열 첫번쨰배열인덱스: 블럭의 종류 두번째배열인덱스 :블럭의 회전
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



//함수명 : printBoard
//Precondition : bo가 적절한 값으로 초기화 되어 있다.
//설명 : 게임화면을 출력
//Postcondition : None
//return : None
void printBoard(int** bo)
{
	for(int i = 0 ; i < BOARD_HEIGHT + 1; i++){
		for(int j = WALLSIZE - 1 ; j < BOARD_WIDTH + WALLSIZE + 1; j++){
			if(bo[i][j] == 1) printf("■ ");
			else if(bo[i][j] ==2) printf("★ ");
			else printf("□ ");
		}
		printf("\n");
	}
}

//Precondition : bo와 bl이 적절한 값으로 초기화 되어 있다.
//설명 : 현재 사용되는 블럭을 배경에 붙여넣는다.보드+블럭
//Postcondition : bo(블럭) 에 bl(블럭)이 붙여진다.
//return : None
void pasteBlock(int** bo, int(*bl)[4], int x, int y)
{
	for(int i = 0 ; i < BLOCK_HEIGHT; i++){
		for(int j = 0 ; j < BLOCK_WIDTH ; j++){

	bo[i+y][j+x] += bl[i][j];
		}
	}
}

//Precondition : bPb와 bo가 적절한 값으로 초기화 되어 있다.
//설명 : 블럭이 붙여진 보드를 원래 배경으로 되돌려 놓는다.
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


//함수명 :initGame
//precondition : None
//함수설명 : 게임에 대한 변수를 초기상태로 설정한다.
//te->board, te->boPlusbl 2차원배열 동적할당
//te->socre = 0 , te->blockState = 0, whichBlock = 랜덤 설정
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
	te->blockState = 0; //회전 4가지모양 
	te->whichBlock = 0;// 배열의 첫번째 index 7가지
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


//함수명 : crushCheck
//Precondition : bpb , x, y는 적절한 값으로 초기화되어 있다.
//설명 : bpb의 블럭이 붙여진 부분을 체크하여 충돌이 일어났는지를 체크한다.(값이 2인지를 확인)
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

//함수명 : lineCheck
//Precondition : bpb , y는 적절한 값으로 초기화되어 있다.
//설명 : y가 가르키는 한 라인의 체크를 한다.
//Postcondition : None
//return : 1 (full line) , 0 (not full)
int lineCheck(int** bpb, int y){return 1;}

//함수명 : lineErase
//Precondition : bpb , y는 적절한 값으로 초기화되어 있다.
//설명 : y가 가르키는 블럭의 맨 아랫줄부터 라인을 체크하여 삭제한다.
//Postcondition : bpb의 라인이 지워진 상태이다.(지워진 라인이 없을시에 bpb는 그대로)
//return : 0 한줄도 못지웠을시, 1 한줄지움 2두줄지움 3세줄지움 4네줄지움
int lineErase(int** bpb, int y){return 1;}

//함수명 : gameOver
//Precondition : Tetris 구조체의 값이 적절히 차 있다.
//설명 : 게임을 초기화시키고 동적할당한 메모리를 모두 해제시킨다. Score를 리턴한다.
//Postcondition : board 및 boPlusbl의 메모리 해제
//return : None
void gameOver(Tetris* te){}

//함수명 : createBlock 
//Precondition : Tetris 구조체의 값이 적절히 차 있다., srand가 1회 이상 호출되어야 한다.
//설명 : 랜덤으로 블럭을 생성한다. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 으로 초기화된다. 
//return : None 
void createBlock(Tetris* te)
{
	te->x = (BOARD_WIDTH + WALLSIZE * 2) / 2 - 2; //x,y 초기화
	te->y = 0; 

	//te->whichBlock = rand() % 7; //whichBlock은 0~6사이의 값
	te->whichBlock = 0;
	te->blockState = 0; //회전상태를 초기값으로
}


//함수명 : moveLeft
//return : 1(성공), 0 실패
int moveLeft(Tetris* te)
{
	pasteBoard(te->boPlusbl,te->board); //일단 움직이기 전에 bpb를 board로 초기화
	te->x--; //좌표이동
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //만약 충돌하면
		pasteBoard(te->boPlusbl,te->board); //bpb 원위치
		te->x++;//좌표를 돌려놓음
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
		return 0;//실패
	}
	return 1; //성공
}
//함수명 : move Right
//return : 1(성공) 0 실패
int moveRight(Tetris* te)
{
	pasteBoard(te->boPlusbl,te->board); //일단 움직이기 전에 bpb를 board로 초기화
	te->x++; //좌표이동
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //만약 충돌하면
		pasteBoard(te->boPlusbl,te->board); //bpb 원위치
		te->x--;//좌표를 돌려놓음
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
		return 0;//실패
	}
	return 1; //성공
}
//함수명 : move Down
//return : 1(성공) 0 실패
int moveDown(Tetris* te)
{
	pasteBoard(te->boPlusbl,te->board); //일단 움직이기 전에 bpb를 board로 초기화
	te->y++; //좌표이동
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //만약 충돌하면
		pasteBoard(te->boPlusbl,te->board); //bpb 원위치
		te->y--;//좌표를 돌려놓음
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기

		//바닥에 도달 -> board(배경)을 bpb으로 초기화
		pasteBoard(te->board,te->boPlusbl);
		createBlock(te);
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);
		//full line 확인
		//game over 확인

		return 0;//실패
	}
	return 1; //성공

}
int rotate(Tetris* te)
{
	int pre_blockstate = te->blockState;//이 전의 회전값을 저장
	pasteBoard(te->boPlusbl,te->board); //일단 움직이기 전에 bpb를 board로 초기화
	te->blockState = (te->blockState + 1) % 4;
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //만약 충돌하면
		pasteBoard(te->boPlusbl,te->board); //bpb 원위치
		te->blockState = pre_blockstate;
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기
		return 0;//실패
	}
	return 1; //성공

}

int spaceMove(Tetris* te)
{
	while(!crashCheck(te->boPlusbl,te->x,te->y)){ //충돌할때까지 체크
		pasteBoard(te->boPlusbl,te->board); //움직이기 전 bPb를 배경으로/
		te->y++;//좌표 이동
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);//붙여넣음
	}
	//충돌 후에
	pasteBoard(te->boPlusbl,te->board); //bpb 원위치
	te->y--;//좌표를 돌려놓음
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y); //block 붙이기

	//바닥에 도달 -> board(배경)을 bpb으로 초기화
	pasteBoard(te->board,te->boPlusbl);
	createBlock(te);
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);
	return 1; //성공
}