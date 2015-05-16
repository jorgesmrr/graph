#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "Vertex.h"
#include <iostream>

using namespace std;

/**
 * Classe Graph para armazenar os vértices de um grafo.
 * As arestas podem ser obtidas a partir da lista de
 * adjacência que cada vértice possui.
 */
class Graph {
private:
    /** Lista com os vértices **/
	LinkedList<Vertex>* vertexes;
	/**
     * Flag utilizada para saber se o conjunto de vértices e/ou de arestas mudou.
     * Por exemplo, uma vez que as componentes sejam identificadas, essa informação
     * será armazenada e o cálculo só será refeito se o grafo tiver mudado (ou seja,
     * changed == true), evitando redundâncias.
     **/
	bool changed;
	/**
	 * Armazena o grau dos vértices caso o grafo seja k-regular, sendo k >= 0.
	 * Do contrário, k = -1.
	 **/
	int k;
	/** Um vetor que indica à qual componente conexa cada vértice pertence **/
	int* componentsFlags;
	/** Quantidade de componentes conexas do grafo **/
	int componentsCount;

    /** Iniciliaza a estrutura para o uso **/
    void initGraph();
    /** Navega na lista de vértices até o vértice com o id informado **/
	void goToVertex(int id);
	/**
	 * Calcula o máximo de arestas que o grafo suporta,
	 * ignorando self-loops e arestas paralelas.
	 **/
	int getMaximumEdgesCount();
	/** Lê um arquivo para construir o grafo **/
	void readFile();
	/** Identifica as componentes do grafo **/
	void computeComponents();
public:
	Graph();
	Graph(const string filename);
	Vertex* getVertex(int id);
	/** Retorna o grau de um vértice **/
	int getVertexDegree(int id);
	/** Adiciona um vértice **/
	void addVertex(float info);
	/** Remove um vértice **/
	void removeVertex(int id);
	/** Adiciona uma aresta **/
	void addEdge(int i, int j, float value);
	/** Remove uam aresta **/
	void removeEdge(int i, int j);
	/** Verifica se uma aresta existe **/
	bool edgeExists(int i, int j);
	/** Verifica se o grafo está completo **/
	bool isComplete();
	/** Verifica se o grafo é k-regular **/
	int isKRegular();
	/** Retorna o número de vértices **/
	int getVertexCount();
	/** Retorna o número de arestas **/
	int getEdgesCount();
	/** Retorna o grau médio **/
	float getAverageDegree();
	/** Retorna a distribuição empírica do grau dos vértices **/
	float* getDegreeDistribution();
	/** Retorna o número de componentes conexas. O grafo é conexo se o valor retornado é 1. **/
	int getComponentsCount();
	/** Retorna o número de vértices na maior componente conexa **/
	int getBiggestComponentSize();
	/** Retorna o número de vértices na menor componente conexa **/
	int getSmallestComponentSize();
	/** Verifica se dois vértices estão conectados **/
	bool isConnected(int i, int j);
	/** Verifica se uma aresta é ponte **/
	bool isBridge(int i, int j);
	/** Verifica se um vértice é ponto de articulação **/
	bool isArticulationVertex(int id);
	/** Exibe o grafo com a mesma estrutura dos arquivos de entrada **/
	void print();
	~Graph();
};

#endif // GRAFO_H_INCLUDED
