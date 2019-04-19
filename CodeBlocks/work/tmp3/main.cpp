#include <iostream>
#include "BcmNullMessageLog.cpp"



using namespace std;

int main()
{
    BcmNullMessageLog *tmp;
    BcmNullMessageLog *showv;
    int ttp=6;

    tmp = new BcmNullMessageLog;
    //showv =tmp;
    cout << tmp << endl;
    cout << tmp.IsFeatureEnabled(ttp) << endl;

    //tmp->BcmNullMessageLog();
    //showv=tmp.BcmNullMessageLog();
    //tmp->BcmNullMessageLog();
    cout << "Hello world!" << endl;
    return 0;
}
