// Smallest subarray with sum greater than a given value
// Given an array of integers and a number x, find the smallest subarray 
// with sum greater than the given value.

// Examples:
// arr[] = {1, 4, 45, 6, 0, 19}
//    x  =  51
// Output: 3
// Minimum length subarray is {4, 45, 6}

// arr[] = {1, 10, 5, 2, 7}
//    x  = 9
// Output: 1
// Minimum length subarray is {10}

// arr[] = {1, 11, 100, 1, 0, 200, 3, 2, 1, 250}
//     x = 280
// Output: 4
// Minimum length subarray is {100, 1, 0, 200}

#include <iostream>
#include <cstdio>

using namespace std;

int smallest_sub_with_sum(int a[], int N, int x) {
	int min_len = N + 1;
	int start = 0, end = 0, curr_sum = 0;

	while (end < N) {
		while (curr_sum <= x && end < N) {
			curr_sum += a[end++];
		}

		while (curr_sum > x && start < N) {
			 if (end - start < min_len) {
			 	 min_len = end - start;
			 }
			curr_sum -= a[start++];
		}
	}
	return min_len;
}

int main() {
	int arr1[] = {1, 4, 45, 6, 10, 19};
    int x = 51;
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    cout << smallest_sub_with_sum(arr1, n1, x) << endl;
 
    int arr2[] = {1, 10, 5, 2, 7};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    x  = 9;
    cout << smallest_sub_with_sum(arr2, n2, x) << endl;
 
    int arr3[] = {1, 11, 100, 1, 0, 200, 3, 2, 1, 250};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    x  = 280;
    cout << smallest_sub_with_sum(arr3, n3, x);
	return 0;
}