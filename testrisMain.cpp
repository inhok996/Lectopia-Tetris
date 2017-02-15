#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h> //random 함수
#include <time.h> //time 함수
#include "linkedList.h"
#include "person.h"
#include "Tetris.h"
#include "CTetris.h"
#define gameStartX 1
#define gameStartY 1
#pragma warning (disable:4996)
FILE * fileOpen(char *filename, char *mode);
void gotoxy(int x, int y);
char inKey(int *keyFlag);
void box(int startX);
int gamePlaying();//게임시작함수
void textcolor(int foreground, int background);
int scorePrint(LinkedList *lp);
int menu();
void dataFileLoad(LinkedList *lp);
int scorePrint(LinkedList *lp, char *str);
//void fileSave();
void input(char * str);
void removeCursor(void); //커서깜빡이 제거
void gameDisplay(CTetris * cte, int startX, int startY);
void backGroundDisplay(CTetris* cte, int startX, int startY);
void nextBlockDisplay(CTetris* cte, int startX, int startY);
void sideDisplay(int currentScore,int level ,int startX, int startY);
void elecDisplay(int lines, int startX, int startY);


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
	//char ch;//사용자로부터 키보드입력 임시저장 변수
	//int kFlag;//inKey()로부터 kFlag리턴
	int startX = 28;//무빙박스의 처음 시작
	FILE *fp;
	LinkedList lp;
	Person rankPerson;
	void *np;
	char str[101] = { 0 };//랭크불러오기에서 이름잠시저장배열
						  //int end;//랭크불러오기에서 종료조건	
	int sScore = 0;//랭크불러오기에서 점수잠시저장배열
	int scoreRes;
	int res;
	srand((unsigned int)time(NULL)); //랜덤함수 seed값 초기화

	create(&lp);
	dataFileLoad(&lp);
	removeCursor();//커서 깜빡이 제거

	while (1)
	{
		startX = 28;
		box(startX);//처음에 박스가 보이기 위해
		startX = menu();
		system("cls");

		if (startX == 28) {//게임시작함수
			sScore = gamePlaying();
			startX = 48;
		}
		if (startX == 48)//랭크함수
		{
			if (sScore > 0)
			{
				fp = fileOpen("c://data//tetrisRanking.txt", "at");
				assert(fp != NULL);
				rankPerson.score = sScore;
				gotoxy(40, 10);//열, 행
				printf("┏━━━━━━━━━━━━━━━━━━━━━┓\n");
				gotoxy(40, 11);//열, 행
				printf("  TOTAL SCORE : %-8d YOUR NAME :           \n", rankPerson.score);
				gotoxy(40, 12);//열, 행
				printf("┗━━━━━━━━━━━━━━━━━━━━━┛");
				gotoxy(76, 11);//열, 행
				input(str);
				//scanf("%s", str);
				printf("\n");

				rankPerson.name = str;
				np = linearSearchUnique(&lp, &rankPerson, personNameCompare);
				//찾은 노드의 주소 리턴
				if (np == NULL)
				{
					fprintf(fp, "%s %d\n", rankPerson.name, rankPerson.score);
					appendFromTail(&lp, &rankPerson, sizeof(Person), personMemCpy);
				}
				else//중복단어 찾으면,
				{
					res = personScoreCompare((Person *)np + 1, &rankPerson);
					if (res > 0)
					{//새로받은 게 크면
						((Person *)np + 1)->score = sScore;
						fp = fileOpen("c://data//tetrisRanking.txt", "wt");

						lp.cur = lp.head->next;
						while (lp.cur != lp.tail)
						{
							fprintf(fp, "%s %d\n", ((Person *)lp.cur + 1)->name, ((Person *)lp.cur + 1)->score);
							lp.cur = lp.cur->next;
						}
					}
				}
				fclose(fp);
			}
				sortList(&lp, sizeof(Person), personScoreCompare, personMemCpy, personClear);

				system("cls");
			
			gotoxy(35, 5);//열, 행
			printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓\n");
			scoreRes = scorePrint(&lp, str);
			gotoxy(35, 6 + scoreRes);//열, 행
			printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
			printf("\t\t\t\t\tpress any key to return\n");
			getch();
			system("cls");
			sScore = 0;
			//랭크함수
		}
		else
		{
			destroy(&lp, personClear);
			break;
		}
	}
	return 0;
}

