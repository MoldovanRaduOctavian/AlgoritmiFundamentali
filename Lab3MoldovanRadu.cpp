/*
* @author Moldovan Radu
* @group 30224
* 
* Specificatiile problemei: compararea metodelor de sortare quicksort si heapsort
* 
* Desi ambii algoritmi prezinta o complexitate in timp O(n * logn), quicksort atinge performante superioare algoritmului heapsort, fiind supusi analizei cazului mediu statistic
* 
* Pentru quicksort, cazul defavorabil il reprezinta furnizarea unui sir de intrare ordonat crescator sau descrescator.
* Cazul favorabil il reprezinta ordonarea unui sir cu elementele ordonate aleator.
* 
*/

#include "Profiler.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

ofstream fout("Lab3MoldovanRadu.csv");
int mediu_c_quick[11000], mediu_a_quick[11000], mediu_total_quick[11000], mediu_c_heap[11000], mediu_a_heap[11000], mediu_total_heap[11000], c_quick, a_quick, c_heap, a_heap;
int v_quick[11000], v_heap[11000];

void max_heapify_radu(int v[], int i, int n)
{
	int left, right, large, aux;
	left = 2 * i;
	right = 2 * i + 1;
	a_heap += 2;

	c_heap++;
	if (left <= n && v[left] > v[i])
	{
		a_heap++;
		large = left;
	}
	else
	{
		a_heap++;
		large = i;
	}

	c_heap++;
	if (right <= n && v[right] > v[large])
	{
		a_heap++;
		large = right;
	}

	c_heap++;
	if (large != i)
	{
		a_heap++;
		aux = v[i];
		v[i] = v[large];
		v[large] = aux;

		max_heapify_radu(v, large, n);
	}


}

void build_max_heap_radu(int v[], int n)
{
	
	for (int i = n / 2; i >= 1; i--)
		max_heapify_radu(v, i, n);
}

int heapsort_radu(int v[], int n)
{
	int aux, len = n;
	a_heap = 1;
	c_heap = 0;

	build_max_heap_radu(v, n);
	for (int i = n; i >= 2; i--)
	{
		a_heap += 4;
		aux = v[1];
		v[1] = v[i];
		v[i] = aux;

		len--;
		max_heapify_radu(v, 1, len);
	}

	return len;
}


int partition_radu(int v[], int pivot, int right)
{
	int aux;

	a_quick += 2;
	int x = v[right];
	int i = pivot - 1;
	for (int j = pivot; j <= right - 1; j++)
	{
		c_quick++;
		if (v[j] <= x)
		{
			a_quick += 4;
			i++;
			aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
	}

	a_quick += 3;
	aux = v[i + 1];
	v[i + 1] = v[right];
	v[right] = aux;

	return i + 1;
}

void quicksort_radu(int v[], int pivot, int right)
{
	c_quick++;
	if (pivot < right)
	{
		a_quick++;
		int q = partition_radu(v, pivot, right);
		quicksort_radu(v, pivot, q - 1);
		quicksort_radu(v, q + 1, right);
	}
}

int random_partition_radu(int v[], int pivot, int right)
{
	int i = pivot + rand() % (right - pivot);
	int aux = v[right];
	v[right] = v[i];
	v[i] = aux;

	return partition_radu(v, pivot, right);
}

int random_select_radu(int v[], int pivot, int right, int i)
{
	int q, k;
	if (pivot == right)
		return v[pivot];

	q = random_partition_radu(v, pivot, right);
	k = q - pivot + 1;

	if (i == k)
		return v[q];

	else if (i < k)
		return random_select_radu(v, pivot, q - 1, i);

	else
		return random_select_radu(v, q + 1, right, i - k);
}

int main()
{
	int a[] = { 6, 6, 7, 4, 3, 2, 1 };
	int b[] = { 6, 6, 7, 4, 3, 2, 1 };
	heapsort_radu(a, 6);
	quicksort_radu(b, 1, 6);

	cout << "Heapsort: ";
	for (int i = 1; i <= 6; i++)
		cout << a[i] << " ";

	cout << "\nQuicksort: ";
	for (int i = 1; i <= 6; i++)
		cout << b[i] << " ";

	cout << "\nRandom Select : " << random_select_radu(a, 1, 6, 2);


	fout << "Caz Mediu" << '\n';
	for (int i=1; i<=5; i++)
		for (int j = 100; j <= 10000; j += 500)
		{
			FillRandomArray(v_heap, j, 0, 10000, false, 0);
			for (int k = 0; k < j; k++)
				v_quick[k] = v_heap[k];

			a_quick = 0;
			c_quick = 0;
			quicksort_radu(v_quick, 1, j);

			heapsort_radu(v_heap, j);

			mediu_c_quick[j] += c_quick;
			mediu_a_quick[j] += a_quick;
			mediu_total_quick[j] = mediu_c_quick[j] + mediu_a_quick[j];

			mediu_c_heap[j] += c_heap;
			mediu_a_heap[j] += a_heap;
			mediu_total_heap[j] = mediu_c_heap[j] + mediu_a_heap[j];
		}

	for (int j = 100; j <= 10000; j += 500)
	{
		mediu_c_quick[j] /= 5;
		mediu_a_quick[j] /= 5;
		mediu_total_quick[j] /= 5;

		mediu_c_heap[j] /= 5;
		mediu_a_quick[j] /= 5;
		mediu_total_heap[j] /= 5;
	}

	string h, s;
	h = "n,a_heap,c_heap,total_heap,a_quick,_c_quick,total_quick";

	fout << h << '\n';
	for (int i = 100; i <= 10000; i += 500)
	{
		s = to_string(i) + "," +
			to_string(mediu_a_heap[i]) + "," +
			to_string(mediu_c_heap[i]) + "," +
			to_string(mediu_total_heap[i]) + "," +
			to_string(mediu_a_quick[i]) + "," +
			to_string(mediu_c_quick[i]) + "," +
			to_string(mediu_total_quick[i]);

		fout << s << '\n';
	}

	fout << "\n\nCaz Defavorabil\n";
	fout << "n,a_quick,c_quick,total_quick" << '\n';
	for (int i = 100; i <= 7000; i += 100)
	{
		FillRandomArray(v_quick, i, 0, 10000, false, 2);

		a_quick = 0;
		c_quick = 0;
		quicksort_radu(v_quick, 1, i);

		s = to_string(i) + "," +
			to_string(a_quick) + "," +
			to_string(c_quick) + "," +
			to_string(a_quick + c_quick);

		fout << s << '\n';
	}

	return 0;
}