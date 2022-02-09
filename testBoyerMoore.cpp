#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#include "read_file.h"
#include "boyer_moore.h"

// Driver program to test above function
int main(int argc, char *argv[])
{
    string txt = read_file( argv[1] );
    string pat = read_file( argv[2] );

    clock_t begin = clock();

    int cou = search((char*)txt.c_str(), (char*)pat.c_str());
    clock_t end = clock();
    double elapsed_secs = double(end - begin)*1000 / CLOCKS_PER_SEC;

    cout<<"Number of matches of \""<<pat<<"\" is "<<cou<<endl<<"Time taken: "<<elapsed_secs<<" [milliseconds]"<<endl;
    
    return 0;
}