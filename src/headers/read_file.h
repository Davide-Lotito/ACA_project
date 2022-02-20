#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//Read the full content of a text-file and return it as type: 'string'.
//START READFILE
string read_file(string pathname){
    std::ifstream t(pathname);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
    //END READFILE
}

