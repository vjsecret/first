/*
    File name : ex026
    Purpose : �`���ɪ��ɮ׳B�z (Ū���P�g�J)  (1)
    Programmer: Mike Chien
    Date: 2008.04.22.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


int main()
{
    fstream inFile;
    double a, b;
    
    // �}���ɮ�, �@��Ū�J�� 
    inFile.open( "G:\\test.txt", ios::in );
    if( inFile != NULL )
    {
        inFile >> a >> b; // �q�ɮפ�, Ū����� 
    }
    inFile.close();
    cout << "a = " << a << endl; 
    cout << "b = " << b << endl;
    
    // �}���ɮ�, �@���g�X�� 
    fstream outFile;
    outFile.open( "test.out", ios::out );
    if( outFile != NULL )
    {   // �N��Ƽg�J�ɮפ�
        outFile << "a = " << a << endl;
        outFile << "b = " << b << endl;
        outFile << "Area = " << a * b << endl;        
        char cBuffer[] = "ABCD1234";
        //  �� write �N��Ƽg�J�ɮפ�
        outFile.write( cBuffer, strlen(cBuffer));
    }
    outFile.close();
    
    system( "pause" );
    return 0;
}
