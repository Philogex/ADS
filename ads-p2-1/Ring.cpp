/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring.cpp
#include "Ring.h"
#include <iostream>

// Ihr Code hier:

void Ring::addNode(std::string description, std::string data) {
    RingNode* newNode = new RingNode(0, description, data);
    if(countNodes == 0) {
        anker = newNode;
        anker->setNext(anker);
        countNodes++;
    }

    else {
        RingNode* tmp = anker->getNext();

        //all elements to countNodes - 1
        for(int i = 0; i < countNodes - 1; i++)
        {
            tmp->setAge(tmp->getAge() + 1);
            tmp = tmp->getNext();
        }
        //last element
        tmp->setAge(tmp->getAge() + 1);

        newNode->setNext(anker->getNext());
        anker->setNext(newNode);
        anker = newNode;
        
        if(countNodes == 6)
        {
            tmp = newNode->getNext();
            newNode->setNext(newNode->getNext()->getNext());
            delete tmp;
        }
        else {
            countNodes++; 
        }
    }
}

bool Ring::search(std::string value) {
    RingNode* tmp = anker;
    for(int i = 0; i < countNodes; i++) {
        if(value == tmp->getData()) { return true; }
        tmp = tmp->getNext();
    }
    return false;
}

void Ring::print() {
    printHelper(anker->getNext());
}

void Ring::printHelper(RingNode* node) {
    if(node == anker) { node->printNode(); return; }
    printHelper(node->getNext());
    node->printNode();
};

void Ring::printSearch(std::string data) {
    RingNode* tmp = anker;
    for(int i = 0; i < countNodes; i++) {
        if(data == tmp->getData()) {
            break;
        }
        tmp = tmp->getNext();
    }

    std::cout   << "+ Gefunden in Backup: Alter "
                << tmp->getAge()
                << ", Beschreibung: "
                << tmp->getDescription()
                << ", Daten: "
                << tmp->getData()
                << std::endl
                << std::endl;
}