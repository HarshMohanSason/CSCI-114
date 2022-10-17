/*                 How to execute: 

 Note: Do not run in console as you won't be able to provide the command line arguments which will lead to a segmentation fault.

- First specify the path and names of the given input files on lines 54 and 67.
- User can change the value of N on line 20 depending on the input size of the Matrix from the file
 
- ls foldername    (wherever the file is located at).
- g++ CSci114_P3.cpp
- ls (a.out file should be there)
- ./a.out _ _ _  (Fill the spaces with the required sizes for the Matricies with dimensions M N K)

*/

#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
 
#define N 6            // User can change the value of N depending on the size of the number of rows of the resultant matrix

int Max_thread = N;        //holds the thread count

using namespace std;

int MatrixA[N][N];
int MatrixB[N][N];
int MatrixC[N][N];

int row_C = 0;
int row1,col1,row,col;

void* MatrixMul(void* arg)            //function to computer the resulting matrix by multiplying both of the matrices
{
    int i = row_C++;
  
    for(int l = 0; l<N; l++)
     for(int m = 0; m<N; m++ )
      MatrixC[i][l] += MatrixA[i][m] * MatrixB[m][l];

      return MatrixC;
}


int main(int argc, char** argv)
{
    for(int i = 0; i<argc; i++){
     row1 = atoi(argv[1]);
     col1 = atoi(argv[2]);
     row =  col1;
     col =  atoi(argv[3]);
    }


    ifstream inputfile1("/Users/harshmohansason/Documents/CSCI114/A.txt");    //make sure to change the location according to the file's lcoation
    
    if (!inputfile1.is_open()) 
    cout<<"Error opening file" ;
    for (int r = 0; r < row1; r++)
    {
        for (int c = 0; c < col1; c++)
        {
          inputfile1 >> MatrixA[r][c];  
        }
    }


    ifstream inputfile("/Users/harshmohansason/Documents/CSCI114/B.txt");       //make sure to change the location according to the file's lcoation
    
    if (!inputfile.is_open()) 
    cout<<"Error opening file" ;

    for (int r = 0; r < row; r++) 
    {
        for (int c = 0; c < col; c++)
        {
          inputfile >> MatrixB[r][c]; 
        }
    }

    pthread_t threads[Max_thread];

    for (int i = 0; i < Max_thread; i++) {
        int* p;
        pthread_create(&threads[i], NULL, MatrixMul, (void*)(p));
    }

    
    for (int i = 0; i < Max_thread; i++)
        pthread_join(threads[i], NULL);  
 
     cout << endl << "Matrix C: " << endl << endl;
       for (int i = 0; i < row1; i++) {
         for (int j = 0; j < col; j++)
            cout << MatrixC[i][j] << " ";       
       cout << endl;
       }        
    return 0;
}
