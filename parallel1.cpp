// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <math.h>         // ceil

//#include "read_file.h"
#include "rabin_karp.cpp"

int RESULT = 0;

void foo(string text, string pattern, int i) 
{
  cout<<"I'm thread "<<i<<", occurence: ";
  int cou = search((char*)pattern.c_str(), (char*)text.c_str(), 101);
  RESULT += cou;

  cout<<cou<<endl;
}


int main(int argc, char *argv[]) 
{ 
  //string txt = read_file( argv[1] );
  //string pat = read_file( argv[2] );
  string txt = "QWERTYUIOPASDFGHJKLZXCVBNMZQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNMQWERTYUIOPASDFGHJKLZXCVBNM";
  string pat = "QWERTYUIOPASDFGHJKLZXCVBNMZ";

  int N = txt.length();
  int M = pat.length();
  int K = N * 10 / M;
  int counter = 0;
  //int L = ceil(N/K);

  vector<string> subtexts;

  try
  {
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
  
  for(int i = 0; i < threads.size(); i++){
    if(RESULT > 0){
      break;
    }
    threads[i].join();
  }

  cout<<"\n"<<"Found: "<<RESULT<<" occurences"<<endl;

  return 0;
}
