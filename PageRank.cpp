#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "test_graph.h"

using namespace std;

/*
 Parameter M adjacency matrix where M_i,j represents the link from 'j' to 'i', such that for all 'j' sum(i, M_i,j) = 1
 Parameter d damping factor
 Parameter v_quadratic_error quadratic error for v
 Return v, a vector of ranks such that v_i is the i-th rank from [0, 1]
*/

int max_iteration = 100;

double sum(double* v, int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += v[i];
	}
	return sum;
}

double max(double*v, int n) {
	double m = 0;
	for (int i = 0; i < n; ++i) {
		if (v[i] > m) m = v[i];
	}
	return m;
}

void norm(double* v, int n) {
	double s = sum(v, n);
	for (int i =0; i < n; ++i) {
		v[i] = v[i] / s;
	}
}

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


void show(double* v, int n) {	
	for (int i = 0; i < n; ++i) {
		cout << i+1 << ":	" << v[i] << endl;
	}
}

void show_int(int* v, int n) {
	for (int i = 0; i < n; ++i) {
		cout << v[i] << endl;
	}
}

double* rank(double M[][V], int n, double d, double v_quadratic_error) {
	double* v = new double[n];
	double* last_v = new double[n];
	// __asm__("lda $9, 7($31) ");
	for (int i = 0; i < n; ++i) {
		v[i] = 1.0 / n;
		last_v[i] = random() + 10000;
	}
	// __asm__("lda $9, 0($31) ");
	
	norm(v, n);
	norm(last_v, n);	
	double* M_hat = new double[n];
	int t = 0;
	do {
		// __asm__("lda $9, 5($31) ");
		for (int i = 0; i < n; ++i) {
			double temp = 0;
			for (int j = 0; j < n; ++j) {
				temp += M[i][j] * last_v[j];
			}
			M_hat[i] = (1 - d) / n + d * temp;
		}
		// __asm__("lda $9, 0($31) ");
		
		for (int i = 0; i < n; ++i) {
			last_v[i] = v[i];
			v[i] = M_hat[i];
		}
		norm(v, n);
		++t;
		//if (max(sub, n) < v_quadratic_error) break;
		
	} while (t < max_iteration);

	return v;
}


void Qsort(double *v, int *a, int left, int right) {
	if (left >= right) return;
	int i = (left + right) / 2;
	double x = v[i];
	swap(v[i], v[right]);
	swap(a[i], a[right]);
	
	int storeindex = left;
	for (int j = left; j < right; ++j) {
		if (v[j] >= x) {
			swap(v[j], v[storeindex]);
			swap(a[j], a[storeindex]);
			++storeindex;
		}
	}
	swap(v[storeindex], v[right]);
	swap(a[storeindex], a[right]);
	Qsort(v, a, left, storeindex - 1);
	Qsort(v, a, storeindex + 1, right);
}



int main() {	

	freopen ("testout.txt","w",stdout);
	srand(time(NULL));
			   
	double s[50][V];
	int a[V];				
	int iter = 50;	   
	for (int t = 0; t < iter; ++t) {		 
		double* r2 = rank(test_graph, V, 0.85, 0.00001);   // INCORRECT is not normalized.

		for (int i = 0; i < V; ++i) {
			s[t][i] = r2[i];
		}
		//cout << "The No." << t << " test:" << endl;
		//cout << "The pagerank\n";
		//show(r2, V);
		//Qsort(r2, a, 0, V-1);
		
		//cout << "The index rank\n";
		//show_int(a, V);
		//cout << "==========================" << endl;
	}
	
	double average[V];
	for (int i = 0; i < V; ++i) {
		average[i] = 0;
		for (int t = 0; t < iter; ++t) {
			average[i] += s[t][i];
		}
		average[i] /= iter;
		a[i] = i+1;	
	}
	//cout << "\nAverage PageRank:\n";
	//show(average, V);
	//cout << "\nAverage Index Rank:\n";
	Qsort(average, a, 0, V -1);
	show_int(a, V);
	fclose(stdout);
}
