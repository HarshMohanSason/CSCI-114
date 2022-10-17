/*
 How to execute with steps:
 
 Load this file in a folder
 ls foldername
 g++ CSci114_P1.cpp
 mv file1 data.in
 mv data.in a.out
 mv a.out file2
 ls
 (The contents are sucessfuly copied and file2 can now be opened)
 */
 
 
#include <iostream>
#include <fstream>
#include <unistd.h>        /* Symbolic Constants */
#include <sys/types.h>        /* Primitive System Data Types */
#include <errno.h>        /* Errors */
#include <stdio.h>        /* Input/Output */
#include <sys/wait.h>        /* Wait for Process Termination */
#include <stdlib.h>        /* General Utilities */

using namespace std;

int A_to_B[2];

int
main ()
{
  int status;

  ifstream infile ("data.in", ios::in | ios::binary );
  ofstream outfile ("data.out", ios::out | ios::binary);

  pipe (A_to_B);
  if (fork () == 0)
    {

      printf ("IN PA\n");
      close (A_to_B[0]);

      char c;
      while (!infile.eof ())
    {

      infile.read ((char *) &c, sizeof (char));
      write (A_to_B[1], (char *) &c, sizeof (char));
    }

      sleep (1);
      printf ("PA:");

      close (A_to_B[1]);
      return 0;
    }
  if (fork () == 0)
    {
      char c;
      printf ("IN PB\n");
      close (A_to_B[1]);
      sleep (1);
      while (!infile.eof ())
    {

      read (A_to_B[0], (char *) &c, sizeof (char));
      outfile.write ((char *) &c, sizeof (char));
    }
      printf ("PB:");

      close (A_to_B[0]);
      return (0);
    }

  infile.close ();
  outfile.close ();
  wait (&status);
  wait (&status);
  printf ("END\n");
}



