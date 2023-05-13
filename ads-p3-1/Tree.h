/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>

using namespace std;

class Tree
{
    public:
        Tree() : anker{nullptr} {}
        ~Tree() { delete anker; anker = nullptr; }

        void addNode(std::string name, int age, double income, int postCode);
        bool searchNode(std::string name);
        void printAll();
        bool deleteNode(int a);
        void printPreorder();
        void printLevelOrder();
        void printLevelOrder(int param);
        int validTree();

        // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben!
        friend TreeNode* get_anker(Tree& TN);

    private:
        int proofRBCriterion(TreeNode* param);
        void balance(TreeNode* param);
        bool rotateTreeRight(TreeNode* param);
        bool rotateTreeLeft(TreeNode* param);
        bool split4Node(TreeNode* param);
        void printPreorderHelper(TreeNode* node);

        TreeNode* anker = nullptr;
        int currentNodeChronologicalID = 0;
};
