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

/* �w�q���c���A */
typedef struct link_node{
   int data;
   struct link_node *link;
} LINK_NODE;



/* ���ͷs�`�I */
LINK_NODE *new_node(int data){
   LINK_NODE *node;
   node=(LINK_NODE *) malloc(sizeof(LINK_NODE));/*<stdlib.h>*/

   // �O���餣��
   if(node == NULL){ return NULL;}

   node->data=data;
   node->link=NULL;
   return node;
}


/* �[�J�s����Ʃ�̫� */
LINK_NODE *push_node(LINK_NODE *list, int data){
   /*���ͷs�`�I*/
   LINK_NODE *node=new_node(data);

   // �[�J�Ĥ@�ӷs�`�I
   if(list==NULL){
       list=node;
   }else{
       LINK_NODE *p=list;
       // ���o�̫�@�Ӹ`�I
       while(p->link!=NULL){p=p->link;}
       p->link=node;
   }
   return list;
}


/* �ƧǴ��J�s�`�I */
LINK_NODE *sort_insert(LINK_NODE *list,int data){
   // �[�J�Ĥ@�����

   // ���ͷs�`�I
   LINK_NODE *node=new_node(data);
   if(list==NULL){ list=node; return list; }

   // �M��j����(data)����}
   LINK_NODE *r=list,*q=list;
   while(r!=NULL && r->data<data){ q=r; r=r->link; }

   if(r==list){ // ���`�I
       node->link=list; list=node;
   }else{ // �[�J�s�`�I�󤤶�
       node->link=q->link;
       q->link=node;
   }
   return list;
}


/* �p���C���� */
int get_length(LINK_NODE *list){
   LINK_NODE *p=list;
   int count=0;
   while(p!=NULL){
       count++;
       p=p->link;
   }

   return count;
}


/* �j�M���(data)���`�I��l */
LINK_NODE *search_node(LINK_NODE *list, int data){
   LINK_NODE *p=list;
   while(p!=NULL && p->data!=data){ p=p->link; }
   return p ;
}


/* �L�X�Ҧ���C���Ҧ���� */
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
/* link list (�s����C) */
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
