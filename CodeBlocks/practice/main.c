//**********展示typedef、調用外部函示與變數*************//
//**********剩使用變數做位元運算***********************//
#include <stdio.h>
#include <stdlib.h>
#include "0912.h"
#ifndef   GLOBAL_Q
#define   GLOBAL_Q       24
#endif
#include "IQmathLib.h"

#ifdef	__cplusplus
extern	"C" {
#endif

float g_fLocalDrift;
float pt(float tin);

#ifdef	__cplusplus
}
#endif
//extern	float g_fLocalDrift;


#define PI 3.14159
#define __IQMATHLIB_H_INCLUDED__
#define   FLOAT_MATH     1
#define   IQ_MATH        0
#ifndef   MATH_TYPE
#define   MATH_TYPE      IQ_MATH
#define   QG          GLOBAL_Q
#define   Q29         29
#endif
typedef   long    _iq29;
#define   _IQ29(A)      (long) ((A) * 536870912.0L)
extern    float _IQ29toF(long A);

typedef union tagG1{
    float e1;
struct
    {float e2;
     float e3;
    }eend;
}G1;
G1 test2;

// 定義callback function的prototype。
typedef void (* CALLBACK) (float);
// 定義了一個名為ShowPercentage的函式。這就是我們的callback函式。
// 他的prototype必須與前面的CALLBACK宣告一致。
void ShowPercentage(float percentage)
{
    printf("percentage=%f\n",percentage);
}
void calculate(float a, float b, CALLBACK callback)
{  callback(a*b*100);}

void mytest(float a){
printf("a=%f\n",a);
}
typedef void(* SHOW)(float);
void tempmain(float a, SHOW cc){
    printf("tt_a=%f\n",a);
cc(a*2);
}

int main()
{
    float tp1;
    float tp2=1.1;
    //bool ts;
    float test;
    float test3;
    float tt=3;
    //_iq input, sin_out;
    tp1=12345;
    test2.e1=1;test2.eend.e2=2;test2.eend.e3=3;
    /******************************/
    test=test2.eend.e2;
    //ts=test2.eend.e3 & (1<<2);
    test3=pt(tp2);

    //input=_IQ29(0.25*PI); /* 0.25´p radians represented in Q29 format*/
    //sin_out =_IQ29*sin(input);
    calculate(0.23,0.55,ShowPercentage);
    printf("tt=%f\n",tt);
    tempmain(tt,mytest);
    printf("tt=%f\n",tt);
    /******************************/
    printf("%f\n",tp1);
    printf("%g\n",test2);
    printf("%f\n",test3);
    printf("%f\n",g_fLocalDrift);

    //printf("%f\n",g_fLocalDrift);
    printf("Hello world!\n");
    return 0;
}
