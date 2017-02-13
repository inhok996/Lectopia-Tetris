#include "Tetris.h"


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
	},
	{
		{
			{0,0,0,0}, 
			{0,1,0,0},
			{1,1,1,0}, 
			{0,0,0,0}
		},   
		{ 
			{0,0,0,0}, 
			{0,1,0,0}, 
			{1,1,0,0}, 
			{0,1,0,0} 
		},    
		{ 
			{0,0,0,0}, 
			{0,0,0,0}, 
			{1,1,1,0}, 
			{0,1,0,0} 
		},    

		{ 
			{0,0,0,0}, 
			{0,1,0,0}, 
			{0,1,1,0}, 
			{0,1,0,0} 
		}, 
	},
	{
		{
			{0,0,0,0}, 
			{0,0,1,0},
			{1,1,1,0}, 
			{0,0,0,0}
		},   
		{ 
			{0,1,1,0}, 
			{0,0,1,0}, 
			{0,0,1,0}, 
			{0,0,0,0} 
		},    
		{ 
			{1,1,1,0}, 
			{1,0,0,0}, 
			{0,0,0,0}, 
			{0,0,0,0} 
		},    

		{ 
			{1,0,0,0}, 
			{1,0,0,0}, 
			{1,1,0,0}, 
			{0,0,0,0} 
		}, 
	},
	{
		{
			{0,1,0,0}, 
			{0,1,0,0},
			{0,1,0,0}, 
			{0,1,0,0}
		},   
		{ 
			{0,0,0,0}, 
			{0,0,0,0}, 
			{1,1,1,1}, 
			{0,0,0,0} 
		},    
		{ 
			{0,1,0,0}, 
			{0,1,0,0}, 
			{0,1,0,0}, 
			{0,1,0,0} 
		},    

		{ 
			{0,0,0,0}, 
			{0,0,0,0}, 
			{1,1,1,1}, 
			{0,0,0,0} 
		}, 
	},
	{
		{
			{1,1,0,0}, 
			{1,1,0,0},
			{0,0,0,0}, 
			{0,0,0,0}
		},   
		{ 
			{1,1,0,0}, 
			{1,1,0,0}, 
			{0,0,0,0}, 
			{0,0,0,0} 
		},    
		{ 
			{1,1,0,0}, 
			{1,1,0,0}, 
			{0,0,0,0}, 
			{0,0,0,0} 
		},    

		{ 
			{1,1,0,0}, 
			{1,1,0,0}, 
			{0,0,0,0}, 
			{0,0,0,0} 
		}, 
	},
	{
		{
			{0,0,0,0}, 
			{0,1,1,0},
			{1,1,0,0}, 
			{0,0,0,0}
		},   
		{ 
			{0,1,0,0}, 
			{0,1,1,0}, 
			{0,0,1,0}, 
			{0,0,0,0} 
		},    
		{ 
			{0,0,0,0}, 
			{0,1,1,0}, 
			{1,1,0,0}, 
			{0,0,0,0} 
		},    

		{ 
			{0,1,0,0}, 
			{0,1,1,0}, 
			{0,0,1,0}, 
			{0,0,0,0} 
		}, 
	},
	{
		{
			{0,0,0,0}, 
			{1,1,0,0},
			{0,1,1,0}, 
			{0,0,0,0}
		},   
		{ 
			{0,0,1,0}, 
			{0,1,1,0}, 
			{0,1,0,0}, 
			{0,0,0,0} 
		},    
		{ 
			{0,0,0,0}, 
			{1,1,0,0}, 
			{0,1,1,0}, 
			{0,0,0,0} 
		},    

		{ 
			{0,0,1,0}, 
			{0,1,1,0}, 
			{0,1,0,0}, 
			{0,0,0,0} 
		}, 
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
			if(bo[i][j] == 1) printf("��");
			else if(bo[i][j] ==2) printf("��");
			else printf("  ");
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
int lineCheck(int** bPb, int y)
{
	for(int i=0;i<BOARD_WIDTH; i++)
	{
		if(bPb[y][WALLSIZE+i] != 1  ||  y >= BOARD_HEIGHT  ) break;
		if(i==BOARD_WIDTH-1) return 1;
	}
	return 0;
}

//�Լ��� : lineErase
//Precondition : bpb , y�� ������ ������ �ʱ�ȭ�Ǿ� �ִ�.
//���� : y�� ����Ű�� ���� �� �Ʒ��ٺ��� ������ üũ�Ͽ� �����Ѵ�.
//Postcondition : bpb�� ������ ������ �����̴�.(������ ������ �����ÿ� bpb�� �״��)
//return : 0 ���ٵ� ����������, 1 �������� 2�������� 3�������� 4��������
int lineErase(int** bPb, int y)
{
	int i, j, k, cnt = 0;
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		if( lineCheck(bPb,y+i) )
		{
			if( y+i >= BOARD_HEIGHT || (y+i) <1) break;
			else{
				cnt++; 
				moveBoardDown(bPb, y+i);
			}
		}
	}
	return cnt;
}

