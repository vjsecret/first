#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define input 3
#define year 3
#define ratio 0.07


float stay(float x, float r, int iyear){
    float answer;
    int i;
        answer=x*(1+r);
        for(i=1;i<iyear;i++){
        //answer=(answer+x)*pow((1+r),iyear);
        answer=(answer+x)*(1+r);
        }
        return answer;
}
int main()
{
    //float x,year;
    //float r ,answer;
    float answer;
    answer = stay(input,ratio,year);
    printf("answer=%f\n",answer);
    printf("Hello world!\n");
    return 0;
}

