#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>
#include <math.h>

using namespace std;

class HashTable {
public:
	HashTable(int size, double threshold=0.6);	// Konstruktor
	~HashTable();								// Destruktor
	int insert(int item);						// fuegt ein Element der Hashtabelle hinzu
	int at(int i);								// Liefert das i-te Element der Hashtabelle zurueck
	int getCollisionCount();    				// Liefert die Anzahl der Kollisionen zurueck
	int getSize();								// Liefert die Groesse der Hashtabelle zurueck
	int getElements();							// Liefert die Anzahl der Elemente der Hashtabelle zurueck
	void print();								// Ausgabe der Hashtable ind er Form:
												// [0] -> 1
												//  .....
private:	
	int size;									// Groesse der HashTable
	int elements;								// Anz. d. Elemente in HashTable
	int collisionCount;							// Anz. d. Kollisionen beim Einfuegen
	double threshold_rehashing;					// Schwellwert fuers rehashing (size/elements)
	vector<int>* hashTable;						// HashTable
	int hashValue(int item);					// calculate hash value
	void rehashing();							// rehashing
};

// Helper Funktion:
int get_next_prime(int a);						// Gibt zu einer natuerlichen Zahl a, die naechstgroessere Primzahl zurueck

#endif 