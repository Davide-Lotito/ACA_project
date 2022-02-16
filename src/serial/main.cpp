// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "../headers/read_file.h"
#include "../headers/rabin_karp.h"

int main(int argc, char *argv[])
{
    system("clear");
	system(("python3 ../clean_data/remove_nl.py "+string(argv[1])).c_str());
	system(("python3 ../clean_data/remove_nl.py "+string(argv[2])).c_str());		
	string txt = read_file( "./genome_no_new_lines.txt" );
	string pat = read_file( "./pat_no_new_lines.txt" );
	system("rm genome_no_new_lines.txt  pat_no_new_lines.txt");

    clock_t begin = clock();

    int cou = search((char*)txt.c_str(), (char*)pat.c_str());
    clock_t end = clock();
    double elapsed_secs = double(end - begin)*1000 / CLOCKS_PER_SEC;

    cout<<"Occurences: "<<cou<<" time taken: "<<elapsed_secs<<" [milliseconds]"<<endl;
    
    return 0;
}