#include <iostream>
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
    long i,j,n=10,m=2;
    double t,a=0.0,b=1,h,k1[10],k2[10],y[10],y0[10];
    h=(b-a)/n;
    t=a;
    y0[1]=1.0;
    y0[2]=0.0;
    
    for(j=1;j<=m;j++)
    {
    y[j]=y0[j];
    printf("t      y1       |y1-w1(t)|     y2     |y2-w2(t)|\n");
    printf("==============================================================================\n");
    printf("%.2lf %10.7lf %10.7lf %10.7lf %10.7lf\n",t,y[1],fabs(y0[1]-w1(t)),y[2],fabs(y0[2]-w2(t)));
    }
    for(i=1;i<=n;i++)
    {
         for(j=1;j<=m;j++)
         {
              if(j==1)              
               k1[j]=h*f1(0,y[j+1],0);
              else if (j==2)
               k1[j]=h*f2(y[j-1],y[j],t);
         }
         for(j=1;j<=m;j++)
         {
              if(j==1)
               k2[j]=h*f1(0,(y[j+1]+k1[j+1]),0);
              else if (j==2)
               k2[j]=h*f2((y[j-1]+k1[j-1]),(y[j]+k1[j]),(t+h));
         }
         for(j=1;j<=m;j++)
           y[j]=y[j]+0.5*(k1[j]+k2[j]);
           t=a+i*h;
           if(i%1==0)
            printf("%.2lf %10.7lf %10.7lf %10.7lf %10.7lf\n",t,y[1],fabs(y[1]-w1(t)),y[2],fabs(y[2]-w2(t)));
    }
    system("pause"); 
    return 0;   
}
