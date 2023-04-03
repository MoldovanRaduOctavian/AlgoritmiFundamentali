#include <iostream>
using namespace std;

int a[100], n;

void bubble()
{
	int aux;
	for (int i=0; i<n; i++)
		for (int j=0; j<n-1; j++)
			if (a[j] > a[j + 1])
			{
				aux = a[j];
				a[j] = a[j + 1];
				a[j + 1] = aux;
			}
}


int  main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	bubble();

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";

	return 0;
}