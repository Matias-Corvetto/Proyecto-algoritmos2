#include <iostream>
#include "Lista.cpp"
#include "../ejercicio6-utils/MinHeap.cpp"
#define INF 9999999

using namespace std;

class Arista
{
public:
	int destino;
	int ponderacion;
	Arista(int destino, int ponderacion)
	{
		this->destino = destino;
		this->ponderacion = ponderacion;
	}
};

template <class T>
class Grafo
{
private:
	int cantVertices;
	int tope;
	T **vertices;
	Lista<Arista *> **ListaAdy;

	void buscarVertice(T origen, int &posOrigen, T destino, int &posDestino)
	{
		for (int i = 0; i < this->tope && (posOrigen == -1 || posDestino == -1); i++)
		{

			if (this->vertices[i] && *this->vertices[i] == origen)
			{
				posOrigen = i;
			}
			if (this->vertices[i] && *this->vertices[i] == destino)
			{
				posDestino = i;
			}
		}
	}

	int buscarElemSinIncidenciasOrden(int *cantInicidencias)
	{
		T *prox = NULL;
		int proxPos = -1;
		for (int i = 0; i < this->tope; i++)
		{
			if (cantInicidencias[i] == 0)
			{
				if (!prox)
				{
					prox = this->vertices[i];
					proxPos = i;
				}
				else
				{
					if (*prox > *this->vertices[i])
					{
						prox = this->vertices[i];
						proxPos = i;
					}
				}
			}
		}
		return proxPos;
	}

	int posVertex(T vertex)
	{
		for (int i = 0; i < this->tope; i++)
		{

			if (this->vertices[i] && *this->vertices[i] == vertex)
			{
				return i;
			}
		}
		return -1;
	}

	bool existeEnLista(Lista<Arista *> *lista, int pos)
	{
		int largo = lista->getLargo();
		for (int i = 0; i < largo; i++)
		{
			if (lista->getPos(i)->destino == pos)
			{
				return true;
			}
		}
		return false;
	}

public:
	Grafo(int tope)
	{
		this->tope = tope;
		this->cantVertices = 0;

		this->vertices = new T *[tope];
		for (int i = 0; i < tope; i++)
		{
			vertices[i] = NULL;
		}

		this->ListaAdy = new Lista<Arista *> *[tope];
		for (int i = 0; i < tope; i++)
		{
			ListaAdy[i] = new Lista<Arista *>();
		}
	}

	void agregarVertice(T vertice)
	{
		this->vertices[this->cantVertices++] = new T(vertice);
	}

	void agregarArista(T origen, T destino, int ponderacion)
	{
		int posOrigen = -1;
		int posDestino = -1;
		this->buscarVertice(origen, posOrigen, destino, posDestino);
		Arista *arista = new Arista(posDestino, ponderacion);
		this->ListaAdy[posOrigen]->addFin(arista);
	}

	void agregarAristaNoDirigido(T origen, T destino, int ponderacion)
	{
		int posOrigen = -1;
		int posDestino = -1;
		this->buscarVertice(origen, posOrigen, destino, posDestino);
		Arista *aristaDestino = new Arista(posDestino, ponderacion);
		Arista *aristaOrigen = new Arista(posOrigen, ponderacion);
		this->ListaAdy[posOrigen]->addFin(aristaDestino);
		this->ListaAdy[posDestino]->addFin(aristaOrigen);
	}

	Lista<T> *ordenTopologico(bool &tieneCiclo)
	{
		Lista<T> *ret = new Lista<T>();
		int *cantIncidencias = new int[this->tope];

		for (int i = 0; i < this->tope; i++)
		{
			cantIncidencias[i] = 0;
		}

		for (int i = 0; i < this->tope; i++)
		{
			for (int j = 0; j < this->tope; j++)
			{
				if (existeEnLista(this->ListaAdy[j], i))
				{
					cantIncidencias[i]++;
				}
			}
		}

		for (int k = 0; k < this->tope; k++)
		{
			int posSinIndicencias = buscarElemSinIncidenciasOrden(cantIncidencias);
			if (posSinIndicencias == -1)
			{
				tieneCiclo = true;
				delete ret;
				return new Lista<T>();
			}
			else
			{
				ret->addFin(*this->vertices[posSinIndicencias]);
				cantIncidencias[posSinIndicencias]--;
				int largo = this->ListaAdy[posSinIndicencias]->getLargo();
				for (int i = 0; i < largo; i++)
				{
					Arista *arista = ListaAdy[posSinIndicencias]->getPos(i);
					cantIncidencias[arista->destino]--;
				}
			}
		}

		delete[] cantIncidencias;
		return ret;
	}

	int dijkstra(T from, T to)
	{
		int posFrom = posVertex(from);
		int posTo = posVertex(to);

		int *cost = new int[this->tope];
		bool *visited = new bool[this->tope];

		for (int i = 0; i < this->tope; i++)
		{
			cost[i] = INF;
			visited[i] = false;
		}

		cost[posFrom] = 0;

		MinHeap<int> *heap = new MinHeap<int>(this->tope * this->tope);
		heap->enqueue(0, posFrom);

		while (!heap->isEmpty())
		{
			int v = heap->getMinPos();
			heap->dequeue();

			if (!visited[v])
			{
				visited[v] = true;

				Lista<Arista *> *actual = this->ListaAdy[v]->clonar();
				while (!actual->esVacia())
				{
					int i = actual->getPpio()->destino;
					int ponderacion = actual->getPpio()->ponderacion;
					if (!visited[i] && cost[i] > cost[v] + ponderacion)
					{
						cost[i] = cost[v] + ponderacion;
						heap->enqueue(cost[i], i);
					}
					actual->borrarPpio();
				}
				delete actual;
			}
		}

		delete heap;
		if (!visited[posTo])
		{
			return -1;
		}
		return cost[posTo];
	}

	int *prim()
	{
		int *dis = new int[this->tope];
		int *ant = new int[this->tope];
		bool *vis = new bool[this->tope];

		for (int i = 0; i < this->tope; i++)
		{
			dis[i] = INF;
			ant[i] = -1;
			vis[i] = false;
		}

		dis[0] = 0;

		MinHeap<int> *heap = new MinHeap<int>(this->tope * this->tope);
		heap->enqueue(0, 0);

		while (!heap->isEmpty())
		{
			int proxPos = heap->getMinPos();
			heap->dequeue();

			if (!vis[proxPos])
			{
				vis[proxPos] = true;

				Lista<Arista *> *actual = this->ListaAdy[proxPos]->clonar();
				while (!actual->esVacia())
				{
					int i = actual->getPpio()->destino;
					int ponderacion = actual->getPpio()->ponderacion;
					if (!vis[i] && dis[i] > ponderacion)
					{
						dis[i] = ponderacion;
						ant[i] = proxPos;

						heap->enqueue(dis[i], i);
					}
					actual->borrarPpio();
				}
				delete actual;
			}
		}
		delete heap;
		return dis;
	}

	~Grafo()
	{
		for (int i = 0; i < this->tope; i++)
		{
			delete this->vertices[i];
			delete this->ListaAdy[i];
		}
	}
};
