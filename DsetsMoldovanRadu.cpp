/*
* @author Moldovan Radu
* @group 30224
* 
* Operatiile pentru multimi disjuncte sunt utile pentru gasirea componenetelor conexe ale unui graf
* O modalitate eficienta de a implementa operatiile pentru multimi disjuncte foloseste reprezentarea sub forma de arbore pentru a desemna o multime
* Complexitatea in timp a algoritmului lui Krusakal pentru gasirea arborelui de acoperire de cost minim este O(nr_muchii * log(nr_noduri))
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

ofstream fout("DsetsMoldovanRadu.csv");

struct nod
{
	int val;
	int rank;
	nod* parent;
};

struct edge
{
	nod* a;
	nod* b;
	int len;
};

edge e[50000];
nod* v[12000];
int total;


nod* CreateNod(int val)
{
	nod* ret = (nod*)malloc(sizeof(nod));
	ret->parent = NULL;
	ret->rank = 0;
	ret->val = val;

	return ret;
}

void make_set_radu(nod* x)
{
	total += 2;
	x->parent = x;
	x->rank = 0;
}

void link_radu(nod* x, nod* y)
{
	total++;
	if (x->rank > y->rank)
	{
		total++;
		y->parent = x;
	}
		

	else
	{
		total++;
		x->parent = y;
	}


	total++;
	if (x->rank == y->rank)
	{
		total++;
		y->rank++;
	}

}

nod* find_set_radu(nod* x)
{
	total++;
	if (x != x->parent)
	{
		total++;
		x->parent = find_set_radu(x->parent);
	}
		

	return x->parent;
}

void uni_radu(nod* x, nod* y)
{
	link_radu(find_set_radu(x), find_set_radu(y));
}

int part_radu(edge a[], int l, int r)
{
	total += 2;
	int pivot = a[r].len;
	int div = l;

	for (int i = l; i <= r; i++)
	{
		total++;
		if (a[i].len <= pivot)
		{
			total += 4;
			edge aux = a[i];
			a[i] = a[div];
			a[div] = aux;

			div++;
		}
	}

	return div - 1;
}

void quick_sort_radu(edge a[], int l, int r)
{
	total++;
	if (l < r)
	{
		total++;
		int p = part_radu(a, l, r);
		quick_sort_radu(a, l, p - 1);
		quick_sort_radu(a, p + 1, r);
	}
}

edge* kruskal_radu(edge* x, int m, int* cost, int* ret_len)
{
	total += 2;
	edge aux;
	edge* ret = (edge*)malloc(m * sizeof(edge));
	int c = 0;

	//quick_sort(x, 0, m - 1);

	for (int i = 0; i < m; i++)
	{
		total++;
		if (find_set_radu(x[i].a) != find_set_radu(x[i].b))
		{
			total += 2;
			*cost += x[i].len;
			ret[c++] = x[i];
			uni_radu(x[i].a, x[i].b);
		}
	}
		
	total++;
	*ret_len = c;
	return ret;
}

void generare_graf_radu(int n)
{
	int  x, y, l, ok = 0;
	char viz[10100];
	while (ok == 0)
	{
		ok = 1;
		
		for (int i = 0; i < 10000; i++)
			viz[i] = 0;

		for (int i = 0; i < 4 * n; i++)
		{
			x = rand() % n;
			y = rand() % n;
			l = rand() % 10000;

			e[i].a = v[x];
			e[i].b = v[y];
			e[i].len = l;

			viz[x] = 1;
			viz[y] = 1;
		}

		for (int i = 0; i < n; i++)
			if (viz[i] == 0)
			{
				ok = 0;
				break;
			}
	}
		
}

void clear()
{
	for (int i = 0; i < 12000; i++)
		if (v[i] != NULL)
			free(v[i]);
}

int main()
{
	srand(time(0));

	int n = 10;
	for (int i = 0; i < n; i++)
	{
		v[i] = CreateNod(i);
		make_set_radu(v[i]);
	}

	uni_radu(v[1], v[3]);
	uni_radu(v[4], v[6]);
	uni_radu(v[0], v[2]);
	uni_radu(v[7], v[8]);
	
	
	cout << find_set_radu(v[0])->val << '\n';
	cout << find_set_radu(v[4])->val << '\n';
	cout << find_set_radu(v[7])->val << '\n';



	cout << "\n\n\n";
	for (int i = 0; i < 9; i++)
	{
		v[i] = CreateNod(i);
		make_set_radu(v[i]);
	}

	e[0].a = v[0];
	e[0].b = v[1];
	e[0].len = 4;

	e[1].a = v[0];
	e[1].b = v[2];
	e[1].len = 4;

	e[2].a = v[1];
	e[2].b = v[2];
	e[2].len = 2;

	e[3].a = v[2];
	e[3].b = v[3];
	e[3].len = 3;

	e[4].a = v[2];
	e[4].b = v[4];
	e[4].len = 2;

	e[5].a = v[2];
	e[5].b = v[5];
	e[5].len = 4;

	e[6].a = v[3];
	e[6].b = v[5];
	e[6].len = 3;

	e[7].a = v[4];
	e[7].b = v[5];
	e[7].len = 3;

	int cost = 0;
	int len;
	edge* msp;

	quick_sort_radu(e, 0, 7);
	msp = kruskal_radu(e, 8, &cost, &len);

	for (int i = 0; i < len; i++)
		cout << msp[i].a->val << " " << msp[i].b->val << " " << msp[i].len << '\n';

	generare_graf_radu(1500);

	cout << cost;

	/*fout << "n,total" << '\n';
	for (int i = 100; i <= 10000; i += 100)
	{
		clear();
		for (int j = 0; j < i; j++)
		{
			v[j] = CreateNod(j);
			make_set_radu(v[j]);
		}

		total = 0;

		generare_graf_radu(i);
		quick_sort_radu(e, 0, 4 * i - 1);
		total = 0;
		kruskal_radu(e, 4 * i, &cost, &len);
		fout << to_string(i) + "," + to_string(total) << '\n';
	}
	*/
	return 0;
}