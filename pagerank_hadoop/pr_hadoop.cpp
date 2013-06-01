#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include "graph.h"

using namespace std;

int max_iteration = 2;
const int dim = 100;
const double damp = 0.8;
double pr[dim];

void init_pr() {
	for (int i = 0; i < dim; ++i) {
		pr[i] = 1.0 / double(dim);
	}
}

int linklist[dim][dim];
int linkto[dim];

void init_map() {
	for (int i = 0; i < dim; ++i) {
		linkto[i] = 0;
		for (int j = 0; j < dim; ++j) {
			if (g[i][j]) linklist[i][linkto[i]++] = j;
		}
	}
}

class recv_list {
public:
	class recv_node {
	public:
		int page;
		double pr;
		recv_node(int p = -1, double r = -1): page(p), pr(r) {}
	};
	recv_node *head;
	int num;
	int curr;
	recv_list(int n = dim): num(n) {
		head = new recv_node[num];
		curr = 0;
	}
	void append(int p, double r) {
		head[curr++] = recv_node(p, r);
	}
	void update_pr(double r) {
		head[curr++].pr = r;
	}
	void reset_curr() {
		curr = 0;
	}
	~recv_list() {
		delete [] head;
	}
};

recv_list rl[dim];

int iter = 0;

void mapper() {
	for (int i = 0; i < dim; ++i) {
		rl[i].reset_curr();
	}
	for (int i = 0; i < dim; ++i) {
		int linkto_no = linkto[i];
		for (int j = 0; j < linkto_no; ++j) {
			if (iter == 0) {
				rl[linklist[i][j]].append(i, pr[i] / double(linkto_no));
			}
			else rl[linklist[i][j]].update_pr(pr[i] / double(linkto_no));
		}
	}
}

void reducer() {
	for (int i = 0; i < dim; ++i) {
		pr[i] = (1 - damp) / dim;
		for (int j = 0; j < rl[i].curr; ++j) {
			pr[i] += damp * rl[i].head[j].pr;
		}
	}
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

void check_deadend() {
	for (int i = 0; i < dim; ++i) {
		int sum = 0;
		for (int j = 0; j < dim; ++j) {
			sum += g[i][j];
		}
		if (!sum) fprintf(stderr, "dead end exists");
	}
}

int main() {
	//check_deadend();
	init_map();
	for (max_iteration = 5; max_iteration <= 50; max_iteration+=5) {
	// __asm__
	init_pr();
	for (iter = 0; iter < max_iteration; ++iter) {
		mapper();
		reducer();
	}
	// __asm__
	char filename[100];
	strcpy(filename, "pr_result_");
	char s[10];
	sprintf(s, "%d", max_iteration);
	strcat(filename, s);
	strcat(filename, ".txt");
	freopen(filename, "w", stdout);
	int rank[dim];
	for (int i = 0; i < dim; ++i) {
		rank[i] = i + 1;
	}
	Qsort(pr, rank, 0, dim - 1);
	for (int i = 0; i < dim; ++i) {
		cout << pr[i] << endl;
	}
	for (int i = 0; i < dim; ++i) {
		cout << rank[i] << endl;
	}
	fclose(stdout);
	}
	return 0;
}

