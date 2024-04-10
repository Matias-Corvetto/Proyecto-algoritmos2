#include <iostream>
#include "ejercicio4-utils/Lista.cpp"


void verRelieve(int *mountains, int mitad, bool *noEsPico) {
	if (mountains[mitad] > mountains[mitad + 1])
	{
		noEsPico[mitad + 1] = true;
	} else if (mountains[mitad] < mountains[mitad + 1]){
		noEsPico[mitad] = true;
	} else {
		noEsPico[mitad] = true;
		noEsPico[mitad + 1] = true;
	
	}

	if (mountains[mitad] > mountains[mitad - 1])
	{
		noEsPico[mitad - 1] = true;
	} else if (mountains[mitad] < mountains[mitad - 1]) {
		noEsPico[mitad] = true;
	} else {
		noEsPico[mitad] = true;
		noEsPico[mitad - 1] = true;
	}
}

void buscarPicos(int *mountains, int ini, int fin, Lista<int> *&picos, bool *noEsPico)
{
	if (fin-ini == 1) {
		if (mountains[ini] > mountains[fin] && !noEsPico[ini]) {
			picos->addFin(mountains[ini]);
		} else if (mountains[ini] < mountains[fin] && !noEsPico[fin]) {
			picos->addFin(mountains[fin]);
		}
		return;
	} else if (ini == fin && !noEsPico[ini]) {
		picos->addFin(mountains[ini]);
		return;
	} else if (ini == fin) {
		return;
	}

	int mitad = (ini + fin) / 2;

	verRelieve(mountains, mitad, noEsPico);

	buscarPicos(mountains, ini, mitad, picos, noEsPico);
	buscarPicos(mountains, mitad + 1, fin, picos, noEsPico);
}

int main()
{
	int n;
	std::cin >> n;

	int *mountains = new int[n];

	for (int i = 0; i < n; i++)
	{
		std::cin >> mountains[i];
	}

	Lista<int> *picos = new Lista<int>();

	bool *noEsPico = new bool[n];
	for (int i = 0; i < n; i++)
	{
		noEsPico[i] = false;
	}

	buscarPicos(mountains, 0, n - 1, picos, noEsPico);

	if (picos->esVacia())
	{
		std::cout << "No se encontraron picos" << std::endl;
	}
	else
	{
		while (!picos->esVacia())
		{
			std::cout << picos->getPpio() << std::endl;
			picos->borrarPpio();
		}
	}

	delete[] mountains;
	delete picos;
}