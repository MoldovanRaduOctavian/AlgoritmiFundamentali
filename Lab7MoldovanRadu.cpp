#include <iostream>
using namespace std;

struct nod
{
	int val;
	int c;
	nod* next[100];
};

nod* CreateNod(int val)
{
	nod* ret = (nod*)malloc(sizeof(nod));
	ret->val = val;
	ret->c = 0;

	for (int i = 0; i < 100; i++)
		ret->next[i] = NULL;

	return ret;
}


/*nod* GenBtree(int a[], int n)
{
	nod* head;
	
	for (int i=0; i<n; i++)
		if (a[i] == -1)
		{
			head = (nod*)malloc(sizeof())
		}
}*/

void rec_parinte(nod* head, int* parent)
{
	for (int i = 0; i < head->c; i++)
	{
		parent[head->next[i]->val] = head->val;
		
		if (head->next[i]->c != 0)
			rec_parinte(head->next[i], parent);
	}

}

void gen_parinte(nod* head, int* parent)
{
	for (int i = 0; i < 100; i++)
		parent[i] = -1;

	rec_parinte(head, parent);
}

int  main()
{
	int rez[100] = { 0 };
	
	nod* head = CreateNod(7);
	head->c = 3;
	head->next[0] = CreateNod(2);
	head->next[1] = CreateNod(5);
	head->next[2] = CreateNod(6);
	head->next[0]->c = 3;
	head->next[1]->c = 2;
	head->next[2]->c = 0;

	head->next[0]->next[0] = CreateNod(1);
	head->next[0]->next[1] = CreateNod(4);
	head->next[0]->next[2] = CreateNod(9);
	

	head->next[1]->next[0] = CreateNod(3);
	head->next[1]->next[1] = CreateNod(8);

	gen_parinte(head, rez);

	for (int i = 1; i <= 9; i++)
		cout << rez[i] << " ";

	return 0;
}