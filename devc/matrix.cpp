#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70
//#include <cstdlib>
unsigned int h_A,size_A;
int num;
//double starttime, endtime;
/*void randomInit(float*, int);
void randomInit(float* data, int size)
{
    for (int i = 0; i < size; ++i)
        data[i] = rand() / (float)RAND_MAX;
}*/

using namespace std; //when it add, then you can use endl
main() //int main(int argc, char *argv[]) 
{
       double starttime, endtime;
       starttime=clock();
       printf("starttime=%f\n",starttime);
// initialize host memory
/*    randomInit(h_A, size_A);
    randomInit(h_B, size_B);
*/       int m[2][2];//={{1,2},{3,4}};
       int i,j;   
       int a = 5, b =3;
       printf("a-b=%d\n",a-b);   
//       for(i=1;i<=9;i++)   for(j=1;j<=9;j++)     
         srand((unsigned) time(NULL));
       for(i=0;i<=1;i++) 
       {   
            for(j=0;j<=1;j++)   
            {     
                   //m[i-1][j-1]=i*j;
                   //cout << i << "*" << j << "=" << m[i-1][j-1] << "\t"; 
                   m[i][j]=rand();
                   cout<< "m["<< i <<"]["<< j <<"]="<< m[i][j] << endl;  
            }   
            cout << "\n"; 
       } 
     
       //printf("%f\n",A);
       endtime=clock();//chap6 page69
       printf("endtime=%f\n",endtime);
       printf("CLOCKS_PER_SEC=%g\n",CLOCKS_PER_SEC);//(*10^3)
       printf(" CLK_TCK=%g\n", CLK_TCK);
       cout <<"time=" << (double)(endtime-starttime)/ CLK_TCK << "s"<< endl;
       system ("pause");
}


