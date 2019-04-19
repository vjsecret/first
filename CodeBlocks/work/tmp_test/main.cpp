#include <iostream>

#ifndef TMP_APP1_H_INCLUDED
#include "BcmHttpWebDirectory.cpp"
#endif // TMP_APP1_H_INCLUDED
typedef long long			s64;
typedef s64 acpi_native_int;
#define  _AUPBND                (sizeof (acpi_native_int) - 1)
#define  _ADNBND                (sizeof (acpi_native_int) - 1)
#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define putc(c, fp) _IO_putc (c, fp)

using namespace std;

int main()
{
//=============global=========//
    char *q, *p, *t;
    int l_flag;
    char xbuff[64];

    q = "0x10";
    xbuff[0] = '%';

    int tmp11=11;
    char *tmp1=NULL,*tmp2;
    //===========================//
    //BcmHttpWebDirectory *tmp;
    //tmp = BcmHttpWebDirectory->add(1,2.2);

    //tmp2 = va_arg(tmp11,tmp1);
    while (*q != 0) {
	if (*q != '%') {
	    putc(*q, fp);
	    q++;
	    continue;
	}

    //cout << "tmp" << tmp << endl;
    cout << "Hello world!" << endl;
    return 0;
}
