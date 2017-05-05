#ifndef MSTREE_H
#define MSTREE_H
#include <set>
class weight;

class msTree {
public:
	void initGraph();
	void createGraph();
	void printGraph();
	int find(int&);
	bool unions(int, int);
	msTree();
	~msTree();

private:
	std::set<weight> * w;
	int numV, numE;
	int * u;
};

#endif
