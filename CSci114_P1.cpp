/* How to execute (with Commands):
 
   Load this file in a folder
   ls foldername
   g++ CSci114_P1.cpp
   ls
   mv file1 data.in
   mv data.in a.out
   ls
   mv a.out file2
   ls
   (When the file2 is ran, the contents from file1 are seen in file2)
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream readfile;
    ofstream outfile;
     
    readfile.open("data.in", ios::in | ios::binary);
    outfile.open("data.out", ios::out | ios::binary);
    
    char c;
    while(!readfile.eof())
    {
       readfile.read((char*)&c, sizeof(c));
       outfile.write((char*)&c, sizeof(c));
    }
    
    readfile.close();
    outfile.close();
    
return 0;
}

