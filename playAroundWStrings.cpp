#include <stdio.h>
#include <stdlib.h>
#include <iostream>  
#include <string>
using namespace std;
#include "split_strings.h"


int main(int argc, char* argv[]){

    //string concatenation and int cast to string.
    // string s = string("ciao ")+std::to_string(2)+" mondo"+"\n";
    // cout<<s;

    //splitting up a string made up of two ints and a separator
    // s = "1:2";
    // int partOne;
    // int partTwo;

    // sscanf(s.c_str(), "%d:%d", &partOne, &partTwo);
    // cout<< partOne<<"    "<< partTwo <<endl;

    vector<string> res = split(":", "Ciao:mondo");
    
    for (string i: res){
        cout << i << '\n';
    }


}


