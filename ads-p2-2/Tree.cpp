/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>

#include <queue>

using namespace std;

// Ihr Code hier:
void Tree::addNode(std::string name, int age, double income, int postCode) {
    int orderID = static_cast<int>(age + postCode + income);
    TreeNode* newNode = new TreeNode(orderID, currentNodeChronologicalID++, name, age, income, postCode);
    TreeNode* ptr = anker;

    if(anker == nullptr) {
        anker = newNode;
        return;
    }

    while(true) {
        if(ptr->getOrderID() > orderID) {
            if(ptr->getLeft() == nullptr) { ptr->setLeft(newNode); return; }
            else {ptr = ptr->getLeft(); }
        }
        else {
            if(ptr->getRight() == nullptr) { ptr->setRight(newNode); return; }
            else {ptr = ptr->getRight(); }
        }
    }
}

void Tree::findMinNodeAndParentInBranch(TreeNode* &node, TreeNode* &parent) {
    while(true) {
        if(node->getLeft() == nullptr) { return; }
        parent = node;
        node = node->getLeft();
    }
}

bool Tree::deleteNode(int ID) {

    if(anker == nullptr) { return false; }

    TreeNode* node = anker;
    TreeNode* parent = nullptr;

    while(true) {
        if(node->getOrderID() == ID) { break; }
        if(node->getOrderID() > ID) {
            parent = node;
            node = node->getLeft();
        }
        else {
            parent = node;
            node = node->getRight();
        }
    }

    //node is root
    if(node == anker) {
        //root has no child branches
        if(node->getRight() == nullptr && node->getLeft() == nullptr) {
            delete anker;
            anker = nullptr;
            return true;
        }
        //root only has left child branch
        else if(node->getRight() == nullptr) {
            TreeNode* left = node->getLeft();
            node->setLeft(nullptr);
            delete node;
            anker = left;
            return true;
        }
        //root only has right child branch
        else if(node->getLeft() == nullptr) {
            TreeNode* right = node->getRight();
            node->setRight(nullptr);

            TreeNode* min = right;
            TreeNode* minParent = nullptr;
            findMinNodeAndParentInBranch(min, minParent);

            if(minParent != nullptr) { minParent->setLeft(min->getRight()); }

            delete node;
            anker = min;
            return true;
        }
        //root has two child branches
        else {
            TreeNode* right = node->getRight();
            TreeNode* left = node->getLeft();
            node->setRight(nullptr);
            node->setLeft(nullptr);

            TreeNode* min = right;
            TreeNode* minParent = nullptr;
            findMinNodeAndParentInBranch(min, minParent);

            if(minParent != nullptr) { minParent->setLeft(min->getRight()); }

            delete node;
            min->setLeft(left);
            if(min != right) { min->setRight(right); }
            anker = min;
            return true;
        }
    }

    //node is not root
    else {
        //node has no child branches
        if(node->getRight() == nullptr && node->getLeft() == nullptr) {
            if(parent->getOrderID() > node->getOrderID()) {
                parent->setLeft(nullptr);
            }
            else {
                parent->setRight(nullptr);
            }
            delete node;
            return true;
        }
        //node only has left child branch
        else if(node->getRight() == nullptr) {
            TreeNode* left = node->getLeft();
            node->setLeft(nullptr);
            if(parent->getOrderID() > node->getOrderID()) {
                parent->setLeft(left);
            }
            else {
                parent->setRight(left);
            }
            delete node;
            return true;
        }
        //node only has right child branch
        else if(node->getLeft() == nullptr) {
            TreeNode* right = node->getRight();
            node->setRight(nullptr);

            TreeNode* min = right;
            TreeNode* minParent = nullptr;
            findMinNodeAndParentInBranch(min, minParent);

            if(minParent != nullptr) { minParent->setLeft(min->getRight()); }

            if(parent->getOrderID() > node->getOrderID()) {
                parent->setLeft(min);
            }
            else {
                parent->setRight(min);
            }
            delete node;
            return true;
        }
        //node has two child branches
        else {
            TreeNode* right = node->getRight();
            TreeNode* left = node->getLeft();
            node->setRight(nullptr);
            node->setLeft(nullptr);

            TreeNode* min = right;
            TreeNode* minParent = nullptr;
            findMinNodeAndParentInBranch(min, minParent);

            if(minParent != nullptr) { minParent->setLeft(min->getRight()); }

            min->setLeft(left);
            if(min != right) { min->setRight(right); }
            delete node;
            if(parent->getOrderID() > node->getOrderID()) {
                parent->setLeft(min);
            }
            else {
                parent->setRight(min);
            }
            return true;
        }
    }

    return false;
}

