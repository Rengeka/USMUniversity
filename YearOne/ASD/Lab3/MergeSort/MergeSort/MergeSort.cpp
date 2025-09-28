#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* left = (int*)calloc(n1, sizeof(int));
    int* right = (int*)calloc(n2, sizeof(int));

    for (int i = 0; i < n1; ++i) {
        left[i] = arr[low + i];
    }
    for (int i = 0; i < n2; ++i) {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1) {
        arr[k++] = left[i++];
    }
    while (j < n2) {
        arr[k++] = right[j++];
    }
}

void mergesort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main()
{

    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int* arr = new int[n];

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }

    cout << "Original array: \n";
   // printArray(arr, n);

   // cout << "\n";

    double t;
    clock_t c;
    c = clock();

    mergesort(arr, 0, n - 1);
    t = (float)(clock() - c) / 1000;

   // printArray(arr, n);
    cout <<  "Time = " << t;
    delete[] arr;

    return 0;

}



