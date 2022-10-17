/*
                  How to Execute

ls foldername
g++ CSci114_P4.cpp
ls (To check for the out file) 
./a.out _ _ (No of threads and processes)

*/


#include <iostream>
#include <string> 
#include <thread> 
#include <fstream>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 5    //  no of processes      You can change it according to the request file
#define M 6    //  no of resources      You can change it according to the request file
	
int Process[N];
int Resource[M];

int safeSeq[N];    // To store safe sequence
int alloc[N][M];
int MAX[N][M];
int ProcessesRun = 0;

pthread_mutex_t lockResources; 
pthread_cond_t condition;

using namespace std; 

/* Let n be the number of processes in the system and m be the no
of resources in the system.

** Available[j] : 1d array of size m indicating the available resources
** Max[i,j] : 2d array of size n*m defining max demand of each process
** Allocation[i,j]: 2d array defning no of resources of each type allocated to each process
** Need[i,j]: 2d array indicating the resource need. 

*/

void calculateNeed(int need[N][M], int maxm[N][M], int allot[N][M])
{
	// Calculating Need of each N
	for (int i = 0 ; i < N ; i++)
		for (int j = 0 ; j < M ; j++)

			// Need of instance = maxm instance -
			//				 allocated instance
			need[i][j] = maxm[i][j] - allot[i][j];
}

bool isSafe(int Nprocesses[], int avail[], int maxm[][M],
			int allot[][M])
{
	int need[N][M];

	calculateNeed(need, maxm, allot);

	bool finish[N] = {0};

	int work[M];
	for (int i = 0; i < M ; i++)
		work[i] = avail[i];

	int count = 0;
	while (count < N)
	{
	
		bool found = false;
		for (int p = 0; p < N; p++)
		{
			if (finish[p] == 0)
			{
				int j;
				for (j = 0; j < M; j++)
					if (need[p][j] > work[j])
						break;

				if (j == M)
				{
					
					for (int k = 0 ; k < M ; k++)
						work[k] += allot[p][k];

					safeSeq[count++] = p;

					finish[p] = 1;

					found = true;
				}
			}
		}

		if (found == false)
		{
			cout << "System is not in safe state";
			return false;
		}
	}

	cout << "System is in safe state.\nSafe"
		" sequence is: ";
	return true;
}

void* process(void *arg)

{
  int hold = *((int *) arg);

  pthread_mutex_lock(&lockResources);

  while (hold != safeSeq[ProcessesRun])
    pthread_cond_wait(&condition, &lockResources);
    
    cout<<"Allocation Vector: "<<endl;
    cout<<endl;
    for(int i=0; i<M; i++)
    { cout<<alloc[hold][i];
    }

    sleep(1);

   ProcessesRun++;
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&lockResources);
	pthread_exit(NULL);

}


int main(int argc, char** argv)
{

int row1, col1;
   srand(time(NULL));
{
   for(int i = 0; i<argc; i++){
     row1 = atoi(argv[1]);
     col1 = atoi(argv[2]);
   }

 ifstream inputfile1("/Users/harshmohansason/Documents/CSCI114/requests.txt");    //make sure to change the location according to the file's lcoation
    
    if (!inputfile1.is_open()) 
    cout<<"Error opening file" ;

    for (int r = 0; r < row1; r++)
    {
       inputfile1>>Process[r];

        for (int c = 0; c < col1; c++)
        {
          inputfile1 >>Resource[c];  
        }
    }

  isSafe(Process,Resource, MAX, alloc);

   cout<<"Sequence found: "<<endl;

  pthread_t processes[N];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

	int processNumber[N];
	for(int i=0; i<N; i++) processNumber[i] = i;

        for(int i=0; i<N; i++)
                pthread_create(&processes[i], &attr, process, (void *)(&processNumber[i]));

        for(int i=0; i<N; i++)
                pthread_join(processes[i], NULL);

        cout<<"finished: "<<endl;

    return (0);
}
}