/*
* @author Moldovan Radu
* @group 30224
* 
* Algoritmul DFS parcurge muchiile incidente celui mai recent descoperit nod care are inca muchii neparcurse.
* In momentul in care toate muchiile incidente unui nod sunt parcurse, se revine la nodul anterior.
* Complexitatea in timp a algoritmului DFS este O(nr_noduri + nr_muchii)
* 
*/
#include <iostream>
#include <string>
#include <fstream>
#define MIN(x, y) ((x<y)?(x):(y))
#define WHITE 0
#define GRAY 1
#define BLACK 2
using namespace std;

ofstream fout("dfs.csv");

struct nod
{
	int val;
	int SzAdj;
	nod* adj[300];
};


nod* reff[300] = {NULL};
int finish[300];
int par[300];
int color[300];
int discover[300];
int ts[300];
int ts_size;
int timer;

int index[300];
int lowlink[300];
int onstack[300];

int curr_index;

struct stck
{
	int top;
	int item[400];
};

stck st;

void push(int val)
{
	st.top++;
	st.item[st.top] = val;

}

int pop()
{
	return st.top < 0 ? -1 : st.item[st.top--];
}

int total;

nod* CreateNod(int val)
{
	nod* ret = (nod*)malloc(sizeof(nod));
	ret->SzAdj = 0;
	ret->val = val;

	return ret;
}

void AddAdj(int n, int r)
{
	reff[n]->adj[reff[n]->SzAdj] = reff[r];
	reff[n]->SzAdj++;
}

int IsAdj(int n, int r)
{
	for (int i = 0; i < reff[n]->SzAdj; i++)
		if (reff[n]->adj[i] == reff[r])
			return 1;

	return 0;
}

void dfs_visit(int u)
{
	timer++;
	discover[u] = timer;
	color[u] = GRAY;
	total += 3;

	cout << u << '\n';

	for (int i = 0; i < reff[u]->SzAdj; i++)
	{
		total++;
		if (color[reff[u]->adj[i]->val] == WHITE)
		{
			total++;
			par[reff[u]->adj[i]->val] = u;
			dfs_visit(reff[u]->adj[i]->val);
		}
	}

	total += 4;
	color[u] = BLACK;
	timer++;
	finish[u] = timer;
	ts[ts_size++] = u;
}

void dfs()
{
	for (int i = 0; i < 200; i++)
	{
		color[i] = WHITE;
		par[i] = -1;
		finish[i] = -1;
		discover[i] = -1;
	}

	ts_size = 0;
	timer = 0;
	total = 0;

	for (int i = 0; i < 200; i++)
		if (reff[i] != NULL && color[i] == WHITE)
			dfs_visit(i);


}

void topological_sort()
{
	dfs();

	cout << '\n';
	int aux;
	for (int i = 0; i <= ts_size / 2; i++)
	{
		aux = ts[i];
		ts[i] = ts[ts_size - i - 1];
		ts[ts_size - i - 1] = aux;

	}

	for (int i = 0; i < ts_size; i++)
		cout << ts[i] << " ";
}



void free_graph()
{
	for (int i = 0; i < 300; i++)
		if (reff[i] != NULL)
			free(reff[i]);
}

void tarjan(int v)
{
	int aux;

	index[v] = curr_index;
	lowlink[v] = curr_index;
	curr_index++;

	push(v);
	onstack[v] = 1;

	for (int i = 0; i < reff[v]->SzAdj; i++)
	{
		if (index[reff[v]->adj[i]->val] == -1)
		{
			tarjan(reff[v]->adj[i]->val);
			lowlink[v] = MIN(lowlink[v], lowlink[reff[v]->adj[i]->val]);
		}

		else if (onstack[reff[v]->adj[i]->val])
			lowlink[v] = MIN(lowlink[v], index[reff[v]->adj[i]->val]);
	}

	if (index[v] == lowlink[v])
	{
		while ((aux = pop()) != -1)
		{
			onstack[aux] = 0;
			cout << aux << " ";

			if (aux == v)
			{
				cout << '\n';
				break;
			}
		}
	}

}

void tarj_reset()
{
	for (int i = 0; i < 300; i++)
	{
		index[i] = -1;
		lowlink[i] = -1;
		onstack[i] = 0;
	}

	curr_index = 0;

	for (int i = 0; i < 300; i++)
		if (reff[i] != NULL && index[i] == -1)
			tarjan(i);
}

void generare_graf(int n, int e)
{
	int x, y, ok = 0;
	char ad[250][250], viz[250];

	for (int i=0; i<200; i++)
		for (int j = 0; j < 200; j++)
		{
			ad[i][j] = 0;
		}

	for (int i = 0; i < e;)
	{
		x = rand() % n;
		y = rand() % n;

		if (ad[x][y] != 1)
			i++;

		ad[x][y] = 1;
	}

	for (int i = 0; i < n; i++)
		reff[i] = CreateNod(i);

	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 200; j++)
			if (ad[i][j] == 1)
				AddAdj(i, j);
	
}

int main()
{
	for (int i = 0; i < 300; i++)
		reff[i] = NULL;

	reff[0] = CreateNod(0);
	reff[1] = CreateNod(1);
	reff[2] = CreateNod(2);
	reff[3] = CreateNod(3);
	reff[4] = CreateNod(4);
	/*reff[5] = CreateNod(5);
	reff[6] = CreateNod(6);
	reff[7] = CreateNod(7);*/

	AddAdj(0, 2);
	AddAdj(0, 3);
	AddAdj(1, 0);
	AddAdj(2, 1);
	AddAdj(3, 4);

	for (int i=0; i<100; i++)
		if (reff[i] != NULL)
		{
			cout << i << ": ";

			for (int j = 0; j < reff[i]->SzAdj; j++)
				cout << reff[i]->adj[j]->val << " ";

			cout << '\n';
		}
	

	cout << "\n\n";

	dfs();

	cout << '\n';
	topological_sort();
	cout << '\n';
	for (int i = 0; i < 5; i++)
		cout << finish[i] << " ";

	cout << '\n';

	tarj_reset();

	/*srand(time(0));

	fout << "e,total" << '\n';
	for (int x = 1000; x <= 4500; x += 100)
	{
		free_graph();
		generare_graf(100, x);

		dfs();

		fout << to_string(x) + "," + to_string(total);
		fout << '\n';

		
	}

	fout << "n,total" << '\n';
	for (int y = 100; y <= 200; y += 10)
	{
		free_graph();
		generare_graf(y, 4500);

		dfs();

		fout << to_string(y) + "," + to_string(total);
		fout << '\n';

	}*/

	//tarj_reset();

	return 0;
}