void input(char * str)
{
	int i = 0;
	int length = 8;
	char c;
	while (1)
	{
		if (i == length + 1)printf("\b ");
		gotoxy(76 + i, 11);
		if (i <= length)
			c = getche();
		else {
			c = getch();
			printf("\b ");
		}

		str[i] = c;

		if (i <= length && c != 8) { i++; }
		else {

			if (c == 8 && i != 0)
			{
				printf(" ");
				i--; if (i <1)i = 0;
			}
		}
		if (c == 13)break;
	}
	str[i - 1] = '\0';
	gotoxy(30, 30);
}

int scorePrint(LinkedList *lp, char *str)
{
	Node *np;
	int i, j = 0;
	//if (lp->length == 0)return i;
	np = lp->head->next;
	for (i = 0; i < lp->length; i++)
	{

		gotoxy(35, 6 + i);
		printf("┃  ID : ");
		textcolor(LIGHTBLUE + j, BLACK);
		if (strcmp(((Person *)np + 1)->name, str) == 0)textcolor(13, BLACK);
		gotoxy(45, 6 + i);
		printf("%-20s", ((Person *)np + 1)->name);
		gotoxy(55, 6 + i);
		textcolor(LIGHTGRAY, BLACK);
		printf("Score : ");
		gotoxy(65, 6 + i);
		textcolor(LIGHTBLUE + j, BLACK);
		if (strcmp(((Person *)np + 1)->name, str) == 0)textcolor(13, BLACK);
		printf("%-10d", ((Person *)np + 1)->score);
		gotoxy(83, 6 + i);
		textcolor(LIGHTGRAY, BLACK);
		printf("┃\n");
		np = np->next;
		if (j < 2) { j++; }
		else
			j = 6;
	}
	return i;
}

