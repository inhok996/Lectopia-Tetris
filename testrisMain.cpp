#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include <assert.h>
#include <stdlib.h> //random �Լ�
#include <time.h> //time �Լ�
#include "linkedList.h"
#include "person.h"
#include "Tetris.h"
#pragma warning (disable:4996)
FILE * fileOpen(char *filename, char *mode);
void gotoxy(int x, int y);
char inKey(int *keyFlag);
void box(int startX);
void gamePlaying();//���ӽ����Լ�
void textcolor(int foreground, int background);
int menu();
//void fileSave();

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
	char ch;//����ڷκ��� Ű�����Է� �ӽ����� ����
	int kFlag;//inKey()�κ��� kFlag����
	int startX = 28;//�����ڽ��� ó�� ����
	FILE *fp;
	LinkedList lp;
	Person rankPerson;
	char str[101];//��ũ�ҷ����⿡�� �̸��������迭
	int end;//��ũ�ҷ����⿡�� ��������	
	int sScore;//��ũ�ҷ����⿡�� �����������迭
	srand((unsigned int)time(NULL)); //�����Լ� seed�� �ʱ�ȭ
	create(&lp);
	
	while (1)
	{
		box(startX);//ó���� �ڽ��� ���̱� ����
		startX = menu();
		system("cls");

		if (startX == 28){//���ӽ����Լ�
			gamePlaying();
		}
		else if (startX == 48)
		{ 
			fp = fileOpen("c://data//tetrisRanking.txt", "rt");
			assert(fp != NULL);
			//printf("1");
			while (1){
				end = fscanf(fp, "%s", str);
				fscanf(fp, "%d", &sScore);//fgets(0���� �ؾ��ұ�
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
		}//��ũ�Լ�
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
	if (ascii == -32 || ascii == 0){ // �Էµ� ������ �ƽ�Ű�ڵ尡 -32�̰ų� 0�̸� Ư��Ű�� �ԷµȰ��� 
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

void gamePlaying(){

	Tetris tetris;
	char ch;//����ڷκ��� Ű�����Է� �ӽ����� ����
	int kFlag;//inKey()�κ��� kFlag����

	initGame(&tetris);
	createBlock(&tetris);
	pasteBlock(tetris.boPlusbl,block[tetris.whichBlock][tetris.blockState],tetris.x,tetris.y);
	system("cls");
	printf("Game Start!!!! Press Any Key\n");
	getch();
	tetris.gameState = PLAYING;
	system("cls");
	while(tetris.gameState){
		system("cls");
		printBoard(tetris.boPlusbl);
		ch = inKey(&kFlag);//kFlag �� ���¸� ��Ÿ��(Ư��Ű�� �Ϲ�Ű�� ���� ���� ����)
		switch(ch){
		case LEFT_ARROW:moveLeft(&tetris); break;
		case RIGHT_ARROW:moveRight(&tetris); break;
		case UP_ARROW: rotate(&tetris); break;
		case DOWN_ARROW: moveDown(&tetris); break;
		case SPACE: spaceMove(&tetris); break;
		case ESC: break;
		}
	}
}
