#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int cou=0; 

#define d 256



string read_file(string pathname){
    std::ifstream t(pathname);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}



 
/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
 
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;
 
    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
 
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
 
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                //printf("Pattern found at index %d \n", i);
                cou++;
        }
 
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
 
            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
        }
    }
}
 
// // Driver program to test above function
// int main()
// {
//     char txt[20000];
//     int q = 101; // A prime number
    
//     //scanf("%s",&txt);
//     std::ifstream file;
//     file.open("inputtext.txt");
//     //file>>txt;
//     file.getline(txt,19999);
//     file.close();


//     //printf("100%s100\n",txt );
//     //char *pat = "ABABAAABAB";
//     //char *pat ="learning";
//     char pat[30];

//     file.open("pat.txt");
//     while(file.getline(pat,29))
//     {


//     clock_t begin = clock();


//     search(pat, txt, q);
//     clock_t end = clock();
//     double elapsed_secs = double(end - begin)*1000 / CLOCKS_PER_SEC;


//     //cout<<txt<<endl;
//     cout<<"Number of matches of \""<<pat<<"\" is "<<cou<<endl<<"Time taken:"<<elapsed_secs<<endl;
//     cou=0;
//     }
//    file.close();

    
//     return 0;
// }


// int main(int argc, char *argv[]){


//     clock_t begin = clock();


//     // int q = 101;
//     int q = 6700417;

//     string txt = read_file(argv[1]);
//     string pat = read_file(argv[2]);
//     //cout << txt << "\n" << pat;

//     char* pat_c_str =  (char*)pat.c_str();
//     char* txt_c_str =  (char*)txt.c_str();

//     cout << pat_c_str << "\n" << txt_c_str << "\n";

//     search(pat_c_str, txt_c_str, q);

//     cout << "found: " << cou << "\n";

//     clock_t end = clock();
//     double elapsed_secs = double(end - begin)*1000 / CLOCKS_PER_SEC;
//     cout << "elapsed seconds" << elapsed_secs << "\n";

// }




 
// Driver program to test above function
int main(int argc, char *argv[])
{
    // char txt[20000];
    string txt = read_file( argv[1] );

    int q = 101; // A prime number
    
    //scanf("%s",&txt);
    std::ifstream file;
    // file.open("inputtext.txt");
    //file>>txt;
    // file.getline(txt,19999);
    // file.close();


    //printf("100%s100\n",txt );
    //char *pat = "ABABAAABAB";
    //char *pat ="learning";
    // char pat[30];
    int PATSIZE = 1000;
    char pat[PATSIZE];

    file.open(argv[2]);
    while(file.getline(pat,PATSIZE-1))
    {


    clock_t begin = clock();


    search(pat, (char*)txt.c_str(), q);
    clock_t end = clock();
    double elapsed_secs = double(end - begin)*1000 / CLOCKS_PER_SEC;


    //cout<<txt<<endl;
    cout<<"Number of matches of \""<<pat<<"\" is "<<cou<<endl<<"Time taken:"<<elapsed_secs<<endl;
    cou=0;
    }
   file.close();

    
    return 0;
}