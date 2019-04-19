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
    int i,n=10;
    double a=0.0,b=1,step,u[n+1],y1[n+2],y2[n+2],y3[n+2],y4[n+2],y5[n+2],k11[n+1],k21[n+1],k31[n+1],k41[n+1],k51[n+1],p1[n+1],p2[n+1],p3[n+1],p4[n+1],p5[n+1];
    step=(b-a)/n;
    y1[1]=0.1;
    y2[1]=0.1;
    y3[1]=0.1;
    y4[1]=0;
    y5[1]=0;
    for (i=0;i<=n;i++)
    {
     u[i]=-((100/5.83)*y1[i]-(620/5.83))-57.2;
    }
    //start
    for (i=0;i<=n;i++)
    {
    //step1
    k11[i]=y2[i+1]-l1*(y1[i+1]-y1[i]);
    k21[i]=a1*y2[i+1]+a2*y3[i+1]+a3*u[i]-l2*(y1[i+1]-y1[i]);
    //printf("k11=%f\t",k11[i]);
    //printf("k21=%f\n",k21[i]);
    //step2
    p1[i]=y1[i+1]+step*k11[i];
    p2[i]=y2[i+1]+step*k21[i];
    //printf("p1=%f\t",p1[i]);
    //printf("p2=%f\n",p2[i]);
    //step4
    y1[i+2]=y1[i]+0.5*step*(k11[i]+p2[i]-l1*(p1[i]-y1[i]));
    printf("y1=%f\n",y1[i]);
    }
    
//�g�Jdata      
    fstream outFile;
    outFile.open( "observer.txt", ios::out );
    if( outFile != NULL )    
        {   // �N��Ƽg�J�ɮפ�    
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
