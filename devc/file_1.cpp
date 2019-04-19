/*
    File name : ex026
    Purpose : 循序檔的檔案處理 (讀取與寫入)  (1)
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
    
    // 開啟檔案, 作為讀入用 
    inFile.open( "G:\\test.txt", ios::in );
    if( inFile != NULL )
    {
        inFile >> a >> b; // 從檔案中, 讀取資料 
    }
    inFile.close();
    cout << "a = " << a << endl; 
    cout << "b = " << b << endl;
    
    // 開啟檔案, 作為寫出用 
    fstream outFile;
    outFile.open( "test.out", ios::out );
    if( outFile != NULL )
    {   // 將資料寫入檔案中
        outFile << "a = " << a << endl;
        outFile << "b = " << b << endl;
        outFile << "Area = " << a * b << endl;        
        char cBuffer[] = "ABCD1234";
        //  用 write 將資料寫入檔案中
        outFile.write( cBuffer, strlen(cBuffer));
    }
    outFile.close();
    
    system( "pause" );
    return 0;
}
