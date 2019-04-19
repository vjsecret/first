#include <stdio.h>
#include <stdlib.h>
#define		List_Entry(pNode, Type, Name)	\
			((Type *)((char *)pNode - (unsigned long)(&((Type *)0)->Name)))
int *s2;
/*==============================================================================+
|           Type definition                                                     |
+==============================================================================*/
typedef     char                    		INT8_T;
typedef     unsigned char           		UINT8_T;
typedef     int	                   			INT16_T;
typedef     unsigned int          			UINT16_T;
typedef     long                    		INT32_T;
typedef     unsigned long           		UINT32_T;
typedef     UINT8_T              			BYTE_T;
typedef     UINT16_T             			WORD_T;
typedef     UINT32_T             			DWORD_T;
typedef     UINT16_T             			BOOL_T;
typedef		INT8_T							CHAR_T;
typedef		INT16_T							SHORT_T;
typedef		INT32_T							LONG_T;
typedef		float							FLOAT_T;
typedef     INT32_T 						BASE_T ;
typedef     UINT32_T						UBASE_T;
typedef		UINT32_T						SIZE_T;
typedef		UINT32_T						TICK_T;
typedef     unsigned  int       			BYTE;   // 16-Bit
typedef     unsigned  int 					WORD;   // 16-Bit
typedef     long                			LONG;   // 32-Bit
typedef     unsigned long       			DWORD;  // 32-Bit
typedef     WORD                			BOOL;
typedef     WORD                			HANDLE; // Handle (ID) of object
typedef		double							TFLOAT;

typedef		void (*TASKFUNC)(void *pPara);
typedef		struct tagNODE NODE_T;
typedef struct tagNODE
{
	NODE_T		*pPrev;
	NODE_T		*pNext;
};

typedef struct tagTASK
{
	NODE_T           Node;                               // Task list node

    // Task's function
    TASKFUNC         pFunc;                             // Task function
    void            *pPara;                             // function parameter

    // Tick
	TICK_T       	InitTick;                        	// task's initialized tick
	TICK_T       	TimeoutTick;                   		// Timeout tick

	// Run Count
	WORD_T          wInitCount;
	WORD_T			wCount;
}TASK_T;

void Task_Start(TASK_T *pTask){
	NODE_T			*pNode;
	TASK_T			*pTempTask;

	pTempTask	=	List_Entry(pNode, TASK_T, Node);
	printf("Node=%p\n",&pTempTask->Node);
	printf("����pTempTask_addr=%p\n\n",pTempTask);
}

void temp1(int *paraa)
{
    int *t1=&paraa; //���Ыŧi���ɭԤ@�w�n�����O�����m
    int t2=2;
    printf("����paraa_addr=%p\n",&paraa);
    //�n�ǡA������paraa�w�g�O���ФF�A���Υ[&�N���ӬO�a�}�F�A������Pı�o���٬O��ŧi���`�Ƥ@��
    //printf("para_addr=%X\n",&paraa);
    printf("����paraa����=%d\n",paraa);
//*t1=&paraa;

t2=paraa;
printf("����t1���V����m=%p\n",t1);
printf("����t1����=%d\n",*t1);
printf("t2_addr=%p\n",&t2);
printf("t2=%d\n\n",t2);

//����t1,t2�ȡA�u��t1��v�Tparaa��,t2�u��Q�ʨ�paraa�v�T
*t1=1;
t2=5;
printf("����t1���V����m=%p\n",t1);
printf("����t1����=%d\n",*t1);
printf("����paraa_addr=%p\n",&paraa);
//printf("para_addr=%X\n",&paraa);
printf("����paraa����=%d\n",paraa);

printf("s2=%d\n\n",s2); //C�y���S�ʡA�ǤJ���Ȥ��|������
};
void temp2(int *paraa)
{
    int*  t1=&paraa;
//t1=&s2;
printf("����t1���V����m=%p\n",t1);
printf("����t1����=%d\n",*t1);
printf("����paraa_addr=%p\n",&paraa);
//printf("para_addr=%X\n",&paraa);
printf("����paraa����=%d\n",paraa);
}
int main()
{
    TASK_T s1;
    s1.Node.pPrev=0;
    s1.Node.pNext=0;
    Task_Start(&s1);

    s2=3;
    //�n�ǡA������s2�w�g�O���ФF�A������Pı�o���٬O��ŧi���`�Ƥ@��
    temp1(s2);
    temp2(s2);
    printf("Hello world!\n\n");

    int var = 10;
    int *ptr = &var;

    printf("���� ptr �x�s���ȡG%X\n", ptr);
    printf("���X ptr ���V���O�����m���ȡG%d\n", *ptr);

    return 0;
}
