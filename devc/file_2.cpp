/*
    File name : ex027
    Purpose : 循序檔的檔案處理 (讀取與寫入)  (2)
    Programmer: Mike Chien
    Date: 2008.04.22.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    // 開啟檔案, 作為寫出用 
    fstream outFile;
    outFile.open( "test2.txt", ios::out );
    if( outFile != NULL )
    {   // 將資料寫入檔案中
        outFile << "C++ " << endl;
        outFile << "File Handling " << endl;
        outFile << "Write data to a text file " << endl;        
    }
    outFile.close();

    // 開啟檔案, 作為讀入資料用
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
