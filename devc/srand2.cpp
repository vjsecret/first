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
    //cudaError_t  r;   //�������~�T�� 
    
    srand(200);   //�]�w�üƪ� 
    int size=5;
    int a[5], b[5];        
    for(int k=0; k<=size; k++)
    {
      a[k]=rand();
      b[k]=0;
    }                  

    //��l�� A�BB ��}�C
        printf("(1) Initialize Random Array : size=%d  a[]={rand()}  b={0}\n", size);                  
        printf("    a[]={%d,%d,%d,...}\n", a[0], a[1], a[2]);
        printf("    b[]={%d,%d,%d,...}\n\n", b[0], b[1], b[2]);
      //��X��}�C���e�T�Ӽƭ�
	system("pause");
  
}
