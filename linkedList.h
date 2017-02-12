#pragma once
#pragma warning(disable:4996)

typedef struct _node Node;
struct _node{
	Node *prev; //�� ��带 ����Ű�� ���
	Node *next; //�� ��带 ����Ű�� ���
};
typedef struct _linkedList{
	Node *head;
	Node *cur;
	Node *tail;
	int length; //������ ����� ���� ���� ���
}LinkedList;

//��ũ�帮��Ʈ ���� �Լ�

//����ũ�帮��Ʈ �ʱ�ȭ
void create(LinkedList *linkedList);

//����� �ڿ� ����� �߰�(���� ����)-�߰��� ������� �ּ� ����
//item : �߰��� ������ �ϳ��� �����ϰ� �ִ� ���� �ּ�
//size : �߰��� ������ �ϳ��� ũ��
//myMemCpy : �߰��� �����͸� �����ϴ� ���� �Լ��� �ּ�
Node *appendFromHead(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

//���ϳ�� �տ� �� ��� �߰�(���� ����) - �߰��� ������� �ּ� ����
Node *appendFromTail(LinkedList * linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

//�� ��� �����Ͽ� ���������� ������ �ʱ�ȭ���� �� �� ������� �ּҸ� �����ϴ� �Լ�
Node * makeNode(void *item, Node *prev, Node *next, size_t size, void(*myMemCpy)(void *, void *));

Node * deleteNode(LinkedList *linkedList, Node *index, void(*dataFree)(void *));

Node *linearSearchUnique(LinkedList *linkedList, void *target, int(*compare)(void *, void *));

Node **linearSearchDuplicate(LinkedList *linkedList, void *target, int *searchNodeCount, int(*compare)(void *, void *));

void sortList(LinkedList *linkedList, size_t size, int(*compare)(void *, void *), void(*myMemCpy)(void *, void *), void(*dataFree)(void *));

void display(LinkedList *linkedList, void(*dataPrint)(void *));

void destroy(LinkedList *linkedList, void(*dataFree)(void *));