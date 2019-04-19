#include <stdlib.h>
#include <time.h>
#define MAX 6
#define SWAP(x,y) {int t; t = x; x = y; y = t;}

int partition(int[], int[], int, int);
void quickSort(int[], int[], int, int);
void test(int x,int y){printf("call_TEST=%d,%d",x,y);}

/*
void SWAP(int *x,int *y) {
    int t;
    t = *x;
    *x = *y;
    *y = t;
}
*/
void swap(int idata,int odata){
    int temp;
    temp=idata;
    idata=odata;
    odata=temp;
}
int getSortedNum(int num, int order)
{
    //int digit[10]={0};
    //int digit[MAX] = {12,1,19,33,65,6};
    //int digit2[MAX] = {22,11,29,43,75,16};
    int i, j, temp, temp2, digit[MAX], digit2[MAX];

srand(time(NULL));

printf("排序前：");
for(i = 0; i < MAX; i++) {
digit[i] = rand() % 100;
printf("%d ", digit[i]);
}
printf("value：");
for(i = 0; i < MAX; i++) {
digit2[i] = rand() % 100;
printf("%d ", digit2[i]);
}
/*    for (i=0; i<10; i++)
    {
        digit[i] = num%10;
        num /= 10;
    }*/
/*    i = 9;
   while (i>=0)
    {
        if (digit[i]!=0)
        {
            size = i+1;
            break;
        }
        i--;
    }*/

        for (i=0;i<MAX-1;i++){
            for (j=i+1; j<MAX; j++){
                //printf("i=%d,j=%d\n", i,j);
                if (digit[i]<digit[j])
                {
                    temp = digit[i];
                    digit[i] = digit[j];
                    digit[j] = temp;
                    temp2 = digit2[i];
                    digit2[i] = digit2[j];
                    digit2[j] = temp2;
                }
            }
        }
    /*temp = digit[0];
    for (i=1;i<MAX;i++)
    {
        temp *= 10;
        temp += digit[i];
    }*/
    //return temp;
    printf("\n排序後：");
    printf("Num=%d,%d,%d,%d,%d,%d\n", digit[0],digit[1],digit[2],digit[3],digit[4],digit[5]);
    printf("value=%d,%d,%d,%d,%d,%d\n", digit2[0],digit2[1],digit2[2],digit2[3],digit2[4],digit2[5]);
}
int getSortedNum(int, int);

int main(void) {

int num, size, idx;
int bigNum, smallNum;
/*
scanf("%d", &num);
if (num==0){
    printf("Original number was %d\n", num);
    return 0;
}*/
bigNum = getSortedNum(num,1);
//printf("bigNum=%d\n", bigNum);

/*
srand(time(NULL));
int number[MAX] = {12,1,19,33,65,6};
int number2[MAX] = {22,11,29,43,75,16};

printf("排序前：");
printf("call_TEST=%d,%d\n",number[1],number2[1]);

int i;
for(i = 0; i < MAX; i++) {
//number[i] = rand() % 100;
printf("%d ", number[i]);
}
printf("value：");
for(i = 0; i < MAX; i++) {
//number[i] = rand() % 100;
printf("%d ", number2[i]);
}
/*
printf("排序前：");
int i;
for(i = 0; i < MAX; i++) {
number[i];
printf("%d= ", number[i]);
//
quickSort(number, number2, 0, MAX-1);

printf("\\n排序後：");
for(i = 0; i < MAX; i++){
printf("%d ", number[i]);
}
printf("value：");
for(i = 0; i < MAX; i++){
printf("%d ", number2[i]);
}
printf("\\n");
*/
return 0;
}

int partition(int number[],int number2[], int left, int right) {
int i = left - 1;
int j;
printf("\ni=%d",i);

for(j = left; j < right; j++) {
if(number[j] <= number[right]) {
i++;
SWAP(number[i], number[j]);
SWAP(number2[i], number2[j]);
}
}

SWAP(number[i+1], number[right]);
SWAP(number2[i+1], number2[right]);
//test(number[i+1], number[right]);
return i+1;
}

void quickSort(int number[],int number2[], int left, int right) {
if(left < right) {
int q = partition(number, number2, left, right);
quickSort(number, number2, left, q-1);
quickSort(number, number2, q+1, right);
}
}
