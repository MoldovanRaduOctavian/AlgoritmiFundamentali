/*
* @author Moldovan Radu
* @group 30224
	
	Specificatia problemei: implementarea si studiul complexitatii unui algoritm ce interclaseaza k liste sortate	

	Modalitatea de generare a listelor afecteaza foarte mult timpul de rulare (ex: daca avem una dintre liste mult mai lunga decat celelalte vs liste de dimensiuni aproximativ egale)
	Din grafice se observa ca modificarea lui N produce o crestere liniara a numarului de operatii, iar modificarea lui K produce o crestere logaritmica, fapt ce justifica complexitea
	in timp O(N * log K) a algoritmului

*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

ofstream fout("Lab4MoldovanRadu.csv");

struct nod
{
	int val;
	nod* next;
};

nod* liste[600];
nod* heap[10000];
int h_size, total;

nod* generare_lista(int len)
{
	int rint = rand() % 1000;
	
	nod* head = (nod*)malloc(sizeof(nod));
	head->val = rint;
	head->next = NULL;

	nod* aux1 = head;
	nod* aux2;

	len--;
	while (len > 0)
	{
		rint += rand() % 1000;
		aux2 = (nod*)malloc(sizeof(nod));

		aux2->val = rint;
		aux2->next = NULL;
		aux1->next = aux2;
		aux1 = aux2;

		len--;

	}

	return head;

}

void generare_input(int k, int n)
{
	

	int len_aux[12000] = {0}, rint, rest = n;

	for (int i = 0; i < n; i++)
		len_aux[rand() % k]++;

	//cout << '\n';

	for (int i = 0; i < k; i++)
		liste[i] = generare_lista(len_aux[i]);

	

}

void print(nod* head)
{
	while (head != NULL)
	{
		cout << head->val << " ";
		head = head->next;
	}
}

void print_liste(int k)
{
	for (int i = 0; i < k; i++)
	{
		print(liste[i]);
		cout << '\n';

	}
}

void min_heapify(int i, int size)
{
	
	total += 2;
	int left = 2 * i, right = 2 * i + 1;
	int low;

	nod* aux;

	total++;
	if (left <= size && heap[left]->val < heap[i]->val)
	{
		total++;
		low = left;
	}

	else
	{
		total++;
		low = i;
	}

	total++;
	if (right <= size && heap[right]->val < heap[low]->val)
	{
		total++;
		low = right;
	}

	total++;
	if (low != i)
	{
		total += 3;
		aux = heap[i];
		heap[i] = heap[low];
		heap[low] = aux;

		min_heapify(low, size);

	}

}

void build_min_heap(int size)
{
	for (int i = size / 2; i >= 1; i--)
		min_heapify(i, size);
}

nod* merge_k_liste(int k)
{
	total += 2;
	nod* head = (nod*)malloc(sizeof(nod));
	nod* la = head;
	nod* aux;

	for (int i = 0; i < k; i++)
		heap[i + 1] = liste[i];

	
	build_min_heap(k);
	total++;
	h_size = k;

	while (h_size)
	{
		total++;
		aux = heap[1];

		total += 2;
		la->next = aux;
		la = la->next;

		total++;
		if (aux->next != NULL)
		{
			total++;
			heap[1] = heap[1]->next;
			min_heapify(1, h_size);
		}

		else
		{
			heap[1] = heap[h_size];

			total++;
			h_size--;
			min_heapify(1, h_size);
		}
	}

	return head->next;

}

void del(nod* head)
{
	nod* aux;
	while (head != NULL)
	{
		aux = head->next;
		free(head);
		head = aux;
	}
}

int main()
{
	srand(time(0));
	generare_input(4, 20);
	print_liste(4);

	cout << '\n';

	nod* merged = merge_k_liste(4);
	print(merged);
	del(merged);

	fout << '\n';
	fout << "k=5";
	fout << '\n';

	fout << "n,total";
	fout << '\n';
	for (int i = 100; i <= 10000; i += 100)
	{
		generare_input(5, i);
		total = 0;
		merged = merge_k_liste(5);
		del(merged);

		fout << to_string(i) + "," + to_string(total) + '\n';
	}
	
	fout << '\n';
	fout << "k=10";
	fout << '\n';

	fout << "n,total";
	fout << '\n';

	for (int i = 100; i <= 10000; i += 100)
	{
		generare_input(10, i);
		total = 0;

		merged = merge_k_liste(10);
		del(merged);

		fout << to_string(i) + "," + to_string(total) + '\n';
	}

	fout << '\n';
	fout << "k=100";
	fout << '\n';

	fout << "n,total";
	fout << '\n';

	for (int i = 100; i <= 10000; i += 100)
	{
		generare_input(100, i);
		total = 0;

		merged = merge_k_liste(100);
		del(merged);

		fout << to_string(i) + "," + to_string(total) + '\n';
	}
	
	
	fout << '\n';
	fout << "n=10000";
	fout << '\n';

	fout << "k,total";
	fout << '\n';

	for (int i = 10; i <= 500; i += 10)
	{
		generare_input(i, 10000);
		total = 0;

		merged = merge_k_liste(i);
		del(merged);

		fout << to_string(i) + "," + to_string(total) + '\n';
	}
	

	return 0;
}