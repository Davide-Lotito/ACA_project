#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <iostream> //cout
#include <string>
#include <unordered_map> //hash strings (for debugging)
#include <malloc.h> //get dyn-allocated size  (for debugging)

#include "../headers/read_file.h"
#include "../headers/rabin_karp.h"

#define TAG 555
#define SEPARATOR "&"


int main (int argc, char *argv[]) {
	//START COMMON
	MPI_Status status;
	int myrank, size, retVal;	

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	hash<string> hasher; //only for debug
	//END COMMON

	//START MASTER
	if (myrank == 0){ 

		system("clear");
		system(("python3 ../clean_data/remove_nl.py "+string(argv[1])).c_str());
		system(("python3 ../clean_data/remove_nl.py "+string(argv[2])).c_str());		
		string txt = read_file( "./genome_no_new_lines.txt" );
		string pat = read_file( "./pat_no_new_lines.txt" );
		system("rm genome_no_new_lines.txt  pat_no_new_lines.txt");


    	long long int N = txt.length();
    	int M = pat.length();
		int payLoadSize = (int)(N/(size-1));

		clock_t t = clock();

		cout<<"size of the full text: "<<N<<" and the "<<"size of the pattern: "<<M<<endl;

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
		}
		double millisecs = 1000* double(clock() - t)/CLOCKS_PER_SEC;
		//END MASTER
		cout<<"Found: "<<results<<" occurences"<<" in "<<millisecs<<" milliseconds."<<endl;
	}
	
	//START SLAVE
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
		free(buf);
		//END SLAVE
		cout<<"";
	}
	//START FINALCOM
	MPI_Finalize();
	//END FINALCOM
    return 0;
}