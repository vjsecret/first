#include<stdio.h>    
#include<stdlib.h> 
#include<time.h> 
#include <math.h>

using namespace std;
int main()
{   
	int m=1024;
    int n=1024;
    int l=1024;
    //cudaError_t  r;   //�������~�T�� 
    
    
    int size=5;
    int a[5]={0,1,2,3,4}, b[5];        
//    a[5]={0,1,2,3,4};               

    //��l�� A�BB ��}�C
        printf("(1) Initialize Random Array : size=%d  a[]={rand()}  b={0}\n", size);                  
        printf("    a[]={%d,%d,%d,...}\n", a[0], a[1], a[2]);
        printf("    b[]={%d,%d,%d,...}\n\n", b[0], b[1], b[2]);
      //��X��}�C���e�T�Ӽƭ�
	system("pause");
  
}
