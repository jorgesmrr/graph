#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Edge.h"
#include "LinkedList.h"

using namespace std;

/**
 * Classe Vertex para armazenar informações
 * de um vértice do Graph. Cada Vertex possui o identificador,
 * a informação e um ponteiro para a lista de vértices adjacentes.
 */
class Vertex {
private:
	int id;
	float info;
	LinkedList<Edge>* edges;
public:
	Vertex(int id, float info);
	~Vertex();
	int getId();
	void setId(int id);
	float getInfo();
	void setInfo(float info);
	bool hasEdgeTo(int vertexId);
	LinkedList<Edge>* getEdges();
};

#endif // VERTICE_H_INCLUDED
