all: PageRank

PageRank: src/PageRank.cpp src/test_graph.h
	g++ src/PageRank.cpp -o PageRank
