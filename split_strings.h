#include <stdio.h>
#include <stdlib.h>
#include <iostream>  
#include <string>
#include <vector>
#include <unordered_map> //hash
using namespace std;
#include <regex>


vector<string> split(string pattern, string string){
    //https://stackoverflow.com/questions/16749069/c-split-string-by-regex
    std::vector<std::string> results;
    regex e(pattern);
    regex_token_iterator<string::iterator> i(string.begin(), string.end(), e, -1);
    regex_token_iterator<string::iterator> end;
    while (i != end){
        results.push_back(*i++);
    }
    return results;
}

