#include "Graph.h"
#include "Utils.h"
#include <stddef.h>
#include <iostream>
#include <fstream>

using namespace std;

Graph::Graph() {
    initGraph();
}

Graph::Graph(const string filename){
    initGraph();

    ifstream file;
    file.open(filename.c_str());

    int n = 0;
    file >> n;

    for(int i = 0; i < n; i++)
        this->addVertex(0);

    while(!file.eof()){
        int vertex1, vertex2;
        file >> vertex1 >> vertex2;
        this->addEdge(vertex1, vertex2, 0);
    }

    file.close();
}

void Graph::initGraph(){
    this->vertexes = new LinkedList<Vertex>();
    this-> k = -1;
    this->changed = false;
    this->componentsFlags = NULL;
    this->componentsCount = 1;
}

int Graph::getMaximumEdgesCount(){
    int vertexCount = getVertexCount();
    return (vertexCount * (vertexCount - 1))/2;
}

void Graph::goToVertex(int id){
    this->vertexes->goFirst();
    while(this->vertexes->get()->getId() != id)
        this->vertexes->next();
}

void Graph::computeComponents(){
    if(changed || componentsFlags == NULL){
        /// quantidade de componentes encontradas
        componentsCount = 0;
        /// utilizado para identificar as componentes (n�o pode ser decrementado)
        int componentsAux = 0;

        /// inicializa vetor
        componentsFlags = new int[this->vertexes->getSize()];
        for(int i = 0; i < this->vertexes->getSize(); i++){
            componentsFlags[i] = 0;
        }

        /// percorre v�rtices
        this->vertexes->goFirst();
        for(int i = 1; this->vertexes->get() != NULL; i++){
            /// ...percorre adjac�ncias
            this->vertexes->get()->getEdges()->goFirst();
            while(this->vertexes->get()->getEdges()->get() != NULL){

                /// se o vizinho est� em uma componente...
                if(componentsFlags[this->vertexes->get()->getEdges()->get()->getVertexId() - 1] != 0){
                    /// ...e o v�rtice atual ainda n�o foi 'movido' para nenhuma componente...
                    if(componentsFlags[i-1] == 0){
                        /// ...'move' o v�rtice atual para a componente do vizinho
                        componentsFlags[i-1] = componentsFlags[this->vertexes->get()->getEdges()->get()->getVertexId() - 1];
                    } else if (componentsFlags[i-1] != componentsFlags[this->vertexes->get()->getEdges()->get()->getVertexId() - 1]){
                        /// ...sen�o, se este vizinho est� em uma componente diferente,
                        /// 'movemos' todos de da componente do vizinho para a do v�rtice atual
                        int aux = componentsFlags[this->vertexes->get()->getEdges()->get()->getVertexId() - 1];
                        for(int j = 0; j < this->vertexes->getSize(); j++) {
                            if(componentsFlags[j] == aux){
                                componentsFlags[j] = componentsFlags[i-1];
                            }
                        }
                        componentsCount--;
                    }
                }

                this->vertexes->get()->getEdges()->next();
            }

            /// ...se o v�rtice ainda n�o est� em uma componente,
            /// ele est� desconectado dos anteriores, em uma nova componente
            if(componentsFlags[i-1] == 0) {
                componentsFlags[i-1] = ++componentsAux;
                componentsCount++;
            }

            this->vertexes->next();
        }
    }
}

Vertex* Graph::getVertex(int id){
    if(id <= vertexes->getSize()){
        this->goToVertex(id);
        return this->vertexes->get();
    } else
        return NULL;
}

void Graph::addVertex(float info){
    this->vertexes->add(new Vertex(this->vertexes->getSize() + 1, info));
    this->changed = true;
}

void Graph::removeVertex(int id){
    if(id > 0 && id <= vertexes->getSize()){
        /// itera at� o v�rtice desejado e o remove
        goToVertex(id);
        vertexes->remove();

        /// percorre todos os v�rtices
        vertexes->goFirst();
        while(vertexes->get() != NULL){
            /// se o id � maior que o id do v�rtice removido...
            if(vertexes->get()->getId() > id){
                /// ...decrementa o id em 1 unidade
                vertexes->get()->setId(vertexes->get()->getId() - 1);
            }

            /// percorre arestas
            vertexes->get()->getEdges()->goFirst();
            while(vertexes->get()->getEdges()->get() != NULL){
                int aux = vertexes->get()->getEdges()->get()->getVertexId();
                /// se a aresta tem destino ao v�rtice removido
                if(aux == id)
                    /// ...remove a aresta
                    vertexes->get()->getEdges()->remove();
                else if(aux > id)
                    /// ...sen�o, se a aresta tem destino a um v�rtice de id maior que
                    /// o id do v�rtice removido, decrementa-o em 1 unidade
                    vertexes->get()->getEdges()->get()->setVertexId(aux - 1);
                vertexes->get()->getEdges()->next();
            }
            vertexes->next();
        }

        changed = true;
    }
}

