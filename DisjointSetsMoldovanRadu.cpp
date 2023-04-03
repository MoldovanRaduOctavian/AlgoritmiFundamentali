#include <iostream>
#define lim (0x7fffffff)
using namespace std;

int p[100];

int gasire_multime(int x)
{
	while (p[x] != x)
		x = p[x];

	return x;
}


void reuniune(int x, int y)
{
	int aux1 = gasire_multime(x);
	int aux2 = gasire_multime(y);

	p[aux1] = aux2;
}

void kruskal(int adj[100][100], int n)
{
	int cost = 0;
	int minn = 0x7fffffff;
	int x, y;

	for (int i = 0; i < n; i++)
		p[i] = i;

	int m = 0;
	while (m < n - 1)
	{
		minn = 0x7fffffff;
		x = -1;
		y = -1;

		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				if (gasire_multime(i) != gasire_multime(j) && adj[i][j] < minn)
				{
					minn = adj[i][j];
					x = i;
					y = j;
				}

		reuniune(x, y);
		cout << "{" << x << " " << y << "}" << '\n';

		cost += minn;
		m++;
	}

	cout << "cost minim = " << cost << '\n';

}

int main()
{
	int n = 5;
	int g[100][100] = {
			{lim, 2, lim, 6, lim},
			{2, lim, 3, 8, 5},
			{lim, 3, lim, lim, 7},
			{6, 8, lim, lim, 9},
			{lim, 5, 7, 9, lim}
	};

	kruskal(g, n);

	return 0;
}