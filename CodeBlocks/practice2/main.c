#include <stdio.h>
#include <stdlib.h>
#define tp11 55;

typedef struct Balltest {
    char color[10];
    double radius;
    char *test;
}Ball;
//ball1 = {"red", 5.0}, ball2;
enum Action{stop = 1, sit, stand = 3, walk, run};

union StateMachine {
    char character;
    int number;
    double fnumber;
    char *str;
};

typedef struct tagmyball{
double tp1;
double tp2;
}myball;

void foo(Ball /* or Ball+變數名*/);

int main()
{
//struct&typedef_practice
    //enum DB{tp11};
    Ball ball2,ball = {"red", 5.0};
    foo(ball);
    printf("ball: %s,\t%.2f\n", ball.color, ball.radius);


    //Ball * const ball3;
    //struct Ball = {"red", 5.0};
    //struct Ball ball1 = {"red", 5.0};
    //ball1->color= "red";
    //Ball.color = "red";
    //struct Ball ball2;
    strcpy(ball2.color, "green");
    //ball2.radius=10;
    ball2.radius=walk;
    ball2.test="red";
    //ball3.color={"green"};
    //ball2->radius=15;
    //ball3->radius=5;
    //printf("%s\n",ball1.color);
    printf("%s\n",ball2.color);
    printf("ball2_radius:%.2f\n",ball2.radius);
    printf("%s\n",ball2.test);
    //printf("%.2f\n",&ball3->test);
    //printf("%.2f\n",ball3->radius);
    //printf("%s\n",Ball.color);
    //printf("%f\n",Ball.radius);

//enum_practice
    enum Action action1=walk;
    printf("Action:%d\t,%d\t,%d\t,%d\t,%d\n",stop, sit, stand, walk, run);

//union_practice
    union StateMachine machine;
    machine.number = 1;
    machine.fnumber= 3;
    //machine.number = 1;
    //machine.str="green";
    printf("sizeof: %d\n", sizeof(machine));
    printf("number: %d\n", machine.number);
    printf("fnumber: %f\n", machine.fnumber);
    printf("machine: %g\n", machine);
    //printf("machine: %g\n", machine);


//換掉goto的改寫練習
  int input = 5;
  while(1) {
        printf("輸入一數：");
        //scanf("%d", &input);

        if(input != 0) {
            printf("100 / %d = %f\n", input, (double) 100 / input);
            break;
        }
        puts("除數不可為 0");
    }

int i = 0;
int num = 0;
num = ++i;   // 相當於i = i + 1; num = i;
printf("%d\n" ,num);
num = --i;    // 相當於i = i - 1; num = i;
printf("%d\n" ,num);

num = i++;    // 相當於num = i; i = i + 1;
printf("%d\n", num);
num = i--;     // 相當於 num = i; i = i - 1;
printf("%d\n", num);

//prog_End
    return 0;
}
void foo(Ball ball){ // ball 成員值被複製過來
     ball.radius = 100.0;
     printf("ball: %s,\t%.2f\n", ball.color, ball.radius);
}
