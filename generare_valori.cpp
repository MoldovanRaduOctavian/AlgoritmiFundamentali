#include <iostream>
#include <fstream>
using namespace std;

int n, minn, maxx, x;
ofstream fout("output_rand.txt");

int main()
{
	cin >> n >> minn >> maxx;
	srand(time(0));
	while (n--)
	{
		x = minn + rand() % (maxx - minn);
		fout << x << '\n';
	}

	return 0;
}