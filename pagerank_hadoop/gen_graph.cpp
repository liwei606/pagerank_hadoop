#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int dim = 100;
int g[dim][dim];

int random_init() {
	if (rand() % 50 < 30) return 0;
	else return 1;
}

int main() {
	srand(time(NULL));
	freopen("graph.h", "w", stdout);
	cout << "#ifndef _GRAPH_H" << endl;
	cout << "#define _GRAPH_H" << endl;
	cout << "\nint g[" << dim << "][" << dim << "] = {\n";
	for (int i = 0; i < dim; ++i) {
		cout << "\t{ ";
		for (int j = 0; j < dim; ++j) {
			g[i][j] = random_init();
			cout << g[i][j];
			if (j != dim - 1) cout << ", ";
		}
		cout << "},\n";
	}
	cout << "};\n";
	
	cout << "#endif\n";
	fclose(stdout);
	return 0;
}
