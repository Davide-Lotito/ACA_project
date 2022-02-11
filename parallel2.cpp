#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <iostream>  
#include <string>
#include <unordered_map> //hash

#include "./headers/read_file.h"
#include "./headers/boyer_moore.h"

#include "split_strings.h"

#define TAG 555

#define SEPARATOR "&"

int main (int argc, char *argv[]) {

   


	MPI_Status status;
	int myrank, size, retVal;	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	hash<string> hasher; //only for debug


	string txt = read_file( argv[1] );
    string pat = read_file( argv[2] );
    int N = txt.length();
    int M = pat.length();
	int payLoadSize = (int)(N/(size-1));
	int fullMessageSize = payLoadSize+1+M+1;


	/*
	Master's Part
	*/
	if (myrank == 0){   

		cout<<"size of the full text: "<<N<<endl;

		// master sends a 'subtext'  to each of the slaves
		int offset = 0;
		for (int p = 1; p < size; ++p){
			
			string subtxt = txt.substr(offset, payLoadSize);

			string message = string(subtxt)+SEPARATOR+string(pat)+"\0";
		
			// retVal = MPI_Send(subtxt.c_str(), payLoadSize, MPI_CHAR, p, TAG, MPI_COMM_WORLD);
		    retVal = MPI_Send(message.c_str(),  fullMessageSize   , MPI_CHAR, p, TAG, MPI_COMM_WORLD);


			offset+=payLoadSize;
		}

		// master receives results from slaves
		for (int p = 1; p < size; ++p){
            int result;
			MPI_Recv(&result, 1, MPI_INT, p, TAG, MPI_COMM_WORLD, &status);
			if(result !=0){
                cout<<"Occurences: "<<result<<endl;
                break;
            }
		}
	}
	
	/*
	Slaves' Part
	*/
	if(myrank != 0){

		//slave
		// char buf[payLoadSize+1];
		char buf[fullMessageSize];
		
		// slaves receive a small vector...
		retVal = MPI_Recv(&buf, fullMessageSize, MPI_CHAR, 0, TAG, MPI_COMM_WORLD, &status);
	
		// no need, \0 put in master //buf[fullMessageSize] = '\0'; //add the terminator -- only for debug

		vector<string> parts = split(SEPARATOR, string(buf));
		string subtext = parts[0];
		string pattern = parts[1];

		// search
        // int result = search(buf,(char*)pat.c_str());
		int result = search((char*)subtext.c_str(), (char*)pattern.c_str());

		cout<<"Slave of rank: "<<myrank<<" subtext hash: "<<subtext.length()<<" length of the string: "<<subtext.length()<<endl;

		// sends back the results to the master
		retVal = MPI_Send(&result, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD);

	}
	
	MPI_Finalize();
    return 0;
}