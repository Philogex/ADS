#ifndef _NODE_H
#define _NODE_H
class Node
{
public:
    int   value;
    Node *next, *prev;

public:
    Node();
    Node(int value, Node* next = 0, Node* prev = 0);
    ~Node();
};
#endif