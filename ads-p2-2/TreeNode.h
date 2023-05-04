/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode
{
    public:
        TreeNode(int p1, int p2, std::string p3, int p4, double p5, int p6) : nodeOrderID{p1}, nodeChronologicalID{p2}, name{p3}, age{p4}, income{p5}, postCode{p6} {}
        ~TreeNode() { delete left; delete right; }

        //getters & setters
        int getOrderID() { return nodeOrderID; }
        void setOrderID(int param) { nodeOrderID = param; }
        int getChronoID() { return nodeChronologicalID; }
        void setChronoID(int param) { nodeChronologicalID = param; }
        std::string getName() { return name; }
        void setName(std::string param) { name = param; }
        int getAge() { return age; }
        void setAge(int param) { age = param; }
        double getIncome() { return income; }
        void setIncome(double param) { income = param; } 
        int getPostCode() { return postCode; }
        void setPostCode(int param) { postCode = param; }
        TreeNode* getLeft() { return left; }
        void setLeft(TreeNode* param) { left = param; }
        TreeNode* getRight() { return right; }
        void setRight(TreeNode* param) {right = param; }

        void print();

    private:
        int nodeOrderID;
        int nodeChronologicalID;
        std::string name;
        int age;
        double income;
        int postCode;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
};
