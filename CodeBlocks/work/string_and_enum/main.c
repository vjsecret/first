#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //string test

#define CHANNEL_TABLE_MAX_ROWS   128          /* max rows of table */
#define CHANNEL_TABLE_MAX_COLS   16           /* max cols of table */
#define CHANNEL_TABLE_MAX_ITEMS  64           /* max len of one table item */

static const char* UsChannelEntry[] =
{
   "10"
};

typedef enum
{
   US_CHANNEL_CHID = 0,
   US_CHANNEL_FREQ,
   US_CHANNEL_WIDTH,
   US_CHANNEL_TYPE
}US_CHANNEL_ENTRY;

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

/*
struct ej_handler {
	char *pattern;
	void (*output)(int argc, char **argv, FILE *stream);
};*/

int temp(int a){
return a=a+5;
}

int main(int argc, char *argv[])
{
    int cols = 0;
    int ctest1 = 0, ctest2 = 0, ctest3 = 0;
    char ctmp='c';

    cols = sizeof(UsChannelEntry)/sizeof(char*);
    printf("cols=%d\n",cols);
    char* chTable = malloc(cols);   //chTable = (char *)malloc(CHANNEL_TABLE_MAX_ROWS*cols*CHANNEL_TABLE_MAX_ITEMS, 0);
    memset((void *)chTable, '\0', cols);  //memset((void *)chTable, '\0', CHANNEL_TABLE_MAX_ROWS*cols*CHANNEL_TABLE_MAX_ITEMS);
    strcmp("10", chTable);
    //chTable+(3*cols + US_CHANNEL_CHID)*CHANNEL_TABLE_MAX_ITEMS); =>???

    printf("chTable=%s\n",chTable);

    US_CHANNEL_ENTRY tmp=1;
    printf("tmp=%d\n",tmp);
    printf("US_CHANNEL_ENTRY=%d\n",US_CHANNEL_CHID);
    printf("US_CHANNEL_FREQ=%d\n",US_CHANNEL_FREQ);
    printf("US_CHANNEL_WIDTH=%d\n",US_CHANNEL_WIDTH);
    printf("US_CHANNEL_TYPE=%d\n",US_CHANNEL_TYPE);

//=================
    ctest1=isalnum('Z');
    ctest2=isalpha('z');
    printf("ctest1=%d\n",ctest1);
    printf("ctest2=%d\n",ctest2);

    ctmp=ctmp+15;
    printf("Anum=%d\n",ctmp);
    printf("Ac=%c\n",ctmp);
//=================
/* link list (連結串列) */
   LINK_NODE *list=NULL;

   list=sort_insert(list,4);
   list=sort_insert(list,2);
   list=sort_insert(list,7);
   list=sort_insert(list,9);
   list=sort_insert(list,14);
   display(list);

   printf("--------------------------\n");

   list=push_node(list,4);
   list=push_node(list,2);
   list=push_node(list,7);
   list=push_node(list,9);
   list=push_node(list,14);
   display(list);

   //_getch();
  //=================

    printf("Hello world!\n");
    return 0;
}
