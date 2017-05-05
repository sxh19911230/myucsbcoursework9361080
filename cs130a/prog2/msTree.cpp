#include <iostream>
#include "msTree.h"
#include <set>
#include <unistd.h>
using namespace std;


class weight {
public:
	int u;
	int v;
	int w;
	bool operator<(const weight& o) const {
		if (w < o.w) return true;
		if (w == o.w && u < o.u) return true;
		if (w == o.w && u == o.u && v <= o.v) return true;
		return false;
	}
};

msTree::msTree() {
	initGraph();
}

msTree::~msTree() {
	delete w;
	delete [] u;
}

void msTree::initGraph() {
	cin >> numV >> numE;
	//assign
	w = new set<weight>();
	weight t1;
	for (int i = 0; i < numE; i++) {
                cin >> t1.u >> t1.v >> t1.w;
		w->insert(t1);
	}

	u = new int[numV];
	for (int i = 0; i < numV; i++)
		u[i] = -1;
/*
	for (set<weight>::iterator it = w->begin(); it != w->end(); ++it)
                cout << it->u << it->v << endl;
*/	
}


int msTree::find(int& i) {
	if (u[i] < 0) return i;
	i = find(u[i]);
	return i;	
}

bool msTree::unions(int n1, int n2) {
	n1 = find(--n1);
	n2 = find(--n2);
	if (n1 == n2) return false;
	if (u[n1] < u[n2]) {
		u[n1] += u[n2];
		u[n2] = n1;
	} else {
		u[n2] += u[n1];
		u[n1] = n2;
	}
	return true;
}
void msTree::createGraph() {
	set<weight>::iterator it = w->begin();
	set<weight>::iterator lastIt;
	while (it != w->end()) {
		if (!unions(it->u,it->v)) {
			cout << "Edge (" << it->u << ',' << it->v << ") creates cycle" << endl;
			w->erase(it);
			it = lastIt;
		}
		else 
			cout << "Edge (" << it->u << ',' << it->v << ") successfully inserted" << endl;
		lastIt = it++;
	}

}

void msTree::printGraph() {
	int t = 0, j;
	t = find(t);
	for (int i = 1; i < numV; ++i) {
		j = i;
		if (find(j) != t) {
		cout << "ERROR: MST not found." << endl;
		return;
		}
	}
	int totalWeight = 0;
        for (set<weight>::iterator it = w->begin(); it != w->end(); ++it) {
		cout << it->u << ' ' << it->v << endl;
		totalWeight += it->w;
        }
	cout << totalWeight << endl;
	
}


