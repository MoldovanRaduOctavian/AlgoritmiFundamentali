#include <iostream>
using namespace std;


void bfs(int adj[100][100], int n, int start)
{
	int viz[100] = {0};
	int l = 0, r = 1;
	int q[100] = { 0 };
	int curr;
	q[0] = start;
	viz[start] = 1;
	
	while (l < r)
	{
		curr = q[l];
		cout << curr << '\n';
		l++;
		for (int i=0; i<n; i++)
			if (adj[curr][i] == 1 && viz[i] == 0)
			{
				q[r++] = i;
				viz[i] = 1;
			}
	}
}


int main()
{
	int adj[100][100] = { {0, 1, 1, 0},
						  {1, 0, 0, 1},
						  {1, 1, 0, 1},
						  {1, 1, 1, 0}
	};

	bfs(adj, 4, 0);

	return 0;
}