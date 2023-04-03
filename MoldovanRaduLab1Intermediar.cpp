/*
* @author Moldovan Radu
* @group 30224
* 
* Specificatiile problemei, ex: Compararea metodelor de sortare bubble, select si insert sort.
* 
* Bubble sort - Metoda de sortare ce se bazeaza pe interschimbarea elementelor adiacente din sirul ce se cere sortat, aflate in dezordine.
*				Cu o modificare care verifica daca s-a petrecut vreo interschimbare in ultima iteratie a for-ului interior, bubble sort devine eficient pentru siruri aporape sortate.
*				Dupa fiecare iteratie a for-ului interior, in capatul sirului ajunge cea mai mare valoare.
*
* Select sort - Metoda de sortare bazata pe plasarea pe pozitia k a lui k-lea cel mai mic numar din sir.
*				Select sort imparte sirul in 2 sectiuni: sortata si nesortata.
* 
* Insert sort - Metoda de sortare care imparte sirul intr-o parte sortata si una nesortata: se alege un element din partea nesortata si se compara cu elementele din partea sortata pana se gaseste pozitia potrivita pentru inserare.
*
* Stabilitate - Bubble sort: stabil
*				Select sort: instabil fara modificari
*				Insert sort: stabil
* 
* Eficienta - Cei 3 algoritmi au complexitatea O(n ^ 2), insa din grafice reiese ca in orice situatie bubble sort prezinta un numar mult mai mare de operatii efectuate fata de select si insert.
*			  Pentru valori aproape sortate sau sortate, insert sort este mult mai eficient decat select sort.
*			  Pentru valori sortate descrescator (caz nefavorabil), select sort este mai eficient decat insert sort.
			  In cazul mediu statistic, select si insert sort prezinta performante asemanatoare.
			  Alt avantaj al insert sort fata de select sort il reprezinta stabilitatea algoritmului.
* 
*/

#include "Profiler.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream fout("MoldovanRaduLab1.csv", ios_base::app);

int v[10000], v_bubble[10000], v_select[10000], v_insert[10000], n;
int a_bubble, c_bubble, a_select, c_select, a_insert, c_insert, total_bubble, total_select, total_insert;
int mediu_a_bubble[11000], mediu_c_bubble[11000], mediu_total_bubble[11000],
	mediu_a_select[11000], mediu_c_select[11000], mediu_total_select[11000],
	mediu_a_insert[11000], mediu_c_insert[11000], mediu_total_insert[11000];

void bubble_sort(int v[], int n)
{
	int aux;
	
	a_bubble = 0;
	c_bubble = 0;
	total_bubble = 0;

	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n - 1; j++)
		{
			
			c_bubble++;
			if (v[j] > v[j + 1])
			{
				a_bubble += 3;
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;	
			}

		}

	}

	total_bubble = a_bubble + c_bubble;

}

void select_sort(int v[], int n)
{
	
	int ind_maxx = 0;
	int aux;

	a_select = 0;
	c_select = 0;
	total_select = 0;

	for (int i = 0; i < n - 1; i++)
	{
		ind_maxx = i;
		a_select++;
		for (int j = i + 1; j < n; j++)
		{
			c_select++;
			if (v[j] < v[ind_maxx])
			{
				a_select++;
				ind_maxx = j;
			}
				
		}
			
		a_select += 3;
		aux = v[i];
		v[i] = v[ind_maxx];
		v[ind_maxx] = aux;

	}

	total_select = a_select + c_select;

}

void insert_sort(int v[], int n)
{
	
	int j, val;

	a_insert = 0;
	c_insert = 0;
	total_insert = 0;

	for (int i = 1; i < n; i++)
	{
		j = i - 1;

		a_insert++;
		val = v[i];

		c_insert++;
		while (j >= 0 && val < v[j])
		{
			c_insert++;
			a_insert++;
			v[j + 1] = v[j];
			j--;
		}


		a_insert++;
		v[j + 1] = val;

	}

	total_insert = a_insert + c_insert;

}

