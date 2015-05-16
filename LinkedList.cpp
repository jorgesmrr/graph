#include "LinkedList.h"
#include "Vertex.h"
#include "Edge.h"
#include "NodeContainer.h"
#include <stddef.h>
#include <iostream>

using namespace std;

template <class T>
LinkedList<T>::LinkedList() {
	this->first = NULL;
	this->it = NULL;
	this->size = 0;
}

template <class T>
T* LinkedList<T>::get(){
    if(it != NULL)
        return this->it->getElement();
    else
        return NULL;
}

template <class T>
void LinkedList<T>::goFirst(){
    this->it = first;
}

template <class T>
void LinkedList<T>::next(){
    if(it != NULL)
        this->it = it->getNext();
}

template <class T>
void LinkedList<T>::add(T* newElement){
    if(first == NULL){
        first = new NodeContainer<T>(newElement);
        it = first;
    } else if(it == NULL){
        this->goFirst();
        while(it->getNext() != NULL)
            this->next();
        it->setNext(new NodeContainer<T>(newElement));
        it = it->getNext();
    } else {
        NodeContainer<T>* aux = new NodeContainer<T>(newElement);
        aux->setNext(it->getNext());
        it->setNext(aux);
        it = aux;
    }
    size++;
}

template <class T>
void LinkedList<T>::remove(){
    if(it == NULL)
        return;
    else if (it == first){
        delete it;
        first = NULL;
        it = NULL;
        size--;
    } else {
        NodeContainer<T>* aux = it;
        goFirst();
        while(it->getNext() != aux)
            next();
        it->setNext(aux->getNext());
        delete aux;
        size--;
    }
}

template <class T>
int LinkedList<T>::getSize(){
    return this->size;
}

template <class T>
LinkedList<T>::~LinkedList() {
	if(first == NULL)
        return;
    else{
        goFirst();
        while(it != NULL){
            NodeContainer<T>* aux = it;
            it = it->getNext();
            delete aux;
        }
    }
}

template class LinkedList<Vertex>;
template class LinkedList<Edge>;
template class LinkedList<int>;
template class LinkedList<char>;
