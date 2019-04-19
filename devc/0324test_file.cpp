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
/* Score s[3] ={{80, 80}, {75, 85}, {90, 83}}, tmp;
       cout  <<s[0]
             <<s[1]
             <<s[2]
             <<endl;*/
    double a, b;
    int c[]={0,1,2,3,4},size;
    size=sizeof(c)/4;
    //cout<<size<<endl;    
    // 開啟檔案, 作為寫出用 
    fstream outFile;
    outFile.open( "test_out.xls", ios::out );
    if( outFile != NULL )    
        {   // 將資料寫入檔案中    
            for (int i=0;i<=size;i++)
            {
            outFile << c[i] << endl;
            }
        
        outFile <<  b << endl;
        outFile <<  a * b << endl;        
        //char cBuffer[] = "ABCD1234";
        //  用 write 將資料寫入檔案中
        //outFile.write( cBuffer, strlen(cBuffer));
        }
    outFile.close();
    
        system( "pause" );
    return 0;
}
