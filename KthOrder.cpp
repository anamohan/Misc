//Given an array write a program to find kth smallest element in the array
#include <iostream>
#include <cstdio>

using namespace std;

int Partition(int a[], int p, int q) {
	int i = p - 1;
	int j = q;
	while (true) {
		while (a[++i] < a[q]);
		while (a[q] < a[--j]) 
			if (j == p) break;
		if (i >= j) break;
		swap(a[i], a[j]);
	}
	swap(a[i], a[q]);
	return i;
}

int QuickSort(int a[], int p, int q, int k) {
	if (k <= 0) return -1;
	if (q == p) return a[p];
	int partition = Partition(a, p, q);
	int n = partition - p + 1;
	if (n == k) {
		return a[partition];
	} else if (k < partition) {
		return QuickSort(a, p, partition - 1, k);
	} else {
		return QuickSort(a, partition + 1, q, k - n);
	}
}

int main() {
	int arr[] = {12, 1, 78, 90, 57, 89, 56};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 0;
    printf("%d\n", QuickSort(arr, 0, n - 1, k));
    return 0;
}