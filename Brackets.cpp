// Given a string of parenthesis, write a function if it is balanced.
#include <cstdio>
#include <string>
#include <stack>

using namespace std;

bool isLeftBracket(char c) {
	if (c == '(' || c == '{' || c == '[') {
		return true;
	} else {
		return false;
	}
} 

bool isRightBracket(char c) {
	if (c == ')' || c == '}' || c == ']') {
		return true;
	} else {
		return false;
	}
}

bool isMatchingPair(char left, char right) {
	if (left == '{' && right == '}') return true;
	if (left == '(' && right == ')') return true;
	if (left == '[' && right == ']') return true;
	return false;
}

void isBalanced(string expr) {
	stack<char> s;
	for (int i = 0; i < expr.length(); i++) {
		if (isLeftBracket(expr[i])) {
			s.push(expr[i]);
		} else if (isRightBracket(expr[i])) {
			if (s.empty()) {
				printf("Not Balanced\n");
				return;
			}
			char c = s.top();
			s.pop();
			if (!isMatchingPair(c, expr[i])) {
				printf("Not Balanced\n");
				return;
			}
		}
	}
	if (s.empty()) {
		printf("Balanced\n");
	} else {
		printf("Not Balanced\n");
	}
}

int main() {
	string expr = "{[]}(";
	isBalanced(expr);
	return 0;
}