/*************************************************
 * ADS Praktikum 2.1
 * Unit-Testdatei
 * Stand: 05.03.2019
 *
 *************************************************
 * Änderungen untersagt!
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include "catch.h"
#include <iostream>
#include <string>

using namespace std;

// Friend-Methode fuer Testroutine
TreeNode* get_anker(Tree& Tr)
{
    return Tr.anker;
}

/***********************************************
 * Testroutine des Baums:
 *  - Einfaches Hinzufuegen und Suchen
 *  - Loeschen in unterscheidlicher Ausprägung
 *  + Loeschen ohne Nachfolger
 *  + Loeschen mit einem Nachfolger
 *  + Loeschen mit zwei Nachfolger
 *  + Loeschen der Wurzel
 *  - Hinzufuegen vieler Nodes als Grossbaum
 */
TEST_CASE("Tree Testing", "[TREE]")
{

    Tree* nTree = new Tree();

    SECTION("Hinzufuegen von Nodes und Suche - simple")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        REQUIRE(nTree->searchNode("Mayer") == true);
        REQUIRE(nTree->searchNode("Mayer7") == true);
        REQUIRE(nTree->searchNode("Mayer6") == true);
        REQUIRE(nTree->searchNode("Mayer5") == true);
        REQUIRE(nTree->searchNode("Mayer4") == true);
        REQUIRE(nTree->searchNode("Mayer3") == true);
        REQUIRE(nTree->searchNode("Mayer2") == true);

        REQUIRE(nTree->searchNode("Mueller") == false);
        REQUIRE(nTree->searchNode("Mayer99") == false);
    }

    SECTION("Loeschen von Nodes - ohne Nachfolger")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        nTree->addNode("Mayer8", 8, 0, 0);
        REQUIRE(nTree->searchNode("Mayer8") == true);

        TreeNode* tnanker = get_anker(*nTree);

        //[error]
        nTree->deleteNode(8);
        REQUIRE(tnanker->getLeft()->getLeft() == nullptr);
    }

    SECTION("Loeschen von Nodes - mit einem Nachfolger")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        nTree->addNode("Mayer8", 8, 0, 0);
        nTree->addNode("Mayer9", 7, 0, 0);

        REQUIRE(nTree->searchNode("Mayer8") == true);
        REQUIRE(nTree->searchNode("Mayer9") == true);

        TreeNode* tnanker = get_anker(*nTree);

        // linke Seite
        nTree->deleteNode(8);
        REQUIRE(tnanker->getLeft()->getLeft() != nullptr);
        REQUIRE(tnanker->getLeft()->getRight() == nullptr);
        //[error]
        REQUIRE(tnanker->getLeft()->getLeft()->getOrderID() == 7);

        nTree->deleteNode(7);
        REQUIRE(tnanker->getLeft()->getLeft() == nullptr);
        REQUIRE(tnanker->getLeft()->getRight() == nullptr);
        REQUIRE(tnanker->getLeft()->getOrderID() == 10);

        REQUIRE(nTree->searchNode("Mayer8") == false);
        REQUIRE(nTree->searchNode("Mayer9") == false);

        // rechte Seite
        nTree->addNode("Mayer8", 8, 0, 0);
        nTree->addNode("Mayer9", 9, 0, 0);
        REQUIRE(nTree->searchNode("Mayer8") == true);
        REQUIRE(nTree->searchNode("Mayer9") == true);

        nTree->deleteNode(8);
        REQUIRE(tnanker->getLeft()->getLeft() != nullptr);
        REQUIRE(tnanker->getLeft()->getLeft()->getOrderID() == 9);

        nTree->deleteNode(9);
        REQUIRE(tnanker->getLeft()->getLeft() == nullptr);
        REQUIRE(tnanker->getLeft()->getOrderID() == 10);

        REQUIRE(nTree->searchNode("Mayer8") == false);
        REQUIRE(nTree->searchNode("Mayer9") == false);
    }

    SECTION("Loeschen von Nodes - mit zwei Nachfolger")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        TreeNode* tnanker = get_anker(*nTree);

        REQUIRE(tnanker->getOrderID() == 20);
        REQUIRE(tnanker->getRight()->getOrderID() == 30);
        REQUIRE(tnanker->getRight()->getLeft()->getOrderID() == 25);
        REQUIRE(tnanker->getRight()->getLeft()->getRight()->getOrderID() ==
                26);
        REQUIRE(tnanker->getRight()->getRight()->getLeft()->getOrderID() ==
                35);

        nTree->deleteNode(30);
        REQUIRE(tnanker->getOrderID() == 20);
        //[error]
        REQUIRE(tnanker->getRight()->getOrderID() == 35);
        REQUIRE(tnanker->getRight()->getRight()->getOrderID() == 40);
        REQUIRE(tnanker->getRight()->getRight()->getLeft() == nullptr);
        REQUIRE(tnanker->getRight()->getRight()->getRight() == nullptr);
        REQUIRE(tnanker->getRight()->getLeft()->getOrderID() == 25);
        REQUIRE(tnanker->getRight()->getLeft()->getRight()->getOrderID() ==
                26);
        REQUIRE(tnanker->getRight()->getLeft()->getLeft() == nullptr);

        nTree->deleteNode(35);
        REQUIRE(tnanker->getOrderID() == 20);
        REQUIRE(tnanker->getRight()->getOrderID() == 40);
        REQUIRE(tnanker->getRight()->getLeft()->getOrderID() == 25);
    }

    SECTION("Loeschen von Nodes - ab Wurzel")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        TreeNode* tnanker = get_anker(*nTree); // Initiale Übergrabe des Ankers

        /*
        Lösche den Baum schrittweise durch entfernen der Wurzel
        */
        REQUIRE(tnanker->getOrderID() == 20);
        nTree->deleteNode(20);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        //[error]
        REQUIRE(tnanker->getOrderID() == 25);
        REQUIRE(tnanker->getRight()->getOrderID() == 30);
        REQUIRE(tnanker->getRight()->getLeft()->getOrderID() == 26);
        REQUIRE(tnanker->getRight()->getRight()->getOrderID() == 40);

        nTree->deleteNode(25);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->getOrderID() == 26);
        REQUIRE(tnanker->getRight()->getOrderID() == 30);
        REQUIRE(tnanker->getRight()->getLeft() == nullptr);
        REQUIRE(tnanker->getRight()->getRight()->getOrderID() == 40);

        nTree->deleteNode(26);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->getOrderID() == 30);
        //[error]
        REQUIRE(tnanker->getRight()->getOrderID() == 40);
        REQUIRE(tnanker->getRight()->getLeft()->getOrderID() == 35);
        REQUIRE(tnanker->getRight()->getRight() == nullptr);

        nTree->deleteNode(30);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->getOrderID() == 35);
        REQUIRE(tnanker->getRight()->getOrderID() == 40);
        REQUIRE(tnanker->getRight()->getLeft() == nullptr);
        REQUIRE(tnanker->getRight()->getRight() == nullptr);

        nTree->deleteNode(35);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->getOrderID() == 40);
        REQUIRE(tnanker->getRight() == nullptr);
        REQUIRE(tnanker->getLeft()->getOrderID() == 10);

        nTree->deleteNode(40);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->getOrderID() == 10);
        REQUIRE(tnanker->getRight() == nullptr);
        REQUIRE(tnanker->getLeft() == nullptr);

        nTree->deleteNode(10);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker == nullptr);
    }

    SECTION("Hinzufuegen von Nodes - Erzeuge Grossbaum")
    {

        for (int i = 0; i < 124; i++)
        {
            string info = "Name-" + to_string(i);

            // Random Income und PostCode
            double r   = rand() + 1;
            int    PostCode = rand() + 1;
            nTree->addNode(info, 0, r, PostCode);
        }
        nTree->printAll();
        nTree->printLevelOrder();
        std::cout << "========================================" << endl;
        std::cout << "Testausgabe des Grossbaums abgeschlossen" << endl;
    }
}

