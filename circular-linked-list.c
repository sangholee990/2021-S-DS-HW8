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
        
        
        printf("[------ [이상호] [2018038016] ------]\n");
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
		   free(p->llink); // 이전노드 해제 
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
    
    listNode* node=h; //접근할 노드 
	
	if(h ==NULL){ //노드가 비었으면  
		  printf("리스트가 초기화 되지 않았습니다\n"); // 오류 메세지 
		  return 0; 
	} 
    
    else if (h->rlink == h){ //리스트에 헤드노드만 존재하면 
    	   printf("노드가 없습니다\n"); // 오류 메세지 
    	   return 0;
	}
	
	// 노드가 하나이상 있을때
	for(;node->rlink != h;node = node->rlink); // 접근노드가 마지막 노드를 가리키게
	node->llink->rlink = h; //삭제 후 마지막 오른쪽을 헤드노드에 연결
	h->llink= node->llink; //삭제 후 마지막 노드의 왼쪽을 헤드노드에 왼쪽에 연결 
	free(node);
	 

	return 1;
}


int insertFirst(listNode* h, int key) {
    
    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 삽입하는 노드 동적 할당 
    listNode* now = h ->rlink; // 움직일 포인터를 첫번째 노드로 초기화
	
	node->key = key; // 새로운 노드에 키값 넣기
	node->llink = h;
	node->rlink = h;
	
	if(now=h) //리스트가 비어있다면 
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
    
    listNode* now = NULL; // 움직이는 포인터를 첫 번째 노드로
	
	if(h==NULL) // 리스트에 노드가 없다면
	{
		printf("더 이상 삭제할 노드가 없다면\n");
		return 0;
	 } 
	 
	else //리스트에 노드가 하나이상 있다면
	{
		now = h->rlink; // now에 헤드노드 rlink 설정
		h->rlink = now->rlink; //첫번째 노드를 삭제노드의 다음 노드로 변경
		if (now->rlink != h) //리스트의 너드가 두개 이상 이면 
		        now->rlink->llink= now->llink; // 삭제한 노드의 다음 노드의 왼쪽을 삭제한 노드의 왼쪽이랑 연결
		else // 리스트의 노드가 유일할때 
		     h->llink=h; 	 // 헤드노드의 왼쪽을 자기자신을 가리키게함
		
		free(now); // 삭제 노드 메모리 동적 할당 해제	  
		
		return 1;		 
	 } 

}


int invertList(listNode* h) {
	
	listNode* pre = h; //이전 노드 가리키는 노드 선언
	listNode* now =NULL; // 현재 노드 가리키는 노드 선언
	
	if (h==NULL){ //초기화된 리스트가 없다면 
		printf("리스트가 초기화 되지 않았습니다\n");
		return 0;
	} 
	
	else
	{
		for (; previous->rlink != h; previous = previous->rlink);	//pre 노드가 마지막 노드를 가리킬때 까지 반복 
	    for (now = h; pre->llink != h; now = now->llink) {		//현재 노드를 헤드노드 부터 반복  
		       now->llink = now->rlink;								//now의 왼쪽을 now의 오른쪽을 가리키게 
		       now->rlink = pre;									//now의 오른쪽을 이전노드를 가리키게 
		       pre = now;									    //이전노드를 현재노드로 
	    }
	}


	return 0;
}




