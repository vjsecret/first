#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <ctime>
#include <iostream> //when it add, then you can use cout
#include <stdlib.h> //use rand //chap6 page70

#ifndef _TM_DEFINED /*�p�G�S���w�q_TM_DEFINED*/
struct tm {
        int tm_sec;     /* �� �V ���Ȱ϶���[0,59] */
        int tm_min;     /* �� - ���Ȱ϶���[0,59] */
        int tm_hour;    /* �� - ���Ȱ϶���[0,23] */
        int tm_mday;    /* �@�Ӥ뤤����� - ���Ȱ϶���[1,31] */
        int tm_mon;     /* ����]�q�@��}�l�A0�N��@��^ - ���Ȱ϶���[0,11] */
        int tm_year;    /* �~���A��ȵ����ڦ~����h1900 */
        int tm_wday;    /* �P�� �V ���Ȱ϶���[0,6]�A�䤤0�N��P���ѡA1�N��P���@�A�H������ */
        int tm_yday;    /* �q�C�~��1��1��}�l���Ѽ� �V ���Ȱ϶���[0,365]�A�䤤0�N��1��1��A1�N��1��2��A�H������ */
        int tm_isdst;   /* �L�O�ɼ��ѲšA���L�O�ɪ��ɭԡAtm_isdst�����C�����L�O�ɪ��i�ԡAtm_isdst��0�F���F�ѱ��p�ɡAtm_isdst()���t�C*/
        };
#define _TM_DEFINED  /*����struct tm���_�w�q*/
#endif

using namespace std; //when it add, then you can use endl
main()
{
//2001�~1��2�� ����
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
