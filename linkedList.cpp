#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "linkedList.h"
//제네릭코드므로 Person이 들어가면 안돼!!
void create(LinkedList *linkedList)
{
	//반드시 calloc 메모리 할당해야돼!!
	linkedList->head = (Node *)calloc(1, sizeof(Node));//Head Node 생성 , 전달인자 2개, sizeof(Node) = 24Byte
	//main에서 list를 선언한거지 여기서는 사용할수 없으니 linkedList사용
	linkedList->tail = (Node *)calloc(1, sizeof(Node));//tail Node 생성
	//링크드리스트를 만들기 위하여 1.2.3.4. 만들어야됨
	linkedList->head->prev = linkedList->head;//3.
	linkedList->head->next = linkedList->tail;//1. LV에 적혀져있는게 그방에 접근하여 거기의 주소들 접근(?)
	linkedList->tail->prev = linkedList->head;//2. 주소 대입	
	linkedList->tail->next = linkedList->tail;//4.
	linkedList->length = 0;//linkedList가 가르키는 list의 lenght를 0(data가 들어가있는 방개수가 아직 0)
	linkedList->cur = NULL;//linkedList가 가르키는 list의 cur을 NULL pointer로 초기화

	return;
}
Node * makeNode(void *item, Node *prev, Node *next, size_t size, void(*myMemCpy)(void *, void *))//뒤에 2개 Node pointer
{
	Node *np;

	np = (Node *)calloc(1, sizeof(Node) + size);//여기서 동적 M할당
	//calloc(내가 초기화시킬 방 한개, prev+next+내가 저장할 데이터 영역의크기)
	if (np == NULL) return NULL;//return np;도 가능. 여기서 이것을 해줘야 그밑에것 하지 않음.
	//성공시 1. 2. 3. 4.
	np->prev = prev;//1.
	np->next = next;//2.

	//강사님은 3번 : prev->next=list->cur;//나는 여기서 list->cur 모두 np로 설정
	//4번 : prev = list->cur;
	np->prev->next = np;//3.
	np->next->prev = np;//4. tailnode를 넣으면 안됨. 왜냐하면 appendFromHead에서도 사용되기 때문.
	//여기까지 선만 정리. 이제 데이터 초기화해야 함.
	//np->data = *item;//bit copy므로 안돼!!
	myMemCpy(np + 1, item);//np+1 or (char *)np + 8
	return np;
}
Node *appendFromHead(LinkedList *linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *))
{
	linkedList->cur = makeNode(item, linkedList->head, linkedList->head->next, size, myMemCpy);
	if (linkedList->cur != NULL) linkedList->length++;
	return linkedList->cur;
}
Node *appendFromTail(LinkedList * linkedList, void *item, size_t size, void(*myMemCpy)(void *, void *))//linkedList는 4byte, data의 주소가 날라옴
{
	linkedList->cur = makeNode(item, linkedList->tail->prev, linkedList->tail, size, myMemCpy);//새노드의 prev, next에 넣어줄 주소를 주겟다
	//        (성공 : 새노드의 주소 리턴, 실패 : NULL pointer)
	//갔다오면, 1. 2. 3. 4. 모두 갔다온 것
	//데이터가 하나 들어간것이니까 밑처럼

	if (linkedList->cur != NULL) linkedList->length++;//성공시
	//실패할 경우 for문 if문통해 printf("잘못됨");
	return linkedList->cur;
}
void display(LinkedList *linkedList, void(*dataPrint)(void *))
//나는 리턴값은 따로 없고 datatype *의 전달인자를 갖는 포인터야.
//4바이트의 함수포인터.
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

	linkedList->cur = linkedList->head->next;				//첫 노드 연결
	for (i = 0; i<linkedList->length; i++){
		res = compare(linkedList->cur + 1, target);

		if (res == 0){ return linkedList->cur; }  // 찾으면 찾은 노드의 주소 리턴
		linkedList->cur = linkedList->cur->next;
	}
	return NULL; // 못찾으면 NULL pointer 리턴
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
Node * deleteNode(LinkedList *linkedList, Node *index, void(*dataFree)(void *))//맨첫사람, 중간, 끝 사람 삭제됬는지 확인
{
	if (index == NULL) return NULL;
	index->prev->next = index->next;
	dataFree(index + 1); //부가 메모리 지워야지 
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
	void *temp2;//스왑용 메모리
	int res, i, j;

	temp2 = calloc(1, size);//struct Person을 보냈겠지!! size를
	//void *로 해준 것은 아무거나 넣어도 되기 때문에, 그리고 Person을 calloc()으로 잡아준 것이기 때문에 밑에서 free()로 해제해줌

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
	dataFree(temp2);//temp2에 부가 메모리가 붙기 때문에 그것을 없애기 위해 2번하는데 -> 부가 메모리를 해제하는 부분
	//만약 노드로 보내줬었다면 temp2+1해야 함
	free(temp2);//temp2의 person구조체 메모리 쪽을 해제하는 부분(calloc()때 Person구조체쪽만 할당했으니 그 부분만 free()가 없애준다)
	return;
}