void dataFileLoad(LinkedList *lp) // 데이터 파일내의 데이터를 리스트에 저장 
{
	FILE *fp;
	Person inData; //DataType은 Person 구조체 타입
	char name[20];

	fp = fopen("c:\\data\\tetrisRanking.txt", "rt");
	assert(fp != NULL);

	while (fscanf(fp, "%s", name) != EOF) //inData는 완벽한 데이터가 들어와야함
	{
		inData.name = (char *)malloc(sizeof(char)*strlen(name) + 1);
		assert(inData.name != NULL);

		fscanf(fp, "%d", &inData.score); //나이를 읽어옴

		strcpy(inData.name, name);

		appendFromHead(lp, &inData, sizeof(Person), personMemCpy); //lp는 링크드리스트 관리구조체, inData의 시작주소를 보냄
																   //appendFromTail(lp, &inData);

		free(inData.name);
	}
	fclose(fp); //파일 닫기! 
				//tail노드 앞에 노드가 생김
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
	if (ascii == -32 || ascii == 0) { // 입력된 문자의 아스키코드가 -32이거나 0이면 특수키가 입력된것임 
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

int gamePlaying() {
	CTetris cte; //Color Tetris
	char ch;//사용자로부터 키보드입력 임시저장 변수
	int kFlag;//inKey()로부터 kFlag리턴
	time_t ePrev , eCur; //eraseDisplay timer 
	int moved = 1; //move가 일어나면
	int pause = 0; //pause 발생시
	int gFlag = 1; //ghost on off
	int eLines = 0; //moveDown, spaceMove에서 지워진 라인 수나 레벨업을 표시
	int eSaved = 0; //saved lines elecDisplay parameter
	int eFlag = 0; //erese display 시작과 동시에 켜지고 diplay 이후 꺼짐
	clock_t start, finish, delay; //Level 관련 변수
	int level = 1; //게임의 레벨
	int maxLevel = 10; //최대게임레벨
	int levTerm = 150; //레벨당 달성목표
	delay = 1000; //레벨 1의 delay

	CinitGame(&cte);
	cte.tetris.nextBlock = rand() % BLOCK_NUM; //최초 NextBlock 생성 CreateBlock의 Precondition
	cte.tetris.gameState = PLAYING;
	system("cls");
	backGroundDisplay(&cte, gameStartX, gameStartY);
	gotoxy(gameStartX+5,gameStartY+4);
	printf("Game Start!!!!");
	gotoxy(gameStartX+5,gameStartY+5);
	printf("Press Any Key");
	getch();
	//최초블럭 생성
	createBlock(&cte.tetris);
	pasteBlock(cte.tetris.boPlusbl, block[cte.tetris.whichBlock][cte.tetris.blockState], cte.tetris.x, cte.tetris.y);
	CblockColoring(cte.cBlock,block[cte.tetris.whichBlock][cte.tetris.blockState],cte.tetris.whichBlock+2);
	pasteBlock(cte.CboPlusbl, cte.cBlock, cte.tetris.x, cte.tetris.y);
	start = clock(); //timer start
	while (cte.tetris.gameState) {
		if (moved) { //이동이 일어나면 display
			if(level - 1 != (cte.tetris.score / levTerm)){ if(level < maxLevel) level++; eLines = 5;} //레벨업도 전광판 표시
			if(gFlag) CmakeGhost(&cte);
			gameDisplay(&cte, gameStartX + 2, gameStartY);
			nextBlockDisplay(&cte, gameStartX + 5, gameStartY + 1);
			if(eFlag == 0 && (eLines >= 2)){
				time(&ePrev); //display start
				eFlag = 1; //eraseDisplay Start
				eSaved = eLines;
			}
			if(eFlag && (ePrev == time(&eCur))){ elecDisplay(eSaved,gameStartX + 6 , gameStartY + 5);} //약 1초동안 표시
			else { eFlag = 0; eSaved = 0;} //원래대로 돌려놓음
			sideDisplay(cte.tetris.score, level,gameStartX, gameStartY);
			moved = 0; //다음번 루프때 다시 출력하지 않도록 수정
		}
		if (!kbhit()) {
			finish = clock();
			if(!pause){
				if (finish - start >= (delay - (level - 1) * 100)) { //
					moved = 1; eLines = CmoveDown(&cte);
					start = finish; //이전시간을 현재시간으로 초기화
				}
			}
		}
		else {
			ch = inKey(&kFlag);//kFlag 가 상태를 나타냄(특수키다 일반키다 구분 상태 여부)
			switch (ch) {
			case LEFT_ARROW:if(!pause) moved = CmoveLeft(&cte); break;
			case RIGHT_ARROW:if(!pause) moved = CmoveRight(&cte); break;
			case UP_ARROW:if(!pause) moved = Crotate(&cte); break;
			case DOWN_ARROW:if(!pause) moved = 1; eLines = CmoveDown(&cte); break;
			case SPACE:if(!pause) moved = 1; eLines = CspaceMove(&cte); break;
			case 'p': if(pause == 0) pause = 1; //pause flag
					  else if(pause == 1) {pause = 0; start = clock(); } //pause 해제와 함께 time재시작
					  break;
			case 'g': if(gFlag == 0) gFlag = 1; //ghost flag
					  else gFlag = 0;
					  break;
			case ESC: cte.tetris.gameState = GAME_OVER; break;
			}
		}
	}

	//while루프 탈출, GameOver
	gameDisplay(&cte, gameStartX + 2, gameStartY);
	gotoxy(gameStartX+4,gameStartY+7);
	printf("You Scored : %d",cte.tetris.score);
	gotoxy(gameStartX+5,gameStartY+8);
	printf("Press Any Key");
	CgameOver(&cte); //tetris structure에 동적할당된 메모리 초기화및 값들 초기화
	getch();
	system("cls");
	//점수입력란

	return cte.tetris.score;
}

void removeCursor(void)

{

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

}

void gameDisplay(CTetris * cte, int startX, int startY)
{
	gotoxy(startX, startY);
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		gotoxy(startX, startY + i);
		for (int j = 0; j <BOARD_WIDTH; j++)
		{
			switch (cte->CboPlusbl[i][WALLSIZE + j])
			{
			case 0: printf("  "); break;
			case 1:textcolor(15, 7); printf("□"); textcolor( 15, 0); break;
			case 2:textcolor(15, 4); printf("■"); textcolor(15, 0); break;
			case 3:textcolor(15, 6); printf("■"); textcolor(15, 0); break;
			case 4:textcolor(15, 14); printf("■"); textcolor(15, 0); break;
			case 5:textcolor(15, 2); printf("■"); textcolor(15, 0); break;
			case 6:textcolor(15, 1); printf("■"); textcolor(15, 0); break;
			case 7:textcolor(15, 5); printf("■"); textcolor(15, 0); break;
			case 8:textcolor(15, 3); printf("■"); textcolor(15, 0); break;
			default: textcolor(15, 3); printf("■"); textcolor(15, 0); break;
			}
		}
		//빨 주 노 초 파 남 보
		//4  6  14  2  1  5  3
		//12 8 14  10  9  13  11


		printf("\n");
	}
}

void nextBlockDisplay(CTetris* cte, int startX, int startY)
{
	CblockColoring(cte->cBlock,block[cte->tetris.nextBlock][0],cte->tetris.nextBlock+2);//cte 의 Cblock을 Coloring
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 2);
	for (int i = 0; i<BLOCK_WIDTH; i++) {
		gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 2 + i);
		for (int j = 0; j < BLOCK_HEIGHT; j++) {
			switch (cte->cBlock[i][j])
			{
			case 1:printf("■"); break;
			case 2:textcolor(15, 4); printf("■"); textcolor(15, 0); break;
			case 3:textcolor(15, 6); printf("■"); textcolor(15, 0); break;
			case 4:textcolor(15, 14); printf("■"); textcolor(15, 0); break;
			case 5:textcolor(15, 2); printf("■"); textcolor(15, 0); break;
			case 6:textcolor(15, 1); printf("■"); textcolor(15, 0); break;
			case 7:textcolor(15, 5); printf("■"); textcolor(15, 0); break;
			case 8:textcolor(15, 3); printf("■"); textcolor(15, 0); break;
			default: printf("  ");
			}
		}
	}
}

