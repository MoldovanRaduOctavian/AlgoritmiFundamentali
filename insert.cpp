#include <iostream>
using namespace std;

int a[] = {3, 2, 1}, n = 3;

void insert()
{
	int j, val;
	for (int i = 1; i < n; i++)
	{
		j = i - 1;
		val = a[i];
		while (j >= 0 && val < a[j])
		{
			a[j + 1] = a[j];
			j--;
		}
	
		a[j + 1] = val;

	}

}

int main()
{
	/*cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];*/

	insert();

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";

	return 0;
}