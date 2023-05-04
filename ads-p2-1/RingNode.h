/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>
#include <iostream>

class RingNode{
	public:
		RingNode() {}
		RingNode(int age, std::string description, std::string data) : oldAge{age}, description{description}, symbolicData{data} {}

		int getAge() { return oldAge; };
		void setAge(int age) { this->oldAge = age; };
		std::string getDescription() { return description;};
		void setDescription(std::string description) { this->description = description; };
		std::string getData() { return symbolicData; };
		void setData(std::string data) { this->symbolicData = data; };
		RingNode* getNext() { return next; };
		void setNext(RingNode* next) { this->next = next; };

		//hilfsfunktion. wuerde die eig. in die cpp datei packen, aber eine einzelne funktion...
		void printNode() {
			std::cout 	<< "Alter: " << oldAge
						<< ", Beschreibung: " << description
						<< ", Daten: " << symbolicData
						<< std::endl 
						<< "---------------------" 
						<< std::endl 
						<< std::endl;
		}

	private:
		int oldAge = 0;
		std::string description = "";
		std::string symbolicData = "";
		RingNode* next = nullptr;
};