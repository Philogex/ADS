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

bool Tree::split4Node(TreeNode* node) {
    if(node->getLeft() != nullptr && node->getRight() != nullptr) { 
        if(!node->getRed() && node->getLeft()->getRed() && node->getRight()->getRed()) {
            node->setRed(true);
            node->getLeft()->setRed(false);
            node->getRight()->setRed(false);
            return true;
        }
    }
    return false;
}

void Tree::addNode(std::string name, int age, double income, int postCode) {
    int orderID = static_cast<int>(age + postCode + income);
    TreeNode* newNode = new TreeNode(orderID, currentNodeChronologicalID++, name, age, income, postCode);

    //add node to empty tree and color black
    if(anker == nullptr) {
        newNode->setRed(false);
        anker = newNode;
        return;
    }

    TreeNode* ptr = anker;

    //search node while repeadetly calling split4Node (wasteful ressource management) and inserting node if possible. simultaniously set parent of inserted node
    while(true) {
        if(ptr->getOrderID() > orderID) {
            if(ptr->getLeft() == nullptr) { 
                newNode->setParent(ptr); 
                ptr->setLeft(newNode); 
                ptr = ptr->getLeft(); 
                break; 
            }
            else { ptr = ptr->getLeft(); }
        }
        else {
            if(ptr->getRight() == nullptr) { 
                newNode->setParent(ptr); 
                ptr->setRight(newNode); 
                ptr = ptr->getRight(); 
                break; 
            }
            else { ptr = ptr->getRight(); }
        }
        split4Node(ptr);
    }

    //find two consecutive red nodes and call rebalancing function
    //if you switch the conditions you get errored to hell and back :)
    while(ptr != nullptr && ptr->getParent() != anker) {
        if(ptr->getRed() && ptr->getParent()->getRed()) { balance(ptr); }
        ptr = ptr->getParent();
    }
}

//ich hoffe sie bekommt durchfall. das kommt wirklich vom herzen
void Tree::balance(TreeNode* root) {
    //left-left
    if(root->getParent()->getLeft() == root && root->getParent()->getParent()->getLeft() == root->getParent()) {
        if(root->getParent()->getParent()->getRight() == nullptr) {
            rotateTreeRight(root->getParent()->getParent());
            root->getParent()->setRed(false);
            root->getParent()->getRight()->setRed(true);
        } 
        else if(root->getParent()->getParent()->getRight()->getRed()) {
            root->getParent()->getParent()->setRed(true);
            root->getParent()->setRed(false);
            root->getParent()->getParent()->getRight()->setRed(false);
        }
        else {
            rotateTreeRight(root->getParent()->getParent());
            root->getParent()->setRed(false);
            root->getParent()->getRight()->setRed(true);
            if(root->getParent()->getRight() != nullptr) {
                root->getParent()->getRight()->setRed(true);
            }
        }
    }
    //left-right
    else if(root->getParent()->getRight() == root && root->getParent()->getParent()->getLeft() == root->getParent()) {
        if(root->getParent()->getParent()->getRight() == nullptr) {
            TreeNode* tmp = root->getParent()->getParent();
            rotateTreeLeft(root->getParent());
            rotateTreeRight(tmp);
            root->setRed(false);
            root->getRight()->setRed(true);
        } 
        else if(root->getParent()->getParent()->getRight()->getRed()) {
            root->getParent()->getParent()->setRed(true);
            root->getParent()->setRed(false);
            root->getParent()->getParent()->getRight()->setRed(false);
        }
        else {
            TreeNode* tmp = root->getParent()->getParent();
            rotateTreeLeft(root->getParent());
            rotateTreeRight(tmp);
            root->setRed(false);
            root->getRight()->setRed(true);
        }
    }
    //right-right
    else if(root->getParent()->getRight() == root && root->getParent()->getParent()->getRight() == root->getParent()) {
        if(root->getParent()->getParent()->getLeft() == nullptr) {
            rotateTreeLeft(root->getParent()->getParent());
            root->getParent()->setRed(false);
            root->getParent()->getLeft()->setRed(true);
        } 
        else if(root->getParent()->getParent()->getLeft()->getRed()) {
            root->getParent()->getParent()->setRed(true);
            root->getParent()->setRed(false);
            root->getParent()->getParent()->getLeft()->setRed(false);
        }
        else {
            rotateTreeLeft(root->getParent()->getParent());
            root->getParent()->setRed(false);
            root->getParent()->getLeft()->setRed(true);
            if(root->getParent()->getLeft() != nullptr) {
                root->getParent()->getLeft()->setRed(true);
            }
        }
    }
    //right-left
    else if(root->getParent()->getLeft() == root && root->getParent()->getParent()->getRight() == root->getParent()) {
        if(root->getParent()->getParent()->getLeft() == nullptr) {
            TreeNode* tmp = root->getParent()->getParent();
            rotateTreeRight(root->getParent());
            rotateTreeLeft(tmp);
            root->setRed(false);
            root->getLeft()->setRed(true);
        } 
        else if(root->getParent()->getParent()->getLeft()->getRed()) {
            root->getParent()->getParent()->setRed(true);
            root->getParent()->setRed(false);
            root->getParent()->getParent()->getLeft()->setRed(false);
        }
        else {
            TreeNode* tmp = root->getParent()->getParent();
            rotateTreeRight(root->getParent());
            rotateTreeLeft(tmp);
            root->setRed(false);
            root->getLeft()->setRed(true);
        }
    }
    anker->setRed(false);
}

