#pragma once
#pragma warning(disable:4996)

typedef struct _node Node;
struct _node{
	Node *prev; //앞 노드를 가리키는 멤버
	Node *next; //뒷 노드를 가리키는 멤버
};
typedef struct _linkedList{
	Node *head;
	Node *cur;
	Node *tail;
	int length; //데이터 노드의 개수 저장 멤버
}LinkedList;

//링크드리스트 관리 함수

//더블링크드리스트 초기화
void create(LinkedList *linkedList);

//헤드노드 뒤에 새노드 추가(역순 저장)-추가한 새노드의 주소 리턴
//item : 추가할 데이터 하나를 저장하고 있는 곳의 주소
//size : 추가할 데이터 하나의 크기
//myMemCpy : 추가할 데이터를 복사하는 보조 함수의 주소
Node *appendFromHead(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

//테일노드 앞에 새 노드 추가(정순 저장) - 추가한 새노드의 주소 리턴
Node *appendFromTail(LinkedList * linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *));

//새 노드 생성하여 전달인자의 내용을 초기화까지 한 후 새노드의 주소를 리턴하는 함수
Node * makeNode(void *item, Node *prev, Node *next, size_t size, void(*myMemCpy)(void *, void *));

Node * deleteNode(LinkedList *linkedList, Node *index, void(*dataFree)(void *));

Node *linearSearchUnique(LinkedList *linkedList, void *target, int(*compare)(void *, void *));

Node **linearSearchDuplicate(LinkedList *linkedList, void *target, int *searchNodeCount, int(*compare)(void *, void *));

void sortList(LinkedList *linkedList, size_t size, int(*compare)(void *, void *), void(*myMemCpy)(void *, void *), void(*dataFree)(void *));

void display(LinkedList *linkedList, void(*dataPrint)(void *));

void destroy(LinkedList *linkedList, void(*dataFree)(void *));