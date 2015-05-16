#ifndef NODECONTAINER_H_INCLUDED
#define NODECONTAINER_H_INCLUDED

/**
 * Classe para encapsular um elemento da ListAdj.
 * Cont�m o elemento e um ponteiro para o pr�ximo.
 */
template <class T>
class NodeContainer {
private:
	T* element;
	NodeContainer* next;
public:
	NodeContainer(T* element);
	T* getElement();
	NodeContainer* getNext();
	void setNext(NodeContainer* next);
	~NodeContainer();
};

#endif // NODECONTAINER_H_INCLUDED
