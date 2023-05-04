/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring.h
#pragma once
#include<string>
#include "catch.h"
#include"RingNode.h"

class Ring{
	
	public:
		Ring() {}
		~Ring() { 
			RingNode* cur = anker;
			RingNode* next = nullptr;
			for(int i = 0; i < countNodes; i++) {
				next = cur->getNext();
				delete cur;
				cur = next;
			}
		}
		void addNode(std::string description, std::string data);
		bool search(std::string value);
		void print();
		void printSearch(std::string data);

		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_countNodes(Ring& r);
		
	private:
		int countNodes = 0;
		RingNode* anker = nullptr;
		void printHelper(RingNode* node);
};




/*
#pragma once
#include<string>
#include "catch.h"
#include"RingNode.h"

class Ring{
	
	private:
		// Ihr Code hier:	
		int countNodes = 0;
		RingNode* anker = nullptr;
		//
		////////////////////////////////////
	public:
		// Ihr Code hier:
		Ring() : anker(nullptr){};

		void addNewNode(std::string desc, std::string data);
		bool search(std::string data);
		void print();

		// Hilfsfunktion um den gesuchten Eintrag auszugeben
		void print_search(std::string data);
		//
		////////////////////////////////////
		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_countNodes(Ring& r);
};
*/