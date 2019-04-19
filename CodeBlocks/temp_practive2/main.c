#include <stdio.h>
#include <stdlib.h>
typedef     unsigned  int 		WORD;   /* 16-Bit */
typedef     unsigned long       DWORD;  /* 32-Bit */

typedef union  tagTMasterCtlCMD
{
    DWORD   all;
    struct
    {
        WORD    wCMD                : 16;   // Bit0~15:     CMD
        WORD    bConfigActive       : 4;    // Bit16~19:    ConfigActive(4bit).
        WORD    bActStep            : 4;    // Bit20~23:    Action Step.
        WORD    bMotorEnable        : 1;    // Bit24:       Motor Enable.
        WORD    bStandstillEnable   : 1;    // Bit25:       Standstill Enable.

        WORD    bRsvd1              : 1;    // Bit26:       Anders 20120213.
        WORD    bRsvd2              : 5;
    }Info;
}TCtlCMD;

typedef struct  tagTAxisController
{
    TCtlCMD                 CurrMasterCtlCMD;
    TCtlCMD                 LastMasterCtlCMD;
    WORD					wPrepare;		    	// Anders 20121130.
    WORD					wLastPrepare;			// Anders 20130125.
    WORD                    wControlSource;         // 0:PLC Master; 1:PC.
    void (*pCtlFunc)        (struct tagTAxisController * const pAxisController);
    void (*pTestCtlFunc)    (struct tagTAxisController * const pAxisController);
    WORD                    wHeartbeetCounter;
} TAxisController;
typedef struct  tagTMOAxisController
{
    TAxisController				InheritMAController;
}TMOAxisController;
TMOAxisController   g_AxisController[2];

void test1(int *p1){
printf("p1=%p\n",p1);
int *i=&p1;//i沒有指到外面i的地址
*i=1;
printf("i=%p,&i=%p\n",i,&i);
printf("i=%p,*i=%d,&i=%p\n",i,*i,&i);
}
void test11(int *p1){
printf("p1=%p\n",p1);
int i=p1;//i沒有指到外面i的地址
//*i=1;
printf("11:i=%p,&i=%p\n",i,&i);
//printf("11:i=%p,*i=%d,&i=%p\n",i,*i,&i);
}
void test2(int *p1){
printf("p1=%p\n",p1);
//int *i=p1;//i有指到外面i的地址
int *i=&p1;//與上面的差別?
*i=1;
printf("2:i=%p,&i=%p\n",i,&i);
printf("2:i=%p,*i=%d,&i=%p\n",i,*i,&i);
}
void test22(int *p1){
printf("p1=%p\n",p1);
//int *i=p1;//i有指到外面i的地址
int *i=p1;//與上面的差別?
*i=1;
printf("22:i=%p,&i=%p\n",i,&i);
printf("22:i=%p,*i=%d,&i=%p\n",i,*i,&i);
}
void test3(int p1){
printf("p1=%p\n",p1);
int i=p1;//i有指到外面i的地址
i=3;
printf("3:i=%p,&i=%p\n",i,&i);
//printf("3:i=%p,*i=%d,&i=%p\n",i,*i,&i);
}
void test4(int p1){
printf("p1=%p\n",p1);
int i=p1;//i有指到外面i的地址
i=4;
printf("4:i=%p,&i=%p\n",i,&i);
//printf("4:i=%p,*i=%d,&i=%p\n",i,*i,&i);
}

int main()
{
    memset(&g_AxisController, 0, sizeof(g_AxisController));
    printf("&g_AxisController=%p\n",&g_AxisController);
    printf("g_AxisController=%p\n",g_AxisController);
    printf("&g_AxisController[1]=%p\n",&g_AxisController[1]);
    printf("g_AxisController[1]=%p\n",g_AxisController[1]);
    //printf("*g_AxisController[1]=%d\n",*g_AxisController[1]);
    printf("&g_AxisController[1].InheritMAController=%p\n",&g_AxisController[1].InheritMAController);
    printf("&g_AxisController[1].InheritMAController.CurrMasterCtlCMD=%p\n",&g_AxisController[1].InheritMAController.CurrMasterCtlCMD);
    printf("g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.wCMD=%p\n",g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.wCMD);
    g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.wCMD=1;
    printf("g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.wCMD=%p\n",g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.wCMD);
    printf("g_AxisController=%p\n",g_AxisController);
    printf("g_AxisController[1]=%p\n",g_AxisController[1]);
    printf("g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.bStandstillEnable=%p\n",g_AxisController[1].InheritMAController.CurrMasterCtlCMD.Info.bStandstillEnable);
    printf("&g_AxisController[1].InheritMAController.LastMasterCtlCMD=%p\n",&g_AxisController[1].InheritMAController.LastMasterCtlCMD);
    printf("&g_AxisController[2]=%p\n",&g_AxisController[2]);
    printf("g_AxisController[2]=%p\n\n",g_AxisController[2]);//為什麼沒跟上面一樣???

    TAxisController  *pAxisController=&g_AxisController[1];
    printf("&pAxisController=%p\n",&pAxisController);
    printf("&pAxisController->CurrMasterCtlCMD=%p\n",&pAxisController->CurrMasterCtlCMD);
    printf("&pAxisController=%p\n",&pAxisController->CurrMasterCtlCMD.all);
    printf("&pAxisController=%p\n",&pAxisController->CurrMasterCtlCMD.Info);
    printf("pAxisController->CurrMasterCtlCMD.Info.wCMD=%p\n",pAxisController->CurrMasterCtlCMD.Info.wCMD);
    printf("pAxisController->CurrMasterCtlCMD.Info.bStandstillEnable=%p\n",pAxisController->CurrMasterCtlCMD.Info.bStandstillEnable);
    printf("&pAxisController->LastMasterCtlCMD=%p\n",&pAxisController->LastMasterCtlCMD);
    printf("&pAxisController=%p\n",&pAxisController->wPrepare);
    printf("&pAxisController=%p\n",&pAxisController->wLastPrepare);
    printf("&pAxisController=%p\n",&pAxisController->wControlSource);
    printf("&pAxisController->wHeartbeetCounter=%p\n\n",&pAxisController->wHeartbeetCounter);



    int i = 10;
    printf("&i=%p\n",&i);
    int *iPtr= &i,*ic;
    //iPtr = &i;
    *iPtr=6;
    //iPtr=6;會錯誤
    ic=&iPtr;
    //*ic=5;
    printf("&i=%p\n",&i);
    test1(i);//不會影響到p1
    printf("i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
    printf("&iPtr=%p,ic=%p,*ic=%d\n\n",&iPtr,ic,*ic);
    test11(i);//不會影響到p1
    printf("i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
    printf("&iPtr=%p,ic=%p,*ic=%d\n\n",&iPtr,ic,*ic);
    test2(&i);//會改變p1
    printf("2:i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
    printf("2:&iPtr=%p,ic=%p,*ic=%d\n",&iPtr,ic,*ic);
    test22(&i);//會改變p1
    printf("2:i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
    printf("2:&iPtr=%p,ic=%p,*ic=%d\n",&iPtr,ic,*ic);
    test3(i);//會改變p1
    printf("3:i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
    printf("3:&iPtr=%p,ic=%p,*ic=%d\n",&iPtr,ic,*ic);
    test4(&i);
    printf("4:i=%d,ptr=%p,iptr=%d\n",i,iPtr,*iPtr);
    printf("4:&iPtr=%p,ic=%p,*ic=%d\n",&iPtr,ic,*ic);
    printf("Hello world!\n");
    return 0;
}