void Graph::addEdge(int i, int j, float value){
    if(Utils::isInRange(1, this->vertexes->getSize(), i, j)){
        /// como estamos tratando de grafos n�o direcionados,
        /// inserimos uma aresta (i,j) e uma (j,i)
        this->goToVertex(i);
        this->vertexes->get()->getEdges()->add(new Edge(j, value));
        this->goToVertex(j);
        this->vertexes->get()->getEdges()->add(new Edge(i, value));
        this->changed = true;
    }
}

void Graph::removeEdge(int i, int j){
    if(Utils::isInRange(1, this->vertexes->getSize(), i, j) && !edgeExists(i,j)){
        /// remove a aresta de i para j
        this->goToVertex(i);
        LinkedList<Edge>* edges = this->vertexes->get()->getEdges();
        edges->goFirst();
        while(edges->get()->getVertexId() != j)
            edges->next();
        edges->remove();

        /// remove a aresta de j para i
        this->goToVertex(j);
        edges = this->vertexes->get()->getEdges();
        edges->goFirst();
        while(edges->get()->getVertexId() != i)
            edges->next();
        edges->remove();
        this->changed = true;
    }
}

bool Graph::edgeExists(int i, int j){
    goToVertex(i);
    vertexes->get()->getEdges()->goFirst();
    while(vertexes->get()->getEdges()->get() != NULL){
        if(vertexes->get()->getEdges()->get()->getVertexId() == j)
            return true;
        vertexes->get()->getEdges()->next();
    }
    return false;
}

bool Graph::isComplete(){
    return getEdgesCount() == getMaximumEdgesCount();
}

int Graph::isKRegular(){
    /// se o grafo n�o tenha mudado e k j� foi calculado...
    if(!changed && k != -1)
        return k;
    else {
        /// ...sen�o verifica se todos os n�s t�m o mesmo grau
        vertexes->goFirst();
        k = vertexes->get()->getEdges()->getSize();
        vertexes->next();

        while(vertexes->get() != NULL){
            if(k != vertexes->get()->getEdges()->getSize()){
                k = -1;
                return k;
            }
            vertexes->next();
        }

        return k;
    }
}

int Graph::getVertexCount(){
    return this->vertexes->getSize();
}

int Graph::getEdgesCount(){
    this->vertexes->goFirst();
    int edgesCount = 0;
    while(this->vertexes->get() != NULL){
        edgesCount += this->vertexes->get()->getEdges()->getSize();
        this->vertexes->next();
    }
    return edgesCount / 2;
}

float Graph::getAverageDegree(){
    return (float) 2 * getEdgesCount() / getVertexCount();
}

float* Graph::getDegreeDistribution(){
    /// inicializa��o
    int n = getVertexCount();
    float* dist = new float[n];
    for(int i = 0; i < n; i++)
        dist[i] = 0;

    /// conta quantos v�rtices h� para cada grau poss�vel
    vertexes->goFirst();
    while(vertexes->get() != NULL){
        dist[vertexes->get()->getEdges()->getSize()]++;
        vertexes->next();
    }

    /// divide cada quantidade pelo total de n�s
    for(int i = 0; i < n; i++)
        dist[i] /= n;

    return dist;
}

int Graph::getComponentsCount(){
    computeComponents();
    return componentsCount;
}

int Graph::getBiggestComponentSize(){
    if(componentsCount == 1)
        return getVertexCount();
    else {
        /// inicializa��o
        int* count = new int[getVertexCount()];
        for (int i = 0; i < getVertexCount(); i++){
            count[i] = 0;
        }
        /// conta quantos v�rtices cada componente tem
        for (int i = 0; i < getVertexCount(); i++){
            count[componentsFlags[i]]++;
        }
        /// pega a maior quantidade
        int biggest = count[0];
        for (int i = 0; i < getVertexCount(); i++){
            if(count[i] > biggest)
                biggest = count[i];
        }
        return biggest;
    }
}

int Graph::getSmallestComponentSize(){
    if(componentsCount == 1)
        return getVertexCount();
    else {
        /// inicializa��o
        int* count = new int[getVertexCount()];
        for (int i = 0; i < getVertexCount(); i++){
            count[i] = 0;
        }
        /// conta quantos v�rtices cada componente tem
        for (int i = 0; i < getVertexCount(); i++){
            count[componentsFlags[i]]++;
        }
        /// pega a menor quantidade
        int smallest = 0;
        for (int i = 0; i < getVertexCount(); i++){
            if(smallest == 0 || (count[i] > 0 && count[i] < smallest) )
                smallest = count[i];
        }
        return smallest;
    }
}

