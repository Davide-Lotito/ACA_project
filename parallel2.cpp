#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <iostream> //cout
#include <string>
#include <unordered_map> //hash strings (for debugging)
#include <malloc.h> //get dyn-allocated size  (for debugging)

#include "./headers/read_file.h"
#include "./headers/boyer_moore.h"

#define TAG 555
#define SEPARATOR "&"


int main (int argc, char *argv[]) {

	MPI_Status status;
	int myrank, size, retVal;	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	hash<string> hasher; //only for debug
	
	/*
	Master's Part
	*/
	if (myrank == 0){   

		string txt = read_file( argv[1] );
		string pat = read_file( argv[2] );
    	long long int N = txt.length();
    	int M = pat.length();
		int payLoadSize = (int)(N/(size-1));

		cout<<"size of the full text: "<<N<<endl;
		cout<<"size of the pattern: "<<M<<endl;

		// master sends a 'subtext'  to each of the slaves
		long long int offset = 0;
		for (int p = 1; p < size; ++p){
			
			string subtxt = txt.substr(offset, payLoadSize);
			string message = string(subtxt)+SEPARATOR+string(pat)+"\0";
			// cout<<"number of elements in the message: "<<message.length()<<"\n"; 

		    retVal = MPI_Send(message.c_str(),  message.length() , MPI_CHAR, p, TAG, MPI_COMM_WORLD);
			offset+=payLoadSize;
		}

		int result;
		int results=0;
		// master receives results from slaves
		for (int p = 1; p < size; ++p){
            //int result;
			MPI_Recv(&result, 1, MPI_INT, p, TAG, MPI_COMM_WORLD, &status);
			results+=result;
			/*if(result !=0){
                cout<<"Occurences: "<<result<<endl;
                break;
            }*/
		}
		cout<<"Occurences: "<<results<<endl;
	}



	/*
	Slaves' Part
	*/
	if(myrank != 0){

		//Dynamic probing of incoming message size. 
		//got help from here:
		//https://mpitutorial.com/tutorials/dynamic-receiving-with-mpi-probe-and-mpi-status/

		
		// Probe for an incoming message from master
		MPI_Status status;
		MPI_Probe(0, TAG, MPI_COMM_WORLD, &status);
		
	    // When probe returns, the status object has the size and other
        // attributes of the incoming message. Get the message size
		int messageSize; //size of the incoming string
        MPI_Get_count(&status, MPI_CHAR, &messageSize);

		// cout<< "number of elements in message as received by slave: "<<messageSize<<"\n";
	
		// Allocate a buffer to hold the incoming chars
		int numBytes = sizeof(char)*(messageSize);
		
		char* buf = (char*)malloc(numBytes);
		
		retVal = MPI_Recv(buf, messageSize, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


		// split into subtext and pattern
		// https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
		char* pattern;
    	char* text;

		// get the subtext
		text = strtok(buf, SEPARATOR);
		// get the pattern
		pattern = strtok(NULL, SEPARATOR);

		// search
		int result = search(text, pattern);

		cout<<"Slave of rank: "<<myrank<<" subtext hash: "<<hasher(text)<<" length of the string: "<<strlen(text)<<endl;

		// sends back the results to the master
		retVal = MPI_Send(&result, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);

	}
	
	MPI_Finalize();
    return 0;
}