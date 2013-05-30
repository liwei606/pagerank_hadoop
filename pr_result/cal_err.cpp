#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdlib.h>

using namespace std;

const int V = 100;

int v[V];
int t[V];

double error_ten(int n) {
	double found = 0;
	for (int i = n; i < 10 + n; ++i) {
		for (int j = n; j < 10 + n; ++j) {
			if (v[i] == t[j]) ++found;
		}
	}
	return 10.0 -found;
}

int main() {
	freopen("validate.txt", "r", stdin);
	for (int i = 0; i < V; ++i) {
		cin >> v[i];
	}
	fclose(stdin);
	for (char a = '0'; a <= '7'; ++a) {
		string s = " _out.txt";
		s[0] = a;
		freopen(s.c_str(), "r", stdin);
		for (int i = 0; i < V; ++i) {
			cin >> t[i];
		}
		fclose(stdin);
		double count = 0;
		for (int i = 0; i < V/10; ++i) {
			count += error_ten(10.0*i);
		}
		cout << count / double(2*V) << endl;
	}
}