bool Tree::searchNode(std::string name) {

    if (anker == nullptr) {
        return false;
    }

    bool c = false;
    
    queue<TreeNode*> q;
    q.push(anker);
    
    while (!q.empty()) {
        TreeNode* ptr = q.front();
        q.pop();
        
        if (ptr->getName() == name) {
            std::cout << "+ Fundstellen:" << std::endl;
            ptr->print();
            c = true;
        }
        
        if (ptr->getLeft() != nullptr) {
            q.push(ptr->getLeft());
        }
        
        if (ptr->getRight() != nullptr) {
            q.push(ptr->getRight());
        }
    }
    
    if(!c) { std::cout << "- Datensatz nicht gefunden." << std::endl; }
    return c;
}

void Tree::printPreorder(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    const int idWidth = 5;
    const int nameWidth = 14;
    const int ageWidth = 5;
    const int incomeWidth = 12;
    const int postCodeWidth = 8;
    const int orderIdWidth = 10;

    std::cout 
        << left << setw(idWidth) << node->getChronoID() << "|"
        << left << setw(nameWidth) << node->getName() << "|"
        << left << setw(ageWidth) << node->getAge() << "|"
        << left << setw(incomeWidth) << setprecision(2) << fixed << node->getIncome() << "|"
        << left << setw(postCodeWidth) << node->getPostCode() << "|"
        << left << setw(orderIdWidth) << node->getOrderID() << "|"
        << std::endl;

    printPreorder(node->getLeft());
    
    printPreorder(node->getRight());
}

void Tree::printAll() {
    //preorder

    const int idWidth = 5;
    const int nameWidth = 14;
    const int ageWidth = 5;
    const int incomeWidth = 12;
    const int postCodeWidth = 8;
    const int orderIdWidth = 10;

    std::cout 
        << left << setw(idWidth) << "ID" << "|"
        << left << setw(nameWidth) << "Name" << "|"
        << left << setw(ageWidth) << "Age" << "|"
        << left << setw(incomeWidth) << "Income"  << "|"
        << left << setw(postCodeWidth) << "PostCode" << "|"
        << left << setw(orderIdWidth) << "OrderID"
        << std::endl;

    std::cout
        << std::string(idWidth , '-') << '+'
        << std::string(nameWidth, '-') << '+'
        << std::string(ageWidth, '-') << '+'
        << std::string(incomeWidth, '-') << '+'
        << std::string(postCodeWidth, '-') << '+'
        << std::string(orderIdWidth, '-') << '+'
        << std::endl;

    printPreorder(anker);
}

void Tree::printLevelOrder() {
    //levelorder
    if (anker == nullptr) {
        std::cout << "empty tree" << std::endl;
    }
    
    const int idWidth = 5;
    const int nameWidth = 14;
    const int ageWidth = 5;
    const int incomeWidth = 12;
    const int postCodeWidth = 8;
    const int orderIdWidth = 10;
    const int levelWidth = 5;

    std::cout 
        << left << setw(idWidth) << "ID" << "|"
        << left << setw(nameWidth) << "Name" << "|"
        << left << setw(ageWidth) << "Age" << "|"
        << left << setw(incomeWidth) << "Income"  << "|"
        << left << setw(postCodeWidth) << "PostCode" << "|"
        << left << setw(orderIdWidth) << "OrderID" << "|"
        << left << setw(levelWidth) << "Level"
        << std::endl;

    std::cout
        << std::string(idWidth , '-') << '+'
        << std::string(nameWidth, '-') << '+'
        << std::string(ageWidth, '-') << '+'
        << std::string(incomeWidth, '-') << '+'
        << std::string(postCodeWidth, '-') << '+'
        << std::string(orderIdWidth, '-') << '+'
        << std::string(levelWidth, '-') << '+'
        << std::endl;

    queue<TreeNode*> q;
    q.push(anker);

    int cLc = 1;
    int nLC = 0;
    int l = 0;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cLc--;
        
        //node->print();
        std::cout 
            << left << setw(idWidth) << node->getChronoID() << "|"
            << left << setw(nameWidth) << node->getName() << "|"
            << left << setw(ageWidth) << node->getAge() << "|"
            << left << setw(incomeWidth) << setprecision(2) << fixed << node->getIncome() << "|"
            << left << setw(postCodeWidth) << node->getPostCode() << "|"
            << left << setw(orderIdWidth) << node->getOrderID() << "|"
            << left << setw(levelWidth) << l << "|"
            << std::endl;

        
        if (node->getLeft() != nullptr) {
            q.push(node->getLeft());
            nLC++;
        }
        
        if (node->getRight() != nullptr) {
            q.push(node->getRight());
            nLC++;
        }

        if (cLc == 0) {
            cLc = nLC;
            nLC = 0;
            l++;
        }
    }
}