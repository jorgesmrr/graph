#include "Edge.h"
#include "Vertex.h"

using namespace std;

Edge::Edge(int vertexId, float value) {
    this->vertexId = vertexId;
    this->value = value;
}

int Edge::getVertexId(){
    return this->vertexId;
}

void Edge::setVertexId(int vertexId){
    this->vertexId = vertexId;
}

float Edge::getValue(){
    return this->value;
}

void Edge::setValue(float value){
    this->value = value;
}

Edge::~Edge() {

}
