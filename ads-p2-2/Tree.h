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
        ~Tree() { delete anker; }

        void addNode(std::string name, int age, double income, int postCode);
        bool deleteNode(int a);
        bool searchNode(std::string name);
        void printAll();
        void printLevelOrder();

        // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben!
        friend TreeNode* get_anker(Tree& TN);

    private:
        void findMinNodeAndParentInBranch(TreeNode* &node, TreeNode* &parent);
        void printPreorder(TreeNode* node);
        TreeNode* anker;
        int currentNodeChronologicalID = 0;
};
