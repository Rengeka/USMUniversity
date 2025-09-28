#include <iostream>
#include <ctime>

using namespace std;

void Swap(int* i, int* j)
{
	int t = *i;
	*i = *j;
	*j = t;
}

double BubbleSort(int** ar, int size)
{
	clock_t c;
	c = clock();

	for (int i = 0; i < size - 2; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (*ar[j] > *ar[j + 1])
			{
				Swap(ar[j], ar[j + 1]);
			}
		}
	}

	return (float)(clock() - c) / 1000;
}

double InsertionSort(int** ar, int size)
{
	clock_t c;
	c = clock();

	int i, key, j;
	for (i = 1; i < size; i++) {
		key = *ar[i];
		j = i - 1;

		while (j >= 0 && *ar[j] > key) {
			*ar[j + 1] = *ar[j];
			j = j - 1;
		}
		*ar[j + 1] = key;
	}

	return (float)(clock() - c) / 1000;
}

int binarySearch(int** ar, int item,
	int low, int high)
{
	if (high <= low)
		return (item > *ar[low]) ?
		(low + 1) : low;

	int mid = (low + high) / 2;

	if (item == *ar[mid])
		return mid + 1;

	if (item > *ar[mid])
		return binarySearch(ar, item,
			mid + 1, high);
	return binarySearch(ar, item, low,
		mid - 1);
}

double InsertionBinarySort(int** ar, int size)
{
	clock_t c;
	c = clock();

	int i, loc, j, k, selected;

	for (i = 1; i < size; ++i)
	{
		j = i - 1;
		selected = *ar[i];

		loc = binarySearch(ar, selected, 0, j);

		while (j >= loc)
		{
			*ar[j + 1] = *ar[j];
			j--;
		}
		*ar[j + 1] = selected;
	}

	return (float)(clock() - c) / 1000;
}

double SelectionSort(int** ar, int size)
{
	clock_t c;
	c = clock();

	/*int* min;
	for (int j = 0; j < size - 1; j++)
	{
		min = ar[j];
		int t;

		for (int i = 0 + j; i < size; i++)
		{
			if (*min > *ar[i])
			{
				min = ar[i];
			}
		}
		Swap(ar[j], min);
	}*/

	int* min;
	for (int j = size - 1; j > 0; j--)
	{
		min = ar[j];

		for (int i = 0; i <= j; i++)
		{
			if (*min < *ar[i])
			{
				min = ar[i];
			}
		}
		Swap(ar[j], min);
	}

	return (float)(clock() - c) / 1000;
}

void PrintArray(int** ar, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << *ar[i] << std::endl;
	}
	std::cout << "" << std::endl;
}

void RandomizeArray(int** ar, int size)
{
	for (int i = 0; i < size; i++)
	{
		*ar[i] = rand() % 100000;
	}
}

int partition(int** arr, int start, int end)
{

	int pivot = *arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (*arr[i] <= pivot)
			count++;
	}

	int pivotIndex = start + count;
	swap(*arr[pivotIndex], *arr[start]);

	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (*arr[i] <= pivot) {
			i++;
		}

		while (*arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(*arr[i++], *arr[j--]);
		}
	}

	return pivotIndex;
}

void QuickSort(int** arr, int start, int end)
{
	if (start >= end)
		return;

	int p = partition(arr, start, end);

	QuickSort(arr, start, p - 1);


	QuickSort(arr, p + 1, end);
}

double StartQuickSort(int** ar, int size)
{
	clock_t c;
	c = clock();

	QuickSort(ar, 0, size - 1);

	return (float)(clock() - c) / 1000;
}

void heapify(int** arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && *arr[l] > *arr[largest])
		largest = l;

	if (r < n && *arr[r] > *arr[largest])
		largest = r;

	if (largest != i)
	{
		Swap(arr[i], arr[largest]);

		heapify(arr, n, largest);
	}
}

double HeapSort(int** arr, int n)
{
	clock_t c;
	c = clock();

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}

	return (float)(clock() - c) / 1000;
}

