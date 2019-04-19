#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct option_set {
	int *data;
	struct option_set *next;
};

void swee(int *a, int *b)
{
    a=b;
    printf("a=%d\n",a);
}

struct option_set udhcp_find_option(struct option_set *tmp_set;)
{
    float a=0;
    struct option_set tmp;
    printf("tmp=%d\n",tmp.next);
    printf("tmp=%f\n",tmp.next);
    printf("tmp=%g\n",tmp.next);
    tmp.next=tmp.next;
    //printf("tmp=%d\n",tmp->next);
    //printf("tmp=%f\n",tmp->next);
    //printf("tmp=%g\n",tmp->next);
    //tmp->next=tmp->next;

    for (;;)
    {
        printf("a=%f\n",a);
        a++;
        if (a==3){break;}
    }

    printf("tmp=%d\n",tmp.next);
    printf("tmp=%f\n",tmp.next);
    printf("tmp=%g\n",tmp.next);
    //printf("tmp=%d\n",tmp->next);
    //printf("tmp=%f\n",tmp->next);
    //printf("tmp=%g\n",tmp->next);
    //tmp->next=tmp->next;

    return tmp;
}

int main()
{
    char *tmc;
    tmc="abcd efgh";
    struct option_set *tmp_set;
    int *c=1,*d=3;
    swee(c,d);

    tmc++;
    //printf("tmc_g=%g\n",tmc);
    //printf("tmc_d=%d\n",tmc);
    //printf("tmc_f=%f\n",tmc);
    printf("tmc_s=%s\n",tmc);
    /*for(int i = 0; i != 6; ++i) {
        printf("tmc_s=%s\n",tmc++);
    }*/



    /*struct option_set tmp_set;
    printf("tmp_set=%d\n",tmp_set.next);
    printf("tmp_set=%f\n",tmp_set.next);
    printf("tmp_set=%g\n",tmp_set.next);
    tmp_set.next=tmp_set.next;*/
    //struct option_set *tmp_set;
    printf("tmp_set=%d\n",tmp_set->next);
    printf("tmp_set=%f\n",tmp_set->next);
    printf("tmp_set=%g\n",tmp_set->next);
    tmp_set->next=tmp_set->next;

    printf("===========function start===========\n");
    *tmp_set= udhcp_find_option(*tmp_set);
    //udhcp_find_option(tmp_set);
    printf("===========function end===========\n");

    /*tmp_set.next=tmp_set.next;
    printf("tmp_set=%d\n",tmp_set.next);
    printf("tmp_set=%f\n",tmp_set.next);
    printf("tmp_set=%g\n",tmp_set.next);
    tmp_set.next=tmp_set.next;*/
    printf("tmp_set=%d\n",tmp_set->next);
    printf("tmp_set=%f\n",tmp_set->next);
    printf("tmp_set=%g\n",tmp_set->next);
    tmp_set->next=tmp_set->next;

    printf("Hello world!\n");

    return 0;
}
