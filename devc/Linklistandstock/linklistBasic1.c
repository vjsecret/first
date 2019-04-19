#include <stdio.h>
#include <stdlib.h>

//https://dotblogs.com.tw/ibllcwhchiu/2017/05/03/datastructure_part1
struct node{
	int data;
	struct node *next;
};
typedef struct node Node;


//https://lakesd6531.pixnet.net/blog/post/329288496-c%E8%AA%9E%E8%A8%80-%E9%8F%88%E7%B5%90%E4%B8%B2%E5%88%97(link-list)%E7%9A%84%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B
void func1(void){	
  Node a,b,c;
  Node *ptr=&a; //宣告ptr，並將他只向節點a
  
  a.data=12;
  a.next=&b;
  b.data=30;
  b.next=&c;
  c.data=64;
  c.next=NULL;

  while(ptr!=NULL){
  	printf("address=%p, ",ptr); //印出節點的位址 
  	printf("data=%d ",ptr->data); //印出節點的資料 
  	printf("next=%p\n",ptr->next); //印出下一個節點位址 
  	ptr=ptr->next;  //將ptr指向下一個節點 
  } 
}


struct node1{
	int data;
	struct node *next;
};
typedef struct node1 NODE;

NODE* GetNode(void)
{
    NODE* ptr = (NODE*)malloc(sizeof(NODE)); // 宣告指標ptr，並指向NODE大小的空間
    if(ptr == NULL)
        exit(1);
    return ptr; //回傳這個空間的指標
}
NODE* InsertNode(NODE* pHead, NODE* ptr, int data)
{
    NODE* NewNode = GetNode();
    NewNode->data = data;
    NewNode->next = NULL;

    if( ptr == NULL )           //插在Head之前，ptr為NULL
    {
        NewNode->next = pHead;
        pHead = NewNode;
    }
    else if( ptr->next == NULL) //插在尾巴之後，ptr的下個節點為NULL
    {
        ptr->next = NewNode;
    }
    else                        //插在中間，讓前面指向New，讓New指向後面
    {
        NewNode->next = ptr->next;
        ptr->next = NewNode;
    }
    return pHead;               //因為頭指標可能會變，回傳頭指標
}
void FreeNode( NODE* ptr )
{
    free(ptr);
}
NODE* FindNode(NODE* ptr, int data)
{
    NODE* pTempNode = ptr;    //為了不動到原本指標，宣告一個新指標做移動
    while( pTempNode->next != NULL && pTempNode != data )
    {
        pTempNode = pTempNode->next;
    }
    return pTempNode;
}

//https://jax-work-archive.blogspot.com/2009/04/c-link-list.html 
/* 定義結構型態 */  
typedef struct link_node{  
   int data;  
   struct link_node *link;  
} LINK_NODE;

/* 產生新節點 */  
LINK_NODE *new_node(int data){  
   LINK_NODE *node;  
   node=(LINK_NODE *) malloc(sizeof(LINK_NODE));/*<stdlib.h>*/  
     
   // 記憶體不足  
   if(node == NULL){ return NULL;}  
     
   node->data=data;    
   node->link=NULL;       
   return node;  
}  

/* 加入新的資料於最後 */  
LINK_NODE *push_node(LINK_NODE *list, int data){  
   /*產生新節點*/  
   LINK_NODE *node=new_node(data);    
  
   // 加入第一個新節點  
   if(list==NULL){      
       list=node;  
   }else{  
       LINK_NODE *p=list;    
       // 取得最後一個節點  
       while(p->link!=NULL){p=p->link;}  
       p->link=node;  
   }     
   return list;  
}  
  
  
/* 排序插入新節點 */  
LINK_NODE *sort_insert(LINK_NODE *list,int data){  
   // 加入第一筆資料  
     
   // 產生新節點  
   LINK_NODE *node=new_node(data);      
   if(list==NULL){ list=node; return list; }    
  
   // 尋找大於資料(data)的位址  
   LINK_NODE *r=list,*q=list;      
   while(r!=NULL && r->data<data){ q=r; r=r->link; }  
  
   if(r==list){ // 首節點  
       node->link=list; list=node;   
   }else{ // 加入新節點於中間  
       node->link=q->link;   
       q->link=node;   
   }      
   return list;   
}  
  
  
/* 計算串列長度 */  
int get_length(LINK_NODE *list){  
   LINK_NODE *p=list;  
   int count=0;    
   while(p!=NULL){      
       count++;    
       p=p->link;    
   }  
     
   return count;  
}  
  
  
/* 搜尋資料(data)的節點位子 */  
LINK_NODE *search_node(LINK_NODE *list, int data){  
   LINK_NODE *p=list;    
   while(p!=NULL && p->data!=data){ p=p->link; }  
   return p ;  
}  
  
  
/* 印出所有串列的所有資料 */  
int display(LINK_NODE *list){  
   LINK_NODE *p=list;  
   while(p!=NULL){   
       printf("%d\n",p->data);/*<stdio.h>*/  
       p=p->link;    
   }  
   return 1;  
}


