#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "Vertex.h"
#include <iostream>

using namespace std;

/**
 * Classe Graph para armazenar os v�rtices de um grafo.
 * As arestas podem ser obtidas a partir da lista de
 * adjac�ncia que cada v�rtice possui.
 */
class Graph {
private:
    /** Lista com os v�rtices **/
	LinkedList<Vertex>* vertexes;
	/**
     * Flag utilizada para saber se o conjunto de v�rtices e/ou de arestas mudou.
     * Por exemplo, uma vez que as componentes sejam identificadas, essa informa��o
     * ser� armazenada e o c�lculo s� ser� refeito se o grafo tiver mudado (ou seja,
     * changed == true), evitando redund�ncias.
     **/
	bool changed;
	/**
	 * Armazena o grau dos v�rtices caso o grafo seja k-regular, sendo k >= 0.
	 * Do contr�rio, k = -1.
	 **/
	int k;
	/** Um vetor que indica � qual componente conexa cada v�rtice pertence **/
	int* componentsFlags;
	/** Quantidade de componentes conexas do grafo **/
	int componentsCount;

    /** Iniciliaza a estrutura para o uso **/
    void initGraph();
    /** Navega na lista de v�rtices at� o v�rtice com o id informado **/
	void goToVertex(int id);
	/**
	 * Calcula o m�ximo de arestas que o grafo suporta,
	 * ignorando self-loops e arestas paralelas.
	 **/
	int getMaximumEdgesCount();
	/** L� um arquivo para construir o grafo **/
	void readFile();
	/** Identifica as componentes do grafo **/
	void computeComponents();
public:
	Graph();
	Graph(const string filename);
	Vertex* getVertex(int id);
	/** Retorna o grau de um v�rtice **/
	int getVertexDegree(int id);
	/** Adiciona um v�rtice **/
	void addVertex(float info);
	/** Remove um v�rtice **/
	void removeVertex(int id);
	/** Adiciona uma aresta **/
	void addEdge(int i, int j, float value);
	/** Remove uam aresta **/
	void removeEdge(int i, int j);
	/** Verifica se uma aresta existe **/
	bool edgeExists(int i, int j);
	/** Verifica se o grafo est� completo **/
	bool isComplete();
	/** Verifica se o grafo � k-regular **/
	int isKRegular();
	/** Retorna o n�mero de v�rtices **/
	int getVertexCount();
	/** Retorna o n�mero de arestas **/
	int getEdgesCount();
	/** Retorna o grau m�dio **/
	float getAverageDegree();
	/** Retorna a distribui��o emp�rica do grau dos v�rtices **/
	float* getDegreeDistribution();
	/** Retorna o n�mero de componentes conexas. O grafo � conexo se o valor retornado � 1. **/
	int getComponentsCount();
	/** Retorna o n�mero de v�rtices na maior componente conexa **/
	int getBiggestComponentSize();
	/** Retorna o n�mero de v�rtices na menor componente conexa **/
	int getSmallestComponentSize();
	/** Verifica se dois v�rtices est�o conectados **/
	bool isConnected(int i, int j);
	/** Verifica se uma aresta � ponte **/
	bool isBridge(int i, int j);
	/** Verifica se um v�rtice � ponto de articula��o **/
	bool isArticulationVertex(int id);
	/** Exibe o grafo com a mesma estrutura dos arquivos de entrada **/
	void print();
	~Graph();
};

#endif // GRAFO_H_INCLUDED
