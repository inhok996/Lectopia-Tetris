#pragma once
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4
#define WALLSIZE 4
#define GAME_OVER 0
#define PLAYING 1
#define PAUSE 2
#define READY 3

extern int block[][4][4][4];

typedef struct _tetris{
	int** board; //백업보드
	int** boPlusbl; //충돌체크, 출력용 보드
	int x; //행원소
	int y; //열원소
	int gameState; // 현재 게임 상태 0 GAMEOVER, 1 PLAYING, 2 PAUSE, 3 READY
	int blockState; //블럭 회전 카운트
	int whichBlock; //블럭 모양
	int NextBlock; //다음블럭////////////////////////////////////////////////////////////////
	int score; //현재 게임 점수
}Tetris;

//함수명 :initGame
//precondition : None
//함수설명 : 게임에 대한 변수를 초기상태로 설정한다.
//te->board, te->boPlusbl 2차원배열 동적할당
//te->socre = 0 , te->blockState = 0, whichBlock = 랜덤 설정
void initGame(Tetris* te);

//함수명 : printBoard
//Precondition : bo가 적절한 값으로 초기화 되어 있다.
//설명 : 게임화면을 출력
//Postcondition : None
//return : None
void printBoard(int** bo);

//함수명 : pasteBoard
//Precondition : bPb와 bo가 적절한 값으로 초기화 되어 있다.
//설명 : 블럭이 붙여진 보드를 원래 배경으로 되돌려 놓는다.
//Postcondition : None
//return : None
void pasteBoard(int**bPb, int** bo);

//함수명 : pasteBlock
//Precondition : bo와 bl이 적절한 값으로 초기화 되어 있다.
//설명 : 현재 사용되는 블럭을 배경에 붙여넣는다.보드+블럭
//Postcondition : bo(블럭) 에 bl(블럭)이 붙여진다.
//return : None
void pasteBlock(int** bo, int(*bl)[4], int x, int y);

//함수명 : crushCheck
//Precondition : bpb , x, y는 적절한 값으로 초기화되어 있다.
//설명 : bpb의 블럭이 붙여진 부분을 체크하여 충돌이 일어났는지를 체크한다.(값이 2인지를 확인)
//Postcondition : None
//return : 1 (crash) , 0 (not crash)
int crashCheck(int** bpb, int x, int y);

//함수명 : lineCheck
//Precondition : bpb , y는 적절한 값으로 초기화되어 있다.
//설명 : y가 가르키는 한 라인의 체크를 한다.
//Postcondition : None
//return : 1 (full line) , 0 (not full)
int lineCheck(int** bpb, int y);

//함수명 : lineErase
//Precondition : bpb , y는 적절한 값으로 초기화되어 있다.
//설명 : y가 가르키는 블럭의 맨 아랫줄부터 라인을 체크하여 삭제한다.
//Postcondition : bpb의 라인이 지워진 상태이다.(지워진 라인이 없을시에 bpb는 그대로)
//return : 0 한줄도 못지웠을시, 1 한줄지움 2두줄지움 3세줄지움 4네줄지움
int lineErase(int** bpb, int y);

//함수명 : gameOver
//Precondition : Tetris 구조체의 값이 적절히 차 있다.
//설명 : 게임을 초기화시키고 동적할당한 메모리를 모두 해제시킨다. Score를 리턴한다.
//Postcondition : board 및 boPlusbl의 메모리 해제
//return : None
void gameOver(Tetris* te);

//함수명 : createBlock 
//Precondition : Tetris 구조체의 값이 적절히 차 있다. 
//설명 : 랜덤으로 블럭을 생성한다. 
//Postcondition : Te->whichBlock = rand();, blockState = 0 으로 초기화된다. 
//return : None 
void createBlock(Tetris* te);


//함수명 : moveLeft
//return : 1(성공), 0 실패
int moveLeft(Tetris* te);
//함수명 : move Right
//return : 1(성공) 0 실패
int moveRight(Tetris* te);
//함수명 : move Down
//return : 1(성공) 0 실패
int moveDown(Tetris* te);
//함수명 : rotate
//return : 1(성공) 0 실패
int rotate(Tetris* te);
//함수명 : spaceMove
//return :1(성공) 0 실패
int spaceMove(Tetris* te);