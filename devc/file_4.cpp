/*
    File name : ex029
    Purpose : 隨機檔的檔案處理
    Programmer: Mike Chien
    Date: 2008.04.22.
*/

#include <iostream>
#include <fstream>
#include <cstring>

struct Score
{
    int math;
    int eng;       
};

using namespace std;

int main()
{
    int i;
    Score s[3] ={{80, 80}, {75, 85}, {90, 83}}, tmp;
    fstream file1;
    file1.open( "test2.dat", ios::out | ios::binary );
    if( file1 != NULL )
    {
        for( i = 0; i < 3; i++ )
        {
            file1.write((char*)&s[i], sizeof(Score)); 
        }    
    }
    file1.close();
    
    file1.open( "test2.dat", ios::in | ios::binary );
    if( file1 != NULL )
    {
        cout << "目前位置 : " << file1.tellg() << endl; 
        file1.seekg( 0, ios::end );
        cout << "檔案大小 : " << file1.tellg() << endl;         
        file1.seekg( 0, ios::beg );        
        file1.read((char*)&tmp, sizeof(Score));         
        cout << "Math : " << tmp.math << endl;
        cout << "Eng : " << tmp.eng << endl;        
        cout << "目前檔案指標位置 : " << file1.tellg() << endl;          
    }
    file1.close();
    
    system( "pause" );
    return 0;
}
