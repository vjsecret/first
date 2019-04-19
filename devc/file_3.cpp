/*
    File name : ex028
    Purpose : 循序檔的檔案處理 (判斷檔案結束) 
    Programmer: Mike Chien
    Date: 2008.04.22.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    // 開啟檔案, 作為讀入資料用
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
