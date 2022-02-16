// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <math.h>         // ceil

#include "../headers/read_file.h"
#include "../headers/rabin_karp.h"

int RESULT = 0;

void foo(string text, string pattern, int i) 
{
  int cou = search((char*)text.c_str(), (char*)pattern.c_str());
  RESULT += cou;
}


int main(int argc, char *argv[]) 
{ 

  system("clear");
  system(("python3 ../clean_data/remove_nl.py "+string(argv[1])).c_str());
  system(("python3 ../clean_data/remove_nl.py "+string(argv[2])).c_str());		
  string txt = read_file( "./genome_no_new_lines.txt" );
  string pat = read_file( "./pat_no_new_lines.txt" );
  system("rm genome_no_new_lines.txt  pat_no_new_lines.txt");

  clock_t t = clock();

  int N = txt.length();
  int M = pat.length();
  int K = N * 10 / M;
  int counter = 0;
  //int L = ceil(N/K);

  vector<string> subtexts;

  try{
    for(int i = 0 ; i < N ; i = i + K){
      string s = txt.substr(i,K);
      subtexts.push_back(s);
      counter++;
    }
  } catch(const std::exception& e) {}
  

  
  vector<thread> threads;

  for(int i = 0; i < subtexts.size(); i++){
    //cout<<subtexts[i]<<endl;
    threads.push_back(thread (foo, subtexts[i], pat, i));
  }

  try{
    for(int i = 0; i < threads.size(); i++){
      if(RESULT > 0){
        for(int j = i; j < threads.size(); j++){
          threads[j].detach();
        }
        break;
      }
    threads[i].join();
    }
  } catch(const std::exception& e) {}

  double millisecs = 1000* double(clock() - t)/CLOCKS_PER_SEC;
  cout<<"Threads: "<<threads.size()<<endl;
  cout<<"Found: "<<RESULT<<" occurences"<<" in "<<millisecs<<" milliseconds."<<endl;

  return 0;
}