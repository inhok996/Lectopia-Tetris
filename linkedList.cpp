#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedList.h"
//���׸��ڵ�Ƿ� Person�� ���� �ȵ�!!
void create(LinkedList *linkedList)
{
	//�ݵ�� calloc �޸� �Ҵ��ؾߵ�!!
	linkedList->head = (Node *)calloc(1, sizeof(Node));//Head Node ���� , �������� 2��, sizeof(Node) = 24Byte
	//main���� list�� �����Ѱ��� ���⼭�� ����Ҽ� ������ linkedList���
	linkedList->tail = (Node *)calloc(1, sizeof(Node));//tail Node ����
	//��ũ�帮��Ʈ�� ����� ���Ͽ� 1.2.3.4. �����ߵ�
	linkedList->head->prev = linkedList->head;//3.
	linkedList->head->next = linkedList->tail;//1. LV�� �������ִ°� �׹濡 �����Ͽ� �ű��� �ּҵ� ����(?)
	linkedList->tail->prev = linkedList->head;//2. �ּ� ����	
	linkedList->tail->next = linkedList->tail;//4.
	linkedList->length = 0;//linkedList�� ����Ű�� list�� lenght�� 0(data�� ���ִ� �氳���� ���� 0)
	linkedList->cur = NULL;//linkedList�� ����Ű�� list�� cur�� NULL pointer�� �ʱ�ȭ

	return;
}
Node * makeNode(void *item, Node *prev, Node *next, size_t size, void(*myMemCpy)(void *, void *))//�ڿ� 2�� Node pointer
{
	Node *np;

	np = (Node *)calloc(1, sizeof(Node) + size);//���⼭ ���� M�Ҵ�
	//calloc(���� �ʱ�ȭ��ų �� �Ѱ�, prev+next+���� ������ ������ ������ũ��)
	if (np == NULL) return NULL;//return np;�� ����. ���⼭ �̰��� ����� �׹ؿ��� ���� ����.
	//������ 1. 2. 3. 4.
	np->prev = prev;//1.
	np->next = next;//2.

	//������� 3�� : prev->next=list->cur;//���� ���⼭ list->cur ��� np�� ����
	//4�� : prev = list->cur;
	np->prev->next = np;//3.
	np->next->prev = np;//4. tailnode�� ������ �ȵ�. �ֳ��ϸ� appendFromHead������ ���Ǳ� ����.
	//������� ���� ����. ���� ������ �ʱ�ȭ�ؾ� ��.
	//np->data = *item;//bit copy�Ƿ� �ȵ�!!
	myMemCpy(np + 1, item);//np+1 or (char *)np + 8
	return np;
}
Node *appendFromHead(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	linkedList->cur = makeNode(item, linkedList->head, linkedList->head->next, size, myMemCpy);
	if (linkedList->cur != NULL) linkedList->length++;
	return linkedList->cur;
}
Node *appendFromTail(LinkedList * linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *))//linkedList�� 4byte, data�� �ּҰ� �����
{
	linkedList->cur = makeNode(item, linkedList->tail->prev, linkedList->tail, size, myMemCpy);//������� prev, next�� �־��� �ּҸ� �ְٴ�
	//        (���� : ������� �ּ� ����, ���� : NULL pointer)
	//���ٿ���, 1. 2. 3. 4. ��� ���ٿ� ��
	//�����Ͱ� �ϳ� �����̴ϱ� ��ó��

	if (linkedList->cur != NULL) linkedList->length++;//������
	//������ ��� for�� if������ printf("�߸���");
	return linkedList->cur;
}
void display(LinkedList *linkedList, void(*dataPrint)(void *))
//���� ���ϰ��� ���� ���� datatype *�� �������ڸ� ���� �����;�.
//4����Ʈ�� �Լ�������.
{
	int i;
	if (linkedList->length == 0) return;
	linkedList->cur = linkedList->head->next;
	for (i = 0; i < linkedList->length; i++)
	{
		dataPrint(linkedList->cur + 1);
		linkedList->cur = linkedList->cur->next;
	}
	return;
}
Node *linearSearchUnique(LinkedList *linkedList, void *target, int(*compare)(void *, void *))
{
	int i, res;

	linkedList->cur = linkedList->head->next;				//ù ��� ����
	for (i = 0; i<linkedList->length; i++){
		res = compare(linkedList->cur + 1, target);

		if (res == 0){ return linkedList->cur; }  // ã���� ã�� ����� �ּ� ����
		linkedList->cur = linkedList->cur->next;
	}
	return NULL; // ��ã���� NULL pointer ����
}
Node **linearSearchDuplicate(LinkedList *linkedList, void *target, int *searchNodeCount, int(*compare)(void *, void *))
{
	int i, j = 0, res;
	Node **searchNodePtr;
	*searchNodeCount = 0;
	linkedList->cur = linkedList->head->next;

	for (i = 0; i<linkedList->length; i++){
		res = compare(linkedList->cur + 1, target);
		if (res == 0){ (*searchNodeCount)++; }
		linkedList->cur = linkedList->cur->next;
	}

	linkedList->cur = linkedList->head->next;
	searchNodePtr = (Node **)calloc((*searchNodeCount), sizeof(Node *));
	assert(searchNodePtr != NULL);
	for (i = 0; i<linkedList->length; i++){
		res = compare(linkedList->cur + 1, target);
		if (res == 0){
			searchNodePtr[j] = linkedList->cur;
			j++;
		}
		linkedList->cur = linkedList->cur->next;
	}
	return searchNodePtr;
}
Node * deleteNode(LinkedList *linkedList, Node *index, void(*dataFree)(void *))//��ù���, �߰�, �� ��� ��������� Ȯ��
{
	if (index == NULL) return NULL;
	index->prev->next = index->next;
	dataFree(index + 1); //�ΰ� �޸� �������� 
	index->next->prev = index->prev;
	free(index);
	linkedList->length--;
	return index;
}
void destroy(LinkedList *linkedList, void(*dataFree)(void *))
{
	int n;
	n = linkedList->length;
	for (int i = 0; i < n; i++){
		linkedList->cur = linkedList->head->next;
		deleteNode(linkedList, linkedList->cur, dataFree);
	}
	free(linkedList->head);
	free(linkedList->tail);
	linkedList->length = 0;
	linkedList->cur = NULL;
	linkedList->head = NULL;
	linkedList->tail = NULL;
	return;
}
void sortList(LinkedList *linkedList, size_t size, int(*compare)(void *, void *), void(*myMemCpy)(void *, void *), void(*dataFree)(void *))
{
	Node *temp;
	void *temp2;//���ҿ� �޸�
	int res, i, j;

	temp2 = calloc(1, size);//struct Person�� ���°���!! size��
	//void *�� ���� ���� �ƹ��ų� �־ �Ǳ� ������, �׸��� Person�� calloc()���� ����� ���̱� ������ �ؿ��� free()�� ��������

	linkedList->cur = linkedList->head->next;

	for (i = 0; i < linkedList->length - 1; i++){
		temp = linkedList->cur->next;
		for (j = i + 1; j < linkedList->length; j++){
			res = compare(linkedList->cur + 1, temp + 1);
			if (res == 1){
				myMemCpy(temp + 2, temp + 1);
				myMemCpy(temp + 1, linkedList->cur + 1);
				myMemCpy(linkedList->cur + 1, temp2);
			}
			temp = temp->next;
		}
		linkedList->cur = linkedList->cur->next;
	}
	dataFree(temp2);//temp2�� �ΰ� �޸𸮰� �ٱ� ������ �װ��� ���ֱ� ���� 2���ϴµ� -> �ΰ� �޸𸮸� �����ϴ� �κ�
	//���� ���� ��������ٸ� temp2+1�ؾ� ��
	free(temp2);//temp2�� person����ü �޸� ���� �����ϴ� �κ�(calloc()�� Person����ü�ʸ� �Ҵ������� �� �κи� free()�� �����ش�)
	return;
}