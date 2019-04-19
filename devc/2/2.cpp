#include <stdio.h>
#include <stdlib.h>
#include<math.h>
int main(int argc, char *argv[])
{
   char B;
   float B_value,value,average;
   printf("Enter desired grade=>");
   scanf("%c",&B);//.Reading characters with scanf()
   printf("Enter minimum average required=>");
   scanf("%f",&B_value);
   printf("Enter current average in course=>");
   scanf("%f",&value);
   printf("Enter how much the final counts As a percentage of the course grade");
   scanf("%f",&average);
   float result=(B_value-average*0.75)/(value/100);
   printf("You need a score of %f the final to get a %c",result,B);
  system("pause");
return(0);
};