bool Graph::isConnected(int i, int j){
    if(Utils::isInRange(1, this->vertexes->getSize(), i, j)){
        /// identifica componentes conexas
        computeComponents();
        /// os v�rtices s�o conexos se pertencem a uma mesma componente conexa
        return componentsFlags[i - 1] == componentsFlags[j - 1];
    } else
        return false;
}

bool Graph::isBridge(int i, int j){
    if(Utils::isInRange(1, this->vertexes->getSize(), i, j)){
        /// armazena o n�mero de compoenentes conexas
        computeComponents();
        int oldComponentsCount = componentsCount;

        /// remove aresta (i,j)
        int edgeValue;
        goToVertex(i);
        vertexes->get()->getEdges()->goFirst();
        while(vertexes->get()->getEdges()->get()->getVertexId() != j)
            vertexes->get()->getEdges()->next();
        edgeValue = vertexes->get()->getEdges()->get()->getValue();
        vertexes->get()->getEdges()->remove();

        /// remove aresta (j,i)
        goToVertex(j);
        vertexes->get()->getEdges()->goFirst();
        while(vertexes->get()->getEdges()->get()->getVertexId() != i)
            vertexes->get()->getEdges()->next();
        vertexes->get()->getEdges()->remove();

        /// calcula quantas componentes conexas o grafo possui sem a aresta
        computeComponents();

        /// a aresta � ponte se uma nova componente conexa surgiu
        bool isBridge = oldComponentsCount < componentsCount;

        /// restaura aresta
        goToVertex(i);
        vertexes->get()->getEdges()->add(new Edge(j, edgeValue));
        goToVertex(j);
        vertexes->get()->getEdges()->add(new Edge(i, edgeValue));

        return isBridge;
    }
    return false;
}

bool Graph::isArticulationVertex(int id){
    /// identifica as componentes
    computeComponents();
    int oldComponentsCount = componentsCount;

    /// remove o v�rtice
    goToVertex(id);
    int vertexInfo = vertexes->get()->getInfo();
    vertexes->remove();

    /// remove todas as arestas associadas ao v�rtice
    LinkedList<Edge>* edges = new LinkedList<Edge>();
    vertexes->goFirst();
    while(vertexes->get() != NULL){
        vertexes->get()->getEdges()->goFirst();
        while(vertexes->get()->getEdges()->get() != NULL){
            int aux = vertexes->get()->getEdges()->get()->getVertexId();
            if(aux == id){
                edges->add(new Edge(vertexes->get()->getId(), vertexes->get()->getEdges()->get()->getValue()));
                vertexes->get()->getEdges()->remove();
            } else if(aux > id){
                vertexes->get()->getEdges()->get()->setVertexId(aux - 1);
            }
            vertexes->get()->getEdges()->next();
        }
        if(vertexes->get()->getId() > id)
            vertexes->get()->setId(vertexes->get()->getId() - 1);
        vertexes->next();
    }

    /// identifica as componentes novamente e compara os resultados
    /// obtidos antes e ap�s a remo��o do v�rtice
    computeComponents();
    bool isArticulationPoint = oldComponentsCount < componentsCount;

    /// restaura v�rtice e suas adjac�ncias
    vertexes->goFirst();
    while(vertexes->get() != NULL){
        int aux = vertexes->get()->getId();
        if(aux >= id){
            vertexes->get()->setId(aux + 1);
        }
        vertexes->get()->getEdges()->goFirst();
        while(vertexes->get()->getEdges()->get() != NULL){
            int aux2 = vertexes->get()->getEdges()->get()->getVertexId();
            if (aux2 > id - 1){
                vertexes->get()->getEdges()->get()->setVertexId(aux2 + 1);
            }
            vertexes->get()->getEdges()->next();
        }
        if(aux == id - 1){
            vertexes->add(new Vertex(id, vertexInfo));
            vertexes->next();
        }
        vertexes->next();
    }
    edges->goFirst();
    while(edges->get() != NULL){
        addEdge(id, edges->get()->getVertexId(), edges->get()->getValue());
        edges->next();
    }

    return isArticulationPoint;
}

void Graph::print(){
    cout << this->vertexes->getSize() << endl;

    this->vertexes->goFirst();
    while(this->vertexes->get() != NULL){
        this->vertexes->get()->getEdges()->goFirst();
        while(this->vertexes->get()->getEdges()->get() != NULL){
            /// S� imprime se o id do v�rtice de origem for menor que o do de destino,
            /// pois o grafo � n�o direcionado
            if(this->vertexes->get()->getId() < this->vertexes->get()->getEdges()->get()->getVertexId()){
                cout << this->vertexes->get()->getId() << " " << this->vertexes->get()->getEdges()->get()->getVertexId() << endl;
            }
            this->vertexes->get()->getEdges()->next();
        }
        this->vertexes->next();
    }
}

Graph::~Graph() {

}
