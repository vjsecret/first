#include<stdio.h>    
#include<stdlib.h> 
#include<time.h> 

#include <math.h>
//--------------------------------------------------------------------
//A : m x l
//B : l x n
//C : m x n    (C=A*B)
//--------------------------------------------------------------------
using namespace std;
int main()
{   
	int m=1024;
    int n=1024;
    int l=1024;
    //cudaError_t  r;   //接收錯誤訊息 
    
    srand(200);   //設定亂數表 
    int size=5;
    int a[5], b[5];        
    for(int k=0; k<=size; k++)
    {
      a[k]=rand();
      b[k]=0;
    }                  

    //初始化 A、B 兩陣列
        printf("(1) Initialize Random Array : size=%d  a[]={rand()}  b={0}\n", size);                  
        printf("    a[]={%d,%d,%d,...}\n", a[0], a[1], a[2]);
        printf("    b[]={%d,%d,%d,...}\n\n", b[0], b[1], b[2]);
      //輸出兩陣列的前三個數值
	system("pause");
  
}
