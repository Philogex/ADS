#include "sorting.h"
#include <cmath>



namespace sorting {

	//************
	// QuickSort *
	//************   

	void InsertionSort(std::vector<int> &vec, int left, int right)
	{
		if(right == 0) { right = static_cast<int>(vec.size()); }
		for(int i = left + 1; i < right; i++) {
			int key = vec[i];
			int n = i - 1;
			while(n >= 0 && vec[n] > key) {
				vec[n + 1] = vec[n];
				n--;
			}
			vec[n + 1] = key;
		}
	}

	int partition(std::vector<int>& vec, int p, int r)
	{
		int x = vec[p];
	
		int c = 0;
		for (int n = p + 1; n <= r; n++) {
			if (vec[n] <= x)
				c++;
		}

		int i = p + c;
		std::swap(vec[i], vec[p]);

		int n = p;
		int j = r;
		while(n < i && j > i) {
			while(vec[n] <= x) {
				n++;
			}
			while(vec[j] > x) {
				j--;
			}
			if(n < i && j > i) {
				std::swap(vec[n++], vec[j--]);
			}
		}

		return i;
	}

	void QuickSort(vector<int>& arr, int left, int right)
	{
		if (left >= right) { return; }

		int x = partition(arr, left, right);

		QuickSort(arr, left, x - 1);
		QuickSort(arr, x + 1, right);
	}

	void HybridQuickSort(vector<int> &arr, int left, int right, int threshold) {
		if (left >= right) { return; }

		if (right - left + 1 <= threshold) {
            InsertionSort(arr, left, right + 1);
        } else {
            int x = partition(arr, left, right);

            HybridQuickSort(arr, left, x - 1, threshold);
            HybridQuickSort(arr, x + 1, right, threshold);
        }
	}


	//************
	// MergeSort *
	//************
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		int leftEnd = pivot - 1;
		int tmpPos = low;
		int n = high - low + 1;

		while (low <= leftEnd && pivot <= high) {
			if (a[low] <= a[pivot]) {
				b[tmpPos] = a[low];
				low++;
			} else {
				b[tmpPos] = a[pivot];
				pivot++;
			}
			tmpPos++;
		}

		while (low <= leftEnd) {
			b[tmpPos++] = a[low++];
		}

		while (pivot <= high) {
			b[tmpPos++] = a[pivot++];
		}

		int i = high - n + 1;

		while(i <= high) {
			a[i] = b[i];
			i++;
		}
	}


	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if (low < high) {
			int m = std::floor((low + high) / 2);

			MergeSort(a, b, low, m);
			MergeSort(a, b, m + 1, high);

			Merge(a, b, low, m + 1, high);
		}
	}

	void natMerge(vector<int> &a, vector<int> &b, int left, int middle, int right) 
	{
		int leftEnd = middle - 1;
		int tmpPos = left;
		int n = right - left + 1;

		while (left <= leftEnd && middle < right) {
			if (a[left] <= a[middle]) {
				b[tmpPos] = a[left];
				left++;
			} else {
				b[tmpPos] = a[middle];
				middle++;
			}
			tmpPos++;
		}

		while (left <= leftEnd) {
			b[tmpPos++] = a[left++];
		}

		while (middle < right) {
			b[tmpPos++] = a[middle++];
		}

		int i = right - n + 1;

		while(i < right) {
			a[i] = b[i];
			i++;
		}
	}

	void natMergeSort(vector<int> &a, vector<int> &b)
	{
		int n = a.size();
		vector<pair<int, int>> runs;

		int left = 0;
		while (left < n) {
			int i = left;

			while (i < n - 1 && a[i] <= a[i + 1])
				i++;

			if (i == n)
				break;

			int right = i;
			while (right < n - 1 && a[right] <= a[right + 1])
				right++;

			runs.push_back(make_pair(left, right));

			left = right + 1;
		}

		while (runs.size() > 1) {
			vector<pair<int, int>> newRuns;
			for (size_t i = 0; i < runs.size() - 1; i += 2) {
				int left = runs[i].first;
				int middle = runs[i].second;
				int right = runs[i + 1].second;

				Merge(a, b, left, middle + 1, right);
				newRuns.push_back(make_pair(left, right));
			}

			if (runs.size() % 2 == 1)
				newRuns.push_back(runs.back());

			runs = newRuns;
		}
	}


	//************
	// Heapsort  *
	//************
	void heapify(vector<int> &a, int n, int i)
	{
		int parent = i;
		int left_child = 2 * i + 1;
		int right_child = 2 * i + 2;

		if (left_child < n && a[left_child] > a[parent])
			parent = left_child;

		if (right_child < n && a[right_child] > a[parent])
			parent = right_child;

		if (parent != i) {
			std::swap(a[i], a[parent]);
			heapify(a, n, parent);
		}
	}


	void HeapSort(vector<int> &a, int n) 
	{
		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(a, n, i);

		for (int i = n - 1; i >= 0; i--) {
			std::swap(a[0], a[i]);
			heapify(a, i, 0);
		}
	}

	//************
	// Shellsort *
	//************
	// Hier soll Hibbard implementiert werden
	void ShellSort_2n(vector<int> &a, int n)
	{
		int gap = 1;
		while (gap < n)
		{
			gap = 2 * gap + 1;
		}
		
		while (gap > 0)
		{
			gap = (gap - 1) / 2;

			for (int i = gap; i < n; i++)
			{
				int temp = a[i];
				int j = i;
				while (j >= gap && a[j - gap] > temp)
				{
					a[j] = a[j - gap];
					j -= gap;
				}
				a[j] = temp;
			}
		}
	}


	void randomizeVector(vector<int> &array, int n) {
		array.resize(n);

		for(unsigned int i=0;i<array.size();i++)
		array[i]=rand() % 1000000;
	}


}





