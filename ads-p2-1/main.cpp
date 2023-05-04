/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.h"

using namespace std;

void print_menu()
{
    cout << "====================================" << endl
        << " SuperBackUp-Organizer over 9000, by. Son Goku" << endl
        << "====================================" << endl
        << "1) Backup anlegen" << endl
        << "2) Backup suchen" << endl
        << "3) Alle Backups ausgeben" << endl
        << "?> ";
}

int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:

    int input;
    Ring backup;

    for (int i = 0; i < 10; i++)
        {
            string info = "Info" + to_string(i);
            string data = "Data" + to_string(i);
            backup.addNode(info, data);
        }


    do
    {    
        print_menu();
        std::cin >> input;
        cin.clear();  

        if(input == 1)
        {
            std::string desc, data;
            std::cout << "+Neuen Datensastz anlegen" << std::endl
                        << "Beschreibung ?> ";

            cin.ignore();
            getline(std::cin, desc);
            std::cout << "Daten ?> ";
            getline(std::cin, data);
            backup.addNode(desc, data);
            std::cout << "+Ihr Datensatz wurde hinzugefuegt." << std::endl;  
        }
        else if(input == 2)
        {
            std::string dataSearch;
            std::cout << "+Nach welchen Daten soll gesucht werden?" << std::endl
                        << "?> ";

            cin.ignore();
            getline(std::cin,dataSearch);

            if(backup.search(dataSearch)) 
            {
                backup.printSearch(dataSearch);
            }
            else
            {
                std::cout << "+ Datensatz konnte nicht gefunden werden." << std::endl;
            }

        }
        else if(input == 3)
        {
            backup.print(); 
        }
        else if(input < 1 || input > 4)     // Input Error
        {
            std::cout << "Ungueltige Eingabe! Wert muss zwischen 1 und 4 liegen" << std::endl;
        }

        std::cout << std::endl;
    } while(input != 4);


	system("Pause");
	return result;
}