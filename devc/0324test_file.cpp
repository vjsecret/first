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
/* Score s[3] ={{80, 80}, {75, 85}, {90, 83}}, tmp;
       cout  <<s[0]
             <<s[1]
             <<s[2]
             <<endl;*/
    double a, b;
    int c[]={0,1,2,3,4},size;
    size=sizeof(c)/4;
    //cout<<size<<endl;    
    // �}���ɮ�, �@���g�X�� 
    fstream outFile;
    outFile.open( "test_out.xls", ios::out );
    if( outFile != NULL )    
        {   // �N��Ƽg�J�ɮפ�    
            for (int i=0;i<=size;i++)
            {
            outFile << c[i] << endl;
            }
        
        outFile <<  b << endl;
        outFile <<  a * b << endl;        
        //char cBuffer[] = "ABCD1234";
        //  �� write �N��Ƽg�J�ɮפ�
        //outFile.write( cBuffer, strlen(cBuffer));
        }
    outFile.close();
    
        system( "pause" );
    return 0;
}
