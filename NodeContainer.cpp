#include "NodeContainer.h"
#include "Vertex.h"
#include "Edge.h"
#include <stddef.h>

using namespace std;

template <class T>
NodeContainer<T>::NodeContainer(T* element) {
	this->element = element;
	this->next = NULL;
}

template <class T>
T* NodeContainer<T>::getElement(){
    return this->element;
}

template <class T>
NodeContainer<T>* NodeContainer<T>::getNext(){
    return this->next;
}

template <class T>
void NodeContainer<T>::setNext(NodeContainer* next){
    this->next = next;
}

template <class T>
NodeContainer<T>::~NodeContainer() {
	delete element;
}

template class NodeContainer<Vertex>;
template class NodeContainer<Edge>;
template class NodeContainer<int>;
template class NodeContainer<char>;
