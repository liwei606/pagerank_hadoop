#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdlib.h>

using namespace std;

const int V = 100;

int v[V];
int t[V];
double error_bound(int n, int bound) {
	double found = 0;
	for (int i = n; i < bound + n; ++i) {
		for (int j = n; j < bound + n; ++j) {
			if (v[i] == t[j]) ++found;
		}
	}
	return double(bound) -found;
}

string fname[7] = {"1_pr_result_10.txt", "2_pr_result_10.txt", "3_pr_result_10.txt", "4_pr_result_10.txt", "5_pr_result_10.txt", "6_pr_result_10.txt", "7_pr_result_10.txt"};

int main() {
	freopen("0_pr_result_10.txt", "r", stdin);
	freopen("error", "w", stdout);

	for (int i = 0; i < V; ++i) {
		cin >> v[i];
	}
	fclose(stdin);
	
	for (int a = 0; a < 7; ++a) {
	
		freopen(fname[a].c_str(), "r", stdin);

		for (int i = 0; i < V; ++i) {
			cin >> t[i];
		}
		fclose(stdin);
		double count = 0;

		for (int i = 0; i < 2; ++i) {
			count = error_bound(0, 10.0*(i+1));
			cout << double(count) / double(10*(i+1)) << endl;
		}
	}
	fclose(stdout);
}
