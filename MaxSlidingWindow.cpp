// Maximum of all subarrays of size k 
#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

void print_max_k(int a[], int N, int k) {
	deque<int> dq(k);

	for (int i = 0; i < k; i++) {
		while (!dq.empty() && a[i] >= a[dq.back()]) {
			dq.pop_back();
		}
		dq.push_back(i);
	}

	for (int i = k; i < N; i++) {
		printf("%d ", a[dq.front()]);

		while (!dq.empty() && dq.front() <= i - k) {
			dq.pop_front();
		}

		while (!dq.empty() && a[i] >= a[dq.back()]) {
			dq.pop_back();
		}
		dq.push_back(i);
	}

	printf("%d ", a[dq.front()]);
}

int main() {
	int arr[] = {12, 1, 78, 90, 57, 89, 56};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    print_max_k(arr, n, k);
	return 0;
}