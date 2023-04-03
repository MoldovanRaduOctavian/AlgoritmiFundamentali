#include <iostream>
using namespace std;

int a[10000], n;

void select()
{
	int ind_maxx = 0;
	int aux;
	for (int i = 0; i < n - 1; i++)
	{
		ind_maxx = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[ind_maxx])
				ind_maxx = j;

		aux = a[i];
		a[i] = a[ind_maxx];
		a[ind_maxx] = aux;

	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	select();

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";

	return 0;
}