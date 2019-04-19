#include <stdio.h>    
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream> //存檔案須用


float a[2]={0,1},b[2]={2,3};
float A[2]={6,7},B[2]={8,9};

void test1(float x[2],float y[2]){
x[0]=x[0]+a[0];
x[1]=x[1]+a[1];
y[0]=y[0]+b[0];
y[1]=y[1]+b[1];
}

using namespace std;
int main(){

	test1(A,B);

//--------------save------------
fstream out2File;
	out2File.open("test1.xls",ios::out );
    if( out2File != NULL )    
        {       
            for (int k=0;k<2;k++)
            {
            out2File << A[k]<<"\t"
				     << B[k]<<"\n"                  
                     << endl;
            }
        }
     out2File.close();  
	system("pause");
}