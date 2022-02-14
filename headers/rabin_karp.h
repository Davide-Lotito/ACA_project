#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


#define R 256 //alphabet dimension
#define Q 78059

  
// return the number of occurences
int search(char txt[] ,char pat[])
{
    int M = strlen(pat);
    int N = strlen(txt);
    int cou = 0;
    int q = Q;
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1; 
 
    // The value of h would be "pow(R, M-1)%q"
    // do not use external library
    // avoid overflow
    for (i = 0; i < M-1; i++)
        h = (h*R)%q;
 
    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (R*p + pat[i])%q;
        t = (R*t + txt[i])%q;
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
                cou++;
        }
 
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (R*(t - txt[i]*h) + txt[i+M])%q;
 
            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
        }
    }
    return cou;
}