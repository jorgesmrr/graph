#ifndef LISTADJ_H_INCLUDED
#define LISTADJ_H_INCLUDED
#include "NodeContainer.h"

using namespace std;

/**
 * Classe gen�rica para construir e manipular uma lista de adjac�ncias. Neste projeto, �
 * utilizada pela classe Grafo para, armazenar seus v�rtices, e pela classe Vertice, para
 * armazenar seus adjacentes/suas arestas.
 */
template <class T>
class LinkedList {
private:
    /** Ponteiro para o elemento inicial **/
    NodeContainer<T>* first;
    /** Ponteiro para o elemento armazenado na posi��o atual **/
    NodeContainer<T>* it;
    /** Quantidade de itens armazenados **/
    int size;
public:
	LinkedList();
	/** Retorna o elemento armazenado na posi��o atual **/
	T* get();
	/** Posiciona o iterador na primeira posi��o da lista **/
	void goFirst();
	/** Avan�a o iterador em uma posi��o **/
	void next();
	/** Adiciona um elemento na posi��o atual e posiciona o iterador no elemento inserido **/
	void add(T* newElement);
	/** Remove um elemento e posiciona o iterador na posi��o anterior � do elemento removido **/
	void remove();
	/** Retorna a quantidade de itens armazenados **/
	int getSize();
	~LinkedList();
};

#endif // LISTADJ_H_INCLUDED