void backGroundDisplay(CTetris* cte, int startX, int startY)
{
	gotoxy(startX, startY);
	for (int i = 0; i < BOARD_HEIGHT + 1; i++) {
		for (int j = WALLSIZE - 1; j < BOARD_WIDTH + WALLSIZE + 1; j++) {
			if (cte->CboPlusbl[i][j] == 1) {
				printf("▤");
			}
			else if (cte->CboPlusbl[i][j] == 2) printf("★");
			else printf("  ");
		}
		printf("\n");
	}
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 2); printf("+-  N E X T  -+ ");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 3); printf("|             | ");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 4); printf("|             | ");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 5); printf("|             | ");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 6); printf("|             | ");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 7); printf("+-- -  -  - --+ ");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 8); printf(" YOUR SCORE :");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 9); printf("        %6d", cte->tetris.score); //현재 스코어
																								  //   gotoxy(startX + 2*(BOARD_WIDTH +4), startY+10); printf(" LAST SCORE :");     
																								  //  gotoxy(startX + 2*(BOARD_WIDTH +4), startY+11); printf("        %6d", 2345); //직전 스코어
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 12); printf(" Level :");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 15); printf("  △   : Shift        SPACE : Hard Drop");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 16); printf("◁  ▷ : Left / Right   P   : Pause    ESC  : Quit");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 17); printf("  ▽   : Soft Drop      G : Ghost on/off");
}

void sideDisplay(int currentScore, int level,int startX, int startY)
{
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 9); printf("        %6d", currentScore); //현재 스코어
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 13); printf("        %6d", level); //현재 스코어
}

//전광판
void elecDisplay(int lines, int startX, int startY)
{
	switch(lines){
	case 2: textcolor(9, 0); gotoxy(startX,startY); printf("＊Double＊"); break;
	case 3:textcolor(10, 0); gotoxy(startX - 1,startY); printf("☆☆Triple☆☆");break;
	case 4:textcolor(14, 0); gotoxy(startX - 3,startY); printf("★★★Tetris★★★");break;
	case 5: textcolor(12, 0); gotoxy(startX - 1,startY); printf("△Level up△");break; 
	}
	textcolor(15, 0);
}