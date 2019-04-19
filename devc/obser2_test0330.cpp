#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
//#define f1(y1,y2,)  (y2-l1*(y1-y1))
//#define f2(y1,y2,t)  ((-4.0*y2-4.0*y1)+4*cos(t)+3*sin(t))
using namespace std;

int main()
{
//Parameters of injection machine
double pi=3.1416,Ps,ei,Kv,tao,Kg,Kh,M,Cf,Bf,V10,A1,A2,AN,CN,Sd,AS,CS,AR,CR,h,AC,CC,m,C,K,sigma,a1,a2,a3,a5,a6,a7,a8; 
int L2,minL2Mx,Nd,Nl,Sl,Rd,Rl,Cd,Cl,Dh,Kp,mu,taustar,Qmod,a4,a9,l1,l2;

Ps = 9.7;									//Ps=Supply pressure%
ei = 10;										//ei=D/A converter output voltage%
Kv = 0.25;									//Kv=valve constant%
tao = 13e-3;								//tao=Time constant%
Kg = 398000;								//Kg=Valve flow constant%
Kh = 1020.4;								//Kh=Hydraulic fluid bulk modulus%
M = 140;										//M=Mass of actuator-screw assembly%
Cf = 961.2868;								//Cf=Coulombic friction force%
Bf = 59.5843;								//Bf=Viscous damping coefficient%
V10 = 675400;								//V10=Volume of oil in the injection cylinder when x=0%
A1 = 5654.8*2;								//A1=Cylinder cross-sectional area%

// Barrel
A2 = 32*32*pi/4;							//A2=Barrel cross-sectional area%
L2 = 40;										//L2=Barrel length%
minL2Mx = 2;								//minL2Mx is to prevent L2-x from becoming zero.%
												//V2 = A2*(40-14.5);					%V2=Volume of polymer%

// Nozzle
Nd = 15;										//Nd=Nozzle diameter%
Nl = 110;										//Nl=Nozzle length%
AN = 15*15*pi/4;
CN = pi*Nd;

// Spure
Sd = 5.5;
Sl = 75;
AS = Sd*Sd*2*pi/4;
CS = pi*Sd;

// Runner
Rd = 8;										//Rd=Runner equivalent diameter%
Rl = 115;									//Rl=Runner equivalent length%
AR = Rd*Rd*pi/4/2;
CR = Rd+pi*Rd/2;

// thin-plate mold
Cd = 20;										//Dd=Disk shape mold internal diameter%
Cl = 120;									//Dl=Gate Pressure sensor position from disk center%
h = 1.2;										//%h=Height of plate shape mold%
AC = 1.2*20;
CC = 2*(h+Cd);
Dh = 15;

// Parameters of polymer PS
Kp = 2283 ;
m = 0.2643;
mu = 15400;
taustar = 22729;
//C = (1/taustar)^(1-m);
//K = mu^m/C;
//sigma = 1.05;								//sigma=Mass density at Tp=478%
sigma = 0.94815;
Qmod = 35;  // Qmod for minor loss

a1 = -1e3*Bf/M;
a2 = -1e3*A2/M;
a3 = 1e3*A1/M;
a4 = Kp;
a5 = -Kp/A2;
a6 = 1e9/sigma;
a7 = -1e3/sigma;    //K=6.1968*10^5%
a8 = -Cf/A1;
//a9=(4.01968*10^5)*(32/pi)^m
//a10=-Cf/M;
a9 = -Qmod;
l1=100;
l2=1;
//======initial
    long i,j,n=10;m=5;
    double a=0.0,b=1,step,u[n+1],y1[n+2],y2[n+2],y3[n+2],y4[n+2],y5[n+2],k11[n+1],k21[n+1],k31[n+1],k41[n+1],k51[n+1],p1[n+1],p2[n+1],p3[n+1],p4[n+1],p5[n+1];
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
    printf("%.2lf %10.7lf %10.7lf %10.7lf %10.7lf\n",t,y0[1],fabs(y0[1]-w1(t)),y0[2],fabs(y0[2]-w2(t)));
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
            printf("%.2lf %10.7lf %10.7lf %10.7lf %10.7lf\n",t,y0[1],fabs(y0[1]-w1(t)),y0[2],fabs(y0[2]-w2(t)));
    }
//寫入data      
    fstream outFile;
    outFile.open( "observer.txt", ios::out );
    if( outFile != NULL )    
        {   // 將資料寫入檔案中    
            for (int j=0;j<=n;j++)
            {
            outFile << y1[j]<< "\t" 
                    << y2[j]<< "\t" 
                    << y3[j]<< "\t" 
                    << y4[j]<< "\t" 
                    << endl;
            }
        }
    outFile.close();
    system("pause"); 
    return 0;   
}   
