/*
* @author Moldovan Radu
* @group 30224
* 
* Specificatiile problemei : analiza performantei operatiunii de cautare intr-o tabela hash cu adresare deschisa ce foloseste verificare patratica
* 
* Efortul mediu de cautare al unui element creste odata cu valoarea factorului de umplere
* Efortul mediu de cautare al unui element ce nu se gaseste in tabela are o crestere mult mai rapida decat efortul mediu de cautare al unui element prezent, acest aspect fiind mai vizibil
* odata cu cresterea factorului de umplere
* Observatie din Cormen : Numarul mediu de elemente accesate pana la gasirea cu succes a unui element in tabela de dispersie este (1/factor_umplere) * ln (1/(1 - factor_umplere))
* pentru tabele cu factorul de umplere < 1
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#define N 10007
using namespace std;

ofstream fout("Lab5MoldovanRadu.csv");

int hash_table[N], gen[N];
int fill_table[] = { 8005, 8505, 9006, 9507, 9907 };
int fill_values[] = { 80, 85, 90, 95, 99 };
int values[N], poz[4000], negasite[4000];
int efort_gasite, efort_negasite;
int efort_maxim_gasite, efort_maxim_negasite;

int h(int val, int i)
{
	return ((val % N) + 2 * i + 2 * i * i) % N;
}

int hash_insert_radu(int hash[], int val)
{
	int i = 0;

	do
	{
		if (hash[h(val, i)] == 0)
		{
			hash[h(val, i)] = val;
			return i;
		}

		else
			i++;
	} while (i != N);

	return -1;

}

int hash_search_radu(int hash[], int val, int mode)
{
	int i = 0, efort = 0;

	do
	{
		efort++;
		if (hash[h(val, i)] == val)
		{
			if (mode == 1)
			{
				efort_gasite += efort;

				if (efort > efort_maxim_gasite)
					efort_maxim_gasite = efort;
			}
			
			return h(val, i);
		}
			

		i++;
	} while (i != N && hash[h(val, i)] != 0);


	if (mode == 1)
	{
		efort_negasite += efort;

		if (efort > efort_maxim_negasite)
			efort_maxim_negasite = efort;
	}
		
	return -1;
}

void clear(int hash[])
{
	for (int i = 0; i < N; i++)
		hash[i] = 0;
}

void generare(int fill)
{
	for (int i = 0; i < N; i++)
		values[i] = 0;

	for (int i = 0; i < 3000; i++)
	{
		poz[i] = 0;
		negasite[i] = 0;
	}


	clear(hash_table);

	for (int i = 0; i < fill; i++)
	{
		values[i] = rand() % 100000;
		hash_insert_radu(hash_table, values[i]);
	}

	for (int i = 0; i < 1500; i++)
		poz[i] = rand() % fill;

	for (int i = 0; i < 1500; i++)
	{
		int aux = rand() % 100000;
		while (hash_search_radu(hash_table, aux, 0) != -1)
			aux = rand() % 100000;

		negasite[i] = aux;
	}

}

int main()
{
	srand(time(NULL));

	
	for (int i = 0; i < 9506; i++)
		hash_insert_radu(hash_table, rand() % 100000);

	hash_insert_radu(hash_table, 100);
	hash_insert_radu(hash_table, 30);

	cout << hash_search_radu(hash_table, 100, 0) << " " << hash_search_radu(hash_table, 30, 0) << " " << hash_search_radu(hash_table, 100008, 0) << '\n';
	cout << hash_table[hash_search_radu(hash_table, 100, 0)] << " " << hash_table[hash_search_radu(hash_table, 30, 0)];
	clear(hash_table);

	string s;
	fout << "Factor de umplere,Efort mediu gasite,Efort maxim gasite,Efort mediu negasite,Efort maxim negasite" << '\n';
	for (int i = 0; i < 5; i++)
	{
		efort_maxim_gasite = 0;
		efort_maxim_negasite = 0;
		efort_gasite = 0;
		efort_negasite = 0;

		for (int j = 0; j < 5; j++)
		{
			generare(fill_table[i]);
			
			for (int k = 0; k < 1500; k++)
			{
				hash_search_radu(hash_table, values[poz[k]], 1);
				hash_search_radu(hash_table, negasite[k], 1);
			}

		}

		float maxg, maxng, medg, medng;
		medg = ((float)efort_gasite) / (1500 * 5);
		medng = ((float)efort_negasite) / (1500 * 5);
		maxg = ((float)efort_maxim_gasite);
		maxng = ((float)efort_maxim_negasite);


		s = to_string(fill_values[i]) + "," +
			to_string(medg) + "," +
			to_string(maxg) + "," + 
			to_string(medng) + "," + 
			to_string(maxng);

		fout << s << '\n';


	}
		


	//cout << hash_search(hash_table, N) << " " << hash_search(hash_table, 2 * N);

	return 0;
}