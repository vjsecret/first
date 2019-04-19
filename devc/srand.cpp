#include <stdio.h>
#include <time.h>
#include <ctime>
#include <windows.h>
#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70
using namespace std; //when it add, then you can use endl
int main()
{
    int size;
    size=9;
    int A[size];
srand((unsigned) time(NULL) );

    for (int i=0; i<=size; i++)
           {
            A[i]=rand(); //how to use srand? page 73
            cout<< "A["<< i <<"]="<< A[i] << endl;
           }

system ("pause");
}