//�Լ��� : gameOver
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�.
//���� : ������ �ʱ�ȭ��Ű�� �����Ҵ��� �޸𸮸� ��� ������Ų��. Score�� �����Ѵ�.
//Postcondition : board �� boPlusbl�� �޸� ����
//return : None
void gameOver(Tetris* te)
{
	int i;
	for (i = 0; i < BOARD_WIDTH; i++)
		if (te->boPlusbl[0][WALLSIZE+i] != 0)
			te->gameState = GAME_OVER;
	free(te->board);
	free(te->boPlusbl);
	te->x = (BOARD_WIDTH + WALLSIZE * 2) / 2 - 2;
	te->y = 0;
	te->blockState = 0; //ȸ�� 4������� 
	te->whichBlock = 0;// �迭�� ù��° index 7����
}

//�Լ��� : createBlock 
//Precondition : Tetris ����ü�� ���� ������ �� �ִ�., srand�� 1ȸ �̻� ȣ��Ǿ�� �Ѵ�. te->nextBlock�� ���� �ѹ� �̻� �ʱ�ȭ �Ǿ� �ִ�.
//���� : �������� ���� �����Ѵ�. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 ���� �ʱ�ȭ�ȴ�. 
//return : None 
void createBlock(Tetris* te)
{
	te->x = (BOARD_WIDTH + WALLSIZE * 2) / 2 - 2; //x,y �ʱ�ȭ
	te->y = 0; 

	te->whichBlock = te->nextBlock;
	te->nextBlock = rand() % BLOCK_NUM;
	//te->whichBlock = 0;
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
		//lineErase
		switch(lineErase(te->boPlusbl,te->y)){
		case 1: te->score += 10; break; //single score
		case 2: te->score += 30; break; //double
		case 3: te->score += 50; break; //triple
		case 4: te->score += 100; break; //tetris
		}

		//�ٴڿ� ���� -> board(���)�� bpb���� �ʱ�ȭ
		pasteBoard(te->board,te->boPlusbl);
		createBlock(te);
		pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);
		//game over Ȯ��
		if(crashCheck(te->boPlusbl,te->x,te->y)){ //���λ��� ���� ���� �浹�̸�?
			te->gameState = GAME_OVER; //gamestate == GameOver
		}

	}
	return 1; //������ �������� ����

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
	//lineErase
	switch(lineErase(te->boPlusbl,te->y)){
	case 1: te->score += 10; break; //single score
	case 2: te->score += 30; break; //double
	case 3: te->score += 50; break; //triple
	case 4: te->score += 100; break; //tetris
	}
	
	//�ٴڿ� ���� -> board(���)�� bpb���� �ʱ�ȭ
	pasteBoard(te->board,te->boPlusbl);
	createBlock(te);
	pasteBlock(te->boPlusbl,block[te->whichBlock][te->blockState],te->x,te->y);
	//gameOver
	if(crashCheck(te->boPlusbl,te->x,te->y)){ //���λ��� ���� ���� �浹�̸�?
		te->gameState = GAME_OVER; //gamestate == GameOver
	}


	return 1; //������ �������� ����
}


//Precondition : bPb�� y�� ������ ������ �ʱ�ȭ �Ǿ� �ִ�.
//���� : y-1��~0�� �ٿ� �ִ� ���� y��~1���� �ٷ� ���� �ٿ��ֱ� ���ش�.
//Postcondition : None
//return : None
void moveBoardDown(int**bPb, int y)
{
   int i, j;
   for( i = 0 ; i < y ; i++){
      if( y-1 < 1 )break;
      for( j = 0 ; j < BOARD_WIDTH; j++){
         bPb[y - i][j+WALLSIZE] = bPb[y-1 - i][j+WALLSIZE];   //y-1 �ٿ� �ִ� �� y�ٿ� ����, y-2�ٿ� �ִ� �� y-1�ٿ� ����, .. 0�ٿ� �ִ� �� 1�ٿ� ����.
      }
   }
}