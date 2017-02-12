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
//	personClear(p1); //name ����� �޸� ����
//	if (((Person *)p2)->name != NULL)
//	{
//		((Person )p1)->name = (char *)calloc(strlen(((Person *)p2)->name) + 1, sizeof(char));
//		//p2�� �ؾ��Ѵ�!! p1�� name�� ���ع����� os �޸� ���ϴٰ� ���μ���ų����, NULL���� +1�ؾ�
//		strcpy(((Person*)p1)->name, ((Person *)p2)->name);
//	}
//	((Person *)p1)->score = ((Person *)p2)->score;
//	return;
}
void personClear(void *p) //�ȿ� �ִ� ���� ���� ����� -> �޸� ���� -> NULL, 0, ""������ ǥ��
{
	/*if (((Person *)p)->name != NULL)
		free(((Person *)p)->name);
	((Person *)p)->name = 0;*/
	return;
}
void personPrint(void *p)
{
	printf("\n\n\n\t\t���� : %-20s ���� : %d\n", ((Person *)p)->name, ((Person *)p)->score);
	printf("\n");
}
int personNameCompare(void *p1, void *p2)//�̸� ������ ���� ���ϰ�
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
int personCompare(void *p1, void *p2)//���� �ʾ�
{
	if (strcmp(((Person *)p1)->name, ((Person *)p2)->name) == 0)
	{
		if (((Person *)p1)->score == ((Person *)p2)->score)	return 0;
		else return -1;
	}
}