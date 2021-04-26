/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {


	if(*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}


/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
int freeList(listNode* h){
	
	listNode* p = h->rlink; //헤드노드가 가리키는 곳을 p가 가리키도록 해준다 
	
	if(h->rlink == h ) //리스트에 노드가 한개도 없을 때 
	{
		free(h); //헤드 노드만 동적할당받은 메모리 반납 
		return 0;
	 } 
	 
	while( p != h){
		   p = p->rlink; // p가 다음노드를 가리키게
		   free(p->llink) // 이전노드 해제 
	}
	
	free(h); //head노드 해제
	h = NULL; //headnode 를 초기화 

	return 0;
}



void printList(listNode* h) {
	int i = 0; 
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { 
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



int insertLast(listNode* h, int key) {
     
    listNode* node =(listNode*)malloc(sizeof(listNode)); // 삽입할 노드를 동적할당 
    node->llink=h; //새로 생성한 노드에 헤드노드 포인터로 초기화 
    node->rlink=h;
    node->key = key; //키값넣기 
    
    listNode* now = h->llink; // 움직일 포인터를 마지막 노드로 초기화
	 
    if(h == NULL)// 리스트에 노드가 없으면 
    {
    	 h->llink=node; // 새로 삽입하는 노드를 가장 첫노드로 
    	 h->rlink=node;
	}
    
    else
	{
		now->rlink=node; //마지막 노드에 도달하면 새로 삽입한 노드와 연결
		node->llink=now;
		h->llink=node;// 헤드 노드의 llink를 node로  
	 } 
        
	return 1;
}


int deleteLast(listNode* h) {
    
    listNode* now=h; //접근할 노드 
	
	if(h ==NULL){
		  printf("노드가 없습니다\n");
	} 
    

	return 1;
}


int insertFirst(listNode* h, int key) {
    
    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 삽입하는 노드 동적 할당 
    listNode* now = h ->rlink; // 움직일 포인터를 첫번째 노드로 초기화
	
	node->key = key; // 새로운 노드에 키값 넣기
	node->llink = h;
	node->rlink = h;
	
	if(p=h) //리스트가 비어있다면 
	{
		h->llink = node; // 노드의 시작을 새로 삽입한 노드로
		h->rlink = node;	 
	 } 
	
	else //노드가 하나 이상 있다면 
	{
		h->rlink = node;
		node->rlink =now;
		now->llink = node; 
	 } 

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    
    listNode* now = h->rlink; // 움직이는 포인터를 첫 번째 노드로
	
	if(h==NULL) // 리스트에 노드가 없다면
	{
		printf("더 이상 삭제할 노드가 없다면\n");
		return 0;
	 } 
	 
	else //리스트에 노드가 하나이상 있다면
	{
		now = h->rlink; //
	 } 

	return 1;

}


int invertList(listNode* h) {


	return 0;
}




int insertNode(listNode* h, int key) {

	return 0;
}



int deleteNode(listNode* h, int key) {

	return 0;
}
