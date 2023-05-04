/*************************************************
 * ADS Praktikum 1.1
 * Unit-Testdatei
 * Änderungen fürs Praktikum untersagt!
 *************************************************/
#include "List.h"
#include "Node.h"
#include "catch.hpp"
#include <string>

using namespace std;

// Friend-Methode fuer Testroutine
Node* get_anker(List& l)
{
    return l.m_head_tail;
}

int get_AnzahlNodes(List& l)
{
    return l.m_list_size;
}

TEST_CASE("List Testing", "[List]")
{
    List test_list;
    List second;
    SECTION("Hinzufuegen und Suche von Nodes - simple")
    {
        
        test_list.insertFront(5);
        test_list.insertFront(7);

        test_list.insertBack(9);
        test_list.insertBack(4);

        REQUIRE(test_list.size() == 4);

        REQUIRE(test_list.search(7) == true);
        REQUIRE(test_list.search(8) == false);
        REQUIRE(test_list.search(3) == false);
        REQUIRE(test_list.search(9) == true);

        int value;
        test_list.getBack(value);
        REQUIRE(value == 4);
        test_list.getFront(value);
        REQUIRE(value == 7);
    }

    SECTION("Hinzufuegen von Nodes aus zweiter Liste am Ende")
    {
        test_list.insertFront(5);
        test_list.insertFront(7);

        test_list.insertBack(9);
        test_list.insertBack(4);

        second.insertFront(5);
        second.insertFront(5);

        second.insertBack(5);
        second.insertBack(5);

        test_list.insertBack(second);

        REQUIRE(test_list.size() == 8);
        REQUIRE(test_list.test() == true);
    }

    SECTION("Hinzufuegen von Nodes aus zweiter Liste am Anfang")
    {
        test_list.insertFront(5);
        test_list.insertFront(7);

        test_list.insertBack(9);

        second.insertFront(5);
        second.insertFront(5);
        second.insertBack(5);

        test_list.insertFront(second);

        REQUIRE(test_list.size() == 6);

        Node* tmp = get_anker(test_list);
        tmp = tmp->next;
        int value = tmp->value;
        REQUIRE(value == 5);

        tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 5);

        tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 5);

        tmp       = tmp->next;
        value   = tmp->value;
        REQUIRE(value == 7);

        tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 5);

        tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 9);

        for (int i = 0; i < 6; i++)
            tmp = tmp->prev;

        // m_head_tail wieder erreicht
        value = tmp->value;
        REQUIRE(value == 0);
    }
    
    SECTION("Hinzufuegen und Löschen von Nodes - simpel")
    {
        test_list.insertFront(5);
        test_list.insertFront(7);
        test_list.insertFront(9);
        test_list.insertFront(4);

        test_list.insertBack(3);
        test_list.insertBack(2);
        test_list.insertBack(4);
        test_list.insertBack(1);

        REQUIRE(test_list.size() == 8);

        REQUIRE(test_list.del(8) == false);
        REQUIRE(test_list.del(4) == true);
        REQUIRE(test_list.del(1) == true);
        REQUIRE(test_list.del(5) == true);

        REQUIRE(test_list.size() == 5);

        int value;
        test_list.getBack(value);
        REQUIRE(value == 4);
        test_list.getFront(value);
        REQUIRE(value == 9);
    }


    SECTION("Vertauschen von zwei Elementen und testen der Zeiger")
    {
        test_list.insertFront(5);
        test_list.insertFront(7);
        test_list.insertFront(9);
        test_list.insertFront(4);

        test_list.insertBack(3);
        test_list.insertBack(2);
        test_list.insertBack(4);
        test_list.insertBack(1);

        REQUIRE(test_list.size() == 8);

        //////////////////////////////////////////////////////////////
        // Fall 1: Zwei Knoten aus der Mitte, nicht nebeneinander	//
        //////////////////////////////////////////////////////////////
        REQUIRE(test_list.swap(7, 2) == true);
        Node* tmp = get_anker(test_list);
        // prüfe ob 2 an neuem Platz
        for (int i = 0; i < 3; i++)
            tmp = tmp->next;
        int value = tmp->value;
        REQUIRE(value == 2);
        // Prüfe ob 7 an neuem Platz
        for (int i = 0; i < 3; i++)
            tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 7);
        tmp = tmp->next;
        // Prüfe ob Anker wieder erreichbar
        for (int i = 0; i < 7; i++)
            tmp = tmp->prev;
        value = tmp->value;
        REQUIRE(value == 0);
        //////////////////////////////////////////////////////////////////////////
        // Fall 2: Erster Knoten mit einem aus der Mitte, nicht nebeneinander
        // //
        //////////////////////////////////////////////////////////////////////////
        REQUIRE(test_list.swap(4, 5) == true);
        tmp = tmp->next;
        // Prüfe ob neuer erster richtig
        value = tmp->value;
        REQUIRE(value == 5);
        // Prüfe ob 4 an neuem Platz
        for (int i = 0; i < 3; i++)
            tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 4);
        tmp = tmp->next;
        // Prüfe ob Anker wieder erreichbar
        for (int i = 0; i < 5; i++)
            tmp = tmp->prev;
        value = tmp->value;
        REQUIRE(value == 0);
        //////////////////////////////////////////////////////////////////////////
        // Fall 3: Letzter Knoten mit einem aus der Mitte, nicht nebeneinander
        // //
        //////////////////////////////////////////////////////////////////////////
        REQUIRE(test_list.swap(1, 3) == true);
        for (int i = 0; i < 5; i++)
            tmp = tmp->next;
        // Prüfe ob 1 an neuem Platz
        value = tmp->value;
        REQUIRE(value == 1);
        // Prüfe ob neuer letzter richtig
        for (int i = 0; i < 3; i++)
            tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 3);
        tmp = tmp->next;
        // Prüfe ob Anker wieder erreichbar
        for (int i = 0; i < 9; i++)
            tmp = tmp->prev;
        value = tmp->value;
        REQUIRE(value == 0);
        //////////////////////////////////////////////////////
        // Fall 4: Zwei Knoten aus der Mitte, nebeneinander	//
        //////////////////////////////////////////////////////
        REQUIRE(test_list.swap(4, 2) == true);
        for (int i = 0; i < 3; i++)
            tmp = tmp->next;
        // Prüfe ob 4 an neuem Platz
        value = tmp->value;
        REQUIRE(value == 4);
        // Prüfe ob 1 an neuem Platz
        tmp = tmp->next;
        value = tmp->value;
        REQUIRE(value == 2);
        tmp = tmp->next;
        // Prüfe ob Anker wieder erreichbar
        for (int i = 0; i < 5; i++)
            tmp = tmp->prev;
        value = tmp->value;
        REQUIRE(value == 0);
    }
}
