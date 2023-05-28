#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>
//optional
#include <random>

#include"hashtable.h"
#include "sorting.h"

//optional
#include "ConsoleColor.h"

//benchmark functions
void benchmark_insertionsort();
void benchmark_quicksort();
void benchmark_mergesort();
void benchmark_heapsort();
void benchmark_shellsort_2n();
bool check_sorting(int i);


int main(int argc, char** argv) {

	Catch::Session().run();

	std::cout << "\nPress Enter to run measurement" << std::endl;
	std::cin.get();

	if(!check_sorting(100)) { system("pause"); return 0; }
	system("pause");

	HashTable hash_table(1000);
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1000, 1500);
	for(int i = 0; i < 200; i++) {
		hash_table.insert(dist(gen));
	}
	std::cout << "Collisions: " << hash_table.getCollisionCount() << std::endl;
	system("pause");

	//benchmark_insertionsort();

	//benchmark_quicksort();
	//benchmark_mergesort();
	//benchmark_heapsort();
	//benchmark_shellsort_2n();
	
	return 0;
}

bool order(std::vector<int> V) {
	int tmp = V[0];
	for(size_t i = 1; i < V.size(); i++) {
		if(tmp <= V[i]) { continue; }
		else { return false; }
	}
	return true;
}

bool check_sorting(int n = 100) {
	bool c = true;
	vector<int> V;
	//insertionsort
	sorting::randomizeVector(V, n);
	sorting::InsertionSort(V);
	if(!order(V)) {
		std::cout << red << "[-] Insertionsort" << std::endl;
		c = false;
	}
	else {
		std::cout << green << "[+] Insertionsort" << std::endl;
	}

	//quicksort
	sorting::randomizeVector(V, n);
	sorting::QuickSort(V, 0, V.size() - 1);
	if(!order(V)) {
		std::cout << red << "[-] Quicksort" << std::endl;
		c = false;	
	}
	else {
		std::cout << green << "[+] Quicksort" << std::endl;
	}

	//hybridquicksort
	sorting::randomizeVector(V, n);
	sorting::HybridQuickSort(V, 0, V.size() - 1);
	if(!order(V)) {
		std::cout << red << "[-] Hybrid Quicksort" << std::endl;
		c = false;	
	}
	else {
		std::cout << green << "[+] Hybrid Quicksort" << std::endl;
	}

	//mergesort
	sorting::randomizeVector(V, n);
	vector<int> tmp(V.size());
	sorting::MergeSort(V, tmp, 0, V.size() - 1);
	if(!order(V)) {
		std::cout << red << "[-] Mergesort" << std::endl;
		c = false;	
	}
	else {
		std::cout << green << "[+] Mergesort" << std::endl;
	}

	//mergesort
	sorting::randomizeVector(V, n);
	sorting::natMergeSort(V, tmp);
	if(!order(V)) {
		std::cout << red << "[-] Natural Mergesort" << std::endl;
		c = false;	
	}
	else {
		std::cout << green << "[+] Natural Mergesort" << std::endl;
	}

	//heapsort
	sorting::randomizeVector(V, n);
	sorting::HeapSort(V, n);
	if(!order(V)) {
		std::cout << red << "[-] Heapsort" << std::endl;
		c = false;	
	}
	else {
		std::cout << green << "[+] Heapsort" << std::endl;
	}

	//shellsort
	sorting::randomizeVector(V, n);
	sorting::ShellSort_2n(V, n);
	if(!order(V)) {
		std::cout << red << "[-] Shellsort" << white << std::endl;
		c = false;	
	}
	else {
		std::cout << green << "[+] Shellsort" << white << std::endl;
	}
	return c;
}

void benchmark_insertionsort() {

	//file stream
	ofstream insertionsort_measurement;
	insertionsort_measurement.open("insertionsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 100;
	int n_step = 100;
	int n_end = 5000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n<=n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Insertionsort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execute sorting algorithm
		sorting::InsertionSort(V);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		insertionsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	insertionsort_measurement.close();
}

void benchmark_quicksort() {

	//file stream
	ofstream quicksort_measurement;
	quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n<=n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Quicksort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execute sorting algorithm
		sorting::QuickSort(V,0,V.size()-1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	quicksort_measurement.close();
}

void benchmark_mergesort()
{
	//file stream
	ofstream mergesort_measurement;
	mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;
	vector<int> temp_array;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Mergesort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execzute sorting algorithm
		temp_array.resize(V.size());
		sorting::MergeSort(V, temp_array, 0, V.size() - 1);

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		mergesort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	mergesort_measurement.close();


}

void benchmark_heapsort()
{
	//file stream
	ofstream heapsort_measurement;
	heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Heapsort with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execute sorting algorithm
		sorting::HeapSort(V, V.size());

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		heapsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	heapsort_measurement.close();


}

void benchmark_shellsort_2n()
{
	//file stream
	ofstream shellsort_measurement;
	shellsort_measurement.open("shellsort_2n.txt", ios::out | ios::app);

	//benchmark parameters / variables
	double dtime;
	int n_start = 1000;
	int n_step = 1000;
	int n_end = 1000000;

	vector<int> V;

	//actual benchmark loop
	for (int n = n_start; n <= n_end; n += n_step) {

		//"progress bar"
		std::cout << "Running Shellsort_2n with n: " << n << std::endl;

		//generate n random integers
		sorting::randomizeVector(V, n);

		//start measurement
		dtime = omp_get_wtime();

		//execute sorting algorithm
		sorting::ShellSort_2n(V, V.size());

		//stop time
		dtime = omp_get_wtime() - dtime;

		//write to file
		shellsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
	}

	//close file handle
	shellsort_measurement.close();
}