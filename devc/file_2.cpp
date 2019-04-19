/*
    File name : ex027
    Purpose : �`���ɪ��ɮ׳B�z (Ū���P�g�J)  (2)
    Programmer: Mike Chien
    Date: 2008.04.22.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    // �}���ɮ�, �@���g�X�� 
    fstream outFile;
    outFile.open( "test2.txt", ios::out );
    if( outFile != NULL )
    {   // �N��Ƽg�J�ɮפ�
        outFile << "C++ " << endl;
        outFile << "File Handling " << endl;
        outFile << "Write data to a text file " << endl;        
    }
    outFile.close();

    // �}���ɮ�, �@��Ū�J��ƥ�
    fstream inFile;
    char buffer[20], ch;
    inFile.open( "test2.txt", ios::in );
    if( inFile != NULL )
    { 
        inFile.read( buffer, 20 );
        cout << "buffer : " << buffer << endl;
        inFile.getline( buffer, 10 );
        cout << "buffer : " << buffer << endl;
        inFile.get( ch );
        inFile.get( ch );        
        cout << "char : " << ch << endl;        
    }
    inFile.close();
    
    system( "pause" );
    return 0;
}
