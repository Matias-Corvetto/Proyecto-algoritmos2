#include <iostream>
#include "ejercicio4-utils/Lista.cpp"
using namespace std;

// Función para imprimir la solución
void printSolution(int **sudoku, int fil, int col, bool trasponer)
{

	for (int i = 0; i < fil; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << sudoku[i][j];
			if (j < col - 1)
			{
				cout << " ";
			}
		}
		// if (i < fil - 1) {
		cout << endl;
		// }
	}
}

// Función para verificar si la posición es compatible con el número
bool esCompatible(int **sudoku, int num, int posI, int posJ, int fil, int col)
{

	// Revisar si esta en columna
	for (int i = 0; i < fil; i++)
	{
		if (sudoku[i][posJ] == num)
			return false;
	}

	// Revisar si esta en fila
	for (int j = 0; j < col; j++)
	{
		if (sudoku[posI][j] == num)
			return false;
	}

	// Hallar posiciones del cuadrante actual
	int cuadI = (posI / (fil / 3)) * (fil / 3);
	int cuadJ = (posJ / (col / 3)) * (col / 3);

	// Revisar si esta en el cuadrante
	for (int i = cuadI; i < cuadI + fil / 3; i++)
	{
		for (int j = cuadJ; j < cuadJ + col / 3; j++)
		{
			if (sudoku[i][j] == num)
				return false;
		}
	}

	return true;
}

// Función principal de backtracking para resolver el sudoku
void resolverSudoku(int **sudoku, int fil, int col, Lista<int> *cerosI, Lista<int> *cerosJ, bool &solucionado, bool trasponer)
{

	if (solucionado)
	{
		return;
	}

	// Si no hay posiciones vacías, entonces devolver la solución conseguida
	if (cerosI->esVacia() && cerosJ->esVacia())
	{
		solucionado = true;
		printSolution(sudoku, fil, col, trasponer);
		return;
	}

	// Considerar la primer celda vacía e intentar rellenarla
	int i = cerosI->getPpio();
	int j = cerosJ->getPpio();

	if (sudoku[i][j] == 0)
	{

		int k = max(col, fil);

		// Probar distintos números para esta celda
		for (int num = 1; num <= k; num++)
		{

			// Revisar si el número puede ser colocado
			if (esCompatible(sudoku, num, i, j, fil, col))
			{

				// Colocar el número y marcar la celda como ocupada
				sudoku[i][j] = num;
				cerosI->borrarPpio();
				cerosJ->borrarPpio();

				//cout << "Colocando " << num << " en " << i << ", " << j << "  " << cerosI->getLargo() << endl;
				// Recursión para rellenar el resto de las celdas
				resolverSudoku(sudoku, fil, col, cerosI, cerosJ, solucionado, trasponer);

				// Deshacer el cambio
				sudoku[i][j] = 0;
				cerosI->addPpio(i);
				cerosJ->addPpio(j);
			}
		}
	}

	// Si la celda no puede ser rellenada con ningún numero, entonces terminar
	return;
}

// Función main para probar el código de arriba
int main()
{
	int filas = 0;
	cin >> filas;

	int columnas = 0;
	cin >> columnas;

	Lista<int> *cerosI = new Lista<int>();
	Lista<int> *cerosJ = new Lista<int>();

	int **sudoku = NULL;
	bool trasponer = false;

	sudoku = new int *[filas];

	for (int i = 0; i < filas; i++)
	{
		sudoku[i] = new int[columnas];
		for (int j = 0; j < columnas; j++)
		{
			cin >> sudoku[i][j];
			if (sudoku[i][j] == 0)
			{
				cerosI->addFin(i);
				cerosJ->addFin(j);
			}
		}
	}

	bool solucionado = false;

	// printSolution(sudoku, filas, columnas, trasponer);
	resolverSudoku(sudoku, filas, columnas, cerosI, cerosJ, solucionado, trasponer);

	if (!solucionado)
	{
		cout << "La solucion no existe" << endl;
	}

	for (int i = 0; i < filas; i++)
	{
		delete[] sudoku[i];
	}
	delete[] sudoku;

	delete cerosI;
	delete cerosJ;
}