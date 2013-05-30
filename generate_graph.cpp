#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;

const int V = 100;

double test_graph[V][V];

void norm_col(double M[][V], int n) {
	for (int c = 0; c < n; ++c) {
		double col_sum = 0;
		for (int r = 0; r < n; ++r) {
			M[r][c] = random() % V;
			col_sum += M[r][c];
		}
		for (int r = 0; r < n; ++r) {
			M[r][c] /= col_sum;
		}
	}
}

int main() {
	srand(time(NULL));
	norm_col(test_graph, V);
	freopen("test_graph", "w", stdout);
	cout << "{";
	for (int i = 0; i < V; ++i) {
		cout << "{ ";
		for (int j = 0; j < V; ++j) {
			cout << test_graph[i][j] << ", ";
		}
		cout << "},\n";
	}
	fclose(stdout);
}
