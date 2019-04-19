#include <stdio.h>
#include <time.h>
#include <ctime>
#include <windows.h>
#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70
 using namespace std;
 int main()
 {
     int size = 50;
           srand(time(0));   //設定亂數表
                  
        float A[50];        
        for(int k=0; k<size; k++)
        {
                A[k]=rand()/17;                
        }
       cout<< A[0] << endl;
       cout<< A[1] << endl;
       cout<< A[2] << endl;
       printf("A[0]=%f\n",A[0]);
       printf("A[1]=%f\n",A[1]);
       printf("A[2]=%f\n",A[2]);
  system("pause");      
 }
