/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>

// Ihr Code hier:
void TreeNode::print()
{
    std::cout
        << "NodeID: " << nodeChronologicalID
        << ", Name: " << name
        << ", Alter: " << age
        << ", Einkommen: " << income
        << ", PLZ: " << postCode
        << ", PosID: " << nodeOrderID
        << ", Red: " << red
        << std::endl;
}