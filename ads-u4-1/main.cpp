// includes
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// fuer eine bessere Lesbarkeit:
//int INT_MAX = std::numeric_limits<int>::max();

//Aufgabe 1
//Gegeben sei die folgende Zahlenfolge:
std::vector<int> nums = { 19, 85, 27, 22, 83, 95, 73, 28, 53, 20 };

// Optionale Hilfsfunktion zur Ausgabe von Vectoren hier:
void print(std::vector<int> vec)
{
    std::cout << "[";
    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if(i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
//Zeigen Sie das Ablaufprotokoll, wenn Sie die Folge in aufsteigender Reihenfolge mit den folgenden Verfahren sortieren.
//1.Selection Sort
//2.Insertion Sort
//3.BubbleSort
//Geben Sie das Array nach jedem einzelnen Sortierdurchlauf aus.


// SelectionSort
std::vector<int> selection_sort(std::vector<int> vec)
{
    // Ihre Loseung hier
    int min;
    for(int i = 0; i < vec.size(); i++) {
        min = i;
        for(int n = i + 1; n < vec.size(); n++) {
            if(vec[n] < vec[min]) {
                min = n;
            }
        }
        if(min != i) {
            std::swap(vec[min], vec[i]);
        }
        print(vec);
    }
    return vec;
}

// InsertionSort
std::vector<int> insertion_sort(std::vector<int> vec)
{
    // Ihre Loseung hier
    for(int i = 1; i < vec.size(); i++) {
        int key = vec[i];
        int n = i - 1;
        while(n >= 0 && vec[n] > key) {
            vec[n + 1] = vec[n];
            n--;
        }
        vec[n + 1] = key;
        print(vec);
    }
    return vec;
}

// BubbleSort
std::vector<int> bubble_sort(std::vector<int> vec)
{
    // Ihre Loseung hier
    for(int i = 0; i < vec.size() - 1; i++) {
        for(int n = 0; n < vec.size() - i - 1; n++) {
            if(vec[n] > vec[n + 1]) {
                std::swap(vec[n], vec[n + 1]);
            }
        }
        print(vec);
    }
    return vec;
}


//Aufgabe 2
//Zeigen Sie das Ablaufprotokoll analog zur Aufgabe 1 wie ShellSort das Array:

std::vector<int> nums_shell = { 16, 45, 33, 98, 14, 19, 8, 11, 49, 97 };

//sortiert. Verwenden Sie zur Sortierung die folgende Abstandsfolge Hneu = 2Halt + 1.

std::vector<int> shell_sort(std::vector<int> vec)
{
    // Ihre Loesung hier:
    for (int gap = vec.size() / 2; gap > 0; gap /= 2 + 1)
    {
        for (int i = gap; i < vec.size(); i++)
        {
            int temp = vec[i];
            int n = i;
            while(n >= gap && vec[n - gap] > temp) {
                vec[n] = vec[n - gap];
                n -= gap;
            }
            vec[n] = temp;
        }
        print(vec);
    }
    return vec;
}

//Aufgabe 3

//Gegeben sei die folgende Folge :

std::vector<int> nums_adv = { 50, 45, 30, 42, 20, 98, 11, 22, 33, 60 };

//Sortieren Sie die Folge in aufsteigender Reihenfolge mit :
//1.Quick Sort
//2.Merge Sort
//3.Heap Sort
//Geben Sie jeweils das Zwischenergebnis des gesamten Arrays nach jedem Durchlauf aus.
//Geben Sie zu QuickSort und MergeSort jeweils die rekursiven Aufrufe aus und geben Sie beim HeapSort dasjenige Element aus, 
//das bei jedem Schritt durchsickert(perc_down - Element).

int partition(std::vector<int>& vec, int p, int r)
{
    // Ihre Loesung hier:
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

void quick_sort(std::vector<int>& vec, int p, int r)
{
    // Ihre Loesung hier:
    print(vec);
    if (p >= r)
        return;

    int x = partition(vec, p, r);

    quick_sort(vec, p, x - 1);
    quick_sort(vec, x + 1, r);
}

// Startfunktion:
std::vector<int> quick_sort(std::vector<int> vec)
{
    quick_sort(vec, 0, vec.size() - 1);
    return vec;
}

//Merge Sort
void merge(std::vector<int>& vec, std::vector<int>& tmp, int l, int m, int r)
{
    // Ihre Loesung hier:
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (vec[i] <= vec[j]) {
            tmp[k++] = vec[i++];
        } else {
            tmp[k++] = vec[j++];
        }
    }

    while (i <= m) {
        tmp[k++] = vec[i++];
    }

    while (j <= r) {
        tmp[k++] = vec[j++];
    }

    for (int x = l; x <= r; x++) {
        vec[x] = tmp[x];
    }
}

void merge_sort(std::vector<int>& vec, std::vector<int>& tmp, int l, int r)
{
    // Ihre Loesung hier:
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(vec, tmp, l, m);
        merge_sort(vec, tmp, m + 1, r);

        merge(vec, tmp, l, m, r);
        print(vec);
    }
}

// Startfunktion:
std::vector<int> merge_sort(std::vector<int>& vec)
{
    std::vector<int> tmp(vec.size());
    merge_sort(vec, tmp, 0, vec.size() - 1);

    return vec;
}

//HeapSort

//?
inline int left_child_idx(int idx) { return 2 * idx + 1; }

void perc_down(std::vector<int>& vec, int i, int n)
{
    // Ihre Loesung hier:
    int parent = n;
    int left_child = 2 * n + 1;
    int right_child = 2 * n + 2;

    if (left_child < i && vec[left_child] > vec[parent])
        parent = left_child;

    if (right_child < i && vec[right_child] > vec[parent])
        parent = right_child;

    if (parent != n) {
        std::cout << vec[parent] << std::endl;
        std::swap(vec[n], vec[parent]);
        perc_down(vec, i, parent);
    }
}

std::vector<int> heap_sort(std::vector<int> vec)
{
    // Ihre Loesung hier:
    for (int i = vec.size() / 2 - 1; i >= 0; i--)
        perc_down(vec, vec.size(), i);

    for (int i = vec.size() - 1; i >= 0; i--) {
        std::swap(vec[0], vec[i]);
        perc_down(vec, i, 0);
    }

    return vec;
}

int main() {

    //Aufgabe 1
    //Testen Aufgabe1.1 Shell Sort
    std::vector<int> res_selection = selection_sort(nums);
    std::cout << "Result: ";
    print(res_selection);
    
    //Testen Aufgabe1.2 Insertion Sort
    std::vector<int> res_insertion = insertion_sort(nums);
    std::cout << "Result: ";
    print(res_insertion);
    

    //Testen Aufgabe1.3 Bubble Sort
    std::vector<int> res_bubble = bubble_sort(nums);
    std::cout << "Result: ";
    print(res_bubble);

    ////Aufgabe 2
    ////Testen Aufgabe 2 Shell Sort
    std::vector<int> res_shell = shell_sort(nums_shell);
    std::cout << "Result: ";
    print(res_shell);

    ////Aufgabe 3
    ////Testen Aufgabe 3.1 Quick Sort
    std::vector<int> res_quick = quick_sort(nums_adv);
    std::cout << "Result: ";
    print(res_quick);

    ////testen aufgabe 3.2 merge sort
    std::vector<int> res_merge = merge_sort(nums_adv);
    std::cout << "result: ";
    print(res_merge);

    ////Testen Aufgabe 3.3 Heap Sort
    std::vector<int> res_heap = heap_sort(nums_adv);
    std::cout << "Result: ";
    print(res_heap);

    system("pause");

    return 1;
}



