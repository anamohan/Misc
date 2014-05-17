// Given an array, find the max sum over a sub array.

#include <cstdio>

using namespace std;


int max_sum(int a[], int N) {
	int max_sum = 0, curr_sum = 0;
	for (int i = 0; i < N; i++) {
		curr_sum += a[i];
		if (curr_sum < 0) {
			curr_sum = 0;
		}
		if (curr_sum > max_sum) {
				max_sum = curr_sum;
		}
	}
	return max_sum;
}

int main() {
	int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
   	int n = sizeof(a)/sizeof(a[0]);
   	printf("%d\n", max_sum(a, n));
	return 0;
}