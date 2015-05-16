#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

/**
 * Classe para guardar informações sobre uma adjacência
 * de um Vertex. Contém o Vertex de destino e o valor
 * atribuído à adjacência (o significado do valor depende
 * do contexto da aplicação, pode ser custo ou distância,
 * por exemplo).
 */
class Edge {
private:
	int vertexId;
	float value;
public:
	Edge(int vertexId, float value);
	int getVertexId();
	void setVertexId(int vertexId);
	float getValue();
	void setValue(float value);
	~Edge();
};

#endif // ARESTA_H_INCLUDED
