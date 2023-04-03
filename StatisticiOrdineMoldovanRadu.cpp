/*
* @author Moldovan Radu
* @group 30224
*
* complexitatea construirii arborelui este O(n), deoarece algoritmul parcurge fiecare element o singura data
* 
* operatia os_select parcurge la fiecare apel un nivel al arborelui, motiv pentru care timpul de executie creste proportional cu inaltimea arborelui.
* pentru ca arborele de statistici este avl, inaltime este log n, deci complexitatea cautarii unui element este O(log n);
* 
* pentru arbori echilibrati, complexitatea stergerii este O(log n), deoarece h = log n
* 
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Profiler.h"
#define length(x) (sizeof(x)/sizeof(*x))
#define MAX(a, b) ((a > b)?a:b)
using namespace std;

int v[11000], v_rand[11000];
int total;

ofstream fout("StatisticiOrdineMoldovanRadu.csv");

struct nod
{
	int val;
	int size;
	nod* left;
	nod* right;
};


nod* build_tree(int a[], int l, int r)
{
	total++;
	int mid = (l + r) / 2;

	total++;
	if (l > r)
		return NULL;

	total += 5;
	nod* ret = (nod*)malloc(sizeof(nod));
	ret->val = a[mid];
	ret->left = NULL;
	ret->right = NULL;
	ret->size = 1;

	total += 2;
	ret->left = build_tree(a, l, mid - 1);
	ret->right = build_tree(a, mid + 1, r);

	total++;
	if (ret->left != NULL)
	{
		ret->size += ret->left->size;
		total++;
	}

	total++;
	if (ret->right != NULL)
	{
		ret->size += ret->right->size;
		total++;
	}

	return ret;
}

nod* os_select(nod* head, int i)
{
	total++;
	int r = 1;

	total++;
	if (head == NULL)
		return NULL;

	total++;
	if (head->left != NULL)
	{
		total++;
		r = head->left->size + 1;
	}
		


	total += 2;
	if (i == r)
		return head;

	else if (i < r)
		return os_select(head->left, i);

	return os_select(head->right, i - r);
}


nod* minn(nod* head)
{
	total++;
	nod* curr = head;


	while (curr->left != NULL)
	{
		curr = curr->left;
		total++;
	}

	return curr;
}
 
nod* os_delete(nod** head, int val)
{
	total++;
	if (*head == NULL)
		return NULL;

	total += 2;
	nod* aux = NULL;
	(*head)->size--;

	total++;
	if (val < (*head)->val)
	{
		total++;
		(*head)->left = os_delete(&((*head)->left), val);
	}

	else if (val > (*head)->val)
	{
		total++;
		(*head)->right = os_delete(&((*head)->right), val);
	}
		

	else
	{
		total++;
		if ((*head)->left == NULL)
		{
			total++;
			aux = (*head)->right;
			free(*head);
			return aux;
		}

		else if ((*head)->right == NULL)
		{
			total++;
			aux = (*head)->left;
			free(*head);
			return aux;
		}

		total += 3;
		aux = minn((*head)->right);
		(*head)->val = aux->val;
		(*head)->right = os_delete(&((*head)->right), aux->val);

	}

	return *head;

}

void pre(nod* head)
{
	cout << head->val << " " << head->size << '\n';

	if (head->left != NULL) pre(head->left);
	if (head->right != NULL) pre(head->right);
	
}

void PrettyPrint(nod* head, int x)
{
	for (int i = 0; i < x; i++)
		cout << " ";

	cout << head->val << '\n';

	if (head->left != NULL) PrettyPrint(head->left, x + 1);
	if (head->right != NULL) PrettyPrint(head->right, x + 1);
}

void fill(int* a, int n)
{
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
}

int main()
{
	int test[] = { 3, 7, 10, 12, 14, 16, 17, 19, 20,
		21, 26, 28, 30, 35, 38, 39, 41, 47 };

	int x[] = { 1, 2, 3, 4, 5};

	nod* tree = build_tree(test, 0, length(test) - 1);
	nod* t2 = build_tree(x, 0, 4);
	nod* t3;
	

	cout << os_select(tree, 1)->val << " ";
	t3 = os_delete(&tree, 3);
	cout << os_select(t3, 1)->val << " ";
	cout << os_select(t3, 17)-> val << "\n";
	tree = os_delete(&t3, 47);
	t3 = os_delete(&tree, 41);
	cout << os_select(t3, 15)->val;


	cout << "\n\n";
	PrettyPrint(t3, 0);
	cout << "\n\n";

	/*fout << "n,total" << "\n";
	for (int i = 100; i <= 10000; i += 100)
	{
		total = 0;

		for (int j = 1; j <= 5; j++)
		{
			fill(v, i);
			FillRandomArray(v_rand, i, 1, i, true, 0);
			nod* aux = build_tree(v, 0, i);
			
			for (int k = 1; k < i; k++)
			{
				nod* select =  os_select(aux, v[k]);
				if (select != NULL)
				{
					nod* p = os_delete(&aux, select->val);
					aux = p;
				}
			}
			
		}

		total /= 5 * i;
		fout << to_string(i) + "," + to_string(total) << "\n";

	}*/


	return 0;
}