#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <iostream>  

#include "read_file.h"
#include "boyer_moore.h"

#define TAG 555


int main (int argc, char *argv[]) {

    string txt = read_file( argv[1] );
    string pat = read_file( argv[2] );

    int N = txt.length();
    int M = pat.length();

	MPI_Status status;
	int myrank, size, retVal;	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    int payLoadSize = (int)(N/(size-1));

	if (myrank == 0)
	{   
		// master sends only a section
		for (int p = 1; p < size; ++p){
			retVal = MPI_Send(txt.c_str(), payLoadSize, MPI_CHAR, p, TAG, MPI_COMM_WORLD);
        }
		// master receives 
		for (int p = 1; p < size; ++p){
            int result;
			MPI_Recv(&result, 1, MPI_INT, p, TAG, MPI_COMM_WORLD, &status);
			if(result !=0){
                cout<<"Occurences: "<<result<<endl;
                break;
            }
		}
	}
	else
	{

		cout<<"NEW SLAVE!"<<endl;
		//slave
		char buf[payLoadSize];
		// slaves receive a small vector...
		retVal = MPI_Recv(&buf, payLoadSize, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, &status);
		// search 
		int result = 0;
        result = search(buf,(char*)pat.c_str());
		// sends back the results to the master
		retVal = MPI_Send(&result, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
    return 0;
}