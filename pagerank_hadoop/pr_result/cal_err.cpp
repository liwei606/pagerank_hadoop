#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
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
	int iter;
	freopen("error", "w", stdout);
	for (iter = 2; iter <= 5; ++iter) {
	char s[10];
	sprintf(s, "%d", iter);
	char fname[30];
	strcpy(fname, "_pr_result_");
	strcat(fname, s);
	strcat(fname, ".txt");
	char vol[30];
	strcpy(vol, "0");
	strcat(vol, fname);
	freopen(vol, "r", stdin);

	for (int i = 0; i < V; ++i) {
		cin >> v[i];
	}
	fclose(stdin);
	cout << "========== Iteration: "  << iter << "=============="<< endl;
		
	for (int i = 0; i < 2; ++i) {
		cout << "error bound is : "<< (i + 1) * 10 << endl;
	for (char a = '1'; a <= '7'; ++a) {
		
		sprintf(vol, "%c", a);
		strcat(vol, fname);
		freopen(vol, "r", stdin);

		for (int j = 0; j < V; ++j) {
			cin >> t[j];
		}
		fclose(stdin);
		double count = 0;
		count = error_bound(0, 10.0*(i+1));
		cout << a << " " << double(count) / double(10*(i+1)) << endl;
	}
	}
	}
	fclose(stdout);
}