int insertNode(listNode* h, int key) {
	
	listNode* now = h->rlink; //제일 첫번째 노드를 가리키는 리드노드 생성  
	listNode* pre = h; //이전 노드의 위치를 기억하는 포인터 변수 선언
	listNode* node= (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드 동적할당 
	
	int cnt=0; //반복문 카운트 변수
	node->key=key; // 받은 키값 넣기 
	
	node->rlink=h; // 새로 삽입할 노드를 헤드노드로 초기화 
	node->llink=h; 
    
    if ((h->rlink == h) && (h->llink == h)) //리스트에 헤드노드만 있으면 
	{
		h->rlink = node; //새로 생성한 노드를 가장 첫 노드로 삽입
		h->llink = node;
	}
	
	else //리스트에 1개이상의 노드가 있을 경우의수
	{
		if ((now->rlink == h) && (now->llink == h)) //노드가 딱 한개만 있을경우 
		{
			if (now->key >= key) // 새로 넣은 키값이 기존 유일한 키값보다 더작을 경우
			{
				node->rlink=now; // 유일했던 노드  앞에 새로운 노드를 삽입
				now->llink=node;
				h->rlink=node; 
			 } 
		   
		   else //유일한 키값이 새로운 키값보다 작을 경우
		   {
		   	    now->rlink=node; // 유일했던 노드 뒤에 새로운 노드 삽입 
		   	    node->llink=now;
				h->llink=node; 
			} 
			
			return 0;
		}
		
		while(now != h)// 노드가 리스트에 2개이상 존재하면 반복
		{
			cnt++// 반복문 횟수 증가 연산자
			
			if(now->key >= key) // 리드의 키값이 새로만든 노드의 키값보다 크면
			{
				node->rlink=now; //새로 넣을 노드를 리드 앞에 삽입
				now->llink=node;
				
				if(cnt==1) // 반복문에 처음 들어왔을때 (새로 만든 노드가 맨앞일 경우) 
				{
					h->rlink=node; // 헤드노드의 오른쪽링크 즉, 맨처음 노드를 새로만든노드로 초기화
					return 0; // 함수 탈출 
				 } 
				else // cnt != 1 반복문에 두번이상 들어왔을때, (새로만든 노드가 노드 사이에 있을 경우의 수) 
				{
					pre->rlink=node; //이전노드의 다음노드로 새로만든 노드를 삽입한다
					node->llink=pre; // 삽입노드의 왼쪽을 이전노드로
					return 0; // 함수 탈출 
				 } 
			 } 
			 
			 pre=now; //이전노드를 리드가 가리키는 노드로 
			 now = now->rlink// 리드가 다음노드를 가리키게 
		 } 
		 
		 if(now == h)// h->rlink가 h 일때 즉 새로만든 노드가 제일 뒤에 삽입 되어야 할때
		 {
		 	pre->rlink=node; //이전노드의 뒤에 삽입 
		 	node->llink=pre;
		 	h->llink=node;
		  } 
	 } 
    
	return 0;
}



int deleteNode(listNode* h, int key) {
	
	listNode* now = NULL; //노드 접근 구조체 포인터
	
	if (h->rlink == h) //리스트에 헤드 노드밖에 없으면 
	{
           printf("아무 노드도 없습니다.\n"); //에러 메세지  
           return 0;
	 } 
	 
	now = h->rlink; //헤드노드의 오른쪽 링크를 접근할 노드에 삽입
	
	for(;now != h; now= now->rlink) // 마지막 노드까지 반복 
	{
		if (now->key == key && now == h->rlink){ //리스트의 첫번째 노드와 삭제할 키값이 같으면 
			  h->rlink = now->rlink; //첫번째 노드를 삭제노드의 다음으로 변경 
			  if(now->rlink != h) //리스트에 노드가 두개이상 있으면 
			        now->rlink->llink = now->llink; //삭제 노드의 다음노드의 왼쪽을 삭제노드왼쪽과 연결
			  else  // 리스트에 노드가 유일하다면 
			        h->llink=h;    // 헤드노드의 왼쪽노드가 자신을 가리키게함 
			  
			  free(now); //삭제 노드 메모리 해제
			  
			  return 0;			 	  
		} 
		
		else if(now->key == key){ // 첫번째를 제외하고 다른 노드와 삭제할 값이 같다면 
		        
		       now->llink->rlink = now->rlink; //삭제 노드의 이전노드의 오른쪽을 삭제 노드의 오른쪽과 연결
			   
			   if(now->rlink != h) //삭제하는 노드가 리스트의 마지막 노드가 아니면
			       now->rlink->llink =now->llink; // 삭제노드의 다음의 왼쪽을 삭제 노드의 왼쪽과 연결 
			   
			   else
			       h->llink = now->llink; //헤드노드의 왼쪽을 삭제 노드의 왼쪽 노드와  연결 
				
			   free(now); //삭제 노드 메모리 해제
			   
			   
			   return 0;	      
		}
		
	 } 
	return 0;
}
