// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <math.h>         // ceil

#include "./headers/read_file.h"
#include "./headers/rabin_karp.h"
#include "./headers/boyer_moore.h"

int RESULT = 0;

void foo(string text, string pattern, int i) 
{
  //cout<<"I'm thread "<<i<<", occurence: ";
  //int cou = search((char*)text.c_str(), (char*)pattern.c_str(), 101);
  int cou = search((char*)text.c_str(), (char*)pattern.c_str());
  RESULT += cou;
  //cout<<cou<<endl;
}


int main(int argc, char *argv[]) 
{ 
  string txt = read_file( argv[1] );
  string pat = read_file( argv[2] );
  //string txt = "QWERTYUIOPASDFGHJKLZXCVBNMZQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNM";
  //string pat = "QWERTYUIOPASDFGHJKLZXCVBNMZ";

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
