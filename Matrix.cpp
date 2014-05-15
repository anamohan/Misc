// Create a matrix with alternating rectangles of O and X
// Write a code which inputs two numbers m and n and creates a matrix of size m x n (m rows and n columns) in which every elements is either X or 0. The Xs and 0s must be filled alternatively, the matrix should have outermost rectangle of Xs, then a rectangle of 0s, then a rectangle of Xs, and so on.

// Examples:

// Input: m = 3, n = 3
// Output: Following matrix 
// X X X
// X 0 X
// X X X

// Input: m = 4, n = 5
// Output: Following matrix
// X X X X X
// X 0 0 0 X
// X 0 0 0 X
// X X X X X

// Input:  m = 5, n = 5
// Output: Following matrix
// X X X X X
// X 0 0 0 X
// X 0 X 0 X
// X 0 0 0 X
// X X X X X

// Input:  m = 6, n = 7
// Output: Following matrix
// X X X X X X X
// X 0 0 0 0 0 X
// X 0 X X X 0 X
// X 0 X X X 0 X
// X 0 0 0 0 0 X
// X X X X X X X 

#include <cstdio>

using namespace std;

#define MAXN 50

char a[MAXN][MAXN];

void fill_matrix(int m, int n, int k, char c) {
	if (m <= 0 || n <= 0) return;
	if (m == 1) {
		for (int j = 0; j < n; j++) {
			a[k][k + j] = c;
		}
	}
	if (n == 1) {
		for (int i = 0; i < m; i++) {
			a[k + i][k] = c;
		}
	}

	for (int j = 0; j < n - 1; j++) {
		a[k][k + j] = c;
	}

	for (int i = 0; i < m - 1; i++) {
		a[k + i][k + n - 1] = c;
	}

	for (int j = 0; j < n - 1; j++) {
		a[k + m - 1][k + n - 1 - j] = c; 
	}

	for (int i = 0; i < m - 1; i++) {
		a[k + m - 1 - i][k] = c;
	}
	if (c == 'X') {
		c = 'O';
	} else {
		c = 'X';
	}
	fill_matrix(m - 2, n - 2, k + 1, c);
}

int main() {
	int m = 6, n = 7, k = 0;
	char c = 'X';
	fill_matrix(6, 7, 0, 'X');
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}