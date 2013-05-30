#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "graph.h"

using namespace std;

int max_iteration = 2;
const int dim = 100;
const double damp = 0.8;
extern int g[dim][dim];
double pr[dim];

void init_pr() {
	for (int i = 0; i < dim; ++i) {
		pr[dim] = 1.0 / double(dim);
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
		recv_node *next;
		recv_node(int p, double r, recv_node *n = NULL): page(p), pr(r), next(n) {}
	};
	recv_node *head;
	recv_list() {
		head = new recv_node(-1, -1, NULL);
	}
	void append(int p, double r) {
		recv_node *n = new recv_node(p, r);
		n->next = head->next;
		head->next = n;
	}
	~recv_list() {
		recv_node *temp;
		for (recv_node *p = head; p->next; p = p->next) {
			temp = p->next;
			p->next = temp->next;
			delete temp;
		}
		delete head;
	}
};

recv_list rl[dim];

void mapper() {
	for (int i = 0; i < dim; ++i) {
		int linkto_no = linkto[i];
		for (int j = 0; j < linkto_no; ++j) {
			rl[linklist[i][j]].append(i, pr[i] / double(linkto_no));
		}
	}
}

void reducer() {
	for (int i = 0; i < dim; ++i) {
		pr[i] = (1 - damp) / dim;
		for (recv_list::recv_node *p = rl[i].head; p->next; p = p->next) {
			pr[i] += damp * p->next->pr;
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
		if (!sum) fprintf(stderr, "dead end");
	}
}

int main() {
	check_deadend();
	init_pr();
	init_map();
	for (int i = 0; i < max_iteration; ++i) {
		mapper();
		reducer();
	}
	freopen("pr_result.txt", "w", stdout);
	int rank[dim];
	for (int i = 0; i < dim; ++i) {
		rank[i] = i + 1;
	}
	Qsort(pr, rank, 0, dim - 1);
	for (int i = 0; i < dim; ++i) {
		cout << pr[i] << endl;
		//cout << rank[i] << endl;
	}
	fclose(stdout);
	return 0;
}

