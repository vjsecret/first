#include <stdio.h>    
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream> //存檔案須用

int size1=16;    //要配置的記憶體大小
int size=36;    //要配置的記憶體大小
//float* g;       //指向顯示卡記憶體位置的指標
//float* g2;          

float a[9]={-2,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0}, b[9], c[9]; 
float d[36],e[36],f[36],g[36],hc1[36],hc2[36],hd1[36],hd2[36];
/*,9.0,10.0,11.0,12.0,13.0,14.0,15.0}*/ 
float pi=3.1416,Ps,ei,Kv,tao,Kg,Kh,M,Cf,Bf,V10,A1,A2,AN,CN,Sd,AS,CS,AR,CR,h,AC,CC,m,C,K,sigma,Nq,Rq,Sq,Cq,a1,a2,a3,a5,a6,a7,a8,a10,a11;
float vp,x1,x2,x3,x4,x5,xs,xr,xc,x1t,x3t,x1t_bar,x3t_bar,u,ut,ut_bar,x[8],x_bar[8],xi[5],xi_bar[5],y[5],theda,sampletime,step;
float Q[16],C1[10],fx5,G[12],switch1,switch8,AAA[12][6],BBB[12][6],BBBT[12][6],C2[12][6],C3[12][6],temp1[6][7],temp2[6][7], temp3[6]={0},temp4[6][7], temp5[6][7],temp6[6]={0},temp7[6][7],temp8[6][7],finalB[6][5],finalC[5],F[5],F_bar[5],tempp[2];
int sgnx4;
int L2,minL2Mx,Nd,Nl,Sl,Rd,Rl,Cd,Cl,Dh,Kp,mu,taustar,Qmod,a4,a9,l1,l2,nn;
double c_start,c_stop,CPU_execution_time;
using namespace std;
int main(){
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
AS = Sd*Sd*pi/4;
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
//C = pow((1/taustar),(1-m));
C = 6.235393303410815e-04;
K = pow(mu,m)/C;
//sigma = 1.05;								//sigma=Mass density at Tp=478%
sigma = 0.94815;
Qmod = 33;  // Qmod for minor loss

Nq = 32*mu/(pi*Nd*Nd*Nd);
Sq = 32*mu/(pi*Sd*Sd*Sd);
Rq = 32*mu/(pi*Rd*Rd*Rd);
//Nq = 32*mu/(pi*Math::Pow(Nd,3));
//Sq = 32*mu/(pi*Math::Pow(Sd,3));
//Rq = 32*mu/(pi*Math::Pow(Rd,3));
Cq = 6*mu/(Cd*h*h);

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

Q[0] = Nq*CN/AN; 
Q[1] = Sq*CS/AS;
Q[2] = Rq*CR/AR;
Q[3] = Cq*CC/AC;
Q[4] = AN;
Q[5] = AS;
Q[6] = AR; 
Q[7] = AC;
Q[8] = CN;
Q[9] = CS;
Q[10] = 2*CR;
Q[11] = 2*CC; 
printf("Q[]={%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\n\n",Q[0],Q[1],Q[2],Q[3],Q[4],Q[5],Q[6],Q[7],Q[8],Q[9],Q[10],Q[11]);
//initial value
l1=100;
l2=10;
theda = 5;
nn=1000; //stepsize
sampletime=0.01;
step=sampletime/nn;
a10 = (1-m);
a11= -1*m;
x[5] = Nl;

//---------------讀檔 
u =0.1929182*2.2;
x1 = -((100/5.83)*2.434676-(620/5.83))-57.2;
x2 = 0.5;   //1.5
x3 = 0.4;   //(0.5421246-0.53)*30;   
x4 = 0.01;
x5 = 0;  
xs=0;
xr=0;
xc=0;
c_start = (double)clock();	
//-----------------------------------start----------------------------
//for(long int i = 1; i <= 100000; i++ )
//{
//for(long int i = 1; i <= 1000; i++ )
//{
int counter =1;
//-------------------------initial value-----------------
//------------量測值&單位換算 
ut=0.48888884;
x1t=8.13927958833619;
x3t=1.828937999999998;
//--------處理 
ut_bar=u+counter*(ut-u)/step;
x1t_bar=x1+counter*(x1t-x1)/step;
x3t_bar=x3+counter*(x3t-x3)/step;

x[0]=x1;
x[1]=x2;
x[2]=x3;
x[3]=x4;
x[4]=x5;
x[6]=xs;
x[7]=xr;
x[8]=xc;
//printf("x[]={%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
//-------------------------f(x5)
fx5=Nl/AN+x[6]/AS+x[7]/AR+x[8]/AC; 
//printf("fx5=%f\n",fx5);
//------------------判斷sgnx4
if (x[3]>0)
          sgnx4 = 1;
else if (x[3] == 0)
        sgnx4 = 0;
    else
      sgnx4 = -1; 
//printf("sgnx4=%d\n",sgnx4);
//-----------------------gbar&dg/dx4會用到的變數      
C1[0] = Nq*fabs(x[3]);
C1[1] = Sq*fabs(x[3]);
C1[2] = Rq*fabs(x[3]);
C1[3] = Cq*fabs(x[3]);
C1[4] = C*sgnx4; // 差很少
//printf("C*sgnx4=%f;6.235393303410815e-04\n",C1[4]);
C1[5] = 1/(L2-x[0]);
//printf("1/(L2-x[0])=%f;0.026589182244382\n",C1[5]); // 差很少 0.026589182244382
C1[6] = 1/((L2-x[0])*(L2-x[0])); 
//printf("1/(L2-x[0]^2)=%f;0.000706984612424972\n",C1[6]); //(error)0.000706984612424972
C1[7] = 1/(fx5); 
//printf("1/fx5=%f;1.60649624331296\n",C1[7]);//1.60649624331296
C1[8] = 1/(fx5*fx5); //2.58083017977866;
//printf("1/fx5^2=%f;2.58083017977866\n",C1[8]);//2.58083017977866
C1[9] = 2/(L2-x[0]); 
//printf("2/(L2-x[0])=%f;0.0531783644887645;\n",C1[9]); //差很少 0.0531783644887645
//printf("fabs(x[3])=%f\n\n",fabs(x[3]));
//-----------------------------------------------------g_bar,g,dgdx4 G(6),G(7)=dfdx5 ,G(8)=dgdx5
/*for (int i=0;i<4;i++)
    {
     G[i] = Q[i]/(1+6.235393303410815e-04*sgnx4*pow(C1[i],a10)); //gbar
     G[i+8]=6.235393303410815e-04*sgnx4*G[i]*G[i]*Q[i+4]*pow(C1[i],a11)*x(i+5)/Q[i+8]; //G(9)error
    }*/
G[0] = Q[0]/(1+6.235393303410815e-04*sgnx4*pow(C1[0],a10)); //gn_bar
G[1] = Q[1]/(1+6.235393303410815e-04*sgnx4*pow(C1[1],a10)); //gs_bar
G[2] = Q[2]/(1+6.235393303410815e-04*sgnx4*pow(C1[2],a10)); //gr_bar
G[3] = Q[3]/(1+6.235393303410815e-04*sgnx4*pow(C1[3],a10)); //gc_bar
G[8]=6.235393303410815e-04*sgnx4*G[0]*G[0]*Q[4]*pow(C1[0],a11)*x[5]/Q[8];
G[9]=6.235393303410815e-04*sgnx4*G[1]*G[1]*Q[5]*pow(C1[1],a11)*x[6]/Q[9];
G[10]=6.235393303410815e-04*sgnx4*G[2]*G[2]*Q[6]*pow(C1[2],a11)*x[7]/Q[10];
G[11]=6.235393303410815e-04*sgnx4*G[3]*G[3]*Q[7]*pow(C1[3],a11)*x[8]/Q[11];
G[4] = G[0]*Nl+G[1]*x[6]+G[2]*x[7]+G[3]*x[8]; //g  
G[5] = -a10*(G[8]+G[9]+G[10]+G[11]); //dgdx4 G(6) //error
if (x[6] < Sl){
    switch1=1/AS*AS;
    switch8 = G[1]/AS;}
    else
    {switch1=1/(2*AR*AR);  
     switch8 = G[2]/(2*AR);
}
if (x[7]<Rl){
           G[6]=switch1; //G(7)=dfdx5 
           G[7]=switch8; //G(8)=dgdx5 
           }
    else
    {G[6]=1/(2*AC*AC);
     G[7]=G[3]/(2*AC);
}
//printf("switch1=%f,switch8=%f\n",switch1,switch8);
//printf("G[]={%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\n\n",G[0],G[1],G[2],G[3],G[4],G[5],G[6],G[7],G[8]);
//-----------------A1&B1---------------------------
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
AAA[7][4]= 1;
AAA[7][5]= 0;
AAA[8][0]= C1[5];
AAA[8][1]= 1;
AAA[8][2]= 1;
AAA[8][3]= 1;
AAA[8][4]= a7;
AAA[8][5]= 0;
AAA[9][0]= C1[5];
AAA[9][1]= -x[3];
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
BBB[7][0]= 1;
BBB[7][1]= a3;
BBB[7][2]= 3;
BBB[7][3]= 0;
BBB[7][4]= x[1];
BBB[7][5]= 0;
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
//------------------------------------------------------step1
/*for (int j=0;j<12;j++){
    for (int i=0;i<6;i++){
        C2[j][i]=AAA[j][i]*BBB[j][i];
        }
} */
C2[0][0]= AAA[0][0]*BBB[0][0];
C2[0][1]= AAA[0][1]*BBB[0][1];
C2[0][2]= AAA[0][2]*BBB[0][2];
C2[0][3]= AAA[0][3]*BBB[0][3];
C2[0][4]= AAA[0][4]*BBB[0][4];
C2[0][5]= AAA[0][5]*BBB[0][5];
C2[1][0]= AAA[1][0]*BBB[1][0];
C2[1][1]= AAA[1][1]*BBB[1][1];
C2[1][2]= AAA[1][2]*BBB[1][2];
C2[1][3]= AAA[1][3]*BBB[1][3];
C2[1][4]= AAA[1][4]*BBB[1][4];
C2[1][5]= AAA[1][5]*BBB[1][5];
C2[2][0]= AAA[2][0]*BBB[2][0];
C2[2][1]= AAA[2][1]*BBB[2][1];
C2[2][2]= AAA[2][2]*BBB[2][2];
C2[2][3]= AAA[2][3]*BBB[2][3];
C2[2][4]= AAA[2][4]*BBB[2][4];
C2[2][5]= AAA[2][5]*BBB[2][5];
C2[3][0]= AAA[3][0]*BBB[3][0];
C2[3][1]= AAA[3][1]*BBB[3][1];
C2[3][2]= AAA[3][2]*BBB[3][2];
C2[3][3]= AAA[3][3]*BBB[3][3];
C2[3][4]= AAA[3][4]*BBB[3][4];
C2[3][5]= AAA[3][5]*BBB[3][5];
C2[4][0]= AAA[4][0]*BBB[4][0];
C2[4][1]= AAA[4][1]*BBB[4][1];
C2[4][2]= AAA[4][2]*BBB[4][2];
C2[4][3]= AAA[4][3]*BBB[4][3];
C2[4][4]= AAA[4][4]*BBB[4][4];
C2[4][5]= AAA[4][5]*BBB[4][5];
C2[5][0]= AAA[5][0]*BBB[5][0];
C2[5][1]= AAA[5][1]*BBB[5][1];
C2[5][2]= AAA[5][2]*BBB[5][2];
C2[5][3]= AAA[5][3]*BBB[5][3];
C2[5][4]= AAA[5][4]*BBB[5][4];
C2[5][5]= AAA[5][5]*BBB[5][5];
C2[6][0]= AAA[6][0]*BBB[6][0];
C2[6][1]= AAA[6][1]*BBB[6][1];
C2[6][2]= AAA[6][2]*BBB[6][2];
C2[6][3]= AAA[6][3]*BBB[6][3];
C2[6][4]= AAA[6][4]*BBB[6][4];
C2[6][5]= AAA[6][5]*BBB[6][5];
C2[7][0]= AAA[7][0]*BBB[7][0];
C2[7][1]= AAA[7][1]*BBB[7][1];
C2[7][2]= AAA[7][2]*BBB[7][2];
C2[7][3]= AAA[7][3]*BBB[7][3];
C2[7][4]= AAA[7][4]*BBB[7][4];
C2[7][5]= AAA[7][5]*BBB[7][5];
C2[8][0]= AAA[8][0]*BBB[8][0];
C2[8][1]= AAA[8][1]*BBB[8][1];
C2[8][2]= AAA[8][2]*BBB[8][2];
C2[8][3]= AAA[8][3]*BBB[8][3];
C2[8][4]= AAA[8][4]*BBB[8][4];
C2[8][5]= AAA[8][5]*BBB[8][5];
C2[9][0]= AAA[9][0]*BBB[9][0];
C2[9][1]= AAA[9][1]*BBB[9][1];
C2[9][2]= AAA[9][2]*BBB[9][2];
C2[9][3]= AAA[9][3]*BBB[9][3];
C2[9][4]= AAA[9][4]*BBB[9][4];
C2[9][5]= AAA[9][5]*BBB[9][5];
C2[10][0]= AAA[10][0]*BBB[10][0];
C2[10][1]= AAA[10][1]*BBB[10][1];
C2[10][2]= AAA[10][2]*BBB[10][2];
C2[10][3]= AAA[10][3]*BBB[10][3];
C2[10][4]= AAA[10][4]*BBB[10][4];
C2[10][5]= AAA[10][5]*BBB[10][5];
C2[11][0]= AAA[11][0]*BBB[11][0];
C2[11][1]= AAA[11][1]*BBB[11][1];
C2[11][2]= AAA[11][2]*BBB[11][2];
C2[11][3]= AAA[11][3]*BBB[11][3];
C2[11][4]= AAA[11][4]*BBB[11][4];
C2[11][5]= AAA[11][5]*BBB[11][5];
//-------------------------------------------------------step2
/*for (int j =0;j<12;j++){
    for (int i=0;i<6;i++){
    C3[j][i]=C2[j][0]*C2[j][i];
            }
}	*/
C3[0][0]= C2[0][0];
C3[1][0]= C2[1][0];
C3[2][0]= C2[2][0];
C3[3][0]= C2[3][0];
C3[4][0]= C2[4][0];
C3[5][0]= C2[5][0];
C3[6][0]= C2[6][0];
C3[7][0]= C2[7][0];
C3[8][0]= C2[8][0];
C3[9][0]= C2[9][0];
C3[10][0]= C2[10][0];
C3[11][0]= C2[11][0];

C3[0][1]= C2[0][0]* C2[0][1];
C3[0][2]= C2[0][0]* C2[0][2];
C3[0][3]= C2[0][0]* C2[0][3];
C3[0][4]= C2[0][0]* C2[0][4];
C3[0][5]= C2[0][0]* C2[0][5];
C3[1][1]= C2[1][0]* C2[1][1];
C3[1][2]= C2[1][0]* C2[1][2];
C3[1][3]= C2[1][0]* C2[1][3];
C3[1][4]= C2[1][0]* C2[1][4];
C3[1][5]= C2[1][0]* C2[1][5];
C3[2][1]= C2[2][0]* C2[2][1];
C3[2][2]= C2[2][0]* C2[2][2];
C3[2][3]= C2[2][0]* C2[2][3];
C3[2][4]= C2[2][0]* C2[2][4];
C3[2][5]= C2[2][0]* C2[2][5];
C3[3][1]= C2[3][0]* C2[3][1];
C3[3][2]= C2[3][0]* C2[3][2];
C3[3][3]= C2[3][0]* C2[3][3];
C3[3][4]= C2[3][0]* C2[3][4];
C3[3][5]= C2[3][0]* C2[3][5];
C3[4][1]= C2[4][0]* C2[4][1];
C3[4][2]= C2[4][0]* C2[4][2];
C3[4][3]= C2[4][0]* C2[4][3];
C3[4][4]= C2[4][0]* C2[4][4];
C3[4][5]= C2[4][0]* C2[4][5];
C3[5][1]= C2[5][0]* C2[5][1];
C3[5][2]= C2[5][0]* C2[5][2];
C3[5][3]= C2[5][0]* C2[5][3];
C3[5][4]= C2[5][0]* C2[5][4];
C3[5][5]= C2[5][0]* C2[5][5];
C3[6][1]= C2[6][0]* C2[6][1];
C3[6][2]= C2[6][0]* C2[6][2];
C3[6][3]= C2[6][0]* C2[6][3];
C3[6][4]= C2[6][0]* C2[6][4];
C3[6][5]= C2[6][0]* C2[6][5];
C3[7][1]= C2[7][0]* C2[7][1];
C3[7][2]= C2[7][0]* C2[7][2];
C3[7][3]= C2[7][0]* C2[7][3];
C3[7][4]= C2[7][0]* C2[7][4];
C3[7][5]= C2[7][0]* C2[7][5];
C3[8][1]= C2[8][0]* C2[8][1];
C3[8][2]= C2[8][0]* C2[8][2];
C3[8][3]= C2[8][0]* C2[8][3];
C3[8][4]= C2[8][0]* C2[8][4];
C3[8][5]= C2[8][0]* C2[8][5];
C3[9][1]= C2[9][0]* C2[9][1];
C3[9][2]= C2[9][0]* C2[9][2];
C3[9][3]= C2[9][0]* C2[9][3];
C3[9][4]= C2[9][0]* C2[9][4];
C3[9][5]= C2[9][0]* C2[9][5];
C3[10][1]= C2[10][0]* C2[10][1];
C3[10][2]= C2[10][0]* C2[10][2];
C3[10][3]= C2[10][0]* C2[10][3];
C3[10][4]= C2[10][0]* C2[10][4];
C3[10][5]= C2[10][0]* C2[10][5];
C3[11][1]= C2[11][0]* C2[11][1];
C3[11][2]= C2[11][0]* C2[11][2];
C3[11][3]= C2[11][0]* C2[11][3];
C3[11][4]= C2[11][0]* C2[11][4];
C3[11][5]= C2[11][0]* C2[11][5];
//-------------------------------------------------------step3
temp1[0][0]=C2[3][0];
temp1[0][1]=C2[1][0];
temp1[0][2]=C2[4][0];
temp1[0][3]=C2[0][0];
temp1[0][4]=C2[2][0];
temp1[0][5]=C3[0][3];
temp1[0][6]=C3[0][2];
temp2[0][0]=C3[7][2];
temp2[0][1]=C3[8][4];
temp2[0][2]=C3[7][1];
temp2[0][3]=C3[8][4];
temp2[0][4]=C3[9][1];
temp2[0][5]=C3[9][2];
temp2[0][6]=C3[9][2];

temp1[1][0]=C2[3][0];
temp1[1][1]=C3[1][5];
temp1[1][2]=C2[0][0];
temp2[1][0]=C3[7][3];
temp2[1][1]=C3[8][1];
temp2[1][2]=C3[8][1];

temp1[2][0]=C3[1][4];
temp1[2][1]=C3[3][2];
temp1[2][2]=C3[1][2];
temp1[2][3]=C2[1][0];
temp1[2][4]=C3[4][1];
temp1[2][5]=C3[1][1];
temp1[2][6]=C3[6][1];
temp2[2][0]=C2[8][0];
temp2[2][1]=C2[7][0];
temp2[2][2]=C3[8][2];
temp2[2][3]=C3[12][4];
temp2[2][4]=C2[7][0];
temp2[2][5]=C3[8][2];
temp2[2][6]=C2[8][0];

temp1[3][0]=C3[6][3];
temp1[3][1]=C2[0][0];
temp1[3][2]=C3[6][2];
temp1[3][3]=C3[0][4];
temp1[3][4]=C3[0][3];
temp1[3][5]=C3[0][1];
temp1[3][6]=C3[1][3];
temp2[3][0]=C2[8][0];
temp2[3][1]=C3[12][4];
temp2[3][2]=C2[8][0];
temp2[3][3]=C3[10][2];
temp2[3][4]=C3[10][2];
temp2[3][5]=C3[11][2];
temp2[3][6]=C3[11][2];

temp1[4][0]=C3[2][2];
temp1[4][1]=C3[0][3];
temp1[4][2]=C3[0][2];
temp1[4][3]=C3[0][3];
temp1[4][4]=C3[2][2];
temp1[4][5]=C3[0][2];
temp1[4][6]=C3[0][4];
temp2[4][0]=C3[11][1];
temp2[4][1]=C3[10][4];
temp2[4][2]=C3[11][1];
temp2[4][3]=C3[11][1];
temp2[4][4]=C3[10][4];
temp2[4][5]=C3[10][4];
temp2[4][6]=C3[10][3];

temp1[5][0]=C3[0][3];
temp1[5][1]=C3[0][2];
temp1[5][2]=C3[0][5];
temp1[5][3]=C3[0][4];
temp1[5][4]=C3[0][3];
temp1[5][5]=C3[0][5];
temp2[5][0]=C3[10][1];
temp2[5][1]=C3[10][1];
temp2[5][2]=C3[9][3];
temp2[5][3]=C3[9][4];
temp2[5][4]=C3[9][4];
temp2[5][5]=C3[9][4];

temp1[3][4]=temp1[3][4]*x[3];
temp1[4][1]=temp1[4][1]*3;
temp1[5][4]=temp1[5][4]*x[3];
temp1[5][5]=temp1[5][5]*G[4];

/*for (int j=0;j<6;j++){
    for (int i=0;i<7;i++){	
    	temp3[j]+=temp1[j][i]*temp2[j][i];
    	}
}*/
temp7[0][0]= temp1[0][0]*temp2[0][0];
temp7[0][1]= temp1[0][1]*temp2[0][1];
temp7[0][2]= temp1[0][2]*temp2[0][2];
temp7[0][3]= temp1[0][3]*temp2[0][3];
temp7[0][4]= temp1[0][4]*temp2[0][4];
temp7[0][5]= temp1[0][5]*temp2[0][5];
temp7[0][6]= temp1[0][6]*temp2[0][6];

temp7[1][0]= temp1[1][0]*temp2[1][0];
temp7[1][1]= temp1[1][1]*temp2[1][1];
temp7[1][2]= temp1[1][2]*temp2[1][2];
temp7[1][3]= temp1[1][3]*temp2[1][3];
temp7[1][4]= temp1[1][4]*temp2[1][4];
temp7[1][5]= temp1[1][5]*temp2[1][5];
temp7[1][6]= temp1[1][6]*temp2[1][6];

temp7[2][0]= temp1[2][0]*temp2[2][0];
temp7[2][1]= temp1[2][1]*temp2[2][1];
temp7[2][2]= temp1[2][2]*temp2[2][2];
temp7[2][3]= temp1[2][3]*temp2[2][3];
temp7[2][4]= temp1[2][4]*temp2[2][4];
temp7[2][5]= temp1[2][5]*temp2[2][5];
temp7[2][6]= temp1[2][6]*temp2[2][6];

temp7[3][0]= temp1[3][0]*temp2[3][0];
temp7[3][1]= temp1[3][1]*temp2[3][1];
temp7[3][2]= temp1[3][2]*temp2[3][2];
temp7[3][3]= temp1[3][3]*temp2[3][3];
temp7[3][4]= temp1[3][4]*temp2[3][4];
temp7[3][5]= temp1[3][5]*temp2[3][5];
temp7[3][6]= temp1[3][6]*temp2[3][6];

temp7[4][0]= temp1[4][0]*temp2[4][0];
temp7[4][1]= temp1[4][1]*temp2[4][1];
temp7[4][2]= temp1[4][2]*temp2[4][2];
temp7[4][3]= temp1[4][3]*temp2[4][3];
temp7[4][4]= temp1[4][4]*temp2[4][4];
temp7[4][5]= temp1[4][5]*temp2[4][5];
temp7[4][6]= temp1[4][6]*temp2[4][6];

temp7[5][0]= temp1[5][0]*temp2[5][0];
temp7[5][1]= temp1[5][1]*temp2[5][1];
temp7[5][2]= temp1[5][2]*temp2[5][2];
temp7[5][3]= temp1[5][3]*temp2[5][3];
temp7[5][4]= temp1[5][4]*temp2[5][4];
temp7[5][5]= temp1[5][5]*temp2[5][5];
temp7[5][6]= temp1[5][6]*temp2[5][6];

temp3[0]=temp7[0][0]+temp7[0][1]+temp7[0][2]+temp7[0][3]+temp7[0][4]+temp7[0][5]+temp7[0][6];
temp3[1]=temp7[1][0]+temp7[1][1]+temp7[1][2]+temp7[1][3]+temp7[1][4]+temp7[1][5]+temp7[1][6];
temp3[2]=temp7[2][0]+temp7[2][1]+temp7[2][2]+temp7[2][3]+temp7[2][4]+temp7[2][5]+temp7[2][6];
temp3[3]=temp7[3][0]+temp7[3][1]+temp7[3][2]+temp7[3][3]+temp7[3][4]+temp7[3][5]+temp7[3][6];
temp3[4]=temp7[4][0]+temp7[4][1]+temp7[4][2]+temp7[4][3]+temp7[4][4]+temp7[4][5]+temp7[4][6];
temp3[5]=temp7[5][0]+temp7[5][1]+temp7[5][2]+temp7[5][3]+temp7[5][4]+temp7[5][5]+temp7[5][6];
//--------------------------------------------------------------------
/*fstream out1File;
	out1File.open("qcg.xls",ios::out );
    if( out1File != NULL )    
        {       
            for (int k=0;k<12;k++)
            {
            out1File << Q[k]<<"\t"
					 << C1[k]<<"\t"
					 << G[k]<<"\t"
					 << temp3[k]<<"\n"
                     << endl;					 
            }
        }
     out1File.close();  
fstream out2File;
	out2File.open("matrix1.xls",ios::out );
    if( out2File != NULL )    
        {       
            for (int i=0;i<6;i++)
            {
                for (int j=0;j<12;j++)
                {
                    out2File << AAA[j][i]<<"\t"
        					 << BBB[j][i]<<"\t"
        					 << C2[j][i]<<"\t"//AAA*BBB=C2與testA1對照
        					 << C3[j][i]<<"\n"//C2*C2=C3與testA2對照
                             << endl;
                }
            }
        }
     out2File.close();
fstream out3File;
	out3File.open("matrix2.xls",ios::out );
    if( out3File != NULL )    
        {       
            for (int i=0;i<7;i++)
            {
                for (int j=0;j<6;j++)
                {
                    out3File << temp1[j][i]<<"\t"
        					 << temp2[j][i]<<"\t"
        					 << temp7[j][i]<<"\n"
                             << endl;
                }
            }
        }
     out3File.close();  */ 
//-------------------------------------------------------------step4
//---------------------------------------xi(t-T)
xi[0]=x[0];
xi[1]=x[1];
xi[2]=x[2];
xi[3]=C2[0][0]*C1[5]+C2[1][0]*C1[5];
xi[4]=temp3[0];
//--------------------------------------F(t-T)
F[0]=xi[1]-l1*(xi[0]-x[0]);
F[1]=xi[2]-l2*(xi[0]-x[0])+a3*u;
F[2]=xi[3]-3*theda*(xi[0]-x[2]);
F[3]=xi[4]-3*theda*theda*(xi[2]-x[2])+a3*a4*u/(L2-xi[0]);
F[4]=(temp3[2]+temp3[3]+temp3[4]+temp3[5])-theda*theda*theda*(xi[2]-x[2])+temp3[1]*u;
//--------------------------------------xi_bar
xi_bar[0]=xi[0]+step*F[0];
xi_bar[1]=xi[1]+step*F[1];
xi_bar[2]=xi[2]+step*F[2];
xi_bar[3]=xi[3]+step*F[3];
xi_bar[4]=xi[4]+step*F[4];
//--------------------------------------x_bar
x_bar[0]=xi_bar[0];
x_bar[1]=xi_bar[1];
x_bar[2]=xi_bar[2];
x_bar[3]=xi_bar[3]/(L2-xi_bar[0])-a4*xi_bar[1]/a5;
tempp[0]=xi_bar[4]*(L2-xi_bar[0])-a1*a4*xi_bar[1]-a2*a4*xi_bar[2]-(a4*xi_bar[1]*xi_bar[1]+a5*xi_bar[1]*xi_bar[3])/(L2-xi_bar[0]);
//-------------------------------------------判斷xs,xr,xc 
if (x_bar[4]<Sl)
{x_bar[6]=x_bar[4]*AS;
x_bar[7]=0;x_bar[8]=0;
}
else if(x_bar[4]==Sl)
{x_bar[6]=(tempp[0]*Nl/AN-a5*a6*y[2]-a5*a9*x_bar[3]*x_bar[3]-a5*a7*x_bar[3]*G[0]*Nl/(a5*a7*x_bar[3]*G[1]-tempp[0]/AS))*AS;
x_bar[7]=0;x_bar[8]=0;}
else
{
    if (x_bar[4]<Rl){
               x_bar[6]=Sl*AS;
               x_bar[7]=(( tempp[0]*( Nl/AN+Sl/AS )- a5*a6*y[2]- a5*a9*x_bar[3]*x_bar[3]-a5*a7*x_bar[3]*( G[0]*Nl+G[1]*Sl ) )/( a5*a7*x_bar[3]*G[2]- tempp[0]/AR ))*2*AR;x_bar[8]=0;}
    else if(x_bar[4]==Rl){x_bar[6]=Sl*AS;
          x_bar[7]=Rl*AR;x_bar[8]=0;}
    else {
             if (x_bar[4]<Cl){
                        x_bar[6]=Sl*AS;
                        x_bar[7]=Rl*AR;x_bar[8]=(( tempp[0]*( Nl/AN+Sl/AS+Rl/AR)-a5*a6*y[2]- a5*a9*x_bar[3]*x_bar[3]-a5*a7*x_bar[3]*(G[0]*Nl +G[1]*Sl+G[2]*Rl))/( a5*a7*x_bar[3]*G[3]-tempp[0]/AC ))*2*CR;}             
             //else if(x_bar[4]==Cl){}
             else{
                  x_bar[6]=Sl*AS;
                  x_bar[7]=Rl*AR;x_bar[8]=Cl*2*CR;}
         }
}  
//---------------------------------------------------------------K2
x[0]=x_bar[0];
x[1]=x_bar[1];
x[2]=x_bar[2];
x[3]=x_bar[3];
x[4]=x_bar[4];
x[6]=x_bar[6];
x[7]=x_bar[7];
x[8]=x_bar[8];
//printf("x_bar[]={%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",x_bar[0],x_bar[1],x_bar[2],x_bar[3],x_bar[4],x_bar[6],x_bar[7],x_bar[8]);
//迴圈 
//-------------------------f(x5)
fx5=Nl/AN+x[6]/AS+x[7]/AR+x[8]/AC; 
//printf("fx5=%f\n",fx5);
//------------------判斷sgnx4
if (x[3]>0)
          sgnx4 = 1;
else if (x[3] == 0)
        sgnx4 = 0;
    else
      sgnx4 = -1; 
//printf("sgnx4=%d\n",sgnx4);
//-----------------------gbar&dg/dx4會用到的變數      
C1[0] = Nq*fabs(x[3]);
C1[1] = Sq*fabs(x[3]);
C1[2] = Rq*fabs(x[3]);
C1[3] = Cq*fabs(x[3]);
C1[4] = C*sgnx4; // 差很少
//printf("C*sgnx4=%f;6.235393303410815e-04\n",C1[4]);
C1[5] = 1/(L2-x[0]);
//printf("1/(L2-x[0])=%f;0.026589182244382\n",C1[5]); // 差很少 0.026589182244382
C1[6] = 1/((L2-x[0])*(L2-x[0])); 
//printf("1/(L2-x[0]^2)=%f;0.000706984612424972\n",C1[6]); //(error)0.000706984612424972
C1[7] = 1/(fx5); 
//printf("1/fx5=%f;1.60649624331296\n",C1[7]);//1.60649624331296
C1[8] = 1/(fx5*fx5); //2.58083017977866;
//printf("1/fx5^2=%f;2.58083017977866\n",C1[8]);//2.58083017977866
C1[9] = 2/(L2-x[0]); 
//printf("2/(L2-x[0])=%f;0.0531783644887645;\n",C1[9]); //差很少 0.0531783644887645
//printf("fabs(x[3])=%f\n\n",fabs(x[3]));
//-----------------------------------------------------g_bar,g,dgdx4 G(6),G(7)=dfdx5 ,G(8)=dgdx5
G[0] = Q[0]/(1+6.235393303410815e-04*sgnx4*pow(C1[0],a10)); //gn_bar
G[1] = Q[1]/(1+6.235393303410815e-04*sgnx4*pow(C1[1],a10)); //gs_bar
G[2] = Q[2]/(1+6.235393303410815e-04*sgnx4*pow(C1[2],a10)); //gr_bar
G[3] = Q[3]/(1+6.235393303410815e-04*sgnx4*pow(C1[3],a10)); //gc_bar
G[8]=6.235393303410815e-04*sgnx4*G[0]*G[0]*Q[4]*pow(C1[0],a11)*x[5]/Q[8];
G[9]=6.235393303410815e-04*sgnx4*G[1]*G[1]*Q[5]*pow(C1[1],a11)*x[6]/Q[9];
G[10]=6.235393303410815e-04*sgnx4*G[2]*G[2]*Q[6]*pow(C1[2],a11)*x[7]/Q[10];
G[11]=6.235393303410815e-04*sgnx4*G[3]*G[3]*Q[7]*pow(C1[3],a11)*x[8]/Q[11];
G[4] = G[0]*Nl+G[1]*x[6]+G[2]*x[7]+G[3]*x[8]; //g  
G[5] = -a10*(G[8]+G[9]+G[10]+G[11]); //dgdx4 G(6) //error
if (x[6] < Sl){
    switch1=1/AS*AS;
    switch8 = G[1]/AS;}
    else
    {switch1=1/(2*AR*AR);  
     switch8 = G[2]/(2*AR);
}
if (x[7]<Rl){
           G[6]=switch1; //G(7)=dfdx5 
           G[7]=switch8; //G(8)=dgdx5 
           }
    else
    {G[6]=1/(2*AC*AC);
     G[7]=G[3]/(2*AC);
}
//printf("switch1=%f,switch8=%f\n",switch1,switch8);
//printf("G[]={%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",G[0],G[1],G[2],G[3],G[4],G[5],G[6],G[7],G[8],G[9],G[10],G[11]);
//-----------------A1&B1---------------------------

AAA[2][4]= x[1];
AAA[6][0]= C1[5];
AAA[7][0]= C1[6];
AAA[8][0]= C1[5];
AAA[9][0]= C1[5];
AAA[9][1]= -x[3];
AAA[10][0]= C1[6];
AAA[11][0]= C1[6];
AAA[11][4]= x[1];

BBB[0][0]= x[3];
BBB[0][2]= G[4];
BBB[0][3]= x[3];
BBB[0][4]= x[2];
BBB[0][5]= x[3];
BBB[1][0]= x[1];
BBB[1][1]= x[2];
BBB[1][2]= x[1];
BBB[2][2]= x[2];
BBB[2][4]= x[2];
BBB[3][1]= x[3];
BBB[3][2]= x[1];
BBB[4][1]= x[2];
BBB[5][0]= x[3];
BBB[5][2]= x[2];
BBB[5][3]= x[1];
BBB[6][1]= x[2];
BBB[6][2]= x[1];
BBB[7][4]= x[1];
BBB[8][0]= C1[7];
BBB[8][1]= x[2];
BBB[8][3]= G[7];
BBB[8][4]= G[5];
BBB[9][0]= C1[8];
BBB[9][1]= G[6];
BBB[9][3]= G[6];
BBB[9][4]= G[4];
BBB[10][0]= C1[7];
BBB[10][1]= x[1];
BBB[11][0]= C1[9];
BBB[11][4]= x[1];
//------------------------------------------------------step1
C2[0][0]= AAA[0][0]*BBB[0][0];
C2[0][1]= AAA[0][1]*BBB[0][1];
C2[0][2]= AAA[0][2]*BBB[0][2];
C2[0][3]= AAA[0][3]*BBB[0][3];
C2[0][4]= AAA[0][4]*BBB[0][4];
C2[0][5]= AAA[0][5]*BBB[0][5];
C2[1][0]= AAA[1][0]*BBB[1][0];
C2[1][1]= AAA[1][1]*BBB[1][1];
C2[1][2]= AAA[1][2]*BBB[1][2];
C2[1][3]= AAA[1][3]*BBB[1][3];
C2[1][4]= AAA[1][4]*BBB[1][4];
C2[1][5]= AAA[1][5]*BBB[1][5];
C2[2][0]= AAA[2][0]*BBB[2][0];
C2[2][1]= AAA[2][1]*BBB[2][1];
C2[2][2]= AAA[2][2]*BBB[2][2];
C2[2][3]= AAA[2][3]*BBB[2][3];
C2[2][4]= AAA[2][4]*BBB[2][4];
C2[2][5]= AAA[2][5]*BBB[2][5];
C2[3][0]= AAA[3][0]*BBB[3][0];
C2[3][1]= AAA[3][1]*BBB[3][1];
C2[3][2]= AAA[3][2]*BBB[3][2];
C2[3][3]= AAA[3][3]*BBB[3][3];
C2[3][4]= AAA[3][4]*BBB[3][4];
C2[3][5]= AAA[3][5]*BBB[3][5];
C2[4][0]= AAA[4][0]*BBB[4][0];
C2[4][1]= AAA[4][1]*BBB[4][1];
C2[4][2]= AAA[4][2]*BBB[4][2];
C2[4][3]= AAA[4][3]*BBB[4][3];
C2[4][4]= AAA[4][4]*BBB[4][4];
C2[4][5]= AAA[4][5]*BBB[4][5];
C2[5][0]= AAA[5][0]*BBB[5][0];
C2[5][1]= AAA[5][1]*BBB[5][1];
C2[5][2]= AAA[5][2]*BBB[5][2];
C2[5][3]= AAA[5][3]*BBB[5][3];
C2[5][4]= AAA[5][4]*BBB[5][4];
C2[5][5]= AAA[5][5]*BBB[5][5];
C2[6][0]= AAA[6][0]*BBB[6][0];
C2[6][1]= AAA[6][1]*BBB[6][1];
C2[6][2]= AAA[6][2]*BBB[6][2];
C2[6][3]= AAA[6][3]*BBB[6][3];
C2[6][4]= AAA[6][4]*BBB[6][4];
C2[6][5]= AAA[6][5]*BBB[6][5];
C2[7][0]= AAA[7][0]*BBB[7][0];
C2[7][1]= AAA[7][1]*BBB[7][1];
C2[7][2]= AAA[7][2]*BBB[7][2];
C2[7][3]= AAA[7][3]*BBB[7][3];
C2[7][4]= AAA[7][4]*BBB[7][4];
C2[7][5]= AAA[7][5]*BBB[7][5];
C2[8][0]= AAA[8][0]*BBB[8][0];
C2[8][1]= AAA[8][1]*BBB[8][1];
C2[8][2]= AAA[8][2]*BBB[8][2];
C2[8][3]= AAA[8][3]*BBB[8][3];
C2[8][4]= AAA[8][4]*BBB[8][4];
C2[8][5]= AAA[8][5]*BBB[8][5];
C2[9][0]= AAA[9][0]*BBB[9][0];
C2[9][1]= AAA[9][1]*BBB[9][1];
C2[9][2]= AAA[9][2]*BBB[9][2];
C2[9][3]= AAA[9][3]*BBB[9][3];
C2[9][4]= AAA[9][4]*BBB[9][4];
C2[9][5]= AAA[9][5]*BBB[9][5];
C2[10][0]= AAA[10][0]*BBB[10][0];
C2[10][1]= AAA[10][1]*BBB[10][1];
C2[10][2]= AAA[10][2]*BBB[10][2];
C2[10][3]= AAA[10][3]*BBB[10][3];
C2[10][4]= AAA[10][4]*BBB[10][4];
C2[10][5]= AAA[10][5]*BBB[10][5];
C2[11][0]= AAA[11][0]*BBB[11][0];
C2[11][1]= AAA[11][1]*BBB[11][1];
C2[11][2]= AAA[11][2]*BBB[11][2];
C2[11][3]= AAA[11][3]*BBB[11][3];
C2[11][4]= AAA[11][4]*BBB[11][4];
C2[11][5]= AAA[11][5]*BBB[11][5];
//-------------------------------------------------------step2
C3[0][0]= C2[0][0];
C3[1][0]= C2[1][0];
C3[2][0]= C2[2][0];
C3[3][0]= C2[3][0];
C3[4][0]= C2[4][0];
C3[5][0]= C2[5][0];
C3[6][0]= C2[6][0];
C3[7][0]= C2[7][0];
C3[8][0]= C2[8][0];
C3[9][0]= C2[9][0];
C3[10][0]= C2[10][0];
C3[11][0]= C2[11][0];

C3[0][1]= C2[0][0]* C2[0][1];
C3[0][2]= C2[0][0]* C2[0][2];
C3[0][3]= C2[0][0]* C2[0][3];
C3[0][4]= C2[0][0]* C2[0][4];
C3[0][5]= C2[0][0]* C2[0][5];
C3[1][1]= C2[1][0]* C2[1][1];
C3[1][2]= C2[1][0]* C2[1][2];
C3[1][3]= C2[1][0]* C2[1][3];
C3[1][4]= C2[1][0]* C2[1][4];
C3[1][5]= C2[1][0]* C2[1][5];
C3[2][1]= C2[2][0]* C2[2][1];
C3[2][2]= C2[2][0]* C2[2][2];
C3[2][3]= C2[2][0]* C2[2][3];
C3[2][4]= C2[2][0]* C2[2][4];
C3[2][5]= C2[2][0]* C2[2][5];
C3[3][1]= C2[3][0]* C2[3][1];
C3[3][2]= C2[3][0]* C2[3][2];
C3[3][3]= C2[3][0]* C2[3][3];
C3[3][4]= C2[3][0]* C2[3][4];
C3[3][5]= C2[3][0]* C2[3][5];
C3[4][1]= C2[4][0]* C2[4][1];
C3[4][2]= C2[4][0]* C2[4][2];
C3[4][3]= C2[4][0]* C2[4][3];
C3[4][4]= C2[4][0]* C2[4][4];
C3[4][5]= C2[4][0]* C2[4][5];
C3[5][1]= C2[5][0]* C2[5][1];
C3[5][2]= C2[5][0]* C2[5][2];
C3[5][3]= C2[5][0]* C2[5][3];
C3[5][4]= C2[5][0]* C2[5][4];
C3[5][5]= C2[5][0]* C2[5][5];
C3[6][1]= C2[6][0]* C2[6][1];
C3[6][2]= C2[6][0]* C2[6][2];
C3[6][3]= C2[6][0]* C2[6][3];
C3[6][4]= C2[6][0]* C2[6][4];
C3[6][5]= C2[6][0]* C2[6][5];
C3[7][1]= C2[7][0]* C2[7][1];
C3[7][2]= C2[7][0]* C2[7][2];
C3[7][3]= C2[7][0]* C2[7][3];
C3[7][4]= C2[7][0]* C2[7][4];
C3[7][5]= C2[7][0]* C2[7][5];
C3[8][1]= C2[8][0]* C2[8][1];
C3[8][2]= C2[8][0]* C2[8][2];
C3[8][3]= C2[8][0]* C2[8][3];
C3[8][4]= C2[8][0]* C2[8][4];
C3[8][5]= C2[8][0]* C2[8][5];
C3[9][1]= C2[9][0]* C2[9][1];
C3[9][2]= C2[9][0]* C2[9][2];
C3[9][3]= C2[9][0]* C2[9][3];
C3[9][4]= C2[9][0]* C2[9][4];
C3[9][5]= C2[9][0]* C2[9][5];
C3[10][1]= C2[10][0]* C2[10][1];
C3[10][2]= C2[10][0]* C2[10][2];
C3[10][3]= C2[10][0]* C2[10][3];
C3[10][4]= C2[10][0]* C2[10][4];
C3[10][5]= C2[10][0]* C2[10][5];
C3[11][1]= C2[11][0]* C2[11][1];
C3[11][2]= C2[11][0]* C2[11][2];
C3[11][3]= C2[11][0]* C2[11][3];
C3[11][4]= C2[11][0]* C2[11][4];
C3[11][5]= C2[11][0]* C2[11][5];
//-------------------------------------------------------step3
temp4[0][0]=C2[3][0];
temp4[0][1]=C2[1][0];
temp4[0][2]=C2[4][0];
temp4[0][3]=C2[0][0];
temp4[0][4]=C2[2][0];
temp4[0][5]=C3[0][3];
temp4[0][6]=C3[0][2];
temp5[0][0]=C3[7][2];
temp5[0][1]=C3[8][4];
temp5[0][2]=C3[7][1];
temp5[0][3]=C3[8][4];
temp5[0][4]=C3[9][1];
temp5[0][5]=C3[9][2];
temp5[0][6]=C3[9][2];

temp4[1][0]=C2[3][0];
temp4[1][1]=C3[1][5];
temp4[1][2]=C2[0][0];
temp5[1][0]=C3[7][3];
temp5[1][1]=C3[8][1];
temp5[1][2]=C3[8][1];

temp4[2][0]=C3[1][4];
temp4[2][1]=C3[3][2];
temp4[2][2]=C3[1][2];
temp4[2][3]=C2[1][0];
temp4[2][4]=C3[4][1];
temp4[2][5]=C3[1][1];
temp4[2][6]=C3[6][1];
temp5[2][0]=C2[8][0];
temp5[2][1]=C2[7][0];
temp5[2][2]=C3[8][2];
temp5[2][3]=C3[12][4];
temp5[2][4]=C2[7][0];
temp5[2][5]=C3[8][2];
temp5[2][6]=C2[8][0];

temp4[3][0]=C3[6][3];
temp4[3][1]=C2[0][0];
temp4[3][2]=C3[6][2];
temp4[3][3]=C3[0][4];
temp4[3][4]=C3[0][3];
temp4[3][5]=C3[0][1];
temp4[3][6]=C3[1][3];
temp5[3][0]=C2[8][0];
temp5[3][1]=C3[12][4];
temp5[3][2]=C2[8][0];
temp5[3][3]=C3[10][2];
temp5[3][4]=C3[10][2];
temp5[3][5]=C3[11][2];
temp5[3][6]=C3[11][2];

temp4[4][0]=C3[2][2];
temp4[4][1]=C3[0][3];
temp4[4][2]=C3[0][2];
temp4[4][3]=C3[0][3];
temp4[4][4]=C3[2][2];
temp4[4][5]=C3[0][2];
temp4[4][6]=C3[0][4];
temp5[4][0]=C3[11][1];
temp5[4][1]=C3[10][4];
temp5[4][2]=C3[11][1];
temp5[4][3]=C3[11][1];
temp5[4][4]=C3[10][4];
temp5[4][5]=C3[10][4];
temp5[4][6]=C3[10][3];

temp4[5][0]=C3[0][3];
temp4[5][1]=C3[0][2];
temp4[5][2]=C3[0][5];
temp4[5][3]=C3[0][4];
temp4[5][4]=C3[0][3];
temp4[5][5]=C3[0][5];
temp5[5][0]=C3[10][1];
temp5[5][1]=C3[10][1];
temp5[5][2]=C3[9][3];
temp5[5][3]=C3[9][4];
temp5[5][4]=C3[9][4];
temp5[5][5]=C3[9][4];

temp4[3][4]=temp4[3][4]*x[3];
temp4[4][1]=temp4[4][1]*3;
temp4[5][4]=temp4[5][4]*x[3];
temp4[5][5]=temp4[5][5]*G[4];

/*for (int j=0;j<6;j++){
    for (int i=0;i<7;i++){	
    	temp6[j]+=temp4[j][i]*temp5[j][i];
    	}
}*/
temp8[0][0]= temp4[0][0]*temp5[0][0];
temp8[0][1]= temp4[0][1]*temp5[0][1];
temp8[0][2]= temp4[0][2]*temp5[0][2];
temp8[0][3]= temp4[0][3]*temp5[0][3];
temp8[0][4]= temp4[0][4]*temp5[0][4];
temp8[0][5]= temp4[0][5]*temp5[0][5];
temp8[0][6]= temp4[0][6]*temp5[0][6];

temp8[1][0]= temp4[1][0]*temp5[1][0];
temp8[1][1]= temp4[1][1]*temp5[1][1];
temp8[1][2]= temp4[1][2]*temp5[1][2];
temp8[1][3]= temp4[1][3]*temp5[1][3];
temp8[1][4]= temp4[1][4]*temp5[1][4];
temp8[1][5]= temp4[1][5]*temp5[1][5];
temp8[1][6]= temp4[1][6]*temp5[1][6];

temp8[2][0]= temp4[2][0]*temp5[2][0];
temp8[2][1]= temp4[2][1]*temp5[2][1];
temp8[2][2]= temp4[2][2]*temp5[2][2];
temp8[2][3]= temp4[2][3]*temp5[2][3];
temp8[2][4]= temp4[2][4]*temp5[2][4];
temp8[2][5]= temp4[2][5]*temp5[2][5];
temp8[2][6]= temp4[2][6]*temp5[2][6];

temp8[3][0]= temp4[3][0]*temp5[3][0];
temp8[3][1]= temp4[3][1]*temp5[3][1];
temp8[3][2]= temp4[3][2]*temp5[3][2];
temp8[3][3]= temp4[3][3]*temp5[3][3];
temp8[3][4]= temp4[3][4]*temp5[3][4];
temp8[3][5]= temp4[3][5]*temp5[3][5];
temp8[3][6]= temp4[3][6]*temp5[3][6];

temp8[4][0]= temp4[4][0]*temp5[4][0];
temp8[4][1]= temp4[4][1]*temp5[4][1];
temp8[4][2]= temp4[4][2]*temp5[4][2];
temp8[4][3]= temp4[4][3]*temp5[4][3];
temp8[4][4]= temp4[4][4]*temp5[4][4];
temp8[4][5]= temp4[4][5]*temp5[4][5];
temp8[4][6]= temp4[4][6]*temp5[4][6];

temp8[5][0]= temp4[5][0]*temp5[5][0];
temp8[5][1]= temp4[5][1]*temp5[5][1];
temp8[5][2]= temp4[5][2]*temp5[5][2];
temp8[5][3]= temp4[5][3]*temp5[5][3];
temp8[5][4]= temp4[5][4]*temp5[5][4];
temp8[5][5]= temp4[5][5]*temp5[5][5];
temp8[5][6]= temp4[5][6]*temp5[5][6];

temp6[0]=temp8[0][0]+temp8[0][1]+temp8[0][2]+temp8[0][3]+temp8[0][4]+temp8[0][5]+temp8[0][6];
temp6[1]=temp8[1][0]+temp8[1][1]+temp8[1][2]+temp8[1][3]+temp8[1][4]+temp8[1][5]+temp8[1][6];
temp6[2]=temp8[2][0]+temp8[2][1]+temp8[2][2]+temp8[2][3]+temp8[2][4]+temp8[2][5]+temp8[2][6];
temp6[3]=temp8[3][0]+temp8[3][1]+temp8[3][2]+temp8[3][3]+temp8[3][4]+temp8[3][5]+temp8[3][6];
temp6[4]=temp8[4][0]+temp8[4][1]+temp8[4][2]+temp8[4][3]+temp8[4][4]+temp8[4][5]+temp8[4][6];
temp6[5]=temp8[5][0]+temp8[5][1]+temp8[5][2]+temp8[5][3]+temp8[5][4]+temp8[5][5]+temp8[5][6];
//------------------------------------------F_bar
F_bar[0]=xi_bar[1]-l1*(xi_bar[0]-x1t_bar);
F_bar[1]=xi_bar[2]-l2*(xi_bar[0]-x1t_bar)+a3*ut_bar;
F_bar[2]=xi_bar[3]-3*theda*(xi_bar[0]-x3t_bar);
F_bar[3]=xi_bar[4]-3*theda*theda*(xi_bar[2]-x3t_bar)+a3*a4*ut_bar/(L2-xi_bar[0]);
F_bar[4]=(temp6[2]+temp6[3]+temp6[4]+temp6[5])-theda*theda*theda*(xi_bar[2]-x3t_bar)+temp6[1]*ut_bar;
//------------------------------------------xi(t)
y[0]=xi[0]+0.5*step*(F[0]+F_bar[0]);
y[1]=xi[1]+0.5*step*(F[1]+F_bar[1]);
y[2]=xi[2]+0.5*step*(F[2]+F_bar[2]);
y[3]=xi[3]+0.5*step*(F[3]+F_bar[3]);
y[4]=xi[4]+0.5*step*(F[4]+F_bar[4]);
//----------------------------------------inv
x1=x1t;
x2=y[1];
x3=x3t;
x4=y[3]/(L2-y[0])-a4*y[1]/a5;
tempp[1]=y[4]*(L2-y[0])-a1*a4*y[1]-a2*a4*y[2]-(a4*y[1]*y[1]+a5*y[1]*y[3])/(L2-y[0]);
//--------------------------------------判斷xs,xr,xc
if (y[4]<Sl)
{xs=0;
xr=0;xc=0;
}
else if(y[4]==Sl)
{xs=(tempp[1]*Nl/AN-a5*a6*y[2]-a5*a9*y[3]*y[3]-a5*a7*y[3]*G[0]*Nl/(a5*a7*y[3]*G[1]-tempp[1]/AS))*AS;
xr=0;xc=0;}
else
{
    if (y[4]<Rl){
               xs=Sl*AS;
               xr=(( tempp[1]*( Nl/AN+Sl/AS )- a5*a6*y[2]- a5*a9*y[3]*y[3]-a5*a7*y[3]*( G[0]*Nl+G[1]*Sl ) )/( a5*a7*y[3]*G[2]- tempp[1]/AR ))*2*AR;xc=0;}
    else if(y[4]==Rl){xs=Sl*AS;
                      xr=Rl*AR;
                      xc=0;}
    else {
             if (y[4]<Cl){
                        xs=Sl*AS;
                        xr=Rl*AR;xc=(( tempp[1]*( Nl/AN+Sl/AS+Rl/AR )-a5*a6*y[2]- a5*a9*y[3]*y[3]-a5*a7*y[3]*( G[0]*Nl +G[1]*Sl+G[2]*Rl ) )/( a5*a7*y[3]*G[3]-tempp[1]/AC ))*2*CR;}             
             //else if(y[4]==Cl){}
             else{
                  xs=Sl*AS;
                  xr=Rl*AR;xc=Cl*2*CR;}
         }
}
vp=Nl+xs+xr+xc;
xs=xs;
xr=xr;
xc=xc;
x5=vp;
/*//--------------存 temp4、5、8
fstream out4File;
	out4File.open("matrix3.xls",ios::out );
    if( out4File != NULL )    
        {       
            for (int i=0;i<7;i++)
            {
                for (int j=0;j<6;j++)
                {
                    out4File << temp4[j][i]<<"\t"
        					 << temp5[j][i]<<"\t"
        					 << temp8[j][i]<<"\n"
                             << endl;
                }
            }
        }
     out4File.close();
//------------------temp6;y;vp;x1~x5
fstream out5File;
	out5File.open("y.xls",ios::out );
    if( out5File != NULL )    
        {       
            for (int k=0;k<9;k++)
            {
            out5File << temp6[k]<<"\t"					 
					 << vp <<"\t"
					 << y[k]<<"\t"
					 << x[k]<<"\n"
                     << endl;					 
            }
        }
     out5File.close(); */
/*//--------------------------------------finalB
finalB[1][1]=x[0];
finalB[1][2]=x[1];
finalB[1][3]=x[2];
finalB[1][4]=(a4*x[1]+a5*x[3])/C1[5];
finalB[1][5]=temp7[0];
//--------------------------------------------F(x)
finalB[2][1]=x[1];
finalB[2][2]=a1*x[1]+a2*x[2];
finalB[2][3]=finalB[1][4];
finalB[2][4]=temp7[0];
finalB[2][5]=temp7[2]+temp7[3]+temp7[4]+temp7[5];
//--------------------------------------------u
finalB[3][1]=0;
finalB[3][2]=a3;
finalB[3][3]=0;
finalB[3][4]=a3*a4/C1[5];
finalB[3][5]=temp7[1];
//-------------------------------------------gain
float xper[2];
if (counter<=0){
    xper[0]=(x[0]-x1_i);
    xper[1]=(x[2]-x3_i);
    }
    else {
    xper[0]=(x[0]-x1);
    xper[1]=(x[2]-x3);
}
finalB[4][1]=l1*xper[0];
finalB[4][2]=l2*xper[0];
finalB[4][3]=-3*theda*xper[1];
finalB[4][4]=-3*theda*theda*xper[1];
finalB[4][5]=-theda*theda*theda*xper[1];
//--------------------------------------umatrix
finalB[5][1]=u1;
finalB[5][2]=u1;
finalB[5][3]=u1;
finalB[5][4]=x[2];
finalB[5][5]=x[2]; 
//--------------------------------------------step5:f
for(int i=0;i<5;i++){
	finalB[0][i]=finalB[1][i]+finalB[2][i]+finalB[4][i]+finalB[3][i]*finalB[5][i];	
}
for(int i=0;i<5;i++){
	finalC[i]=finalA[0]*finalB[0][i]+finalA[1]*finalB[1][i];	
}
//--------------------------------------------------inv
for (int i=0;i<3;i++){
x[i]=finalC[i];
}
x[3]=finalC[3]/(L2-x[0])-a4*x[1]/a5;
double tempp;
tempp=x[4]*(L2-x[0])-a1*a4*x[1]-a2*a4*x[2]-(a4*x[1]*x[1]+a5*x[1]*x[3])/(L2-x[0]);
x[4]=tempp*Nl/AN-a5*a6*x[2]-a5*a9*x[3]*x[3]-a5*a7*x[3]*G[0]*Nl/(a5*a7*x[3]*G[1]-tempp/AS);
*/

//}
//counter=counter+1;
//}
c_stop = (double)clock(); 
CPU_execution_time = (c_stop - c_start)/(double)CLOCKS_PER_SEC; 
//------------------temp6;y;vp;x1~x5
fstream out5File;
	out5File.open("y.xls",ios::out );
    if( out5File != NULL )    
        {       
            for (int k=0;k<9;k++)
            {
            out5File << temp6[k]<<"\t"					 
					 << vp <<"\t"
					 << y[k]<<"\t"
					 << x[k]<<"\n"
                     << endl;					 
            }
        }
     out5File.close(); 
//=====================將a,b資料寫入檔案中============================================         
/*fstream out1File;
	out1File.open("qcg.xls",ios::out );
    if( out1File != NULL )    
        {       
            for (int k=0;k<12;k++)
            {
            out1File << Q[k]<<"\t"
					 << C1[k]<<"\t"
					 << G[k]<<"\t"
					 << x[k]<<"\n"
                     << endl;					 
            }
        }
     out1File.close();  
fstream out2File;
	out2File.open("matrix1.xls",ios::out );
    if( out2File != NULL )    
        {       
            for (int i=0;i<6;i++)
            {
                for (int j=0;j<12;j++)
                {
                    out2File << AAA[j][i]<<"\t"
        					 << BBB[j][i]<<"\t"
        					 << C2[j][i]<<"\t"//AAA*BBB=C2與testA1對照
        					 << C3[j][i]<<"\t"//C2*C2=C3與testA2對照
                             << endl;
                }
            }
        }
     out2File.close();*/     
     
/*fstream out2File;
	out2File.open("scal.xls",ios::out );
    if( out2File != NULL )    
        {       
            for (int k=0;k<size;k++)
            {
            out2File << temp5[k][0]<<"\t"
				     << temp6[k][0]<<"\t"
                     << temp7[k][0]<<"\t"
                     << finalB[k][0]<<"\t"
                     << finalC[k]<<"\n"                     
                     << endl;
            }
        }
     out2File.close();  */      								
printf(" ======== Execution Infomation ========\n");
//printf("sgnx4=%d\n",sgnx4);
//printf("fx5=%f\n",fx5);
//printf("fabs(x[3])=%f\n",fabs(x[3]));
//printf("switch1=%f,switch8=%f\n",switch1,switch8);
//printf("x[]={%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
//printf("Q[]={%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",Q[0],Q[1],Q[2],Q[3],Q[4],Q[5],Q[6],Q[7],Q[8],Q[9],Q[10],Q[11],Q[12],Q[13],Q[14],Q[15]);
//printf("G[]={%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f}\n",G[0],G[1],G[2],G[3],G[4],G[5],G[6],G[7],G[8],G[9],G[10],G[11]);
//printf(" Excuetion Time on GPU: %3.20f s\n",elapsedTime/1000); 
//printf(" Excuetion Time on GPU=%f\n", elapsedTime/1000);   
printf(" Excuetion Time on CPU: %3.20f s\n\n",CPU_execution_time);	
printf(" Excuetion Time on CPU=%f\n\n", CPU_execution_time);     
system("pause");
}
