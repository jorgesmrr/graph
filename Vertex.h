#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED

#include "Edge.h"
#include "LinkedList.h"

using namespace std;

/**
 * Classe Vertex para armazenar informa��es
 * de um v�rtice do Graph. Cada Vertex possui o identificador,
 * a informa��o e um ponteiro para a lista de v�rtices adjacentes.
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
