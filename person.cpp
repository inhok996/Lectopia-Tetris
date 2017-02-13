/*
* person.cpp
*
*  Created on: 2017. 2. 7.
*      Author: sky93
*/
#include "person.h"

void personMemCpy(void *p1, void *p2) //if문 하나로 수정가능, free를 맨 앞에
{
	if (((Person *)p1)->name == NULL && ((Person *)p2)->name != NULL)
	{
		((Person *)p1)->name = (char *)malloc(sizeof(char) * strlen(((Person *)p2)->name) + 1);
		//(char *)calloc(strlen(((Person*)p2)->name)+1, sizeof(char));
		strcpy(((Person *)p1)->name, ((Person *)p2)->name);
	}
	else if (((Person *)p1)->name != NULL && ((Person *)p2)->name == NULL)
	{
		free(((Person *)p1)->name);
		((Person *)p1)->name = NULL;
	}
	else if (((Person *)p1)->name == NULL && ((Person *)p2)->name == NULL);
	else
	{
		free(((Person *)p1)->name);
		((Person *)p1)->name = (char *)malloc(sizeof(char) * strlen(((Person *)p2)->name) + 1);
		strcpy(((Person *)p1)->name, ((Person *)p2)->name);
	}

	((Person *)p1)->score = ((Person *)p2)->score;
}

void personClear(void *p)
{
	if (((Person *)p)->name != NULL) {
		memset(((Person*)p)->name, 0, strlen(((Person*)p)->name));
		free(((Person*)p)->name);
		((Person*)p)->name = NULL;
	}
	((Person*)p)->score = 0;

	return;
}
void personPrint(void *p)
{
	printf("┃  성명 : %-20s점수 : %-4d┃\n", ((Person*)p)->name, ((Person*)p)->score);
}
int personNameCompare(void *p1, void *p2)
{
	return strcmp(((Person*)p1)->name, ((Person*)p2)->name);
}
int personScoreCompare(void *p1, void *p2)
{
	
	if (((Person*)p1)->score < ((Person*)p2)->score)
		return 1;
	else if (((Person*)p1)->score == ((Person*)p1)->score)
		return 0;
	else
		return -1;
}
int personComapare(void *p1, void *p2)
{
	if (personNameCompare(p1, p2) == 0 && personScoreCompare(p1, p2) == 0)
		return 0;
	else
		return -1;
}
