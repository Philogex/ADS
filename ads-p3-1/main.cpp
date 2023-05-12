/*************************************************
* ADS Praktikum 3
* main.cpp
*
*************************************************/
#pragma GCC diagnostic ignored "-Wunused-variable"
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tree.h"
#include "catch.h"

using namespace std;

void mainscreen_addTreeCSV(Tree*& ref)
{
    char j;
    cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
            "importieren(j / n) ? >";
    cin >> j;
    //added lines bc input buffer is not cleared messing up other functions
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (j == 'j')
    {
        ifstream csvread;
        csvread.open("ExportZielanalyse.csv", ios::in);
        if (!csvread.is_open())
        {
            cout << "Fehler beim Lesen!" << endl;
            return;
        }
        else
        {
            string name, age, postcode, income;

            while (!csvread.eof())
            {
                getline(csvread, name, ';');
                getline(csvread, age, ';');
                getline(csvread, income, ';');
                getline(csvread, postcode, '\n');
                ref->addNode(name, stoi(age), stod(income), stoi(postcode));
            }
            csvread.close();
        }
        cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
    }
}

void mainscreen_addTreeManual(Tree* &ref) {
    std::string name = "";
    int age = 0;
    double income = 0;
    int postCode = 0;

    std::string input = "";

    std::cout << "+ Bitte geben Sie die den Datensatz ein:" << std::endl;
    //name
    while(true) {
        //ist eigentlich useless hier, aber vllt kommen doch fehler vor. sollte aber eig nicht fuer einen string
        std::cout << "Name ?> ";
        std::getline(std::cin, input);
        try {
            name = input;
            break;
        }
        catch (const std::exception& e) {
            std::cout << "- Fehlerhafte Eingabe: " << e.what() << std::endl;
        }
    }

    //age
    while(true) {
        std::cout << "Alter ?> ";
        std::getline(std::cin, input);
        try {
            age = std::stoi(input);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "- Fehlerhafte Eingabe: " << e.what() << std::endl;
        }
    }

    //income
    while(true) {
        std::cout << "Income ?> ";
        std::getline(std::cin, input);
        try {
            income = std::stod(input);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "- Fehlerhafte Eingabe: " << e.what() << std::endl;
        }
    }

    //postCode
    while(true) {
        std::cout << "PLZ ?> ";
        std::getline(std::cin, input);
        try {
            postCode = std::stoi(input);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "- Fehlerhafte Eingabe: " << e.what() << std::endl;
        }
    }

    ref->addNode(name, age, income, postCode);
    std::cout << "+ Ihr Datensatz wurde eingefuegt" << std::endl;
}

void mainscreen_searchName(Tree* &ref) {
    std::cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << std::endl;
    std::string input = "";
    std::cout << "Name ?> ";
    std::getline(std::cin, input);
    ref->searchNode(input);
}

void mainscreen_levelOrder(Tree* &ref) {
    std::cout << "+ Bitte geben Sie das auszugebende Level an" << std::endl;
    std::string input = "";
    std::cout << "Level ?> ";
    std::getline(std::cin, input);
    ref->printLevelOrder(stoi(input));
}

void mainscreen_printMainscreen() {
    std::cout 
        << "=========================================" << std::endl
        << "ADS - ELK - Stack v1.9, by 25th Bam" << std::endl
        << "=========================================" << std::endl
        << "1) Datensatz einfuegen, manuell" << std::endl
        << "2) Datensatz einfuegen, CSV Datei" << std::endl
		<< "3) Suchen" << std::endl
        << "4) Ausgabe in Preorder" << std::endl
        << "5) Ausgabe in Levelorder mit Level" << std::endl
		<< "6) Ausgabe in Levelorder (mit Niveauauswahl)" << std::endl
        << "7) Beenden" << std::endl
        << "?>";
}

int main()
{
    int result = Catch::Session().run();

    // Ihr Code hier:
    Tree* tree = new Tree();
    char input;

    while(true) {
        mainscreen_printMainscreen();
        std::cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!(input >= '0' && input <= '9')) {
            input = 0;
        }
        switch(std::stoi(std::string(1, input))) {
            case 1:
                mainscreen_addTreeManual(tree);
                break;
            case 2:
                mainscreen_addTreeCSV(tree);
                break;
            case 3:
                mainscreen_searchName(tree);
                break;
            case 4:
                tree->printPreorder();
                break;
            case 5:
                tree->printLevelOrder();
                break;
			case 6:
                mainscreen_levelOrder(tree);
                break;
            case 7:
                return 0;
            default:
                std::cout << "- Fehlerhafte Anweisung" << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
