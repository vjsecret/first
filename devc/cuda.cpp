#include <iostream>
#include <fstream> //存檔案須用
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <sys/time.h>
//#include <cuda.h>
//#define f1(y1,y2,)  (y2-l1*(y1-y1))
//#define f2(y1,y2,t)  ((-4.0*y2-4.0*y1)+4*cos(t)+3*sin(t))
using namespace std;

int main()
{
double pi=3.1416,Ps,ei,Kv,tao,Kg,Kh,M,Cf,Bf,V10,A1,A2,AN,CN,Sd,AS,CS,AR,CR,h,AC,CC,m,C,K,sigma,Nq,Rq,Sq,Cq,a1,a2,a3,a5,a6,a7,a8,a10,a11,x1,x2,x3,x4,x5,xs,xr,xc,x[9],Q[16],C1[10],fx5,G[12],switch1,switch8,starttime,endtime,c_start1,c_stop1,CPU_execution_time1,AAA[12][6],BBB[12][6],BBBT[12][6],C2[12][6],C3[12][6];
int L2,minL2Mx,Nd,Nl,Sl,Rd,Rl,Cd,Cl,Dh,Kp,mu,taustar,Qmod,a4,a9,l1,l2,sgnx4;
//cudaEvent_t start,stop;
//cudaEventCreate(&start);
//cudaEventCreate(&stop);
//float elapsedTime;

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
//C = (1/taustar)^(1-m);
//K = mu^m/C;
//sigma = 1.05;								//sigma=Mass density at Tp=478%
sigma = 0.94815;
Qmod = 35;  // Qmod for minor loss

Nq = 32*mu/(pi*pow(Nd,3));
Sq = 32*mu/(pi*pow(Sd,3));
Rq = 32*mu/(pi*pow(Rd,3));
Cq = 6*mu/(Cd*pow(h,3));


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
//計算想要使用的變數G(1)~G(4)=gbar,G(5)=g,G(6)=dg/dx4,G(7)=df/dx5,G(8)=dg/dx5,1/(L2-x1(1)),1/(L2-x1(1))^2,1/f(x5),1/f(x5)^2
fx5=Nl/AN+xs/AS+xr/AR+xc/AC; //f(x5)
//判斷sgnx4,dg/dx5,df/dx5
if (x4>0)
          sgnx4 = 1;
else if (x4 == 0)
        sgnx4 = 0;
    else
      sgnx4 = -1;  
for (int i=0;i<=3;i++)
{
G[i] = C1[i]/(1+C1[4]*pow(Q[i],a10)); //gbar
G[i+8]=-a10*C1[5]*pow(G[i],2)*Q[i+4]*Q[i+8]*pow(Q[i],a11);
}
G[4] = G[1]*Nl+G[2]*x[5]+G[1]*x[6]+G[3]*x[7]; //g
G[5] = G[8]+G[9]+G[10]+G[11]; //dgdx4
if (xs < Sl){
    switch1=1/pow(AS,2);
    switch8 = G[9]/AS;}
else
    {switch1=1/2*pow(AR,2);  
    switch8 = G[10]/(2*AR);
}
if (xr<Rl){
    G[6]=switch1; //G(7)=dfdx5
    G[7]=switch8; //G(8)=dgdx5
}
else
    {G[6]=1/(2*pow(AC,2));
    G[7]=G[11]/(2*AC);
}
AAA[0][0]= a5;
AAA[0][1]= a5;
AAA[0][2]= a7;
AAA[0][3]= a9;
AAA[0][4]= a6;
AAA[0][5]= a7;
AAA[1][0]= a4;
AAA[1][1]= a2;
AAA[1][2]= a1;
AAA[1][3]= a5;
AAA[1][4]= a2;
AAA[1][5]= 1;
AAA[2][0]= a5;
AAA[2][1]= 0;
AAA[2][2]= 1;
AAA[2][3]= 0;
AAA[2][4]= x[1];
AAA[2][5]= 0;
AAA[3][0]= a1;
AAA[3][1]= a1;
AAA[3][2]= a1;
AAA[3][3]= 0;
AAA[3][4]= 0;
AAA[3][5]= 0;
AAA[4][0]= a2;
AAA[4][1]= a1;
AAA[4][2]= 0;
AAA[4][3]= 0;
AAA[4][4]= 0;
AAA[4][5]= 0;
AAA[5][0]= a5;
AAA[5][1]= a2;
AAA[5][2]= a2;
AAA[5][3]= a1;
AAA[5][4]= 0;
AAA[5][5]= 0;
AAA[6][0]= C1[5];
AAA[6][1]= 1;
AAA[6][2]= 1;
AAA[6][3]= 1;
AAA[6][4]= 0;
AAA[6][5]= 0;
AAA[7][0]= C1[6];
AAA[7][1]= 1;
AAA[7][2]= 1;
AAA[7][3]= 0;
AAA[7][4]= 0;
AAA[7][5]= 1;
AAA[8][0]= C1[5];
AAA[8][1]= 1;
AAA[8][2]= 1;
AAA[8][3]= 0;
AAA[8][4]= a7;
AAA[8][5]= 0;
AAA[9][0]= C1[5];
AAA[9][1]= x[3];
AAA[9][2]= 2;
AAA[9][3]= -1;
AAA[9][4]= a7;
AAA[9][5]= 0;
AAA[10][0]= C1[6];
AAA[10][1]= 2;
AAA[10][2]= 1;
AAA[10][3]= 0;
AAA[10][4]= 0;
AAA[10][5]= 0;
AAA[11][0]= C1[6];
AAA[11][1]= 0;
AAA[11][2]= 0;
AAA[11][3]= 0;
AAA[11][4]= x[1];
AAA[11][5]= 0;

BBB[0][0]= x[3];
BBB[0][1]= a6;
BBB[0][2]= G[4];
BBB[0][3]= x[3];
BBB[0][4]= x[2];
BBB[0][5]= x[3];
BBB[1][0]= x[1];
BBB[1][1]= x[2];
BBB[1][2]= x[1];
BBB[1][3]= a6;
BBB[1][4]= a4;
BBB[1][5]= 2;
BBB[2][0]= a6;
BBB[2][1]= 0;
BBB[2][2]= x[2];
BBB[2][3]= 0;
BBB[2][4]= x[2];
BBB[2][5]= 0;
BBB[3][0]= a4;
BBB[3][1]= x[3];
BBB[3][2]= x[1];
BBB[3][3]= 0;
BBB[3][4]= 0;
BBB[3][5]= 0;
BBB[4][0]= a4;
BBB[4][1]= x[2];
BBB[4][2]= 0;
BBB[4][3]= 0;
BBB[4][4]= 0;
BBB[4][5]= 0;
BBB[5][0]= x[3];
BBB[5][1]= a4;
BBB[5][2]= x[2];
BBB[5][3]= x[1];
BBB[5][4]= 0;
BBB[5][5]= 0;
BBB[6][0]= 1;
BBB[6][1]= x[2];
BBB[6][2]= x[1];
BBB[6][3]= a3;
BBB[6][4]= 0;
BBB[6][5]= 0;
BBB[7][0]= x[1];
BBB[7][1]= a3;
BBB[7][2]= 3;
BBB[7][3]= 0;
BBB[7][4]= 0;
BBB[7][5]= 1;
BBB[8][0]= C1[7];
BBB[8][1]= x[2];
BBB[8][2]= 1;
BBB[8][3]= G[7];
BBB[8][4]= G[5];
BBB[8][5]= 0;
BBB[9][0]= C1[8];
BBB[9][1]= G[6];
BBB[9][2]= a9;
BBB[9][3]= G[6];
BBB[9][4]= G[4];
BBB[9][5]= 0;
BBB[10][0]= C1[7];
BBB[10][1]= x[1];
BBB[10][2]= 1;
BBB[10][3]= 0;
BBB[10][4]= 0;
BBB[10][5]= 0;
BBB[11][0]= C1[9];
BBB[11][1]= 0;
BBB[11][2]= 0;
BBB[11][3]= 0;
BBB[11][4]= x[1];
BBB[11][5]= 0;

for(int ii=0;ii<12;ii++){
for(int jj=0;jj<6;jj++){
BBBT[jj][ii]=BBB[ii][jj];
}
}
//AAA*BBB=C2與testA1對照
for (int jjj=0;jjj<12;jjj++){
    for (int iii=0;iii<6;iii++){
        C2[jjj][iii]=AAA[jjj][iii]*BBBT[iii][jjj];
        }
}
//C2*C2=C3與testA2對照
for (int jj =0;jj<12;jj++){
    for (int ii=0;ii<6;ii++){
    C3[jj][ii]=C2[jj][1]*C2[jj][ii];
        }
}

//cudaEventRecord(stop,0);
//cudaEventSynchronize(stop); 
//cudaEventElapsedTime(&elapsedTime, start, stop);
c_stop1 = (double)clock();
endtime = clock();
CPU_execution_time1 = (c_stop1 - c_start1)/(double)CLOCKS_PER_SEC;


printf(" ======== Execution Infomation ========\n");
printf("sgnx4=%d\n",sgnx4);
printf("fx5=%f\n",fx5);
printf("fabs(x[3])=%f\n",fabs(x[3]));
printf("switch1=%f\n",switch1);
printf("switch8=%f\n",switch8);
printf("x[]={%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8]);
printf("Q[]={%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",Q[1],Q[2],Q[3],Q[4],Q[5],Q[6],Q[7],Q[8],Q[9],Q[10],Q[11],Q[12],Q[13],Q[14],Q[15]);
printf("G[]={%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",G[1],G[2],G[3],G[4],G[5],G[6],G[7],G[8],G[9],G[10],G[11]);
//printf(" Excuetion Time on GPU: %3.20f s\n",elapsedTime/1000);       
printf(" Excuetion Time on CPU: %3.20f s\n",CPU_execution_time1); 
cout <<"time=" << (double)(endtime-starttime)/ CLOCKS_PER_SEC << "s"<< endl;
system("pause");    
}   
