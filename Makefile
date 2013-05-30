all: PageRank

PageRank: PageRank.cpp test_graph.h
	g++ PageRank.cpp -o PageRank
