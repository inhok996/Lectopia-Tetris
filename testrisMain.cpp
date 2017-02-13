#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h> //random 함수
#include <time.h> //time 함수
#include "linkedList.h"
#include "person.h"
#include "Tetris.h"
//#include "CTetris.h"
#pragma warning (disable:4996)
FILE * fileOpen(char *filename, char *mode);
void gotoxy(int x, int y);
char inKey(int *keyFlag);
void box(int startX);
void gamePlaying();//게임시작함수
void textcolor(int foreground, int background);
int menu();
//void fileSave();
void backGroundDisplay(int startX, int startY);
void BlockDisplay(Tetris * te);
void removeCursor(void); //커서깜빡이 제거


#define COMMON_KEY 1 
#define SPECIAL_KEY 0 
#define SPACE 32
#define UP_ARROW 72 
#define DOWN_ARROW 80 
#define LEFT_ARROW 75 
#define RIGHT_ARROW 77 
#define ENTER 13 //일반키(getchar()일 때 10, getch()일 때 13 : '\r')
#define ESC 27 //일반키
//배경 및 글꼴 색깔
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15


int main()
{
	char ch;//사용자로부터 키보드입력 임시저장 변수
	int kFlag;//inKey()로부터 kFlag리턴
	int startX = 28;//무빙박스의 처음 시작
	FILE *fp;
	LinkedList lp;
	Person rankPerson;
	char str[101];//랭크불러오기에서 이름잠시저장배열
	int end;//랭크불러오기에서 종료조건	
	int sScore;//랭크불러오기에서 점수잠시저장배열
	srand((unsigned int)time(NULL)); //랜덤함수 seed값 초기화
	create(&lp);
	removeCursor();//커서 깜빡이 제거
	
	while (1)
	{
		box(startX);//처음에 박스가 보이기 위해
		startX = menu();
		system("cls");

		if (startX == 28){//게임시작함수
			gamePlaying();
		}
		else if (startX == 48)
		{ 
			fp = fileOpen("c://data//tetrisRanking.txt", "rt");
			assert(fp != NULL);
			//printf("1");
			while (1){
				end = fscanf(fp, "%s", str);
				fscanf(fp, "%d", &sScore);//fgets(0으로 해야할까
				//end = fgets(str, 100, fp);

				if (str[strlen(str) - 1] == '\n')
					str[strlen(str) - 1] = '\0';
				if (NULL == linearSearchUnique(&lp, str, personNameCompare))
				{
					strcpy(rankPerson.name, str);
					rankPerson.score = sScore;
					appendFromTail(&lp, &rankPerson, sizeof(Person), personMemCpy);
				}
				if (end == EOF)
					break;
			}
			//sortList(&lp, sizeof(Person), personScoreCompare, personMemCpy, personClear);
			display(&lp, personPrint);
			system("pause");
			system("cls");
			continue; 
		}//랭크함수
		else
		{
			destroy(&lp, personClear);
			break;
		}
	}	
	return 0;
}

int menu()
{
	char ch;//사용자로부터 키보드입력 임시저장 변수
	int kFlag;//inKey()로부터 kFlag리턴
	int startX = 28;

	while (1)
	{
		if (kbhit())
		{
			ch = inKey(&kFlag);//kFlag 가 상태를 나타냄(특수키다 일반키다 구분 상태 여부)
			if (ch == ENTER) break;
			else if (ch == LEFT_ARROW)//왼쪽키와 오른쪽키로 구분
			{
				if (startX < 30) startX = 68;
				else startX -= 20;
			}
			else if (ch == RIGHT_ARROW)
			{
				if (startX > 66) startX = 28;
				else startX += 20;
			}
			system("cls");
			box(startX);
		}
		textcolor(LIGHTGRAY, BLACK);
		gotoxy(30, 11);
		printf("┏━━━━━┓");
		gotoxy(30, 12);
		printf("┃ 게임 시작┃");
		gotoxy(30, 13);
		printf("┗━━━━━┛");
		gotoxy(50, 11);
		printf("┏━━━━━┓");
		gotoxy(50, 12);
		printf("┃ 랭크모드 ┃");
		gotoxy(50, 13);
		printf("┗━━━━━┛");
		gotoxy(70, 11);
		printf("┏━━━━━┓");
		gotoxy(70, 12);
		printf("┃ 게임종료 ┃");
		gotoxy(70, 13);
		printf("┗━━━━━┛");

		Sleep(100);
	}
	return startX;
}


