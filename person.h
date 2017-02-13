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
//Person 구조체 보조 함수
void personMemCpy(void *p1, void *p2);
void personClear(void *p); //안에 있던 내용 전부 지우고 -> 메모리 해제 -> NULL, 0, ""등으로 표시
void personPrint(void *p);
int personNameCompare(void *p1, void *p2);
int personScoreCompare(void *p1, void *p2);
int personCompare(void *p1, void *p2);