#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <iostream>

using namespace std; //when it add, then you can use endl
main()
{
          int x;
     time_t now;
     x=time(&now);
     printf("time(now)=%d\n",x);
     
   struct tm *y;
   y=localtime(&now);
   printf("asctime(now)=%s\n", asctime(y));
   system ("pause");
}
