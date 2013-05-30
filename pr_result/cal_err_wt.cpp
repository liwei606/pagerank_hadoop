#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdlib.h>

using namespace std;

const int V = 100;

int v[V];
int t[V];
double e[V/10];
double wt[V/10];

void init_wt() {
	int sum = 0;
	for (int i = 1; i < 10; ++i) {
		sum += i * i;
	}
	for (int i = 1; i < V/10; ++i) {
		wt[i] = double((V/10 - i)*(V/10 - i)) / double(sum);
		cout << wt[i] << endl;
	}
}

double error_bound(int n, int bound) {
	double found = 0;
	for (int i = n; i < bound + n; ++i) {
		for (int j = n; j < bound + n; ++j) {
			if (v[i] == t[j]) ++found;
		}
	}
	return double(bound) -found;
}


int main() {
	init_wt();
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
		fclose(stdin);;;
		double error = 0;
		for (int i = 1; i < V/20; ++i) {
			e[i] = error_bound(0, 10*i) / double(10*i);
			// cout << "e_" << i << " : " << e[i] << endl;	
			error += e[i]*wt[i];
		}
		
		cout << error << endl;
	}
}
