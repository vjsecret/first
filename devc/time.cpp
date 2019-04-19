#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <time.h>
#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70
using namespace std; //when it add, then you can use endl
int main(void) //int main(int argc, char *argv[]) 
{
       double starttime,endtime;
       starttime = clock();
       printf("starttime=%g\n",starttime);
       for (int i=0; i<100000000; i++)
        {
             ;
        }
 
        endtime = clock();//chap6 page69
       printf("endtime=%g\n",endtime);      
       printf("CLOCKS_PER_SEC=%g\n",CLOCKS_PER_SEC);
       printf(" CLK_TCK=%g\n", CLK_TCK);      
       cout <<"time=" << (double)(endtime-starttime)/ CLOCKS_PER_SEC << "s"<< endl;
       system ("pause");
}
