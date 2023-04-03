/*
* @author Moldovan Radu
* @group 30224
* 
* Specificatiile problemei: Compararea metodelor bottom-up si top-down de construire a unui heap
* 
* Metoda bottom-up este mai eficienta decat metoda top-down, fapt ce reiese si din complexitatea in timp a celor doi algoritmi:
*	Bottom-up: O(n)
*	Top-down: O(nlogn)
* 
*/


#include <iostream>
#include <string>
#include <fstream>
#include "Profiler.h"
#define INF -99999999
using namespace std;

ofstream fout("Lab2MoldovanRadu.csv");

int test[10100], ops1, ops2, v_top_down[10100], v_bottom_up[10100], v1[10100], v2[10100];

void max_heapify_radu(int v[], int i, int n)
{
	int left, right, large, aux;
	left = 2 * i;
	right = 2 * i + 1;
	ops1 += 2;

	ops1++;
	if (left <= n && v[left] > v[i])
	{
		ops1++;
		large = left;
	}
	else
	{
		ops1++;
		large = i;
	}
	
	ops1++;
	if (right <= n && v[right] > v[large])
	{
		ops1++;
		large = right;
	}

	ops1++;
	if (large != i)
	{
		ops1 += 3;
		aux = v[i];
		v[i] = v[large];
		v[large] = aux;

		max_heapify_radu(v, large, n);
	}


}

void build_max_heap_radu(int v[], int n)
{
	ops1 = 0;
	for (int i = n / 2; i >= 1; i--)
		max_heapify_radu(v, i, n);
}

int heapsort_radu(int v[], int n)
{
	int aux, len = n;
	
	build_max_heap_radu(v, n);
	for (int i = n; i >= 2; i--)
	{
		aux = v[1];
		v[1] = v[i];
		v[i] = aux;

		len--;
		max_heapify_radu(v, 1, len);
	}

	return len;
}

void heap_increase_key_radu(int v[], int i, int key)
{
	int aux;
	ops2++;
	v[i] = key;
	while (i > 1 && v[i / 2] < v[i])
	{
		ops2 += 4;
		aux = v[i / 2];
		v[i / 2] = v[i];
		v[i] = aux;

		i /= 2;
	}
}

void max_heap_insert_radu(int v[], int* n, int key)
{
	*n = *n + 1;
	v[*n] = INF;
	ops2 += 2;

	heap_increase_key_radu(v, *n, key);
}

void build_top_down_radu(int v[], int* n, int l)
{
	ops2 = 1;
	*n = 1;
	for (int i = 2; i <= l; i++)
		max_heap_insert_radu(v, n, v[i]);
}

int main()
{
	int a[] = { 1, 1, 4, 2, 3, 9, 7, 8, 10, 14, 16 };
	int b[] = { 1, 1, 4, 2, 3, 9, 7, 8, 10, 14, 16 };
	int n = 0;
	build_max_heap_radu(a, 10);
	build_top_down_radu(b, &n, 10);

	cout << "Heapify bottom up: ";
	for (int i = 1; i <= 10; i++)
		cout << a[i] << " ";
	cout << '\n';

	cout << "Heapify top down: ";
	for (int i = 1; i <= 10; i++)
		cout << b[i] << " ";
	cout << '\n';

	cout << "Heapsort: ";
	heapsort_radu(a, 10);
	for (int i = 1; i <= 10; i++)
		cout << a[i] << " ";

	for (int i=1; i<=5; i++)
		for (int j = 100; j <= 10000; j += 500)
		{
			FillRandomArray(v1, j, 10, 10000,false, 0);
			for (int k = 1; k <= j; k++)
				v2[k] = v1[k];

			build_max_heap_radu(v1, j);
			v_bottom_up[j] += ops1;

			n = 0;
			build_top_down_radu(v2, &n, j);
			v_top_down[j] += ops2;

		}

	string h = "n,top_down,bottom_up";
	string s;
	fout << h << '\n';
	for (int i = 100; i <= 10000; i += 500)
	{
		v_bottom_up[i] /= 5;
		v_top_down[i] /= 5;
		
		s = to_string(i) + "," + to_string(v_bottom_up[i]) + "," + to_string(v_top_down[i]);
		fout << s << '\n';
	}

	return 0;
}