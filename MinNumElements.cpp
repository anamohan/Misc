// Given an array of integers. 
// Remove minimum number of elements from the array such that the largest 
// and the smallest number does not differ by more than two times.
// In other words if x is the minimum of the remaining elements in the array 
// and y is the maximum than y<=2x. 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

int min_num(int a[], int N) {
	sort(a, a + N);
	int res = INT_MAX, i, j;
	for (i = 0; i < N; i++) {
		for (j = N - 1; j > i; j--) {
			if (a[j] <= (2 * a[i])) {
				break;
			}
		}
		int curr_min = (N - 1 - j) + i;
		if (curr_min < res) {
			res = curr_min;
		}
	}
	return res;
}

int main() {
	int arr1[] = {4,5,3,8,3,7};
	int n1 = sizeof(arr1)/sizeof(arr1[0]);
	printf("%d\n", min_num(arr1, n1));
	return 0;
}