/*void merge(int** arr, int** left, int leftSize, int** right, int rightSize)
{
	int i = 0, j = 0, k = 0;

	while (i < leftSize && j < rightSize) {
		if (*left[i] <= *right[j]) {
			*arr[k++] = *left[i++];
		}
		else {
			*arr[k++] = *right[j++];
		}
	}

	while (i < leftSize) 
	{
		*arr[k++] = *left[i++];
	}

	while (j < rightSize) 
	{
		*arr[k++] = *right[j++];
	}
}

void MergeSort(int** arr, int left, int right)
{

	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;

	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);

	int** leftArr = (int**)calloc(mid - left + 1, sizeof(int*));
	for (int i = 0; i < mid - left + 1; i++)
	{
		leftArr[i] = (int*)malloc(sizeof(int));
	}

	int** rightArr = (int**)calloc(right - mid, sizeof(int*));
	for (int i = 0; i < right - mid; i++)
	{
		rightArr[i] = (int*)malloc(sizeof(int));
	}

	for (int i = 0; i <= mid - left; i++) 
	{
		*leftArr[i] = *arr[left + i];
	}

	for (int i = 0; i < right - mid; i++) 
	{
		*rightArr[i] = *arr[mid + 1 + i];
	}
	merge(arr, leftArr, mid - left + 1, rightArr, right - mid);

}*/

/*void merge(int** arr, int low, int mid, int high)
{
	int n1 = mid - low + 1;
	int n2 = high - mid;

	int** left = (int**)calloc(n1, sizeof(int*));
	for (int i = 0; i < n1; i++)
	{
		left[i] = (int*)malloc(sizeof(int));
	}

	int** right = (int**)calloc(n2, sizeof(int*));
	for (int i = 0; i < n2; i++)
	{
		right[i] = (int*)malloc(sizeof(int));
	}

	for (int i = 0; i < n1; ++i) {
		*left[i] = *arr[low + i];
	}

	for (int i = 0; i < n2; ++i) {
		*right[i] = *arr[mid + 1 + i];
	}

	int i = 0, j = 0, k = low;

	while (i < n1 && j < n2) {
		if (left[i] <= right[j]) {
			*arr[k++] = *left[i++];
		}
		else {
			*arr[k++] = *right[j++];
		}
	}

	while (i < n1) 
	{
		*arr[k++] = *left[i++];
	}
	while (j < n2) 
	{
		*arr[k++] = *right[j++];
	}
}

void mergesort(int** arr, int low, int high) {
	if (low < high) {
		int mid = low + (high - low) / 2;
		mergesort(arr, low, mid);
		mergesort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}*/


int main()
{
	srand(NULL);
	int j;

	std::cout << "1 - Enter array" << std::endl << "2 - Random array" << std::endl;
	std::cin >> j;

	int n;
	std::cout << "Enter ammount of elements" << std::endl;
	std::cin >> n;

	int** ar = (int**)calloc(n, sizeof(int*));


	switch (j)
	{
	case 1:
	{
		for (int i = 0; i < n; i++) {
			ar[i] = (int*)malloc(sizeof(int));
			std::cout << "Enter " << i << std::endl;
			std::cin >> *ar[i];
		}
	}
	case 2:
	{
		for (int i = 0; i < n; i++)
		{
			ar[i] = (int*)malloc(sizeof(int));
		}
		RandomizeArray(ar, n);
	}
	}

	std::cout << std::endl << "Choose sort type" << std::endl;
	int l;

	std::cout << "1 - Bubble sort" << std::endl
		<< "2 - Selection sort" << std::endl << "3 - Insertion sort"
		<< std::endl << "4 - Insertion binary search sort"
		<< std::endl << "5 - Quick sort"
		<< std::endl << "6 - Heap sort"
		<< std::endl << "7 - Merge sort" << std::endl;
	std::cin >> l;
	std::cout << std::endl;

	double time;

	//PrintArray(ar, n);

	switch (l)
	{
	case 1:
	{
		time = BubbleSort(ar, n);
		break;
	}
	case 2:
	{
		time = SelectionSort(ar, n);
		break;
	}
	case 3:
	{
		time = InsertionSort(ar, n);
		break;
	}
	case 4:
	{
		time = InsertionBinarySort(ar, n);
		break;
	}
	case 5:
	{
		time = StartQuickSort(ar, n);
		break;
	}
	case 6:
	{
		time = HeapSort(ar, n);
		break;
	}
	/*case 7:
	{
		clock_t c;
		c = clock();
		mergesort(ar, 0, n - 1);
		time = (float)(clock() - c) / 1000;
		break;
	}
	case 8:
	{
		//time = BubbleBinarySort(ar, n);
		break;
	}*/
deffault:
	{
		//PrintArray(ar, n);
		break;
	}

	}

	//PrintArray(ar, n);
	std::cout << "Time = " << time << " sec" << std::endl;
}