//wird nicht verwendet
void Tree::recolor(TreeNode* node, bool color) {
    node->setRed(color);
    if(node->getLeft() != nullptr) {
        recolor(node->getLeft(), !color);
    }
    if(node->getRight() != nullptr) {
        recolor(node->getRight(), !color);
    }
}

bool Tree::rotateTreeLeft(TreeNode* root) {
    //error handling
    if(root->getRight() == nullptr) {
        root->setRight(root->getLeft());
        root->setLeft(nullptr);
    }

    TreeNode* new_root = root->getRight();
    //append left child of new_root to right side of root
    root->setRight(new_root->getLeft());
    //set parent of root
    if(new_root->getLeft() != nullptr) {
        new_root->getLeft()->setParent(root);
    }
    //set parent of new_root
    new_root->setParent(root->getParent());
    if(root->getParent() == nullptr) {
        anker = new_root;
    }
    else if(root == root->getParent()->getLeft()) {
        root->getParent()->setLeft(new_root);
    }
    else {
        root->getParent()->setRight(new_root);
    }
    //complete first step and also append root to left side of new_root
    new_root->setLeft(root);
    root->setParent(new_root);

    return true;
}

bool Tree::rotateTreeRight(TreeNode* root) {
    //error handling
    if(root->getLeft() == nullptr) {
        root->setLeft(root->getRight());
        root->setRight(nullptr);
    }

    TreeNode* new_root = root->getLeft();
    //append right child of new_root to left side of root
    root->setLeft(new_root->getRight());
    //set parent of root
    if(new_root->getRight() != nullptr) {
        new_root->getRight()->setParent(root);
    }
    //set parent of new_root
    new_root->setParent(root->getParent());
    if(root->getParent() == nullptr) {
        anker = new_root;
    }
    else if(root == root->getParent()->getLeft()) {
        root->getParent()->setLeft(new_root);
    }
    else {
        root->getParent()->setRight(new_root);
    }
    //complete first step and also append root to left side of new_root
    new_root->setRight(root);
    root->setParent(new_root);

    return true;
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

//noch mehr levelorder?
void Tree::printAll() {
    //levelorder
    if (anker == nullptr) {
        std::cout << "- Leerer Baum" << std::endl;
        return;
    }

    queue<TreeNode*> q;
    q.push(anker);

    int cLc = 1;
    int nLC = 0;
    int l = 0;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cLc--;

        std::cout << l << ": " << node->getOrderID() << std::endl;
        
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

void Tree::printLevelOrder() {
    //levelorder
    if (anker == nullptr) {
        std::cout << "- Leerer Baum" << std::endl;
        return;
    }

    queue<TreeNode*> q;
    q.push(anker);

    int cLc = 1;
    int nLC = 0;
    int l = 0;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cLc--;

        std::string left = "nil";
        std::string right = "nil";
        if(node->getLeft() != nullptr) { left = to_string(node->getLeft()->getOrderID()); }
        if(node->getRight() != nullptr) { right = to_string(node->getRight()->getOrderID()); }

        std::cout 
            << l << ": ("
            << left << ", "
            << node->getOrderID() << ", "
            << right << "); ";

        
        if (node->getLeft() != nullptr) {
            if(!node->getLeft()->getRed()) {
                q.push(node->getLeft());
                nLC++;
            }
        }
        
        if (node->getRight() != nullptr) {
            if(!node->getRight()->getRed()) {
                q.push(node->getRight());
                nLC++;
            }
        }

        if (cLc == 0) {
            cLc = nLC;
            nLC = 0;
            l++;
            std::cout << std::endl;
        }
    }
}

void Tree::printLevelOrder(int level) {
    //levelorder
    if (anker == nullptr) {
        std::cout << "- Leerer Baum" << std::endl;
        return;
    }

    queue<TreeNode*> q;
    q.push(anker);

    int cLc = 1;
    int nLC = 0;
    int l = 0;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cLc--;

        if(l == level) {
            std::string left = "nil";
            std::string right = "nil";
            if(node->getLeft() != nullptr) { left = to_string(node->getLeft()->getOrderID()); }
            if(node->getRight() != nullptr) { right = to_string(node->getRight()->getOrderID()); }

            std::cout 
                << l << ": ("
                << left << ", "
                << node->getOrderID() << ", "
                << right << "); ";
        }
        
        
        if (node->getLeft() != nullptr) {
            if(!node->getLeft()->getRed()) {
                q.push(node->getLeft());
                nLC++;
            }
        }
        
        if (node->getRight() != nullptr) {
            if(!node->getRight()->getRed()) {
                q.push(node->getRight());
                nLC++;
            }
        }

        if (cLc == 0) {
            cLc = nLC;
            nLC = 0;
            l++;
            std::cout << std::endl;
        }
    }
}

int Tree::validTree() {
    if(proofRBCriterion(anker) != -1) {
        return 1;
    }
    return -1;
}

int Tree::proofRBCriterion(TreeNode* root) {
    if(root == nullptr) {
        return 0;
    }
    int left = 0;
    int right = 0;
    left = proofRBCriterion(root->getLeft());
    if(left == -1) { root = nullptr; }
    right = proofRBCriterion(root->getRight());
    if(left == right) { 
        if(!root->getRed()) { return ++left;}
        return left;
    }
    return -1;
}

void Tree::printPreorder() {
    if(anker == nullptr) {
        std::cout << "- Leerer Baum" << std::endl;
        return;
    }
    printPreorderHelper(anker);
}

void Tree::printPreorderHelper(TreeNode* node) {
    if(node == nullptr) { return; }
    std::cout << node->getOrderID() << std::endl;
    printPreorderHelper(node->getLeft());
    printPreorderHelper(node->getRight());
}