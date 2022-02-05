#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
* Read the full content of a text-file and return it as type: 'string'.
*/
string read_file(string pathname){
    std::ifstream t(pathname);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}


// int main(int argc, char *argv[]){
//     string s = read_file(argv[1]);
//     cout << s << "\n";
//     // printf("%s\n", s.c_str());
//     return 0;
// }