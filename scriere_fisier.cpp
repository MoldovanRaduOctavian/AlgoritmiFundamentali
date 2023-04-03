#include <iostream>
#include <fstream>
#define MAX_SIZE 100
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int v[MAX_SIZE], n, i;

int main()
{
	cin >> n;
	i = n - 1;
	while (i != -1)
	{
		fin >> v[i];
		i--;
	}

	int y = 0;
	while (y < n)
		fout << v[y++] << '\n';

	return 0;
}