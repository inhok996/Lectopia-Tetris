#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h> //random �Լ�
#include <time.h> //time �Լ�
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
int gamePlaying();//���ӽ����Լ�
void textcolor(int foreground, int background);
int scorePrint(LinkedList *lp);
int menu();
void dataFileLoad(LinkedList *lp);
int scorePrint(LinkedList *lp, char *str);
//void fileSave();
void input(char * str);
void removeCursor(void); //Ŀ�������� ����
void gameDisplay(CTetris * cte, int startX, int startY);
void backGroundDisplay(CTetris* cte, int startX, int startY);
void nextBlockDisplay(CTetris* cte, int startX, int startY);
void scoreDisplay(int currentScore, int startX, int startY);


#define COMMON_KEY 1 
#define SPECIAL_KEY 0 
#define SPACE 32
#define UP_ARROW 72 
#define DOWN_ARROW 80 
#define LEFT_ARROW 75 
#define RIGHT_ARROW 77 
#define ENTER 13 //�Ϲ�Ű(getchar()�� �� 10, getch()�� �� 13 : '\r')
#define ESC 27 //�Ϲ�Ű
//��� �� �۲� ����
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
	//char ch;//����ڷκ��� Ű�����Է� �ӽ����� ����
	//int kFlag;//inKey()�κ��� kFlag����
	int startX = 28;//�����ڽ��� ó�� ����
	FILE *fp;
	LinkedList lp;
	Person rankPerson;
	void *np;
	char str[101] = { 0 };//��ũ�ҷ����⿡�� �̸��������迭
						  //int end;//��ũ�ҷ����⿡�� ��������	
	int sScore = 0;//��ũ�ҷ����⿡�� �����������迭
	int scoreRes;
	int res;
	srand((unsigned int)time(NULL)); //�����Լ� seed�� �ʱ�ȭ

	create(&lp);
	dataFileLoad(&lp);
	removeCursor();//Ŀ�� ������ ����

	while (1)
	{
		startX = 28;
		box(startX);//ó���� �ڽ��� ���̱� ����
		startX = menu();
		system("cls");

		if (startX == 28) {//���ӽ����Լ�
			sScore = gamePlaying();
			startX = 48;
		}
		if (startX == 48)//��ũ�Լ�
		{
			if (sScore > 0)
			{
				fp = fileOpen("c://data//tetrisRanking.txt", "at");
				assert(fp != NULL);
				rankPerson.score = sScore;
				gotoxy(40, 10);//��, ��
				printf("����������������������������������������������\n");
				gotoxy(40, 11);//��, ��
				printf("  TOTAL SCORE : %-8d YOUR NAME :           \n", rankPerson.score);
				gotoxy(40, 12);//��, ��
				printf("����������������������������������������������");
				gotoxy(76, 11);//��, ��
				input(str);
				//scanf("%s", str);
				printf("\n");

				rankPerson.name = str;
				np = linearSearchUnique(&lp, &rankPerson, personNameCompare);
				//ã�� ����� �ּ� ����
				if (np == NULL)
				{
					fprintf(fp, "%s %d\n", rankPerson.name, rankPerson.score);
					appendFromTail(&lp, &rankPerson, sizeof(Person), personMemCpy);
				}
				else//�ߺ��ܾ� ã����,
				{
					res = personScoreCompare((Person *)np + 1, &rankPerson);
					if (res > 0)
					{//���ι��� �� ũ��
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
			
			gotoxy(35, 5);//��, ��
			printf("��������������������������������������������������\n");
			scoreRes = scorePrint(&lp, str);
			gotoxy(35, 6 + scoreRes);//��, ��
			printf("��������������������������������������������������\n");
			printf("\t\t\t\t\tpress any key to return\n");
			getch();
			system("cls");
			sScore = 0;
			//��ũ�Լ�
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
		printf("��  ID : ");
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
		printf("��\n");
		np = np->next;
		if (j < 2) { j++; }
		else
			j = 6;
	}
	return i;
}

void dataFileLoad(LinkedList *lp) // ������ ���ϳ��� �����͸� ����Ʈ�� ���� 
{
	FILE *fp;
	Person inData; //DataType�� Person ����ü Ÿ��
	char name[20];

	fp = fopen("c:\\data\\tetrisRanking.txt", "rt");
	assert(fp != NULL);

	while (fscanf(fp, "%s", name) != EOF) //inData�� �Ϻ��� �����Ͱ� ���;���
	{
		inData.name = (char *)malloc(sizeof(char)*strlen(name) + 1);
		assert(inData.name != NULL);

		fscanf(fp, "%d", &inData.score); //���̸� �о��

		strcpy(inData.name, name);

		appendFromHead(lp, &inData, sizeof(Person), personMemCpy); //lp�� ��ũ�帮��Ʈ ��������ü, inData�� �����ּҸ� ����
																   //appendFromTail(lp, &inData);

		free(inData.name);
	}
	fclose(fp); //���� �ݱ�! 
				//tail��� �տ� ��尡 ����
}

int menu()
{
	char ch;//����ڷκ��� Ű�����Է� �ӽ����� ����
	int kFlag;//inKey()�κ��� kFlag����
	int startX = 28;

	while (1)
	{
		if (kbhit())
		{
			ch = inKey(&kFlag);//kFlag �� ���¸� ��Ÿ��(Ư��Ű�� �Ϲ�Ű�� ���� ���� ����)
			if (ch == ENTER) break;
			else if (ch == LEFT_ARROW)//����Ű�� ������Ű�� ����
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
		printf("��������������");
		gotoxy(30, 12);
		printf("�� ���� ���ۦ�");
		gotoxy(30, 13);
		printf("��������������");
		gotoxy(50, 11);
		printf("��������������");
		gotoxy(50, 12);
		printf("�� ��ũ��� ��");
		gotoxy(50, 13);
		printf("��������������");
		gotoxy(70, 11);
		printf("��������������");
		gotoxy(70, 12);
		printf("�� �������� ��");
		gotoxy(70, 13);
		printf("��������������");

		Sleep(100);
	}
	return startX;
}


char inKey(int *keyFlag)
{
	char ascii, scan;

	ascii = getch(); // �Էµ� ������ �ƽ�Ű�ڵ带 �Է¹޾ƿ� 
	if (ascii == -32 || ascii == 0) { // �Էµ� ������ �ƽ�Ű�ڵ尡 -32�̰ų� 0�̸� Ư��Ű�� �ԷµȰ��� 
		scan = getch(); // Ư��Ű�� �ԷµǾ��������� scan code���� �Է¹޾ƿ� (�ϵ����� �����ϴ� Ű���� ���ۿ� �����ִ�, �װ� �޾ƿ� <>stdin)
		*keyFlag = SPECIAL_KEY;
		return (scan);//�ƽ�Ű�ڵ带 �����ϴ� ���� �ǹ� �����Ƿ� scan�ڵ� ����
	}
	else { // �Ϲ�Ű�� �ԷµǾ����� 
		*keyFlag = COMMON_KEY;
		return (ascii);
	}
	// getch()�Լ��� Ư��Ű�� �Է¹����� Ascii, Scan code�� ���α׷� ���� ������, 
	// getch()�Լ��� �Ϲ�Ű�� �Է¹����� �׳� Ascii code�� ���α׷� ���� ������ �˴ϴ�. 
	// �����ϼ���~	
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//box() : main()���� �־ �ȴ�. -> ����� ���� �ڽ� �ű��
//�������� : startX
void box(int startX)
{
	textcolor(LIGHTRED, BLACK);
	gotoxy(startX, 10);
	printf("������������������");
	gotoxy(startX, 11);
	printf("��              ��");
	gotoxy(startX, 12);
	printf("��              ��");
	gotoxy(startX, 13);
	printf("��              ��");
	gotoxy(startX, 14);
	printf("������������������");

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
	int color = foreground + background * 16;//foreground ���ڻ�, background ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int gamePlaying() {
	CTetris cte;
	char ch;//����ڷκ��� Ű�����Է� �ӽ����� ����
	int kFlag;//inKey()�κ��� kFlag����
	time_t prev; //�ڵ����� �������� �ð��� ���ϱ� ����
	time_t cur; //����ð�
	int moved = 1; //move�� �Ͼ��
	int pause = 0; //pause �߻���

	CinitGame(&cte);
	cte.tetris.nextBlock = rand() % BLOCK_NUM; //���� NextBlock ���� CreateBlock�� Precondition
	system("cls");
	//backGroundDisplay(3,1);
	printf("Game Start!!!! Press Any Key\n");
	getch();
	cte.tetris.gameState = PLAYING;
	system("cls");
	time(&prev);
	backGroundDisplay(&cte, gameStartX, gameStartY);
	createBlock(&cte.tetris);
	pasteBlock(cte.tetris.boPlusbl, block[cte.tetris.whichBlock][cte.tetris.blockState], cte.tetris.x, cte.tetris.y);
	CblockColoring(&cte);
	pasteBlock(cte.CboPlusbl, cte.cBlock, cte.tetris.x, cte.tetris.y);
	while (cte.tetris.gameState) {
		if (moved) { //�̵��� �Ͼ��
			CmakeGhost(&cte);
			gameDisplay(&cte, gameStartX + 2, gameStartY);
			nextBlockDisplay(&cte, gameStartX + 5, gameStartY + 1);
			scoreDisplay(cte.tetris.score, gameStartX, gameStartY);
			moved = 0; //������ ������ �ٽ� ������� �ʵ��� ����
		}
		if (!kbhit()) {
			time(&cur); //����ð��� ����
			if(!pause){
			if (cur != prev) { //1�ʴ���
				moved = CmoveDown(&cte);
				prev = cur; //�����ð��� ����ð����� �ʱ�ȭ
			}
			}
		}
		else {
			ch = inKey(&kFlag);//kFlag �� ���¸� ��Ÿ��(Ư��Ű�� �Ϲ�Ű�� ���� ���� ����)
			switch (ch) {
			case LEFT_ARROW:if(!pause) moved = CmoveLeft(&cte); break;
			case RIGHT_ARROW:if(!pause) moved = CmoveRight(&cte); break;
			case UP_ARROW:if(!pause) moved = Crotate(&cte); break;
			case DOWN_ARROW:if(!pause) moved = CmoveDown(&cte); break;
			case SPACE:if(!pause) moved = CspaceMove(&cte); break;
			case 'p': if(pause == 0){ pause =1; } 
					  else if(pause == 1) {pause = 0; time(&cur); prev = cur;}
					  break;
			case ESC: cte.tetris.gameState = GAME_OVER; break;

			}
		}
	}

	//while���� Ż��, GameOver
	gameDisplay(&cte, gameStartX + 2, gameStartY);
	//gotoxy(���߾�)
	printf("Game Over �ƹ�Ű�� �����ø� �޴��� ���ư��ϴ�\n"); //�����ؾ� ��
	CgameOver(&cte); //tetris structure�� �����Ҵ�� �޸� �ʱ�ȭ�� ���� �ʱ�ȭ
	getch();
	system("cls");
	//�����Է¶�

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
			case 1:textcolor(15, 7); printf("��"); textcolor( 15, 0); break;
			case 2:textcolor(15, 4); printf("��"); textcolor(15, 0); break;
			case 3:textcolor(15, 6); printf("��"); textcolor(15, 0); break;
			case 4:textcolor(15, 14); printf("��"); textcolor(15, 0); break;
			case 5:textcolor(15, 2); printf("��"); textcolor(15, 0); break;
			case 6:textcolor(15, 1); printf("��"); textcolor(15, 0); break;
			case 7:textcolor(15, 5); printf("��"); textcolor(15, 0); break;
			case 8:textcolor(15, 3); printf("��"); textcolor(15, 0); break;
			default: textcolor(15, 3); printf("��"); textcolor(15, 0); break;
			}
		}
		//�� �� �� �� �� �� ��
		//4  6  14  2  1  5  3
		//12 8 14  10  9  13  11


		printf("\n");
	}
}

void nextBlockDisplay(CTetris* cte, int startX, int startY)
{
	block[cte->tetris.nextBlock][0];
	int tempBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			tempBlock[i][j] = block[cte->tetris.nextBlock][0][i][j];
			if (tempBlock[i][j] == 1) cte->cBlock[i][j] = cte->tetris.nextBlock + 2;//ù��°������ 2������ Coloring��
																					//printf("%d",cte->cBlock[i][j]);
		}
		//printf("\n");
		//getch();
	}

	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 2);
	for (int i = 0; i<BLOCK_WIDTH; i++) {
		gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 2 + i);
		for (int j = 0; j < BLOCK_HEIGHT; j++) {
			switch (tempBlock[i][j])
			{
			case 1:printf("��"); break;
			case 2:textcolor(15, 4); printf("��"); textcolor(15, 0); break;
			case 3:textcolor(15, 6); printf("��"); textcolor(15, 0); break;
			case 4:textcolor(15, 14); printf("��"); textcolor(15, 0); break;
			case 5:textcolor(15, 2); printf("��"); textcolor(15, 0); break;
			case 6:textcolor(15, 1); printf("��"); textcolor(15, 0); break;
			case 7:textcolor(15, 5); printf("��"); textcolor(15, 0); break;
			case 8:textcolor(15, 3); printf("��"); textcolor(15, 0); break;
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
				printf("��");
			}
			else if (cte->CboPlusbl[i][j] == 2) printf("��");
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
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 9); printf("        %6d", cte->tetris.score); //���� ���ھ�
																								  //   gotoxy(startX + 2*(BOARD_WIDTH +4), startY+10); printf(" LAST SCORE :");     
																								  //  gotoxy(startX + 2*(BOARD_WIDTH +4), startY+11); printf("        %6d", 2345); //���� ���ھ�
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 12); printf(" BEST SCORE :");
	//gotoxy(startX + 2*(BOARD_WIDTH +4), startY+13); printf("        %6d", 345); //��ŷ 1�� ���ھ�    
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 15); printf("  ��   : Shift        SPACE : Hard Drop");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 16); printf("��  �� : Left / Right   P   : Pause");
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 17); printf("  ��   : Soft Drop     ESC  : Quit");
}

void scoreDisplay(int currentScore, int startX, int startY)
{
	gotoxy(startX + 2 * (BOARD_WIDTH + 4), startY + 9); printf("        %6d", currentScore); //���� ���ھ�
}