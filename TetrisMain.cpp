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
	int** board;//board���� 2���� �迭
	int** boPlusbl; //�������ȭ��
	int x , y; //block�� �ٿ��� ����
	x = (BOARD_WIDTH + WALLSIZE*2)/2 - 2;
	y = 0;

	int block[][4][4][4]={ //�� 4���� �迭
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
	//vs�ּ� ctrl+k+c , ���� ctrl+k+u
	//board�� �ʱ�ȭ 2���� �迭 calloc
	board = (int**)calloc(1,sizeof(int*)*(BOARD_HEIGHT+WALLSIZE));	
	boPlusbl = (int**)calloc(1,sizeof(int*)*(BOARD_HEIGHT+WALLSIZE));
	for(int i = 0 ; i < BOARD_HEIGHT+WALLSIZE ; i++){
		board[i] = (int*)calloc(1,sizeof(int)*(BOARD_WIDTH+(WALLSIZE*2)));
		boPlusbl[i] = (int*)calloc(1,sizeof(int)*(BOARD_WIDTH+(WALLSIZE*2)));
	}

	//Board�� boPlusbl�� ������
	for(int i = 0 ; i < BOARD_HEIGHT + WALLSIZE ; i++){
		for(int j = 0 ; j < (BOARD_WIDTH + (WALLSIZE*2)); j++){
		//	printf("i=%d, j=%d %p\n",i,j,&board[i][j]);
			if(j < WALLSIZE || j>= BOARD_WIDTH+WALLSIZE){ board[i][j] = boPlusbl[i][j] = 1;}
			if(i >= BOARD_HEIGHT){ board[i][j] = boPlusbl[i][j] = 1;}
		}
	}
	printf("\n\n\nreal board\n");
	//board display ���� ���带 display
	for(int i = 0 ; i < BOARD_HEIGHT + WALLSIZE ; i++){
		for(int j = 0 ; j < BOARD_WIDTH + WALLSIZE*2; j++){
			if(board[i][j] == 1) printf("�� ");
			else printf("�� ");
		}
		printf("\n");
	}

	printf("\n\n\nbefore Paste\n");
	//real board display ����ȭ�鿡 ������ ���带 display
	printBoard(boPlusbl);//before paste
	pasteBlock(boPlusbl,block[0][0],x,y);
	printf("\n\n\nafter Paste\n");
	printBoard(boPlusbl); printf("\n");
	pasteBoard(boPlusbl,board,x,y); //print�� �� ���Ŀ� �ݵ�� �ڷ� �������´�.
	
	for(int i = 0 ; i < 9; i++){
		y += 2;
		pasteBlock(boPlusbl,block[0][0],x,y);
		printBoard(boPlusbl);
		pasteBoard(boPlusbl,board,x,y);//print�� �� ���Ŀ� �ݵ�� �ڷ� �������´�.
		printf("\n");
	}


	return 0;
}

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

//Precondition : bo�� bl�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
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