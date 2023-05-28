#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting {
  
  //****************
  // InsertionSort *
  //****************
  void InsertionSort(std::vector<int> &vec, int left = 0, int right = 0);

  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right);

  //******************
  // HybridQuickSort *
  //******************
  void HybridQuickSort(vector<int> &arr, int left, int right, int threshold = 500);

  //************
  // MergeSort *
  //************
  void Merge(vector<int> &a, vector<int> &b,int low, int pivot, int high);
  void MergeSort(vector<int> &a, vector<int> &b, int low, int high);

  //************************
  // Natuerliche Mergesort *
  //************************
  void natMerge(vector<int>& a, vector<int>& b, int low, int pivot, int high);
  void natMergeSort(vector<int> &a, vector<int> &b);

  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int n);

  //************
  // Shellsort *
  //************
  void ShellSort_2n(vector<int> &a, int n);


  //*******************
  // Helper functions *
  //*******************
  void randomizeVector(vector<int> &array, int n);

}
#endif 
