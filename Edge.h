#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

/**
 * Classe para guardar informa��es sobre uma adjac�ncia
 * de um Vertex. Cont�m o Vertex de destino e o valor
 * atribu�do � adjac�ncia (o significado do valor depende
 * do contexto da aplica��o, pode ser custo ou dist�ncia,
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