char inKey(int *keyFlag)
{
	char ascii, scan;

	ascii = getch(); // 입력된 문자의 아스키코드를 입력받아옴 
	if (ascii == -32 || ascii == 0){ // 입력된 문자의 아스키코드가 -32이거나 0이면 특수키가 입력된것임 
		scan = getch(); // 특수키가 입력되었을때에는 scan code값을 입력받아옴 (하드웨어에서 제공하는 키보드 버퍼에 남아있다, 그걸 받아옴 <>stdin)
		*keyFlag = SPECIAL_KEY;
		return (scan);//아스키코드를 리턴하는 것은 의미 없으므로 scan코드 리턴
	}
	else { // 일반키가 입력되었으면 
		*keyFlag = COMMON_KEY;
		return (ascii);
	}
	// getch()함수로 특수키를 입력받으면 Ascii, Scan code가 프로그램 내로 들어오고, 
	// getch()함수로 일반키를 입력받으면 그냥 Ascii code만 프로그램 내로 들어오게 됩니다. 
	// 참고하세요~	
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//box() : main()문에 넣어도 된다. -> 사용자 선택 박스 옮기기
//전달인자 : startX
void box(int startX)
{
	textcolor(LIGHTRED, BLACK);
	gotoxy(startX, 10);
	printf("┏━━━━━━━┓");
	gotoxy(startX, 11);
	printf("┃              ┃");
	gotoxy(startX, 12);
	printf("┃              ┃");
	gotoxy(startX, 13);
	printf("┃              ┃");
	gotoxy(startX, 14);
	printf("┗━━━━━━━┛");
	
	return;
}

FILE *fileOpen(char *filename, char *mode)
{
	FILE *fp;
	if ((fp = fopen(filename, mode)) == NULL)
	{
		printf("File open error!\n");
	}
	return fp;
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;//foreground 글자색, background 배경색
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gamePlaying(){
	Tetris tetris;
	char ch;//사용자로부터 키보드입력 임시저장 변수
	int kFlag;//inKey()로부터 kFlag리턴
	time_t prev; //자동으로 내려오는 시간을 구하기 위함
	time_t cur; //현재시각
	int moved = 1; //move가 일어나면

	initGame(&tetris);
	tetris.nextBlock = rand() % BLOCK_NUM; //최초 NextBlock 생성 CreateBlock의 Precondition
	createBlock(&tetris);
	pasteBlock(tetris.boPlusbl,block[tetris.whichBlock][tetris.blockState],tetris.x,tetris.y);
	system("cls");
	//backGroundDisplay(3,1);
	printf("Game Start!!!! Press Any Key\n");
	getch();
	tetris.gameState = PLAYING;
	system("cls");
	time(&prev);
	while(tetris.gameState){
		gotoxy(1,1);
		if(moved){ //이동이 일어나면
			printBoard(tetris.boPlusbl); //사용자 게임화면 출력
			moved = 0; //다음번 루프때 다시 출력하지 않도록 수정
		}
		if(!kbhit()){
			time(&cur); //현재시각을 구함
			if(cur != prev){ //1초단위
				moved = moveDown(&tetris);
				prev = cur; //이전시간을 현재시간으로 초기화
			}
		}else{
			ch = inKey(&kFlag);//kFlag 가 상태를 나타냄(특수키다 일반키다 구분 상태 여부)
			switch(ch){
			case LEFT_ARROW:moved = moveLeft(&tetris); break;
			case RIGHT_ARROW:moved = moveRight(&tetris); break;
			case UP_ARROW: moved = rotate(&tetris); break;
			case DOWN_ARROW: moved = moveDown(&tetris); break;
			case SPACE: moved = spaceMove(&tetris); break;
			case ESC: break;
			}
		}
	}
	//while루프 탈출, GameOver
	gotoxy(1,1);
	printBoard(tetris.boPlusbl);
	//gotoxy(정중앙)
	printf("Game Over 아무키나 누르시면 메뉴로 돌아갑니다\n"); //수정해야 함
	gameOver(&tetris); //tetris structure에 동적할당된 메모리 초기화및 값들 초기화
	getch();
	system("cls");
	//점수입력란
	
}

void backGroundDisplay(int startX,int startY)
{
   //맨 윗 줄 찍기
	int i; //index
	gotoxy(startX, startY);
	printf("┏");
	for(i = 0 ; i < BOARD_WIDTH+5 ; i++) printf("━");
	printf("┓");
	for(i = startY ; i < BOARD_HEIGHT ; i++){
		gotoxy(startX, i+1);
		printf("┃                              ┃");
	}
	gotoxy(startX,i);
	printf("┗");
	for(i = 0 ; i < BOARD_WIDTH+5 ; i++) printf("━");
	printf("┛");
}

void BlockDisplay(Tetris * te)
{
   for(int i = 0; i< BLOCK_HEIGHT; i++)
   {
      gotoxy(2 ,te->y+i);
      for(int j = 0 ; j < BOARD_WIDTH ; j ++)
      {
         if(te->boPlusbl[i][j]==1)
            putchar('■');
         else if(te->boPlusbl[i][j]==0)
             putchar('□');
      }
   }
}

void removeCursor(void) 

{ 

        CONSOLE_CURSOR_INFO curInfo; 
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 
        curInfo.bVisible=0; 
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 

} 