// Find the number of occurrences of words in a paragraph.

#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <iterator> 

using namespace std;



int main() {
	string input = "test is a test It is now";
	map<string, int> count_map;

	bool in_word = false;
	string word;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			in_word = false;
			if (word.length() > 0) {
				count_map[word]++;
			}
			continue;
		}
		if (!in_word) {
			in_word = true;
			word = "";
		}
		word += input[i];
	}

	for (map<string, int>:: iterator it = count_map.begin(); it != count_map.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	
	return 0;
}