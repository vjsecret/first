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
            double t,a=0.0,b=1,h,k11[n+1],k12[n+1],k21[n+1],k22[n+1],y1[n+1],y2[n+1],A1[n+1],A2[n+1];
            h=(b-a)/n;
            t=a;
            y1[0]=1.0; 
            y2[0]=0.0; 

//real solve
        for(j=0;j<=n;j++)       
         {
         A1[j]=w1(h*j);
         //printf("w1[0]=%f\n",w1(h*j));
         //printf("A1[0]=%f\n",A1[0]);
         A2[j]=w2(h*j); 
         printf("A1=%f\t A2=%f\n",A1[j],w2(h*j));
         //printf("A1[0]=%f\n",A1[0]); 
         }
//range_kutta
        for(j=0;j<=n;j++) 
        {
            k11[j]=h*f1(y1[j],y2[j],t);
            k12[j]=h*f2(y1[j],y2[j],t);
            k21[j]=h*f1((y1[j]+k11[j]),(y2[j]+k12[j]),(t+h));
            k22[j]=h*f2((y1[j]+k11[j]),(y2[j]+k12[j]),(t+h));
            y1[j+1]=y1[j]+0.5*(k11[j]+k21[j]);
            y2[j+1]=y2[j]+0.5*(k12[j]+k22[j]);
            t=a+(j+1)*h;
            printf("k11=%f\t k12=%f\t k21=%f\t k22=%f\t",k11[j],k12[j],k21[j],k22[j]);
            printf("y1=%f\t y2=%f\n",y1[j],y2[j]); 
        }

//寫入A1,A2       
    fstream outFile;
    outFile.open("2ndkutta.txt",ios::out );
    if( outFile != NULL )    
        {   // 將資料寫入檔案中    
            for (int j=0;j<=n;j++)
            {
            outFile << A1[j]<< "\t" 
                    << A2[j]<< "\t" 
                    << y1[j]<< "\t" 
                    << y2[j]<< "\t" 
                    << endl;
            }
        }
    outFile.close();
    system("pause"); 
    return 0;   
}
