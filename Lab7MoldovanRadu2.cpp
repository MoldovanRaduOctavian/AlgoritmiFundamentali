/*
* @author Moldovan Radu
* @group 30224
* 
* Conversia din arbore multicai in arbore binar duce la utilizarea mai eficienta a memoriei, deoarece pentru a reprezenta copiii nu mai folosim un vector de pointeri next[100], ci
* doar doi pointeri left si right, pentru fiul stang si drept.
* Traversarea preordine a unui arbore multicai este similara cu traversarea preordine a unui arbore binar.
* Transformarile arborelui se efectueaza cu complexitate O(n), si folosesc vectori auxiliari de pointeri catre noduri, care are trebui sa aiba dimensiune egala
* cu numarul de noduri din arbore.
*/

#include <iostream>
#define length(x) (sizeof(x)/sizeof(*x))
using namespace std;

struct nod
{
	int val;
	int nr;
	nod* next[100];
};

struct nod_bi
{
	int val;
	nod_bi* right;
	nod_bi* left;
};

nod* aux[100];
nod_bi* aux_bi[100];

int child[100][100];
int child_len[100];

int input[100], n;

nod* CreateNod(int val)
{
	nod* ret = (nod*)malloc(sizeof(nod));
	ret->val = val;
	ret->nr = 0;

	for (int i = 0; i < 100; i++)
		ret->next[i] = NULL;

	return ret;
}

nod_bi* CreateNodBi(int val)
{
	nod_bi* ret = (nod_bi*)malloc(sizeof(nod_bi));
	ret->val = val;
	ret->left = NULL;
	ret->right = NULL;

	return ret;
}

nod* TransformR2(int a[], int n)
{
	nod* head = NULL;
	
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == -1)
		{
			if (aux[i] == NULL)
			{
				head = CreateNod(i);
				aux[i] = head;
			}

			else
				head = aux[i];
			
		}

		else
		{
			

			if (aux[i] == NULL)
				aux[i] = CreateNod(i);

			if (aux[a[i]] == NULL)
				aux[a[i]] = CreateNod(a[i]);

			aux[a[i]]->next[aux[a[i]]->nr] = aux[i];
			aux[a[i]]->nr++;

		}
	}

	return head;
}

void Btree(nod* head)
{
	if (aux_bi[head->val] == NULL)
		aux_bi[head->val] = CreateNodBi(head->val);

	if (head->next[0] != NULL)
	{
		if (aux_bi[head->next[0]->val] == NULL)
			aux_bi[head->next[0]->val] = CreateNodBi(head->next[0]->val);

		aux_bi[head->val]->left = aux_bi[head->next[0]->val];

		for (int i = 1; i < head->nr; i++)
		{
			if (aux_bi[head->next[i]->val] == NULL)
				aux_bi[head->next[i]->val] = CreateNodBi(head->next[i]->val);

			aux_bi[head->next[i - 1]->val]->right = aux_bi[head->next[i]->val];
		}
	}

	for (int i = 0; i < head->nr; i++)
		if (head->next[i] != NULL)
			Btree(head->next[i]);
}

nod_bi* TransformR3(nod* head)
{
	nod_bi* ret = NULL;
	Btree(head);

	ret = aux_bi[head->val];
	return ret;
}

void Preordine(nod* head)
{
	cout << head->val << " ";
	for (int i = 0; i < head->nr; i++)
		Preordine(head->next[i]);
}

void PreBi(nod_bi* head)
{
	cout << head->val << " ";
	if (head->left != NULL) PreBi(head->left);
	if (head->right != NULL) PreBi(head->right);
}

void PrettyPrintR3(nod_bi* head, int nivel)
{
	for (int i = 0; i < nivel; i++)
		cout << "  ";

	cout << head->val << '\n';

	if (head->left != NULL) PrettyPrintR3(head->left, nivel + 1);
	if (head->right != NULL) PrettyPrintR3(head->right, nivel);
}

void PrettyPrintR2(nod* head, int nivel)
{
	for (int i = 0; i < nivel; i++)
		cout << "  ";

	cout << head->val << '\n';

	for (int i = 0; i < head->nr; i++)
		PrettyPrintR2(head->next[i], nivel + 1);
}

void f1(int a[], int n)
{
	for (int i = 1; i <= n; i++)
		if (a[i] != -1)
			child[a[i]][child_len[a[i]]++] = i;
	
}

void f2(int x, int nivel)
{
	for (int i = 0; i < nivel; i++)
		cout << "  ";
	
	cout << x << '\n';

	for (int i = 0; i < child_len[x]; i++)
		f2(child[x][i], nivel + 1);

}

void PrettyPrintR1(int a[], int n)
{
	int root = 0;

	for (int i=1; i<=n; i++)
		if (a[i] == -1)
		{
			root = i;
			break;
		}

	f1(a, n);
	f2(root, 0);
}

int main()
{
	int arr[] = { 2, 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	/*nod* tree = TransformR2(arr, 9);
	nod_bi* bin = TransformR3(tree);



	PrettyPrintR1(arr, 9);
	PrettyPrintR2(tree, 0);
	PrettyPrintR3(bin, 0);*/

	/*cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> input[i];*/

	int root;
	int x;

	cin >> n;
	cin >> root;
	
	input[root] = -1;
	for (int i = 1; i <= n; i++)
	{
		cout << i << ": ";
		cin >> x;
		while (x != 0)
		{
			input[x] = i;
			cin >> x;
		}
	}

	for (int i = 1; i <= n; i++)
		cout << input[i] << " ";

	nod* tree = TransformR2(input, n);
	nod_bi* bin = TransformR3(tree);
	
	cout << '\n';
	PrettyPrintR1(input, n);
	cout << '\n';
	PrettyPrintR2(tree, 0);
	cout << '\n';
	PrettyPrintR3(bin, 0);


	//Preordine(tree);

	return 0;
}