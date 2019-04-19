#include <stdio.h>
#include <stdlib.h>

#define dblsize 2//骰子個數
#define dblsize2 20//抽籤數

/*

void dblDice(int *arr,int arr_index) //雙骰子
{
    int i,b,sum=0,tempt;
    srand((unsigned) time(NULL));
    for (i=0;i<arr_index;i++)
    {
        arr[i]=rand()%5+1;
        printf("第%d個號碼為%d\n",i+1,arr[i]);
    }
}*/
void dblDice() //骰子
{
    int i,temp_num;

    srand((unsigned) time(NULL));
    for (i=0;i<dblsize;i++)
    {
        temp_num = rand()%5+1;
        printf("第%d個號碼為%d\n",i+1,temp_num);
    }
}

void dblDice2() //抽籤
{
    int i,arr_db[dblsize2],temp_num;
    for (i=0;i<(dblsize2);i++)    {

        temp_num = rand()%20+1; //這行寫不好，取 i ~ 19 的亂數(i 初始為 0)，假設這個亂數值為 x，把 index i，與 index x 的數值互換 。
        arr_db[i]=temp_num;
        //arr_db[temp_num]=i;
        printf("第%d個號碼為%d\n",i,temp_num);
    }
}

int main()
{
    //dblDice(lotto,dblsize);
    dblDice();
    printf("\n\n");
    srand(time(0));
    dblDice2();
    printf("\n\n");
    //system("pause");

    return 0;
}
