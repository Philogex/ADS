#ifndef _NODE_H
#define _NODE_H

template <typename Tf>
class Node
{
public:
    Tf value;
    Node<Tf> *next, *prev;

public:
    Node();
    Node(Tf value, Node<Tf>* next = 0, Node<Tf>* prev = 0);
    ~Node();
};
#endif

template <typename Tf>
Node<Tf>::Node()
{
    next = 0;
    prev = 0;
}

template <typename Tf>
Node<Tf>::Node(Tf value, Node<Tf>* next, Node<Tf>* prev)
{
    this->value  = value;
    this->next = next;
    this->prev = prev;
}

template <typename Tf>
Node<Tf>::~Node()
{}