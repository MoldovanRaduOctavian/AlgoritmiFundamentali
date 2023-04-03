// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define MAX_SIZE 100
using namespace std;

int v[MAX_SIZE], n, minn, maxx;

int main()
{
    ofstream fout("output.csv", ios_base::app);
    cin >> n;

    float f1, f2, f3, f4, f5, f6, f7;
    int i = 1;
    
    while (i <= n)
    {
        f1 = i;
        f2 = 100 * log(i);
        f3 = 10 * i;
        f4 = i * log(i);
        f5 = 0.1 * i * i;
        f6 = 0.01 * i * i * i;
        i++;

        string s = to_string(f1) + "," + to_string(f2) + "," + to_string(f3) + "," + to_string(f4) + "," + to_string(f5) + "," + to_string(f6);
        fout << s << '\n';
    }

    return 0;
}