int main(int argc, char *argv[])
{
  //func1();
/*
  NODE a,b,c;
  NODE *ptr=&a; //宣告ptr，並將他只向節點a
    
  a.data=12;
  a.next=&b;
  b.data=30;
  b.next=&c;
  c.data=64;
  c.next=NULL;

	//create:
	NODE* NewNode = (NODE*)malloc(sizeof(NODE)); // 宣告指標NewNode，並指向NODE大小的空間
    if(NewNode == NULL)
        exit(1);
	NewNode->data = 15;
    NewNode->next = NULL;
    //insert:
	NewNode->next = ptr->next;
    ptr->next = NewNode;

  while(ptr!=NULL){
  	printf("address=%p, ",ptr); //印出節點的位址 
  	printf("data=%d ",ptr->data); //印出節點的資料 
  	printf("next=%p\n",ptr->next); //印出下一個節點位址 
  	ptr=ptr->next;  //將ptr指向下一個節點 
  }
 */
  //FindNode(&a,12); 
	/* 
   LINK_NODE *list=NULL;  
     
   list=sort_insert(list,4);  
   list=sort_insert(list,2);  
   list=sort_insert(list,7);  
   list=sort_insert(list,9);  
   list=sort_insert(list,14);  
   display(list);  
*/ 

printf("=============================================\n"); 	
	NODE* head = (NODE*)malloc(sizeof(NODE)); // 宣告指標head，並指向NODE大小的空間
    if(head == NULL)
        exit(1);
	printf("Head=%p\n",head);
	head->data = 12;
    head->next = NULL;
    
	NODE *Current;
	NODE *pre;
	int *first=NULL;
	int i;
	for(i=0;i<=3;i++){

		//create:
		NODE* newNode = (NODE*)malloc(sizeof(NODE)); // 宣告指標NewNode，並指向NODE大小的空間
	    if(newNode == NULL)
	    	exit(1);
	    newNode->next = NULL;
	    newNode->data=i;
	    printf("New=%p\n",newNode);
	    
		if (i==0){
			Current=head;
			first=newNode;
			printf("first=%p\n",first); //printf("Head=%p\n",Current);	
		}
		else{
			Current=Current->next;	
		}	
		Current->next=newNode;
		
		printf("Current=%p, ",Current);
		printf("Current->next=%p,",Current->next);
		printf("data Current=%d\n",Current->data);
		printf("=======\n");		 
	}
	printf("=====================Current========================\n");
	Current=head;
  	while(Current!=NULL){
	  	printf("address=%p, ",Current); //印出節點的位址 
	  	printf("data=%d ",Current->data); //印出節點的資料 
	  	printf("next=%p\n",Current->next); //印出下一個節點位址 
	  	Current=Current->next;  //將ptr指向下一個節點 
  	}

/*
printf("=============================================\n"); 	
	NODE* head = (NODE*)malloc(sizeof(NODE)); // 宣告指標head，並指向NODE大小的空間
    if(head == NULL)
        exit(1);
	printf("Head=%p\n",head);
	head->data = 12;
    head->next = NULL;
    
	NODE *Current;
	NODE *pre;
	int *first=NULL;
	int i;
	for(i=0;i<=3;i++){

		//create:
		NODE* newNode = (NODE*)malloc(sizeof(NODE)); // 宣告指標NewNode，並指向NODE大小的空間
	    if(newNode == NULL)
	    	exit(1);
	    newNode->next = NULL;
	    newNode->data=i;
	    printf("New=%p\n",newNode);
	    
		if (i==0){
			Current=head;
			first=newNode;
			printf("first=%p\n",first); //printf("Head=%p\n",Current);	
		}
		else{
			Current=pre;	
		}	
		Current->next=newNode;
		pre=newNode;	
		
		printf("Current=%p, ",Current);
		printf("Current->next=%p,",Current->next);
		printf("data Current=%d\n",Current->data);
		printf("address pre=%p,",pre);
		printf("address pre->next=%p,",pre->next);
		//printf("data=%d",ptrT->next->data);
		printf("data=%d\n",pre->data); //印出節點的資料
		printf("=======\n");		 
	}
	printf("=====================Current========================\n");
	Current=head;
  	while(Current!=NULL){
	  	printf("address=%p, ",Current); //印出節點的位址 
	  	printf("data=%d ",Current->data); //印出節點的資料 
	  	printf("next=%p\n",Current->next); //印出下一個節點位址 
	  	Current=Current->next;  //將ptr指向下一個節點 
  	}
	printf("====================pre=========================\n");
	pre=first;
  	while(pre!=NULL){
	  	printf("address=%p, ",pre); //印出節點的位址 
	  	printf("data=%d ",pre->data); //印出節點的資料 
	  	printf("next=%p\n",pre->next); //印出下一個節點位址 
	  	pre=pre->next;  //將ptr指向下一個節點 
  	}

printf("=============================================\n"); 	
	NODE* head = (NODE*)malloc(sizeof(NODE)); // 宣告指標head，並指向NODE大小的空間
    if(head == NULL)
        exit(1);
	printf("Head=%p\n",head);
	head->data = 12;
    head->next = NULL;
    
	NODE *preBefore;
	NODE *ptrNow;
	int *first=NULL;
	int i;
	for(i=0;i<=3;i++){
		//create:
		NODE* Current = (NODE*)malloc(sizeof(NODE)); // 宣告指標NewNode，並指向NODE大小的空間
	    if(Current == NULL)
	    	exit(1);
	    Current->next = NULL;
	    Current->data=i;
	    printf("New=%p\n",Current);
	    
		if (i==0){
			preBefore=head;
			first=Current;
			printf("first=%p\n",first); //printf("Head=%p\n",Current);	
		}
		else{
			preBefore=ptrNow;
			//preBefore=Current;	
		}	
		preBefore->next=Current;
		ptrNow=Current;	
		
		printf("preBefore=%p, ",preBefore);
		printf("preBefore->next=%p,",preBefore->next);
		printf("data preBefore=%d\n",preBefore->data);
		printf("address ptrNow=%p,",ptrNow);
		printf("address ptrNow->next=%p,",ptrNow->next);
		//printf("data=%d",ptrT->next->data);
		printf("data=%d\n",ptrNow->data); //印出節點的資料
		printf("=======\n");		 
	}
	printf("=====================preBefore========================\n");
	preBefore=head;
  	while(preBefore!=NULL){
	  	printf("address=%p, ",preBefore); //印出節點的位址 
	  	printf("data=%d ",preBefore->data); //印出節點的資料 
	  	printf("next=%p\n",preBefore->next); //印出下一個節點位址 
	  	preBefore=preBefore->next;  //將ptr指向下一個節點 
  	}
	printf("====================ptrNow=========================\n");
	ptrNow=first;
  	while(ptrNow!=NULL){
	  	printf("address=%p, ",ptrNow); //印出節點的位址 
	  	printf("data=%d ",ptrNow->data); //印出節點的資料 
	  	printf("next=%p\n",ptrNow->next); //印出下一個節點位址 
	  	ptrNow=ptrNow->next;  //將ptr指向下一個節點 
  	}

/*
printf("=============================================\n");
int i;
for(i=0;i<=3;i++){ 
	NODE* Current = (NODE*)malloc(sizeof(NODE)); // 宣告指標NewNode，並指向NODE大小的空間
    if(Current == NULL)
    	exit(1);
    Current->next = NULL;
    Current->data=i;
    printf("Head=%p\n",Current);
    //int *Current=NULL;    
    int *first=NULL;
    NODE *ptrT;
    
	if (i==0){
		first=Current;
		//ptrT=Current;
		printf("first=%p\n",first); //printf("Head=%p\n",Current);
		
	}
	else
		ptrT->next=Current;
	
	ptrT=Current;
	//ptrT->data=Current->data;	
	
	printf("address ptrT=%p,",ptrT);
	printf("address ptrT->next=%p,",ptrT->next);
	//printf("data=%d",ptrT->next->data);
	printf("data=%d\n",ptrT->data); //印出節點的資料 
}*/


/*
int j=0;
while(j<sizeof(ptrT)){
	printf("address=%p, ",ptrT); //印出節點的位址 
  	printf("data=%d ",ptrT->data); //印出節點的資料 
  	printf("next=%p\n",ptrT->next); //印出下一個節點位址 
  	//ptr=ptr->next;  //將ptr指向下一個節點 
  	j=j+1;
}
*/

//https://kopu.chat/2017/06/02/c-%E8%AA%9E%E8%A8%80%EF%BC%9A%E9%8F%88%E7%B5%90%E4%B8%B2%E5%88%97linked-list%E7%9A%84%E5%BB%BA%E7%AB%8B%E8%88%87%E5%88%AA%E9%99%A4/
//http://alrightchiu.github.io/SecondRound/linked-list-xin-zeng-zi-liao-shan-chu-zi-liao-fan-zhuan.html
  system("PAUSE");	 
  return 0;
}
