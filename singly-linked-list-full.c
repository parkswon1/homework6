#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */
//링크리스트의 몸통이 됨
typedef struct Node { //Node 구조체 선언 호출방식은 listNode임
	int key; //int형 key 변수 선언
	struct Node* link; //Node 구조체형식의 포인터 link 선언
} listNode; 
//링크리스트의 머리가 됨
typedef struct Head { //Head 구조체 선언 호출방식은 headNode임
	struct Node* first; //Node 구조체형식의 포인터 first 선언
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); //headNode형 initialize 함수선언 인자로 headNode* h 를 받아온다
int freeList(headNode* h); //int형 freeList 함수선언 

int insertFirst(headNode* h, int key); //int형 insertFirst 함수선언 인자로 headNode* h, int key 를 받아온다
int insertNode(headNode* h, int key); //int형 insertNode 함수선언 인자로 headNode* h, int key 를 받아온다
int insertLast(headNode* h, int key); //int형 insertLast 함수선언 인자로 headNode* h, int key 를 받아온다

int deleteFirst(headNode* h); //int형 deleteFirst 함수선언 인자로 headNode* h 를 받아온다
int deleteNode(headNode* h, int key); //int형 deleteNode 함수선언 인자로 headNode* h, int key 를 받아온다
int deleteLast(headNode* h); //int형 deleteLast 함수선언 인자로 headNode* h 를 받아온다
int invertList(headNode* h); //int형 invertList 함수선언 인자로 headNode* h 를 받아온다

void printList(headNode* h); //void형 printList 함수선언 인자로 headNode* h 를 받아온다
 
