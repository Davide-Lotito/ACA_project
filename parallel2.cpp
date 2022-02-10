#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <iostream>  

#include <string>
#include <unordered_map>

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


    // (size-1)(N/(size-1)) < N  ?????????? If true = BAAAAD
    int payLoadSize = (int)(N/(size-1));

	

	hash<string> hasher;


	if (myrank == 0)
	{   
		cout<<"size of the full text: "<<N<<endl;


		// master sends a 'subtext'  to each of the slaves
		int offset = 0;
		for (int p = 1; p < size; ++p){
			string subtxt = txt.substr(offset, payLoadSize);
			// cout<<"preparing payload of size: "<<subtxt.length()<<" vs "<<strlen(subtxt.c_str())<<" vs payloadsize:"<<payLoadSize<<endl;
			retVal = MPI_Send(subtxt.c_str(), payLoadSize, MPI_CHAR, p, TAG, MPI_COMM_WORLD);
			offset+=payLoadSize;
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

		//slave
		char buf[payLoadSize+1];
		// slaves receive a small vector...
		retVal = MPI_Recv(&buf, payLoadSize, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, &status);
		buf[payLoadSize] = '\0';


		// search 
		int result = 0;
        result = search(buf,(char*)pat.c_str());
		// sends back the results to the master
		retVal = MPI_Send(&result, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);
		cout<<"Slave of rank: "<<myrank<<" subtext hash: "<<hasher(buf)<<" length of the string: "<< strlen(buf) << " length of the char array: "<< sizeof(buf)/sizeof(buf[0])<<endl;

	}
	
	MPI_Finalize();
    return 0;
}