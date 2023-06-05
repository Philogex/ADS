/*************************************************
* ADS Praktikum 4
* Unit-Testdatei
* Stand: 10.05.2021
*
*************************************************
* Änderungen untersagt!
*************************************************/
#include <vector>
#include "catch.h"
#include "sorting.h"
#include "hashtable.h"

std::vector<int> V{98, 44, 30, 22, 64, 63, 11, 23, 8, 18};

TEST_CASE("Quicksort", "[QUICKSORT]") {

  SECTION("sorting 10 elements - simple") {
  
    std::vector<int> a(V);
	sorting::QuickSort(a,0,a.size()-1);
    
    REQUIRE(a.at(0) == 8);
    REQUIRE(a.at(1) == 11);
    REQUIRE(a.at(2) == 18);
    REQUIRE(a.at(3) == 22);
    REQUIRE(a.at(4) == 23);
    REQUIRE(a.at(5) == 30);
    REQUIRE(a.at(6) == 44);
    REQUIRE(a.at(7) == 63);
    REQUIRE(a.at(8) == 64);
    REQUIRE(a.at(9) == 98);
  }
}


TEST_CASE("ShellSort", "[SHELLSORT]") {


  SECTION("sorting 10 elements - simple with 2n") {

    std::vector<int> b(V);
	sorting::ShellSort_2n(b,b.size());

    REQUIRE(b.at(0) == 8);
    REQUIRE(b.at(1) == 11);
    REQUIRE(b.at(2) == 18);
    REQUIRE(b.at(3) == 22);
    REQUIRE(b.at(4) == 23);
    REQUIRE(b.at(5) == 30);
    REQUIRE(b.at(6) == 44);
    REQUIRE(b.at(7) == 63);
    REQUIRE(b.at(8) == 64);
    REQUIRE(b.at(9) == 98);
  }
}

TEST_CASE("HeapSort", "[HEAPSORT]") {

  SECTION("sorting 10 elements - simple") {
    std::vector<int> c(V);
	sorting::HeapSort(c,c.size());

    REQUIRE(c.at(0) == 8);
    REQUIRE(c.at(1) == 11);
    REQUIRE(c.at(2) == 18);
    REQUIRE(c.at(3) == 22);
    REQUIRE(c.at(4) == 23);
    REQUIRE(c.at(5) == 30);
    REQUIRE(c.at(6) == 44);
    REQUIRE(c.at(7) == 63);
    REQUIRE(c.at(8) == 64);
    REQUIRE(c.at(9) == 98);
  }
}

TEST_CASE("MergeSort", "[MERGESORT]") {

  SECTION("sorting 10 elements - simple") {
  
    std::vector<int> d(V);
    std::vector<int> tmp;
    tmp.resize(d.size());

	sorting::MergeSort(d,tmp,0,d.size()-1);

	REQUIRE(d.at(0) == 8);
	REQUIRE(d.at(1) == 11);
	REQUIRE(d.at(2) == 18);
	REQUIRE(d.at(3) == 22);
	REQUIRE(d.at(4) == 23);
	REQUIRE(d.at(5) == 30);
	REQUIRE(d.at(6) == 44);
	REQUIRE(d.at(7) == 63);
	REQUIRE(d.at(8) == 64);
	REQUIRE(d.at(9) == 98);
  }

}


TEST_CASE("NatMergeSort", "[MERGESORT]") {

    SECTION("sorting 10 elements - simple") {

        std::vector<int> d(V);
        std::vector<int> tmp;
        tmp.resize(d.size());

        sorting::natMergeSort(d, tmp);

        REQUIRE(d.at(0) == 8);
        REQUIRE(d.at(1) == 11);
        REQUIRE(d.at(2) == 18);
        REQUIRE(d.at(3) == 22);
        REQUIRE(d.at(4) == 23);
        REQUIRE(d.at(5) == 30);
        REQUIRE(d.at(6) == 44);
        REQUIRE(d.at(7) == 63);
        REQUIRE(d.at(8) == 64);
        REQUIRE(d.at(9) == 98);
    }
}

TEST_CASE("HashTable", "[HASHTABLE]") {

	SECTION("Hashing 10 elements - Size: 20 : Rehashing") {

		HashTable H(20);

		for (unsigned int i = 0; i < V.size(); i++)
		{
			H.insert(V.at(i));
		}
		H.insert(15);
		H.insert(16);
		H.insert(21);
		H.insert(22);

		if (H.getSize() > 0) {
			REQUIRE(H.at(3) == 44);
			REQUIRE(H.at(8) == 8);
			REQUIRE(H.at(11) == 11);
			REQUIRE(H.at(15) == 15);
			REQUIRE(H.at(16) == 98);
			REQUIRE(H.at(17) == 16);
			REQUIRE(H.at(18) == 18);
			REQUIRE(H.at(22) == 22);
			REQUIRE(H.at(23) == 63);
			REQUIRE(H.at(24) == 64);
			REQUIRE(H.at(27) == 23);
			REQUIRE(H.at(30) == 30);
		}
		REQUIRE(H.getSize() == 41);
		REQUIRE(H.getCollisionCount() == 5);
		REQUIRE(H.getElements() == 14);
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++