#ifndef LISTADJ_H_INCLUDED
#define LISTADJ_H_INCLUDED
#include "NodeContainer.h"

using namespace std;

/**
 * Classe genérica para construir e manipular uma lista de adjacências. Neste projeto, é
 * utilizada pela classe Grafo para, armazenar seus vértices, e pela classe Vertice, para
 * armazenar seus adjacentes/suas arestas.
 */
template <class T>
class LinkedList {
private:
    /** Ponteiro para o elemento inicial **/
    NodeContainer<T>* first;
    /** Ponteiro para o elemento armazenado na posição atual **/
    NodeContainer<T>* it;
    /** Quantidade de itens armazenados **/
    int size;
public:
	LinkedList();
	/** Retorna o elemento armazenado na posição atual **/
	T* get();
	/** Posiciona o iterador na primeira posição da lista **/
	void goFirst();
	/** Avança o iterador em uma posição **/
	void next();
	/** Adiciona um elemento na posição atual e posiciona o iterador no elemento inserido **/
	void add(T* newElement);
	/** Remove um elemento e posiciona o iterador na posição anterior à do elemento removido **/
	void remove();
	/** Retorna a quantidade de itens armazenados **/
	int getSize();
	~LinkedList();
};

#endif // LISTADJ_H_INCLUDED
