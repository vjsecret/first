/*
    File name : ex028
    Purpose : �`���ɪ��ɮ׳B�z (�P�_�ɮ׵���) 
    Programmer: Mike Chien
    Date: 2008.04.22.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    // �}���ɮ�, �@��Ū�J��ƥ�
    fstream inFile;
    char ch;
    inFile.open( "test2.txt", ios::in );
    if( inFile != NULL )
    { 
        while( !inFile.eof() )
        {
            inFile.get( ch );
            cout << ch;                    
        }
        cout << endl;        
    }
    inFile.close();
    
    system( "pause" );
    return 0;
}
