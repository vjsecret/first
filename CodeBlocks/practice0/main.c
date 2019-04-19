//**********展示typedef、調用外部函示與變數*************//
//**********剩使用變數做位元運算***********************//
#include <stdio.h>
#include <stdlib.h>
#include "0912.h"

#ifdef	__cplusplus
extern	"C" {
#endif

float g_fLocalDrift;
float pt(float tin);

#ifdef	__cplusplus
}
#endif
//extern	float g_fLocalDrift;

typedef union tagG1{
    float e1;
struct
    {float e2;
     float e3;
    }eend;
}G1;
G1 test2;

int main()
{
    float tp1;
    float tp2=1.1;
    //bool ts;
    float test;
    float test3;

    tp1=12345;
    test2.e1=1;test2.eend.e2=2;test2.eend.e3=3;
    /******************************/
    test=test2.eend.e2;
    //ts=test2.eend.e3 & (1<<2);
    test3=pt(tp2);
    /******************************/
    printf("%f\n",tp1);
    printf("%g\n",test2);
    printf("%f\n",test3);
    printf("%f\n",g_fLocalDrift);
    //printf("%f\n",g_fLocalDrift);
    printf("Hello world!\n");
    return 0;
}
