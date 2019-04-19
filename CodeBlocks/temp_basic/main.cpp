#include <iostream>
#include <string>

using namespace std;
void printNewline(void);
class Demo {
public:
    Demo();
    Demo(int n);
    Demo(int n1, int n2);
    int getA();
    int getB();
    int do_something();

private:
    int a;
    int b;
    int c=1;
};

Demo::Demo() {
    a = 1;
    b = 1;
}

Demo::Demo(int n) {
    a = n;
    b = n;
}

Demo::Demo(int n1, int n2) {
    a = n1;
    b = n2;
}
int Demo::getA() {
    return a;
}

int Demo::getB() {
    return b;
}
int Demo::do_something() {
    return getA()+getB()+c;
}

int main()
{
    string a = "There is no spoon.";
    cout << "a=" << a << endl;
    cout << "&a=" << &a << endl;
    //b為對 a 的指標
    string *b = &a;
    cout << "b=" << b << endl;
    cout << "*b=" << *b << endl;

    //c為對 a 的參考
    string &c = a;
    cout << "c=" << c << endl; //==a;
    cout << "&c=" << &c << endl; //==&a;

    //d為另一個指標
    string *d = new string("There is no spoon2.");
    cout << "d=" << d << endl;
    cout << "*d=" << *d << endl;

    printNewline();

    //Demo t1;
    Demo t1(10);
    Demo t2(11);
    Demo t3(11, 22);

    cout << endl;
    cout << t1.do_something() << endl;
    cout << t2.do_something() << endl;
    cout << t3.do_something() << endl;
    cout << endl;

    return 0;
}

void printNewline(void) {
    cout << endl;
}