/***********************************************
 * Testroutine des Knotens:
 *  - Einfaches pruefen der Getter und Setter in Ausführung
 */
TEST_CASE("TreeNode Testing", "[TREENODE]")
{

    Tree* smallTree = new Tree();
    smallTree->addNode("Herzog", 20, 0, 0);
    TreeNode* ref = get_anker(*smallTree);

    SECTION("Getter von TreeNode - simple")
    {

        REQUIRE(ref->getName() == "Herzog");
        REQUIRE(ref->getAge() == 20);
        REQUIRE(ref->getIncome() == 0);
        REQUIRE(ref->getLeft() == nullptr);
        REQUIRE(ref->getRight() == nullptr);
        REQUIRE(ref->getChronoID() == 0);
        REQUIRE(ref->getOrderID() == 20);
        REQUIRE(ref->getPostCode() == 0);
    }

    SECTION("Setter von TreeNode - simple")
    {

        ref->setAge(22);
        REQUIRE(ref->getAge() == 22);

        ref->setIncome(1000);
        REQUIRE(ref->getIncome() == 1000);

        ref->setLeft(nullptr);
        REQUIRE(ref->getLeft() == nullptr);

        ref->setRight(nullptr);
        REQUIRE(ref->getRight() == nullptr);

        ref->setName("Kaiser");
        REQUIRE(ref->getName() == "Kaiser");

        ref->setPostCode(1000);
        REQUIRE(ref->getPostCode() == 1000);
    }
    delete smallTree;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// http://www.hashemall.com/
// Zeile 1-291 hat den SHA 256 Hashwert:
// F87C64B1D8F66C7C18FB2EF4B3696AD49A939784186E7E3824749CFA707C1620
