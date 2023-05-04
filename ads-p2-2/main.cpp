/*************************************************
 * ADS Praktikum 2.2
 * main.cpp
 *
 *************************************************/
#pragma GCC diagnostic ignored "-Wunused-variable"
#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;

// Hilfsmethoden fürs Menü hier:

/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV" 
 
Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/
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

void mainscreen_deleteID(Tree* &ref) {
    std::cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << std::endl;
    int ID = 0;
    std::string input = "";
    while(true) {
        std::cout << "OrderID ?> ";
        std::getline(std::cin, input);
        try {
            ID = std::stod(input);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "- Fehlerhafte Eingabe: " << e.what() << std::endl;
        }
    }

    bool result = ref->deleteNode(ID);
    if(result) {
        std::cout << "+ Eintrag wurde geloescht." << std::endl;
    }
    else {
        std::cout << "- Eintrag konnte nicht geloescht werden." << std::endl;
    }
}

void mainscreen_searchName(Tree* &ref) {
    std::cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << std::endl;
    std::string input = "";
    std::cout << "Name ?> ";
    std::getline(std::cin, input);
    ref->searchNode(input);
}

void mainscreen_printMainscreen() {
    std::cout 
        << "=========================================" << std::endl
        << "ADS - ELK - Stack v1.9, by 25th Bam" << std::endl
        << "=========================================" << std::endl
        << "1) Datensatz einfuegen, manuell" << std::endl
        << "2) Datensatz einfuegen, CSV Datei" << std::endl
        << "3) Datensatz loeschen" << std::endl
        << "4) Suchen" << std::endl
        << "5) Datenstruktur anzeigen" << std::endl
        << "6) Level-Order Ausgabe" << std::endl
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
                mainscreen_deleteID(tree);
                break;
            case 4:
                mainscreen_searchName(tree);
                break;
            case 5:
                tree->printAll();
                break;
            case 6:
                tree->printLevelOrder();
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

//Die NodeChronologicalID eignet sich nicht als Positionsangabe. Warum? Wie wuerde sich das auf den Baum auswirken?
//es wuerde einen sehr unbalancierten (worst case) bst erstellen

//Die Erstellung und Verwendung der NodeOrderID ist nicht unproblematisch. Warum?
//weil sie doppelt vorkommen koennen (so ein hinweis steht auch in der pdf?)

//Was wuerde passieren, wenn die NodeOrderID mehrfach vergeben wird?
//(der bst explodiert (ein scherz)) in meinem fall wuerde der datensatz "richtig" eingefuegt werden, jedoch blockiert dieser datensatz den suchalgorithmus, wodurch es zu undefiniertem verhalten kommt. alle funktionen sollten jedoch noch funktionieren

//Welche Interpretation lassen die sortierten Daten spaeter zu? Was koennten Sie aus den Zusammenhaengen schließen?
//gar nichts? der baum richtet sich nur groesstenteils nach dem gehalt, weshalb die person mit dem hoechsten gehalt die am rechteste node ist. aequivalent dazu die niedrigste am weitestens links

//Kennen Sie eine Datenstruktur, die sich fuer eine solche Aufgabe besser eignen wuerde?
//eine map, list, tree und vector sind je nach zweck zu verwenden. 
//in unserem fall wuerde sich eine map oder eine doubly linked list eignen, da wir die informationen in keiner bestimmten reihenfolge evaluieren muessen, und haeufig daten hinzufuegen und loeschen. 
//eine map ermoeglicht sehr schnellen zugriff ueber die orderID, welche jedoch bereits beschriebene probleme aufweist. 
//eine doubly linked list weare daher am besten geeignet, da sie ebenfalls die moeglichkeiten fuer binary search zum schnellen zugriff bietet, falls sie richtig implementiert ist

//Wie kann man die Levelorder Ausgabe ueberpruefen?
//1. neuen bst mit dem output bauen
//2. bst erneut mit levelorder ausgeben und vergleichen