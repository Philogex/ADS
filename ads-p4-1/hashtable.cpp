#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size, double threshold) 
{
	this->size = size;
	this->elements = 0;
	this->collisionCount = 0;
	this->threshold_rehashing = threshold;
	this->hashTable = new std::vector<int>(size, -1);
}

HashTable::~HashTable()
{
	delete this->hashTable;
}

// Berechnung des Hashwertes mit quadr. Sondieren
int HashTable::hashValue(int item) 
{
	// Quadratisches Sondieren
    int i = 1, v;
	int x = item % this->size;
	v = x;
    while ((*this->hashTable)[v] != -1)
    {
        v = (x + i * i) % this->size;
        i++;
    }
	if(v != x) this->collisionCount++;

    return v;
}
	

void HashTable::rehashing()
{
	//create new vector
	int new_size = get_next_prime(this->size * 2);
	vector<int>* new_hashTable = new std::vector<int>(new_size, -1);

	this->collisionCount = 0;
	
	//rehash elements and insert into new vector
	int item, n, x, v;
	
	for(int i = 0; i < this->size; i++) {
		item = (*this->hashTable)[i];
		if(item != -1) {
			n = 1;
			x = item % new_size;
			v = x;
			while ((*new_hashTable)[v] != -1)
			{
				v = (x + n * n) % new_size;
				n++;
			}
			if(v != x) this->collisionCount++;
			(*new_hashTable)[v] = item;
		}
	}

	//reset values and assign new vector
	delete this->hashTable;
	this->hashTable = new_hashTable;
	this->size = new_size;
}

int HashTable::insert(int item) 
{
	if((this->elements + 1.) / this->size >= this->threshold_rehashing) {
		this->rehashing();
	}

	(*this->hashTable)[hashValue(item)] = item;

	this->elements++;

	return 1;
}


int HashTable::at(int i) 
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount() 
{
	return this->collisionCount;
}

int HashTable::getSize() 
{
	return this->size;
}

int HashTable::getElements() 
{
	return this->elements;
}

void HashTable::print() {
	for(int i = 0; i < this->size; i++) {
		std::cout << (*this->hashTable)[i] << ", ";
	}
	std::cout << std::endl;
}

int get_next_prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}

