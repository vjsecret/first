#include <iostream>

typedef struct boll{
int c1;
int c2;
};

class  number{
   private: int d1;
   public: void D1();
   public: void D2();
   public: boll h;
};

class  number2{
   private: boll h2;
   public: void D3();
};
using namespace std;

int main()
{
    number a1;
    int t1=5;
    a1.D1();
    a1.h.c1=3;
    //printf("a1=%d\n",t1);
    //printf("Hello world1!\n" );
    cout << "Hello world!" << endl;

    return 0;
}
void number::D1(){cout << "Demo1!" << endl;};
void number::D2(){cout << "Demo2!" << endl;};
void number2::D3(){h2.c1=3;};
