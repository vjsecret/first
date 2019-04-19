#include <stdio.h>
#include <windows.h>
#include <iostream> //when it add, then you can use cout
double GPU(double a,double b);
using namespace std; //when it add, then you can use endl
int main() //int main(int argc, char *argv[]) 
{
    double c,k;
    c=0.0,k=1.0;
    double out;
    out=GPU(c,k);
    cout <<"k="<< k<< endl;
     cout <<"out="<< out << endl;
    system("pause");
}
double GPU(double a,double b)
{
 b=a+2;
 cout <<"b="<< b<< endl;    
 return b;
}
