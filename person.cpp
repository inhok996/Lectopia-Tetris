#include "person.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void personMemCpy(void *p1, void *p2)
{
	char str[100];
	strcpy(str, ((Person *)p2)->name);
	strcpy(((Person *)p1)->name, str);
	((Person *)p1)->score = ((Person *)p2)->score;
	return;
//	personClear(p1); //name 멤버의 메모리 해제
//	if (((Person *)p2)->name != NULL)
//	{
//		((Person )p1)->name = (char *)calloc(strlen(((Person *)p2)->name) + 1, sizeof(char));
//		//p2로 해야한다!! p1의 name을 구해버리면 os 메모리 구하다가 프로세스킬당함, NULL문자 +1해야
//		strcpy(((Person*)p1)->name, ((Person *)p2)->name);
//	}
//	((Person *)p1)->score = ((Person *)p2)->score;
//	return;
}
void personClear(void *p) //안에 있던 내용 전부 지우고 -> 메모리 해제 -> NULL, 0, ""등으로 표시
{
	/*if (((Person *)p)->name != NULL)
		free(((Person *)p)->name);
	((Person *)p)->name = 0;*/
	return;
}
void personPrint(void *p)
{
	printf("\n\n\n\t\t성명 : %-20s 점수 : %d\n", ((Person *)p)->name, ((Person *)p)->score);
	printf("\n");
}
int personNameCompare(void *p1, void *p2)//이름 같으면 저장 못하게
{
	int res, rr;
	res = strcmp(((Person *)p1)->name, ((Person *)p2)->name);
	if (res > 0) rr = 1;
	else if (res == 0) rr = 0;
	else rr = -1;

	return rr;
}
int personScoreCompare(void *p1, void *p2)
{

	if (((Person *)p1)->score > ((Person *)p2)->score) return 1;
	else if (((Person *)p1)->score == ((Person *)p2)->score) return 0;
	else return -1;
}
int personCompare(void *p1, void *p2)//쓰지 않아
{
	if (strcmp(((Person *)p1)->name, ((Person *)p2)->name) == 0)
	{
		if (((Person *)p1)->score == ((Person *)p2)->score)	return 0;
		else return -1;
	}
}