#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70
//#include <cstdlib>
unsigned int h_A,size_A;
int i;
//clock_t start_tick=0, end_tick=0;
using namespace std; //when it add, then you can use endl
main() //int main(int argc, char *argv[]) 
{
       clock_t start_tick, end_tick;
       double elapsed;
       int temp;
       start_tick=clock();
       printf("start_tick=%f\n",(double) start_tick);
       //h_A=5;size_A=5;
       srand((unsigned) time(NULL));
       /*for (i=0; i<=6; i++)
       {
        A[i]=rand(); //how to use srand? page 73
       }*/
       //printf("%f\n",h_A);
//      randomInit(h_A, size_A);

        for (i=0; i<=1000000; i++)
        {
            double A[];
            A[i]=rand();
         cout<< "A=["<< i <<"]="<< A[i] << endl;
        }
       //printf("%f\n",A);
       end_tick=clock();//chap6 page69
       printf("end_tick=%g\n",(double) end_tick);
       temp = 1000;
       printf("CLOCKS_PER_SEC=%d\n",(int) CLOCKS_PER_SEC);
       printf("CLOCKS_PER_SEC=%d\n",temp);
       printf(" CLK_TCK=%d\n", CLK_TCK);
       elapsed =(double)(end_tick-start_tick)/ CLOCKS_PER_SEC;
       printf("time=%f\n", elapsed);
       cout <<"time=" << (double)elapsed  << "s"<< endl;
       system ("pause");
}
