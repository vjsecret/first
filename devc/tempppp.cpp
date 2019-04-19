#include <stdlib.h> 
#include <iostream>
#include <fstream> //存檔案須用
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;
int main(){
double pi=3.1416,Ps,ei,Kv,tao,Kg,Kh,M,Cf,Bf,V10,A1,A2,AN,CN,Sd,AS,CS,AR,CR,h,AC,CC,m,K,sigma,Nq,Rq,Sq,Cq,a1,a2,a3,a5,a6,a7,a8,a10,a11,x1,x2,x3,x4,x5,xs,xr,xc,x[9],Q[16],C1[10],fx5,G[12],switch1,switch8,starttime,endtime,c_start1,c_stop1,CPU_execution_time1,AAA[12][6],BBB[12][6],BBBT[12][6],C2[12][6],C3[12][6];
int L2,minL2Mx,Nd,Nl,Sl,Rd,Rl,Cd,Cl,Dh,Kp,mu,taustar,Qmod,a4,a9,l1,l2,sgnx4;
//cudaEvent_t start,stop;
//cudaEventCreate(&start);
//cudaEventCreate(&stop);
//float elapsedTime;
long double C;
//Parameters of injection machine
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
C = pow((1/taustar),(1-m));
K = pow(mu,m)/C;
//sigma = 1.05;								//sigma=Mass density at Tp=478%
sigma = 0.94815;
Qmod = 35;  // Qmod for minor loss

Nq = 32*mu/(pi*pow(Nd,3));
Sq = 32*mu/(pi*pow(Sd,3));
Rq = 32*mu/(pi*pow(Rd,3));
Cq = 6*mu/(Cd*pow(h,2));


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
//initial value
l1=100;
l2=10;
// theda = 5

//cudaEventRecord(start,0);
starttime = clock();
c_start1 = (double)clock();
x1 = 1;
x2 = 1.5;
x3 = 1;
x4=-1;
x5 = 0;
xs=0;
xr=0;
xc=0;
a10 = (1-m);
a11= -1*m;
x[0]=x1;
x[1]=x2;
x[3]=x3;
x[4]=x4;
x[5]=x5;
x[6]=xs;
x[7]=xr;
x[8]=xc;
//gbar&dg/dx4會用到的變數
Q[0] = Nq*fabs(x[3]);
Q[1] = Sq*fabs(x[3]);
Q[2] = Rq*fabs(x[3]);
Q[3] = Cq*fabs(x[3]);
Q[4] = Nl; 
Q[5] =xs;
Q[6] = xr;
Q[7] = xc;
Q[8] = AN;
Q[9] = AS;
Q[10] = AR; 
Q[11] =AC;
Q[12] = CN;
Q[13] = CS;
Q[14] = 2*CR;
Q[15] = 2*CC; 
C1[0] = Nq*CN/AN;
C1[1] = Sq*CS/AS;
C1[2] = Rq*CR/AR;
C1[3] = Cq*CC/AC;
C1[4] = C*sgnx4;
C1[5] = 1/(L2-x[0]);
C1[6] = 1/pow((L2-x[0]),2);
C1[7] = 1/fx5;
C1[8] = 1/pow(fx5,2);
C1[9] = 2/(L2-x[0]);	

//Q[0] = Nq*fabs(x[3]);
Q[1] = Sq*fabs(x[3]);
Q[2] = Rq*fabs(x[3]);
Q[3] = Cq*CC/AC;

printf("Sq=%f\n",Sq);
printf("Rq=%f\n",Rq);
printf("C=%f\n",C);
printf("Q[]={%f,%f,%f,%f}\n",Q[1],Q[2],Q[3]);
system("pause");
return 0;
}