int main()
{
	// Testare corectitudine
	int aux_bubble[] = { 5, -4, 33, 2, 1 };
	int aux_select[] = { 5, 4, 3, 200, 1 };
	int aux_insert[] = { 5, 4, 3, 2, 1000 };

	bubble_sort(aux_bubble, 5);
	select_sort(aux_select, 5);
	insert_sort(aux_insert, 5);

	cout << "Bubble: ";
	for (int i = 0; i < 5; i++)
		cout << aux_bubble[i] << " ";

	cout << "\nSelect: ";
	for (int i = 0; i < 5; i++)
		cout << aux_select[i] << " ";

	cout << "\nInsert: ";
	for (int i = 0; i < 5; i++)
		cout << aux_insert[i] << " ";

	/*string s, h;
	h = "n,a_bubble,c_bubble,total_bubble,a_select,c_select,total_select,a_insert,c_insert,total_insert";
	// Caz favorabil

	fout << "Caz favorabil" << "\n\n";
	fout << h << '\n';
	for (int i = 100; i < 10000; i += 500)
	{
		FillRandomArray(v_bubble, i, 1, 10000, false, 1);
		bubble_sort(v_bubble, i);
		select_sort(v_bubble, i);
		insert_sort(v_bubble, i);

		s = to_string(i) + ","
			+ to_string(a_bubble) + ","
			+ to_string(c_bubble) + ","
			+ to_string(total_bubble) + ","
			+ to_string(a_select) + ","
			+ to_string(c_select) + ","
			+ to_string(total_select) + ","
			+ to_string(a_insert) + ","
			+ to_string(c_insert) + ","
			+ to_string(total_insert);
		
		fout << s << '\n';

	}

	
	// Caz Nefavorabil
	fout << "\nCaz nefavorabil\n\n";
	fout << h << '\n';
	for (int i = 100; i < 10000; i += 500)
	{
		FillRandomArray(v_bubble, i, 1, 10000, false, 2);
		FillRandomArray(v_select, i, 1, 10000, false, 2);
		FillRandomArray(v_insert, i, 1, 10000, false, 2);
		bubble_sort(v_bubble, i);
		select_sort(v_select, i);
		insert_sort(v_insert, i);

		s = to_string(i) + ","
			+ to_string(a_bubble) + ","
			+ to_string(c_bubble) + ","
			+ to_string(total_bubble) + ","
			+ to_string(a_select) + ","
			+ to_string(c_select) + ","
			+ to_string(total_select) + ","
			+ to_string(a_insert) + ","
			+ to_string(c_insert) + ","
			+ to_string(total_insert);

		fout << s << '\n';
	}
	
	// Caz Mediu
	for (int i=0; i<5; i++)
		for (int j = 100; j < 10000; j += 500)
		{
			FillRandomArray(v, j, 1, 10000, false, 0);
			for (int k = 0; k < j; k++)
			{
				v_bubble[k] = v[k];
				v_select[k] = v[k];
				v_insert[k] = v[k];

			}

			bubble_sort(v_bubble, j);
			select_sort(v_select, j);
			insert_sort(v_insert, j);

			mediu_a_bubble[j] += a_bubble; mediu_c_bubble[j] += c_bubble; mediu_total_bubble[j] += total_bubble;
			mediu_a_select[j] += a_select; mediu_c_select[j] += c_select; mediu_total_select[j] += total_select;
			mediu_a_insert[j] += a_insert; mediu_c_insert[j] += c_insert; mediu_total_insert[j] += total_insert;
		}
	
	fout << "\nCaz mediu\n\n";
	fout << h << '\n';

	for (int i = 100; i < 10000; i += 500)
	{
		mediu_a_bubble[i] /= 5; mediu_c_bubble[i] /= 5; mediu_total_bubble[i] /= 5;
		mediu_a_select[i] /= 5; mediu_c_select[i] /= 5; mediu_total_select[i] /= 5;
		mediu_a_insert[i] /= 5; mediu_c_insert[i] /= 5; mediu_total_insert[i] /= 5;

		s = to_string(i) + ","
			+ to_string(mediu_a_bubble[i]) + ","
			+ to_string(mediu_c_bubble[i]) + ","
			+ to_string(mediu_total_bubble[i]) + ","
			+ to_string(mediu_a_select[i]) + ","
			+ to_string(mediu_c_select[i]) + ","
			+ to_string(mediu_total_select[i]) + ","
			+ to_string(mediu_a_insert[i]) + ","
			+ to_string(mediu_c_insert[i]) + ","
			+ to_string(mediu_total_insert[i]);

		fout << s << '\n';

	}*/
	
	return 0;
}