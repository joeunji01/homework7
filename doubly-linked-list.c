/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); 

// *h = headNode를 가리키는 포인터
// **h = *(headNode->*first) , listNode를 가리킴 

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [조은지]  [2021076020] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) 
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //headNode 메모리 할당
	(*h)->first = NULL; //headNode->first 가 가리키는게 없음

	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //첫번째 listNode

	listNode* prev = NULL; 
	while(p != NULL) {
		prev = p; //prev= 첫번째 listNode
		p = p->rlink; //p가 다음 노드를 가리킴
		free(prev); //prev 메모리 할당 해제
	}
	free(h); //headNode 메모리 할당 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p; //구조체 포인터 

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //첫번째 노드

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key); //노드 순서=값
		p = p->rlink; //다음 노드로 이동
		i++; //노드 순서 ++
	}

	printf("  items = %d\n", i); //노드 개수
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	
	//추가할 node 동적메모리 할당
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)
	{ //헤드노드가 가리키는게 없다면, 첫번째 노드가 됨
		h->first = node;
		return 0;
	}

	listNode* n = h->first; //n은 첫번째 노드를 가리킴
	while(n->rlink != NULL) { 
		n = n->rlink; //n은 다음 노드를 가리킴
	} //n->rlink 가 NULL 이면 
	n->rlink = node; //n 다음 노드에 새로운 노드 추가
	node->llink = n; //새로운 노드의 이전 노드는 n
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) 
	{
		printf("nothing to delete.\n");
		return 0;
	} 

	listNode* n = h->first; //n은 첫번째 노드를 가리킴
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n); //첫번째 노드 메모리 할당 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { 
		trail = n; //trail이 n이 가리키던 노드 가리킴
		n = n->rlink; //n은 다음 노드를 가리킴
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //trail->rlink 는 n
	free(n); //n이 가리키던 노드 메모리 할당 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	//삽입할 노드 동적 메모리 할당 
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)
	{ //헤드노드가 가리키는게 없다면
		h->first = node; //삽입할 새로운 노드 가리킴
		return 1;
	}

	node->rlink = h->first; //새로운 노드의 rlink는 첫번째 노드를 가리킴
	node->llink = NULL; //새로운 노드의 llink는 가리키지 않음

	listNode *p = h->first; //p는 첫번째 노드를 가리킴
	p->llink = node; // p의 llink는 새로운 노드를 가리킴
	h->first = node; //첫번째 노드는 새로운 노드 (node)가 됨

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //n은 첫번째 노드를 가리킴
	h->first = n->rlink; //헤드노드는 n의 rlink가 가리키는 노드를 가리킴

	free(n); //첫번째 노드 메모리 할당 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) { //노드가 없음
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n은 첫번째 노드를 가리킴
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle; 
		middle = n; //
		n = n->rlink; //middle이 마지막일 경우 ->  n=NULL
		middle->rlink = trail;
		middle->llink = n; 
		//middle이 마지막 노드를 가리킬 때 까지
	}

	h->first = middle; //헤드노드가 원래 리스트의 마지막 노드를 가리킴

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	//삽입할 노드 동적 메모리 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL; 

	if (h->first == NULL)
	{ //헤드노드가 가리키고 있지 않으면, 새로운 노드를 가리킴
		h->first = node; 
		return 0;
	}

	listNode* n = h->first; //n은 첫번째 노드를 가리킴

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { 
		if(n->key >= key) { //첫번째 노드의 key 값이 삽입할 key 값보다 크면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 첫번째 노드를 가리킬 때
				insertFirst(h, key); //n 앞에 새로운 노드 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //삽입할 노드의 rlink가 n을 가리킴
				node->llink = n->llink; //삽입할 노드의 llink가 첫번째 노드의 llink를 가리킴
				n->llink->rlink = node; 
				
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; //n이 첫번째 노드를 가리킴

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //첫번째 노드 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; 
				n->rlink->llink = n->llink;
				//n을 기준으로 앞 뒤로 연결
				free(n); //n 동적 메모리 할당 해제
			}
			return 1;
		}

		n = n->rlink; //n은 다음 노드를 가리킴
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