int main()
{
	printf("[----- [Seok Won Park] [2017018003] -----]");
	char command; //char형 command받아올 변수정의
	int key; //int형 key 변수정의
	headNode* headnode=NULL; //headnode 포인터를 생성하고 NULL로 초기화한다. 

	do{ //command가 Q,q이기 전까지 반복한다.
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command변수 받아와서 저장

		switch(command) {
		case 'z': case 'Z': //z,Z일떄
			headnode = initialize(headnode); //headnode를 initialize인자로 넣고 headnode에 저장
			break;
		case 'p': case 'P': //p,P일떄
			printList(headnode); //printList호출후 headnode 인자로 넣어줌
			break;
		case 'i': case 'I': //i,I일떄
			printf("Your Key = "); 
			scanf("%d", &key); //key 값 받아옴
			insertNode(headnode, key); //insertNode함수 호출후 headnode, key인자로 넣어줌
			break;
		case 'd': case 'D': //d,D일떄
			printf("Your Key = ");
			scanf("%d", &key); //key 값 받아옴
			deleteNode(headnode, key); //deleteNode함수 호출후 headnode, key인자로 넣어줌
			break;
		case 'n': case 'N': //n,N일떄
			printf("Your Key = ");
			scanf("%d", &key); //key 값 받아옴
			insertLast(headnode, key); //insertLast함수 호출후 headnode, key인자로 넣어줌
			break;
		case 'e': case 'E': //e,E일떄
			deleteLast(headnode); //deleteLast함수 호출후 headnode 인자로 넣어줌
			break;
		case 'f': case 'F': //f,F일떄
			printf("Your Key = ");
			scanf("%d", &key); //key 값 받아옴
			insertFirst(headnode, key); //insertFirst함수 호출후 headnode, key인자로 넣어줌
			break;
		case 't': case 'T': //t,T일떄
			deleteFirst(headnode); //deleteFirst함수 호출후 headnode 인자로 넣어줌
			break;
		case 'r': case 'R': //r,R일떄
			invertList(headnode); //invertList함수 호출후 headnode 인자로 넣어줌
			break;
		case 'q': case 'Q': //q,Q일떄
			freeList(headnode); //freeList함수 호출후 headnode 인자로 넣어줌
			break;
		default: //위케이스가 아닌 다른 문자가 들어왔을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1; //정상적 실행시 1리턴
}

headNode* initialize(headNode* h) { //head노드를 malloc으로 메모리 할당 받아오는 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); //headNode형 포인터 temp로 동적 할당을 받는다
	temp->first = NULL; //temp의 first포인터를 NULL로 지정한다.
	return temp; //temp를 리턴한다.
}

int freeList(headNode* h){ //인자로 받아온 링크리스트 동적메모리할당 해제
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //받아온 h의 first인자를 listNode포인터 p에 저장

	listNode* prev = NULL; //listNode포인터 prev를 NULL로 지정하고
	while(p != NULL) { //p가 NULL이 아닐때까지
		prev = p; //prev를 p로 저장하고
		p = p->link; //p를 p링크리스트의 다음노드의 주소로 저장
		free(prev); //prev의 동적할당을 free
	} //first부터 링크리스트의 마지막까지 하나 하나 free시켜주는 모습
	free(h); //마지막으로 headnode까지 free시켜줘서 모든 동적할당을 해제시켜주는 모습
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //h 링크리스트에 node를 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode형 node를 정의하고 동적할당 받음
	node->key = key; //node의 key값을 key로 저장해주고
	node->link = NULL; //link를 아직 연결하지 않았으니 NULL로 초기화시켜준다.

	if (h->first == NULL) //만약 h링크리스트의 first가 비었다면(리스트안에 아무것도 없다면)
	{
		h->first = node;//first에 node를 연결해준다(fisrt에 노드주소를 저장)
		return 0; //실행후 함수 종료
	}

	listNode* n = h->first; //listNode형 n를 정의하고 h의 first 주소 저장
	listNode* trail = h->first; //listNode형 trail를 정의하고 h의 first 주소 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n이 NULL이 아닐때까지
		if(n->key >= key) { //n node의 key값이 함수에 인자로받아온 key값보다 크거나 같은경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 받아온 h리스트의 첫번째 노드일경우
				h->first = node; //h의 첫노드를 node로 만들어줌 
				node->link = n; //node의 link에 n을 연결
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; //node의 link를 n으로 연결
				trail->link = node; //trail의 link를 node로 연결
			}
			return 0;//실행후 함수종료
		}

		trail = n; //작다면 trail이 n이 되고
		n = n->link; //n이 n의 link가 된다.
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; //위 if문이 하나도 실행되지 않았다면 trail의 link가 node가된다.
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//key값을 h링크 리스트의 마지막에다가 넣는다

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node링크리스트 동적할당
	node->key = key; //node의 key에 key값 넣어주고
	node->link = NULL; //link를 NULL로 초기화

	if (h->first == NULL) //만약 h링크리스트가 비었다면
	{
		h->first = node; //node가 h링크리스트의 첫 노드가됨
		return 0; //함수종료
	}

	listNode* n = h->first; //링크리스트 n에다가 h의 첫 노드를 저장
	while(n->link != NULL) { //n의  link가 NULL일떄까지 
		n = n->link; //n을 n의 link로 저장
	} //n에 링크리스트의 마지막 링크가 들어가면서 종료됨
	n->link = node; //마지막 link에 node를 연결해준다
	return 0; //함수종료
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //윗 함수들과 동일

	node->link = h->first; //node의 link를 h의 first로 지정해주고 
	h->first = node; //h의 first를 node로 지정해줘서 첫 노드가 node가 됨

	return 0; // 함수종료
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //first가 NULL이라면 링크가 비었으니 삭제할것이 없다는 오류 출력후 함수종료
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //노드 n을 h의 first로 지정
	listNode* trail = NULL; //노드 trail을 NULL로 초기화

	/* key를 기준으로 삭제할 위치를 찾는다 */
	while(n != NULL) { //n이 마지막이 아닐때까지
		if(n->key == key) { //n의 key가 key값과 같은값이라면
			/* 첫 노드를 삭제해야할 경우 인지 검사 */
			if(n == h->first) { //n이 첫 노드라면 
				h->first = n->link; //h의 first를 첫노드의 link에 연결(2번째 노드에 연결한것)
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //trail의 link를 n의 link로 연결
			}
			free(n); //연결이 해제된 n노드의 동적할당을 free시켜줌
			return 0; //함수종료
		}

		trail = n; //trail은 n이되고
		n = n->link; //n은 n의 link가됨
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //입력한 key값을 가진 노드가 없다는 경고문 출력
	return 0;//함수종료

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { 

	if (h->first == NULL) //first가 NULL이라면 링크가 비었으니 삭제할것이 없다는 오류 출력후 함수종료
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //노드 n을 h의 first로 지정
	listNode* trail = NULL; //노드 trail을 NULL로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { 
		h->first = NULL; //first의 값을 NULL로 해주고
		free(n); //사용하지 않는 n노드의 동적할당을 free시켜줌
		return 0; //함수종료
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { 
		trail = n; 
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; //마지막노드의 link를 NULL로 만들고
	free(n); //n free

	return 0; //함수 종료
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { 

	if (h->first == NULL) //first가 NULL이라면 링크가 비었으니 삭제할것이 없다는 오류 출력후 함수종료
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //n을 h의 first로 지정

	h->first = n->link; //h의 first를 첫노드의 link에 연결(2번째 노드에 연결한것)
	free(n);//필요없어진 n을 free

	return 0; //함수종료
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //first가 NULL이라면 링크가 비었으니 역순처리 할것이 없다는 오류 출력후 함수종료
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n을 h의first로 지정
	listNode *trail = NULL; //taril을 NULL로 초기화
	listNode *middle = NULL; //middle을 NULL로 초기화

	while(n != NULL){ //n이 NULL이 아닐때까지
		trail = middle; //trail을 middle로 만들고
		middle = n; //midell을 n으로 만들고
		n = n->link; //n을 n의 link로 저장
		middle->link = trail; //middle의 link를 taril로 지정한다.
	}

	h->first = middle; //h의 첫번째가 middle이 된다.

	return 0; //함수종료
}


void printList(headNode* h) { //링크 리스트를 출력하는 함수
	int i = 0; //int형 변수 i 0으로 지정
	listNode* p;  //p 노드 정의

	printf("\n---PRINT\n");

	if(h == NULL) { //first가 NULL이라면 링크가 비었으니 print할것이 없다는 오류 출력후 함수종료
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p를 h의 first로 지정

	while(p != NULL) { //NULL이 아닐때까지 i를 증가시키면서
		printf("[ [%d]=%d ] ", i, p->key); //i와 p의 key값을 출력
		p = p->link; //p가 가르키는 노드를 뒤로이동
		i++; 
	}

	printf("  items = %d\n", i); //몇개 노드가 있는지 출력
}

