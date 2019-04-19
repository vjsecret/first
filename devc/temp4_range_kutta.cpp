#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#define f1(y1,y2,t)  (y2)
#define f2(y1,y2,t)  ((-4.0*y2-4.0*y1)+4*cos(t)+3*sin(t))
#define w1(t) ((1+t)*(1.0/exp(2*t))+sin(t))
#define w2(t) (cos(t)-(1.0/exp(2*t))*(2*t+1))
using namespace std;

int main()
{
     //=========================
     //initial
     //==========================
            long i,j,n=10;
            double t,a=0.0,b=1,h,k11[n+1],k12[n+1],k21[n+1],k22[n+1],k31[n+1],k32[n+1],k41[n+1],k42[n+1],y1[n+1],y2[n+1],A1[n+1],A2[n+1];
            h=(b-a)/n;
            t=a;
            y1[0]=1.0;
            y2[0]=0.0; 
            
//range_kutta
        for(j=0;j<=n;j++) 
        {
            k11[j]=h*f1(y1[j],y2[j],t);
            k12[j]=h*f2(y1[j],y2[j],t);
            k21[j]=h*f1(y1[j]+0.5*k11[j],y2[j]+0.5*k12[j],t);
            k22[j]=h*f2(y1[j]+0.5*k11[j],y2[j]+0.5*k12[j],t);
            k31[j]=h*f1(y1[j]+0.5*k21[j],y2[j]+0.5*k22[j],t);
            k32[j]=h*f2(y1[j]+0.5*k21[j],y2[j]+0.5*k22[j],t);    
            k41[j]=h*f1(y1[j]+k31[j],y2[j]+k32[j],t);
            k42[j]=h*f2(y1[j]+k31[j],y2[j]+k32[j],t);
            y1[j+1]=y1[j]+(k11[j]+2*k21[j]+2*k31[j]+2*k41[j])/6;
            y2[j+1]=y2[j]+(k12[j]+2*k22[j]+2*k32[j]+2*k42[j])/6;
            t=a+j*h;
            printf("k11=%f\t k12=%f\t k21=%f\t k22=%f\t",k11[j],k12[j],k21[j],k22[j]);
            printf("k31=%f\t k32=%f\t k41=%f\t k42=%f\t",k31[j],k32[j],k41[j],k42[j]);
            printf("y1=%f\t y2=%f\n",y1[j],y2[j]); 
        }
//寫入A1,A2       
    fstream outFile;
    outFile.open("temp4kutta.txt",ios::out );
    if( outFile != NULL )    
        {   // 將資料寫入檔案中    
            for (int j=0;j<=n;j++)
            {
            outFile << y1[j]<< "\t" 
                    << y2[j]<< "\t" 
                    << endl;
            }
        }
    outFile.close();
    system("pause");  
}
