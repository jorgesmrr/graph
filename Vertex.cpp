#include "Vertex.h"
#include "LinkedList.h"
#include <stddef.h>

using namespace std;

Vertex::Vertex(int id, float info) {
    this->id = id;
    this->info = info;
    this->edges = new LinkedList<Edge>();
}

int Vertex::getId(){
    return this->id;
}

void Vertex::setId(int id){
    this->id = id;
}

float Vertex::getInfo(){
    return this->info;
}

void Vertex::setInfo(float info){
    this->info = info;
}

bool Vertex::hasEdgeTo(int vertexId){
    this->edges->goFirst();
    while(this->edges->get() != NULL){
        if(this->edges->get()->getVertexId() == vertexId)
            return true;
        this->edges->next();
    }
    return false;
}

LinkedList<Edge>* Vertex::getEdges(){
    return this->edges;
}

Vertex::~Vertex() {
	delete edges;
}
