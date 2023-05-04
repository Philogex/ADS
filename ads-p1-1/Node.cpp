#include "Node.h"
Node::Node()
{
    next = 0;
    prev = 0;
    value = 0;
}
Node::Node(int value, Node* next, Node* prev)
{
    this->value  = value;
    this->next = next;
    this->prev = prev;
}
Node::~Node()
{}
