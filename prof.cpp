#include <iostream>
#include "Profiler.h"
using namespace std;

Profiler p("caz_favorabil");

int maxim(int v[], int n)
{
	Operation atribuiri = p.createOperation("Maxim_atribuiri", n);
	Operation comparari = p.createOperation("Maxin_comparari", n);

	int valMaxim = v[0];
	for (int i = 1; i < n; i++)
	{
		comparari.count();
		if (v[i] > valMaxim)
		{
			valMaxim = v[i];
			atribuiri.count();
		}
		
	}

	p.addSeries("Maxim_total", "Maxim_atribuiri", "Maxim_comparari");
	return valMaxim;
}


int main()
{
	int sir[100];

	//favorabil
	for (int i = 10; i <= 100; i += 5)
	{
		FillRandomArray(sir, i, 100, 1000, false, 2);
		
		maxim(sir, i);
	}

	p.createGroup("Favorabil_Nr_atribuiri", "Maxim_atribuiri");
	p.createGroup("Favorabil_Nr_comparari", "Maxim_comparari");
	p.createGroup("Favorabil_Nr_total", "Maxim_total");

	p.showReport();

	//nefavorabil
	p.reset("Caz_Nefavorabil");
	for (int i = 10; i <= 100; i += 5)
	{
		FillRandomArray(sir, i, 100, 1000, false, 1);
		maxim(sir, i);
	}

	p.createGroup("Nefavorabil_Nr_atribuiri", "Maxim_atribuiri");
	p.createGroup("Nefavorabil_Nr_comparari", "Maxim_comparari");
	p.createGroup("Nefavorabil_Nr_total", "Maxim_total");

	p.showReport();

	// mediu statistic
	p.reset("Caz_Mediu");
	for (int j=0; j<5; j++)
		for (int i = 10; i <= 100; i += 5)
		{
			FillRandomArray(sir, i, 100, 1000, false, 0);
			maxim(sir, i);
		}

	p.divideValues("Maxim_atribuiri", 5);
	p.divideValues("Maxim_comparari", 5);
	p.divideValues("Maxim_total", 5);

	p.createGroup("Mediu_Nr_atribuiri", "Maxim_atribuiri");
	p.createGroup("Mediu_Nr_comparari", "Maxim_comparari");
	p.createGroup("Mediu_Nr_total", "Maxim_total");

	p.showReport();


	return 0;
}