#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4
#define WALLSIZE 4
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

void printBoard(int** bo);
void pasteBoard(int**bPb, int** bo,int x,int y);
void pasteBlock(int** bo, int(*bl)[4], int x, int y);
int main(void)
{
	//board init
	int** board;//board보드 2차원 배열
	int** boPlusbl; //현재실행화면
	int x , y; //block이 붙여질 지점
	x = (BOARD_WIDTH + WALLSIZE*2)/2 - 2;
	y = 0;

	int block[][4][4][4]={ //블럭 4차원 배열
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
	//vs주석 ctrl+k+c , 해제 ctrl+k+u
	//board를 초기화 2차원 배열 calloc
	board = (int**)calloc(1,sizeof(int*)*(BOARD_HEIGHT+WALLSIZE));	
	boPlusbl = (int**)calloc(1,sizeof(int*)*(BOARD_HEIGHT+WALLSIZE));
	for(int i = 0 ; i < BOARD_HEIGHT+WALLSIZE ; i++){
		board[i] = (int*)calloc(1,sizeof(int)*(BOARD_WIDTH+(WALLSIZE*2)));
		boPlusbl[i] = (int*)calloc(1,sizeof(int)*(BOARD_WIDTH+(WALLSIZE*2)));
	}

	//Board및 boPlusbl에 벽생성
	for(int i = 0 ; i < BOARD_HEIGHT + WALLSIZE ; i++){
		for(int j = 0 ; j < (BOARD_WIDTH + (WALLSIZE*2)); j++){
		//	printf("i=%d, j=%d %p\n",i,j,&board[i][j]);
			if(j < WALLSIZE || j>= BOARD_WIDTH+WALLSIZE){ board[i][j] = boPlusbl[i][j] = 1;}
			if(i >= BOARD_HEIGHT){ board[i][j] = boPlusbl[i][j] = 1;}
		}
	}
	printf("\n\n\nreal board\n");
	//board display 실제 보드를 display
	for(int i = 0 ; i < BOARD_HEIGHT + WALLSIZE ; i++){
		for(int j = 0 ; j < BOARD_WIDTH + WALLSIZE*2; j++){
			if(board[i][j] == 1) printf("■ ");
			else printf("□ ");
		}
		printf("\n");
	}

	printf("\n\n\nbefore Paste\n");
	//real board display 게임화면에 나오는 보드를 display
	printBoard(boPlusbl);//before paste
	pasteBlock(boPlusbl,block[0][0],x,y);
	printf("\n\n\nafter Paste\n");
	printBoard(boPlusbl); printf("\n");
	pasteBoard(boPlusbl,board,x,y); //print를 한 이후엔 반드시 뒤로 돌려놓는다.
	
	for(int i = 0 ; i < 9; i++){
		y += 2;
		pasteBlock(boPlusbl,block[0][0],x,y);
		printBoard(boPlusbl);
		pasteBoard(boPlusbl,board,x,y);//print를 한 이후엔 반드시 뒤로 돌려놓는다.
		printf("\n");
	}


	return 0;
}

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

//Precondition : bo와 bl이 적절한 값으로 초기화 되어 있다.
//설명 : 블럭이 붙여진 보드를 원래 배경으로 되돌려 놓는다.
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