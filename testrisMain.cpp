#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h> //random �Լ�
#include <time.h> //time �Լ�
#include "linkedList.h"
#include "person.h"
#include "Tetris.h"
//#include "CTetris.h"
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

void backGroundDisplay(int startX, int startY);
void BlockDisplay(Tetris * te);
void removeCursor(void); //Ŀ�������� ����


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
	Node *np;
	char str[101] = { 0 };//��ũ�ҷ����⿡�� �̸��������迭
	//int end;//��ũ�ҷ����⿡�� ��������	
	int sScore = 0;//��ũ�ҷ����⿡�� �����������迭
	int scoreRes;
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

		if (startX == 28){//���ӽ����Լ�
			sScore = gamePlaying();		
			startX = 48;
		}
		if (startX == 48)//��ũ�Լ�
		{ 
			if (sScore>0) 
			{
				fp = fileOpen("c://data//tetrisRanking.txt", "at");
				assert(fp != NULL);
				rankPerson.score = sScore;
				gotoxy(40, 10);//��, ��
				printf("����������������������������������������������\n");
				gotoxy(40, 11);//��, ��
				printf("  TOTAL SCORE : %-8d YOUR NAME :           \n");
				gotoxy(40, 12);//��, ��
				printf("����������������������������������������������");
				gotoxy(76, 11);//��, ��
				scanf("%s", str);
				printf("\n");

				rankPerson.name = str;
				//strcpy(rankPerson.name, str);
				fprintf(fp, "%s %d\n", rankPerson.name, rankPerson.score);
				fclose(fp);
				np = linearSearchUnique(&lp, &rankPerson, personNameCompare);
				if (np == NULL) appendFromTail(&lp, &rankPerson, sizeof(Person), personMemCpy);
				else//�ߺ��ܾ� ã����,
				{
					//npscore = rankPerson.score;
				}
			}
			sortList(&lp, sizeof(Person), personScoreCompare, personMemCpy, personClear);

			system("cls");
			gotoxy(35, 5);//��, ��
			printf("��������������������������������������������������\n");		
			scoreRes = scorePrint(&lp, str);
			gotoxy(35, 6 + scoreRes);//��, ��
			printf("��������������������������������������������������\n");
			printf("�������� �Ѿ���� �ƹ�key�� �����ÿ�");
			getch();
			system("cls");
			sScore = 0;
		}//��ũ�Լ�
		else
		{
			destroy(&lp, personClear);
			break;
		}
	}	
	return 0;
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
		printf("��  ���� : ");
		textcolor(LIGHTBLUE + j, BLACK);
		if (strcmp(((Person *)np + 1)->name, str) == 0)textcolor(13, BLACK);
		gotoxy(45, 6 + i);
		printf("%-20s", ((Person *)np + 1)->name);
		gotoxy(55, 6 + i);
		textcolor(LIGHTGRAY, BLACK);
		printf("���� : ");
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

int gamePlaying(){
	Tetris tetris;
	char ch;//����ڷκ��� Ű�����Է� �ӽ����� ����
	int kFlag;//inKey()�κ��� kFlag����
	time_t prev; //�ڵ����� �������� �ð��� ���ϱ� ����
	time_t cur; //����ð�
	int moved = 1; //move�� �Ͼ��

	initGame(&tetris);
	tetris.nextBlock = rand() % BLOCK_NUM; //���� NextBlock ���� CreateBlock�� Precondition
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
		if(moved){ //�̵��� �Ͼ��
			printBoard(tetris.boPlusbl); //����� ����ȭ�� ���
			moved = 0; //������ ������ �ٽ� ������� �ʵ��� ����
		}
		if(!kbhit()){
			time(&cur); //����ð��� ����
			if(cur != prev){ //1�ʴ���
				moved = moveDown(&tetris);
				prev = cur; //�����ð��� ����ð����� �ʱ�ȭ
			}
		}else{
			ch = inKey(&kFlag);//kFlag �� ���¸� ��Ÿ��(Ư��Ű�� �Ϲ�Ű�� ���� ���� ����)
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
	//while���� Ż��, GameOver
	gotoxy(1,1);
	printBoard(tetris.boPlusbl);
	//gotoxy(���߾�)
	printf("Game Over �ƹ�Ű�� �����ø� �޴��� ���ư��ϴ�\n"); //�����ؾ� ��
	gameOver(&tetris); //tetris structure�� �����Ҵ�� �޸� �ʱ�ȭ�� ���� �ʱ�ȭ
	getch();
	system("cls");
	//�����Է¶�
	return tetris.score;
}

void backGroundDisplay(int startX,int startY)
{
   //�� �� �� ���
	int i; //index
	gotoxy(startX, startY);
	printf("��");
	for(i = 0 ; i < BOARD_WIDTH+5 ; i++) printf("��");
	printf("��");
	for(i = startY ; i < BOARD_HEIGHT ; i++){
		gotoxy(startX, i+1);
		printf("��                              ��");
	}
	gotoxy(startX,i);
	printf("��");
	for(i = 0 ; i < BOARD_WIDTH+5 ; i++) printf("��");
	printf("��");
}

void BlockDisplay(Tetris * te)
{
   for(int i = 0; i< BLOCK_HEIGHT; i++)
   {
      gotoxy(2 ,te->y+i);
      for(int j = 0 ; j < BOARD_WIDTH ; j ++)
      {
         if(te->boPlusbl[i][j]==1)
            putchar('��');
         else if(te->boPlusbl[i][j]==0)
             putchar('��');
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