#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70

#ifndef _TM_DEFINED /*如果沒有定義_TM_DEFINED*/
struct tm {
        int tm_sec;     /* 秒 – 取值區間為[0,59] */
        int tm_min;     /* 分 - 取值區間為[0,59] */
        int tm_hour;    /* 時 - 取值區間為[0,23] */
        int tm_mday;    /* 一個月中的日期 - 取值區間為[1,31] */
        int tm_mon;     /* 月份（從一月開始，0代表一月） - 取值區間為[0,11] */
        int tm_year;    /* 年份，其值等於實際年份減去1900 */
        int tm_wday;    /* 星期 – 取值區間為[0,6]，其中0代表星期天，1代表星期一，以此類推 */
        int tm_yday;    /* 從每年的1月1日開始的天數 – 取值區間為[0,365]，其中0代表1月1日，1代表1月2日，以此類推 */
        int tm_isdst;   /* 夏令時標識符，實行夏令時的時候，tm_isdst為正。不實行夏令時的進候，tm_isdst為0；不了解情況時，tm_isdst()為負。*/
        };
#define _TM_DEFINED  /*防止struct tm重復定義*/
#endif

using namespace std; //when it add, then you can use endl
main()
{
//2001年1月2日 為例
struct tm y2001;
time_t t2001;

y2001.tm_sec = y2001.tm_min = 0; y2001.tm_hour = 0;
y2001.tm_mday = 2;
y2001.tm_mon = 0;
y2001.tm_year = 2001 - 1900;
y2001.tm_isdst = 0;
t2001 = mktime(&y2001);

   struct tm *y;
   y=localtime(&t2001);
   printf("asctime(now)=%s\n", asctime(y));

system ("pause");
}
