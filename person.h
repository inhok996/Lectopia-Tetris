#pragma once
#pragma warning(disable : 4996)
#include <string.h>
#include <malloc.h>
#include <stdio.h>

typedef struct _person
{
	char *name;
	int score;
}Person;
//typedef Person DataType;
//Person ����ü ���� �Լ�
void personMemCpy(void *p1, void *p2);
void personClear(void *p); //�ȿ� �ִ� ���� ���� ����� -> �޸� ���� -> NULL, 0, ""������ ǥ��
void personPrint(void *p);
int personNameCompare(void *p1, void *p2);
int personScoreCompare(void *p1, void *p2);
int personCompare(void *p1, void *p2);