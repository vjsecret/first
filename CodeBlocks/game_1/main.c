#include <stdio.h>
#include <stdlib.h>

#define dblsize 2//��l�Ӽ�
#define dblsize2 20//���Ҽ�

/*

void dblDice(int *arr,int arr_index) //����l
{
    int i,b,sum=0,tempt;
    srand((unsigned) time(NULL));
    for (i=0;i<arr_index;i++)
    {
        arr[i]=rand()%5+1;
        printf("��%d�Ӹ��X��%d\n",i+1,arr[i]);
    }
}*/
void dblDice() //��l
{
    int i,temp_num;

    srand((unsigned) time(NULL));
    for (i=0;i<dblsize;i++)
    {
        temp_num = rand()%5+1;
        printf("��%d�Ӹ��X��%d\n",i+1,temp_num);
    }
}

void dblDice2() //����
{
    int i,arr_db[dblsize2],temp_num;
    for (i=0;i<(dblsize2);i++)    {

        temp_num = rand()%20+1; //�o��g���n�A�� i ~ 19 ���ü�(i ��l�� 0)�A���]�o�ӶüƭȬ� x�A�� index i�A�P index x ���ƭȤ��� �C
        arr_db[i]=temp_num;
        //arr_db[temp_num]=i;
        printf("��%d�Ӹ��X��%d\n",i,temp_num);
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
